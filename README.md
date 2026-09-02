# dadder.sys, Razer: kernel stack buffer overflow reachable by any local user

Discovered through https://github.com/416rehman/DeepZero

**Vendor:** Razer Inc.
**Component:** `dadder.sys`, a Razer mouse filter driver, x64
**Class:** CWE-121 stack-based buffer overflow. CWE-782 exposed IOCTL with insufficient access control.
**Reporter reference:** `2e540b2d6b75e23d`
**Status:** not reported to the vendor. Not in LOLDrivers, not on the Microsoft vulnerable driver blocklist.

| Field | Value |
|---|---|
| Attack vector | Local |
| Privileges required | **Low.** Any account able to log in and run code. Membership of the built-in `Users` group is sufficient. No administrative rights, no elevation, no special privilege. |
| User interaction | None |
| Scope | Kernel address space |
| Confidentiality / Integrity / Availability | High / High / High |
| Outcome demonstrated | An unprivileged process set the kernel instruction pointer to a chosen value in ring 0 |

Six IOCTL handlers copy the caller's input buffer into a fixed stack buffer using
the caller's own `InputBufferLength` as the copy size. Only the pointer is
validated; the length never is. `0x440` bytes of input replace the routine's
return address at input offset `0x438`.

---

## 1. Affected file

| | |
|---|---|
| File name | `dadder.sys` |
| Size | 12,672 bytes |
| SHA-256 | `2e540b2d6b75e23dc776df3e7a65cc9461131ec053a77862da2bc4306e5c05cb` |
| MD5 | `5bc67f1efb6b1d039b151cf7353ec742` |
| Machine | `0x8664` (AMD64) |
| Image base | `0x10000` |
| Link timestamp | `0x46B1A4CF` = 2007-08-02 09:33:03 UTC |
| Package | `dadder.inf` with `dadder64.cat`, catalog-signed by the vendor |
| Obtained from | driver pack `DP_Misc_26053`, `Razer\FORCED\Allx64\Others\` |

Every section's raw pointer equals its virtual address, so file offset and RVA
are the same number throughout this binary. The affected binary and its
decompiled dispatch routine are in [`evidence/`](evidence/).

## 2. How the device is reached

`DriverEntry` creates the device and **never creates a symbolic link**:

```c
RtlInitUnicodeString(&DAT_00011d90, L"\\Device\\dadder");
IoCreateDevice(param_1, 0x20, &DAT_00011d90, 0x22, 0, 0, local_28);
```

`IoCreateDevice` is called with `DeviceType 0x22` (`FILE_DEVICE_UNKNOWN`),
`Exclusive FALSE`, and **no security descriptor**. There is no
`IoCreateSymbolicLink` anywhere, so `\\.\dadder` does not resolve. This is not a
mitigation: a named device object with no symbolic link remains reachable through
the object namespace at

```
\\?\GLOBALROOT\Device\dadder
```

which was confirmed to open from a standard user account (section 5).
`IRP_MJ_DEVICE_CONTROL` is at **RVA 0x790** (`MajorFunction[14]`, written to
`DRIVER_OBJECT + 0xE0` in `DriverEntry`).

## 3. The defect

### 3.1 The frame

`IRP_MJ_DEVICE_CONTROL` is RVA `0x790`. Its prologue, from the shipped binary:

```
dadder+0x790  53                    push  rbx
dadder+0x791  56                    push  rsi
dadder+0x792  57                    push  rdi
dadder+0x793  41 54                 push  r12
dadder+0x795  41 55                 push  r13
dadder+0x797  41 56                 push  r14
dadder+0x799  48 81 ec 38 04 00 00  sub   rsp, 438h
```

Six non-volatile registers are saved, followed by a `0x438`-byte frame. The copy
destination is `lea rcx,[rsp+48h]`.

### 3.2 The copy

Taking IOCTL `0x002224A0`:

```c
puVar9 = *(undefined2 **)(param_2 + 0x18);   /* Irp->AssociatedIrp.SystemBuffer  */
uVar10 = *(undefined4 *)(lVar4 + 0x10);      /* Parameters.DeviceIoControl
                                                .InputBufferLength              */
if (puVar9 != (undefined2 *)0x0) {
    RtlCopyMemory(&uStack_438, puVar9, uVar10);
```

Only the pointer is checked. The copy runs before the driver's later checks, so
no Razer hardware needs to be present.

### 3.3 What the overflow reaches, measured on the machine

Rather than derive the return-address offset by hand from the frame, it was
measured. A run filled the input so that the qword at byte offset N held
`0x00007FFF00000000 | N`, then read the offset back out of the crash dump. The
faulting address was `0x00007FFF00000438`, so:

| Input offset | Lands on |
|---|---|
| `0x000` to `0x3FF` | the buffer, intended |
| `0x408` to `0x430` | the six saved registers |
| **`0x438`** | **the return address** |

and every stack slot above `0x438` was filled with the caller's offset-encoded
bytes, one after another (`0x440`, `0x448`, `0x450`, ...), which shows the whole
region above the buffer is attacker controlled with known provenance, not merely
corrupted. The measurement transcript is in
[`logs/profile_measurement.txt`](logs/profile_measurement.txt) and its dump is
[`evidence/dumps/072526-10562-01.dmp`](evidence/dumps/072526-10562-01.dmp).

### 3.4 Affected control codes

Six control codes reach a handler containing this copy: `0x00222498`,
`0x002224A0`, `0x002224A8`, `0x002224B8`, `0x00222520`, `0x00222528`. All are
`FILE_DEVICE_UNKNOWN`, `METHOD_BUFFERED`, `FILE_ANY_ACCESS`, so no access right
needs to be held on the handle.

## 4. Impact

**Local privilege escalation.** A process running as a standard user, with no
Razer hardware present, can write past the end of a kernel stack buffer for any
length it chooses and replace the return address of a routine running in kernel
mode. Confirmed in section 5: an unprivileged process caused the kernel to
attempt execution at an address it supplied, in ring 0.

**What an attacker still needs, stated precisely.** Turning this control into
code execution requires knowing where the kernel is loaded, and this driver does
not disclose it. As with the other drivers in this family, an unprivileged
account cannot obtain the kernel base from Windows itself: `EnumDeviceDrivers`
returns real module addresses to an elevated caller and zeroes to a standard user
at medium integrity, confirmed on the test machine. An attacker therefore needs a
separate information disclosure to pair with this defect. That does not reduce its
severity: such disclosures are common in other drivers, which is enough to complete a chain. This
report does not assume one.

Establishing controlled kernel execution is sufficient to assess and fix the
defect; no privilege-granting payload was built.

For completeness about what this is not: it is not remotely reachable and not
exploitable without prior local code execution. The realistic attacker is one
already running unprivileged code on the machine.

Because the package is validly catalog-signed, the driver loads on a machine that
never had Razer hardware attached, the pattern used in
bring-your-own-vulnerable-driver attacks.

## 5. Reproducing and observed result

Windows 11 Pro 25H2 (build 26200.8875), x64, **code integrity enforced and test signing
off**, both confirmed with `bcdedit`. Installed from its own catalog-signed
package:

```
pnputil /add-driver dadder.inf /install    ->  Published Name: oem15.inf
sc create dzdadder type= kernel binPath= ...\dadder.sys start= demand
sc start dzdadder                           ->  STATE: RUNNING
```

Build `rustc -O poc/dadder_overflow.rs` and run from a standard user account
(`dzuser`, group `Users` only):

```bash
dadder_overflow.exe --baseline   # 0x400 bytes; below the saved registers; no crash
dadder_overflow.exe --ret        # 0x440 bytes; replaces the return address
dadder_overflow.exe --profile    # offset-encoded, used to measure the 0x438 offset
```

Baseline, as `dzuser`:

```
opened \\?\GLOBALROOT\Device\dadder as dzuser
ioctl 0x00222498, 0x400 bytes: accepted=true error=0
```

The `--ret` run stops the machine. From
[`evidence/dumps/072526-10906-01.dmp`](evidence/dumps/072526-10906-01.dmp):

```
KMODE_EXCEPTION_NOT_HANDLED (1e)
Arg2: 00007fff0000dead   the address the exception occurred at
    Key : AV.Type  Value: Execute
EXECUTE_ADDRESS: 7fff0000dead
PROCESS_NAME:  dadder_overflo
IMAGE_VERSION: 10.0.26100.8875
```

`AV.Type: Execute` with exception parameter 0 of `8` means the fault was taken on
an instruction fetch, the address is exactly the value placed at input offset
`0x438`, and it occurred in kernel mode.

## 6. Suggested remediation

1. Reject any request whose `InputBufferLength` exceeds the destination in all six
   handlers:

   ```c
   if (stack->Parameters.DeviceIoControl.InputBufferLength > sizeof(buffer)) {
       status = STATUS_INVALID_BUFFER_SIZE;
       break;
   }
   ```

2. Create the control device with `IoCreateDeviceSecure` and an SDDL string
   restricting access to administrators and the system. The absence of a symbolic
   link does not prevent ordinary users from opening it through the object
   namespace.

## 7. Disclosure and prior art

**Vendor:** Razer Inc. Razer operates a coordinated vulnerability disclosure
process.

**Prior art:** LOLDrivers (660 entries) searched by SHA-256, MD5 and name, no
entry. Microsoft vulnerable driver blocklist (1,713 deny rules) searched by hash
and name, no entry; the only Razer driver on it is `Rzpnk.sys`, a different file.
No CVE found. Believed previously unreported.

This driver shares the general shape of other Razer filter drivers in the same
packs (`copperhd.sys`, `boomslang.sys`), but its frame is its own: six saved
registers and a `0x438` frame, giving a return address at input offset `0x438`,
measured independently rather than assumed.

## 8. Contents of this directory

```
README.md                              this report
poc/dadder_overflow.rs                 proof of concept, no dependencies
evidence/dadder.sys                    the affected binary
evidence/decompiled/                   decompiled DriverEntry and dispatch routine
evidence/dumps/072526-10562-01.dmp     the offset-encoded measurement (section 3.3)
evidence/dumps/072526-10906-01.dmp     the return-address overwrite (section 5)
logs/profile_measurement.txt           how the 0x438 offset was measured
```

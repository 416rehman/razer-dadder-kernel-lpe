
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined4 FUN_00010790(longlong param_1,ulonglong param_2,ulonglong param_3)

{
  int *piVar1;
  int iVar2;
  uint uVar3;
  longlong lVar4;
  undefined4 *puVar5;
  byte bVar6;
  undefined4 uVar7;
  undefined2 *puVar8;
  undefined2 *puVar9;
  undefined4 uVar10;
  longlong lVar11;
  ulonglong uVar12;
  undefined8 uVar13;
  ulonglong uVar14;
  undefined2 uStack_438;
  undefined uStack_436;
  
  uVar12 = 0;
  uVar14 = 0;
  if (param_1 != DAT_00011da0) {
    lVar4 = *(longlong *)(param_1 + 0x40);
    LOCK();
    *(int *)(lVar4 + 0x68) = *(int *)(lVar4 + 0x68) + 1;
    UNLOCK();
    if (*(char *)(lVar4 + 5) == '\0') {
      *(char *)(param_2 + 0x43) = *(char *)(param_2 + 0x43) + '\x01';
      *(longlong *)(param_2 + 0xb8) = *(longlong *)(param_2 + 0xb8) + 0x48;
      uVar7 = IofCallDriver(*(undefined8 *)(lVar4 + 0x18),param_2);
    }
    else {
      uVar7 = 0xc0000056;
      *(undefined8 *)(param_2 + 0x38) = 0;
      *(undefined4 *)(param_2 + 0x30) = 0xc0000056;
      IofCompleteRequest(param_2,param_2 & 0xffffffffffffff00);
    }
    LOCK();
    piVar1 = (int *)(lVar4 + 0x68);
    iVar2 = *piVar1;
    *piVar1 = *piVar1 + -1;
    UNLOCK();
    if (iVar2 == 1) {
      KeSetEvent(lVar4 + 0x50,0,param_3 & 0xffffffffffffff00);
    }
    return uVar7;
  }
  lVar4 = *(longlong *)(param_2 + 0xb8);
  uVar3 = *(uint *)(lVar4 + 0x18);
  puVar9 = (undefined2 *)0x22249c;
  uVar7 = 0;
  if (0x22249c < uVar3) {
    puVar9 = (undefined2 *)0x10c39;
    switch(uVar3) {
    case 0x2224a0:
      puVar9 = *(undefined2 **)(param_2 + 0x18);
      uVar10 = *(undefined4 *)(lVar4 + 0x10);
      if (puVar9 != (undefined2 *)0x0) {
        RtlCopyMemory(&uStack_438,puVar9,uVar10);
        if (DAT_00011c60 != 0) {
          uVar12 = 0x206d6457;
          puVar9 = (undefined2 *)0x0;
          puVar8 = (undefined2 *)ExAllocatePoolWithTag(0,0x88);
          if (puVar8 != (undefined2 *)0x0) {
            puVar8[1] = 0x1b;
            *puVar8 = 0x88;
            *(undefined4 *)(puVar8 + 0x12) = uVar10;
            *(undefined8 *)(puVar8 + 0x18) = 0;
            *(undefined2 **)(puVar8 + 0x14) = &uStack_438;
            *(undefined *)(puVar8 + 0x40) = 0;
            *(undefined *)((longlong)puVar8 + 0x81) = 9;
            puVar8[0x41] = 7;
            puVar8[0x42] = 0;
            *(undefined4 *)(puVar8 + 0x10) = 0;
            *(undefined8 *)(puVar8 + 0x1c) = 0;
            puVar9 = puVar8;
            FUN_00010690(DAT_00011c88,puVar8,uVar12);
            ExFreePool(puVar8);
          }
        }
        goto LAB_000112f0;
      }
      break;
    default:
switchD_00010874_caseD_222401:
      uVar14 = uVar12;
      uVar7 = 0xc00000bb;
      goto LAB_000112f0;
    case 0x2224a8:
      puVar9 = *(undefined2 **)(param_2 + 0x18);
      uVar10 = *(undefined4 *)(lVar4 + 0x10);
      if (puVar9 != (undefined2 *)0x0) {
        RtlCopyMemory(&uStack_438,puVar9,uVar10);
        if (DAT_00011c60 != 0) {
          uVar12 = 0x206d6457;
          puVar9 = (undefined2 *)0x0;
          puVar8 = (undefined2 *)ExAllocatePoolWithTag(0,0x88);
          if (puVar8 != (undefined2 *)0x0) {
            puVar8[1] = 0x1b;
            *puVar8 = 0x88;
            *(undefined4 *)(puVar8 + 0x12) = uVar10;
            *(undefined8 *)(puVar8 + 0x18) = 0;
            *(undefined2 **)(puVar8 + 0x14) = &uStack_438;
            *(undefined *)(puVar8 + 0x40) = 0;
            *(undefined *)((longlong)puVar8 + 0x81) = 9;
            puVar8[0x41] = 3;
            puVar8[0x42] = 0;
            *(undefined4 *)(puVar8 + 0x10) = 0;
            *(undefined8 *)(puVar8 + 0x1c) = 0;
            puVar9 = puVar8;
            FUN_00010690(DAT_00011c88,puVar8,uVar12);
            ExFreePool(puVar8);
          }
        }
        goto LAB_000112f0;
      }
      break;
    case 0x2224ac:
      lVar11 = *(longlong *)(param_2 + 0x18);
      if ((lVar11 != 0) && (*(int *)(lVar4 + 8) != 0)) {
        if (DAT_00011c60 == 0) goto LAB_000112f0;
        uVar14 = 0x206d6457;
        puVar9 = (undefined2 *)ExAllocatePoolWithTag(0,0x88);
        if (puVar9 != (undefined2 *)0x0) {
          puVar9[0x41] = 3;
LAB_000111d1:
          puVar9[1] = 0x1b;
          *puVar9 = 0x88;
          *(undefined4 *)(puVar9 + 0x12) = 1;
          *(undefined8 *)(puVar9 + 0x18) = 0;
          *(undefined2 **)(puVar9 + 0x14) = &uStack_438;
          *(undefined *)(puVar9 + 0x40) = 0;
          *(undefined *)((longlong)puVar9 + 0x81) = 1;
          puVar9[0x42] = 0;
          *(undefined4 *)(puVar9 + 0x10) = 1;
          *(undefined8 *)(puVar9 + 0x1c) = 0;
          FUN_00010690(DAT_00011c88,puVar9,uVar14);
          ExFreePool(puVar9);
        }
LAB_00011226:
        uVar13 = 4;
        uVar14 = 4;
        goto LAB_0001122f;
      }
      break;
    case 0x2224b4:
      uStack_438._0_1_ = 0;
      if (DAT_00011c60 != 0) {
        uVar12 = 0x206d6457;
        puVar9 = (undefined2 *)0x0;
        puVar8 = (undefined2 *)ExAllocatePoolWithTag(0,0x88);
        if (puVar8 != (undefined2 *)0x0) {
          puVar8[1] = 0x1b;
          *puVar8 = 0x88;
          *(undefined4 *)(puVar8 + 0x12) = 1;
          *(undefined8 *)(puVar8 + 0x18) = 0;
          *(undefined2 **)(puVar8 + 0x14) = &uStack_438;
          *(undefined *)(puVar8 + 0x40) = 0;
          *(undefined *)((longlong)puVar8 + 0x81) = 9;
          puVar8[0x41] = 4;
          puVar8[0x42] = 0;
          *(undefined4 *)(puVar8 + 0x10) = 0;
          *(undefined8 *)(puVar8 + 0x1c) = 0;
          puVar9 = puVar8;
          FUN_00010690(DAT_00011c88,puVar8,uVar12);
          ExFreePool(puVar8);
        }
      }
      goto LAB_000112f0;
    case 0x2224b8:
      puVar9 = *(undefined2 **)(param_2 + 0x18);
      uVar10 = *(undefined4 *)(lVar4 + 0x10);
      if (puVar9 != (undefined2 *)0x0) {
        RtlCopyMemory(&uStack_438,puVar9,uVar10);
        if (DAT_00011c60 != 0) {
          uVar12 = 0x206d6457;
          puVar9 = (undefined2 *)0x0;
          puVar8 = (undefined2 *)ExAllocatePoolWithTag(0,0x88);
          if (puVar8 != (undefined2 *)0x0) {
            puVar8[1] = 0x1b;
            *puVar8 = 0x88;
            *(undefined4 *)(puVar8 + 0x12) = uVar10;
            *(undefined8 *)(puVar8 + 0x18) = 0;
            *(undefined2 **)(puVar8 + 0x14) = &uStack_438;
            *(undefined *)(puVar8 + 0x40) = 0;
            *(undefined *)((longlong)puVar8 + 0x81) = 9;
            puVar8[0x41] = 5;
            puVar8[0x42] = 0;
            *(undefined4 *)(puVar8 + 0x10) = 0;
            *(undefined8 *)(puVar8 + 0x1c) = 0;
            puVar9 = puVar8;
            FUN_00010690(DAT_00011c88,puVar8,uVar12);
            ExFreePool(puVar8);
          }
        }
        goto LAB_000112f0;
      }
      break;
    case 0x222508:
      if (*(undefined4 **)(param_2 + 0x18) != (undefined4 *)0x0) {
        _DAT_00011d74 = **(undefined4 **)(param_2 + 0x18);
        goto LAB_000112f0;
      }
      break;
    case 0x222510:
      lVar11 = *(longlong *)(param_2 + 0x18);
      if ((lVar11 != 0) && (*(int *)(lVar4 + 8) != 0)) {
        uVar14 = uVar12;
        if (DAT_00011c60 != 0) {
          uVar14 = 0x206d6457;
          puVar9 = (undefined2 *)ExAllocatePoolWithTag(0,0x88);
          uStack_438._0_1_ = 0;
          uStack_438._1_1_ = 0;
          if (puVar9 != (undefined2 *)0x0) {
            puVar9[1] = 0x1b;
            *puVar9 = 0x88;
            *(undefined4 *)(puVar9 + 0x12) = 2;
            *(undefined8 *)(puVar9 + 0x18) = 0;
            *(undefined2 **)(puVar9 + 0x14) = &uStack_438;
            *(undefined *)(puVar9 + 0x40) = 0;
            *(undefined *)((longlong)puVar9 + 0x81) = 1;
            puVar9[0x41] = 5;
            puVar9[0x42] = 0;
            *(undefined4 *)(puVar9 + 0x10) = 1;
            *(undefined8 *)(puVar9 + 0x1c) = 0;
            FUN_00010690(DAT_00011c88,puVar9,uVar14);
            ExFreePool(puVar9);
          }
          puVar9 = &uStack_438;
          RtlCopyMemory(lVar11,puVar9,2);
          uVar14 = 4;
        }
        goto LAB_000112f0;
      }
      break;
    case 0x222514:
      lVar11 = *(longlong *)(param_2 + 0x18);
      if ((lVar11 != 0) && (*(int *)(lVar4 + 8) != 0)) {
        uVar14 = uVar12;
        if (DAT_00011c60 != 0) {
          uVar14 = 0x206d6457;
          puVar9 = (undefined2 *)ExAllocatePoolWithTag(0,0x88);
          uStack_438._0_1_ = 0;
          uStack_438._1_1_ = 0;
          uStack_436 = 0;
          if (puVar9 != (undefined2 *)0x0) {
            puVar9[1] = 0x1b;
            *puVar9 = 0x88;
            *(undefined4 *)(puVar9 + 0x12) = 3;
            *(undefined8 *)(puVar9 + 0x18) = 0;
            *(undefined2 **)(puVar9 + 0x14) = &uStack_438;
            *(undefined *)(puVar9 + 0x40) = 0;
            *(undefined *)((longlong)puVar9 + 0x81) = 1;
            puVar9[0x41] = 5;
            puVar9[0x42] = 0;
            *(undefined4 *)(puVar9 + 0x10) = 1;
            *(undefined8 *)(puVar9 + 0x1c) = 0;
            FUN_00010690(DAT_00011c88,puVar9,uVar14);
            ExFreePool(puVar9);
          }
          puVar9 = &uStack_438;
          RtlCopyMemory(lVar11,puVar9,2);
          uVar14 = 4;
        }
        goto LAB_000112f0;
      }
      break;
    case 0x222520:
      puVar9 = *(undefined2 **)(param_2 + 0x18);
      uVar10 = *(undefined4 *)(lVar4 + 0x10);
      if (puVar9 != (undefined2 *)0x0) {
        RtlCopyMemory(&uStack_438,puVar9,uVar10);
        if (DAT_00011c60 != 0) {
          uVar12 = 0x206d6457;
          puVar9 = (undefined2 *)0x0;
          puVar8 = (undefined2 *)ExAllocatePoolWithTag(0,0x88);
          if (puVar8 != (undefined2 *)0x0) {
            puVar8[1] = 0x1b;
            *puVar8 = 0x88;
            *(undefined4 *)(puVar8 + 0x12) = uVar10;
            *(undefined8 *)(puVar8 + 0x18) = 0;
            *(undefined2 **)(puVar8 + 0x14) = &uStack_438;
            *(undefined *)(puVar8 + 0x40) = 0;
            *(undefined *)((longlong)puVar8 + 0x81) = 9;
            puVar8[0x41] = 6;
            puVar8[0x42] = 0;
            *(undefined4 *)(puVar8 + 0x10) = 0;
            *(undefined8 *)(puVar8 + 0x1c) = 0;
            puVar9 = puVar8;
            FUN_00010690(DAT_00011c88,puVar8,uVar12);
            ExFreePool(puVar8);
          }
        }
        goto LAB_000112f0;
      }
      break;
    case 0x222524:
      lVar11 = *(longlong *)(param_2 + 0x18);
      if ((lVar11 != 0) && (*(int *)(lVar4 + 8) != 0)) {
        if (DAT_00011c60 == 0) goto LAB_000112f0;
        uVar14 = 0x206d6457;
        puVar9 = (undefined2 *)ExAllocatePoolWithTag(0,0x88);
        if (puVar9 != (undefined2 *)0x0) {
          puVar9[0x41] = 6;
          goto LAB_000111d1;
        }
        goto LAB_00011226;
      }
      break;
    case 0x222528:
      puVar9 = *(undefined2 **)(param_2 + 0x18);
      uVar10 = *(undefined4 *)(lVar4 + 0x10);
      if (puVar9 != (undefined2 *)0x0) {
        RtlCopyMemory(&uStack_438,puVar9,uVar10);
        if (DAT_00011c60 != 0) {
          uVar12 = 0x206d6457;
          puVar9 = (undefined2 *)0x0;
          puVar8 = (undefined2 *)ExAllocatePoolWithTag(0,0x88);
          if (puVar8 != (undefined2 *)0x0) {
            puVar8[1] = 0x1b;
            *puVar8 = 0x88;
            *(undefined4 *)(puVar8 + 0x12) = uVar10;
            *(undefined8 *)(puVar8 + 0x18) = 0;
            *(undefined2 **)(puVar8 + 0x14) = &uStack_438;
            *(undefined *)(puVar8 + 0x40) = 0;
            *(undefined *)((longlong)puVar8 + 0x81) = 9;
            puVar8[0x41] = 0x10;
            puVar8[0x42] = 0;
            *(undefined4 *)(puVar8 + 0x10) = 0;
            *(undefined8 *)(puVar8 + 0x1c) = 0;
            puVar9 = puVar8;
            FUN_00010690(DAT_00011c88,puVar8,uVar12);
            ExFreePool(puVar8);
          }
        }
        goto LAB_000112f0;
      }
    }
    goto LAB_00011251;
  }
  if (uVar3 == 0x22249c) {
    lVar11 = *(longlong *)(param_2 + 0x18);
    if ((lVar11 != 0) && (*(int *)(lVar4 + 8) != 0)) {
      uVar14 = uVar12;
      if (DAT_00011c60 == 0) goto LAB_000112f0;
      puVar9 = (undefined2 *)ExAllocatePoolWithTag(0,0x88,0x206d6457);
      if (puVar9 != (undefined2 *)0x0) {
        puVar9[1] = 0x1b;
        *puVar9 = 0x88;
        *(undefined4 *)(puVar9 + 0x12) = 4;
        *(undefined8 *)(puVar9 + 0x18) = 0;
        *(undefined2 **)(puVar9 + 0x14) = &uStack_438;
        *(undefined *)(puVar9 + 0x40) = 0;
        *(undefined *)((longlong)puVar9 + 0x81) = 1;
        puVar9[0x41] = 1;
        puVar9[0x42] = 1;
        *(undefined4 *)(puVar9 + 0x10) = 1;
        *(undefined8 *)(puVar9 + 0x1c) = 0;
        FUN_00010690(DAT_00011c88,puVar9,4);
        ExFreePool(puVar9);
      }
      uVar14 = 5;
      uVar13 = 5;
LAB_0001122f:
      puVar9 = &uStack_438;
      RtlCopyMemory(lVar11,puVar9,uVar13);
      goto LAB_000112f0;
    }
    goto LAB_00011251;
  }
  puVar9 = (undefined2 *)0x10876;
  uVar10 = 0;
  switch(uVar3) {
  case 0x222400:
    if (*(undefined8 **)(param_2 + 0x18) != (undefined8 *)0x0) {
      puVar9 = (undefined2 *)0x100000;
      ObReferenceObjectByHandle(**(undefined8 **)(param_2 + 0x18),0x100000,0,0,&DAT_00011da8,0);
      DAT_00011c73 = 1;
      DAT_00011c80 = 0;
      DAT_00011d68 = 0;
      uVar7 = 0;
      goto LAB_000112f0;
    }
    break;
  default:
    goto switchD_00010874_caseD_222401;
  case 0x222404:
    if (DAT_00011da8 != 0) {
      ObfDereferenceObject();
      DAT_00011da8 = 0;
    }
    DAT_00011c73 = 0;
    uVar7 = uVar10;
    goto LAB_000112f0;
  case 0x222408:
    puVar5 = *(undefined4 **)(param_2 + 0x18);
    if ((puVar5 != (undefined4 *)0x0) && (*(int *)(lVar4 + 8) != 0)) {
      bVar6 = KeAcquireSpinLockRaiseToDpc(&DAT_00011db0);
      uVar14 = (ulonglong)(DAT_00011d68 + 1U);
      if (0x31 < DAT_00011d68 + 1U) {
        uVar14 = uVar12;
      }
      DAT_00011d68 = (int)uVar14;
      *puVar5 = *(undefined4 *)(&DAT_00011ca0 + uVar14 * 4);
      puVar9 = (undefined2 *)(ulonglong)bVar6;
      KeReleaseSpinLock(&DAT_00011db0,puVar9);
      uVar14 = 4;
      uVar7 = uVar10;
      goto LAB_000112f0;
    }
    break;
  case 0x222420:
    if (*(undefined4 **)(param_2 + 0x18) != (undefined4 *)0x0) {
      _DAT_00011d70 = **(undefined4 **)(param_2 + 0x18);
      uVar7 = uVar10;
      goto LAB_000112f0;
    }
    break;
  case 0x222424:
    if (*(undefined4 **)(param_2 + 0x18) != (undefined4 *)0x0) {
      DAT_00011c44 = **(undefined4 **)(param_2 + 0x18);
      uVar7 = uVar10;
      goto LAB_000112f0;
    }
    break;
  case 0x222440:
    if (*(undefined4 **)(param_2 + 0x18) != (undefined4 *)0x0) {
      DAT_00011c48 = **(undefined4 **)(param_2 + 0x18);
      uVar7 = uVar10;
      goto LAB_000112f0;
    }
    break;
  case 0x222444:
    if (*(undefined **)(param_2 + 0x18) != (undefined *)0x0) {
      DAT_00011c41 = **(undefined **)(param_2 + 0x18);
      uVar7 = uVar10;
      goto LAB_000112f0;
    }
    break;
  case 0x222448:
    if (*(undefined **)(param_2 + 0x18) != (undefined *)0x0) {
      DAT_00011c75 = **(undefined **)(param_2 + 0x18);
      uVar7 = uVar10;
      goto LAB_000112f0;
    }
    break;
  case 0x222454:
    if (*(undefined **)(param_2 + 0x18) != (undefined *)0x0) {
      DAT_00011c76 = **(undefined **)(param_2 + 0x18);
      uVar7 = uVar10;
      goto LAB_000112f0;
    }
    break;
  case 0x222490:
    uStack_438._0_1_ = 0;
    if (DAT_00011c60 != 0) {
      uVar12 = 0x206d6457;
      puVar9 = (undefined2 *)0x0;
      puVar8 = (undefined2 *)ExAllocatePoolWithTag(0,0x88);
      if (puVar8 != (undefined2 *)0x0) {
        puVar8[1] = 0x1b;
        *puVar8 = 0x88;
        *(undefined4 *)(puVar8 + 0x12) = 1;
        *(undefined8 *)(puVar8 + 0x18) = 0;
        *(undefined2 **)(puVar8 + 0x14) = &uStack_438;
        *(undefined *)(puVar8 + 0x40) = 0;
        *(undefined *)((longlong)puVar8 + 0x81) = 9;
        puVar8[0x41] = 8;
        puVar8[0x42] = 0;
        *(undefined4 *)(puVar8 + 0x10) = 0;
        *(undefined8 *)(puVar8 + 0x1c) = 0;
        puVar9 = puVar8;
        FUN_00010690(DAT_00011c88,puVar8,uVar12);
        ExFreePool(puVar8);
      }
    }
    goto LAB_000112f0;
  case 0x222498:
    puVar9 = *(undefined2 **)(param_2 + 0x18);
    uVar10 = *(undefined4 *)(lVar4 + 0x10);
    if (puVar9 != (undefined2 *)0x0) {
      RtlCopyMemory(&uStack_438,puVar9,uVar10);
      if (DAT_00011c60 != 0) {
        uVar12 = 0x206d6457;
        puVar9 = (undefined2 *)0x0;
        puVar8 = (undefined2 *)ExAllocatePoolWithTag(0,0x88);
        if (puVar8 != (undefined2 *)0x0) {
          puVar8[1] = 0x1b;
          *puVar8 = 0x88;
          *(undefined4 *)(puVar8 + 0x12) = uVar10;
          *(undefined8 *)(puVar8 + 0x18) = 0;
          *(undefined2 **)(puVar8 + 0x14) = &uStack_438;
          *(undefined *)(puVar8 + 0x40) = 0;
          *(undefined *)((longlong)puVar8 + 0x81) = 9;
          puVar8[0x41] = 9;
          puVar8[0x42] = 0;
          *(undefined4 *)(puVar8 + 0x10) = 0;
          *(undefined8 *)(puVar8 + 0x1c) = 0;
          puVar9 = puVar8;
          FUN_00010690(DAT_00011c88,puVar8,uVar12);
          ExFreePool(puVar8);
        }
      }
      goto LAB_000112f0;
    }
  }
LAB_00011251:
  uVar7 = 0xc0000017;
LAB_000112f0:
  *(ulonglong *)(param_2 + 0x38) = uVar14;
  *(undefined4 *)(param_2 + 0x30) = uVar7;
  IofCompleteRequest(param_2,(ulonglong)puVar9 & 0xffffffffffffff00);
  return uVar7;
}



// ======================================== //
//   INTERNAL SUBFUNCTIONS CALLED BY DISPATCH   //
// ======================================== //


undefined8 FUN_00010690(longlong param_1,undefined8 param_2,ulonglong param_3)

{
  longlong lVar1;
  int iVar2;
  longlong lVar3;
  ulonglong uVar4;
  ulonglong uVar5;
  undefined4 local_58;
  undefined4 local_54;
  undefined local_50 [16];
  undefined local_40 [32];
  
  lVar1 = *(longlong *)(param_1 + 0x40);
  KeInitializeEvent(local_40,0,param_3 & 0xffffffffffffff00);
  uVar5 = 0;
  uVar4 = 0;
  lVar3 = IoBuildDeviceIoControlRequest
                    (0x220003,*(undefined8 *)(lVar1 + 0x18),0,0,0,0,1,local_40,local_50);
  if (lVar3 == 0) {
    return 0xc000009a;
  }
  *(undefined8 *)(*(longlong *)(lVar3 + 0xb8) + -0x40) = param_2;
  iVar2 = IofCallDriver(*(undefined8 *)(lVar1 + 0x18),lVar3);
  if (iVar2 == 0x103) {
    local_58 = 0xff676980;
    local_54 = 0xffffffff;
    uVar5 = uVar5 & 0xffffffffffffff00;
    uVar4 = uVar4 & 0xffffffffffffff00;
    iVar2 = KeWaitForSingleObject(local_40,0,uVar4,uVar5,&local_58);
    if (iVar2 == 0x102) {
      IoCancelIrp(lVar3);
      KeWaitForSingleObject(local_40,0,uVar4 & 0xffffffffffffff00,uVar5 & 0xffffffffffffff00,0);
    }
  }
  return 0;
}


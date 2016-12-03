case 0x00: /**** HLT ****/
    HaltFlag = 1;
    CYCLES(4);
    break;
case 0x01: /**** HLT ****/
    HaltFlag = 1;
    CYCLES(4);
    break;
case 0x02: /**** RLC ****/
    carry = A >> 1;
    A = (A << 1) | carry;
    CYCLES(5);
    break;
case 0x03: /**** RNC ****/
    if (carry == 0) RETURN();
    CYCLES(4);
    break;
case 0x04: /**** ADI @1 ****/
    carry = 0;
    FETCH();
    _BinaryAdd();
    A = pszValue = MB;
    CYCLES(8);
    break;
case 0x05: /**** RST 00 ****/
    MA = 0x00;
    CALL();
    CYCLES(5);
    break;
case 0x06: /**** MVI A,@1 ****/
    FETCH();
    A = MB;
    CYCLES(8);
    break;
case 0x07: /**** RET ****/
    RETURN();
    CYCLES(5);
    break;
case 0x08: /**** INR B ****/
    pszValue = B = (B + 1) & 0xFF;
    CYCLES(5);
    break;
case 0x09: /**** DCR B ****/
    pszValue = B = (B - 1) & 0xFF;
    CYCLES(5);
    break;
case 0x0a: /**** RRC ****/
    carry = A & 1;
    A = (A >> 1) | (carry << 7);
    CYCLES(5);
    break;
case 0x0b: /**** RNZ ****/
    if (pszValue != 0) RETURN();
    CYCLES(4);
    break;
case 0x0c: /**** ACI @1 ****/
    FETCH();
    _BinaryAdd();
    A = pszValue = MB;
    CYCLES(8);
    break;
case 0x0d: /**** RST 08 ****/
    MA = 0x08;
    CALL();
    CYCLES(5);
    break;
case 0x0e: /**** MVI B,@1 ****/
    FETCH();
    B = MB;
    CYCLES(8);
    break;
case 0x0f: /**** RET ****/
    RETURN();
    CYCLES(5);
    break;
case 0x10: /**** INR C ****/
    pszValue = C = (C + 1) & 0xFF;
    CYCLES(5);
    break;
case 0x11: /**** DCR C ****/
    pszValue = C = (C - 1) & 0xFF;
    CYCLES(5);
    break;
case 0x12: /**** RAL ****/
    temp16 = (A << 1)|carry;
    carry = A>>7;
    A = temp16 & 0xFF;
    CYCLES(5);
    break;
case 0x13: /**** RP ****/
    if ((pszValue & 0x80) == 0) RETURN();
    CYCLES(4);
    break;
case 0x14: /**** SUI @1 ****/
    carry = 0;
    FETCH();
    _BinarySubtract();
    A = pszValue = MB;
    CYCLES(8);
    break;
case 0x15: /**** RST 10 ****/
    MA = 0x10;
    CALL();
    CYCLES(5);
    break;
case 0x16: /**** MVI C,@1 ****/
    FETCH();
    C = MB;
    CYCLES(8);
    break;
case 0x17: /**** RET ****/
    RETURN();
    CYCLES(5);
    break;
case 0x18: /**** INR D ****/
    pszValue = D = (D + 1) & 0xFF;
    CYCLES(5);
    break;
case 0x19: /**** DCR D ****/
    pszValue = D = (D - 1) & 0xFF;
    CYCLES(5);
    break;
case 0x1a: /**** RAR ****/
    temp16 = A|(carry << 8);
    carry = temp16&1;
    A = temp16>>1;
    CYCLES(5);
    break;
case 0x1b: /**** RPO ****/
    if (_IsParityEven(pszValue) == 0) RETURN();
    CYCLES(4);
    break;
case 0x1c: /**** SBI @1 ****/
    FETCH();
    _BinarySubtract();
    A = pszValue = MB;
    CYCLES(8);
    break;
case 0x1d: /**** RST 18 ****/
    MA = 0x18;
    CALL();
    CYCLES(5);
    break;
case 0x1e: /**** MVI D,@1 ****/
    FETCH();
    D = MB;
    CYCLES(8);
    break;
case 0x1f: /**** RET ****/
    RETURN();
    CYCLES(5);
    break;
case 0x20: /**** INR E ****/
    pszValue = E = (E + 1) & 0xFF;
    CYCLES(5);
    break;
case 0x21: /**** DCR E ****/
    pszValue = E = (E - 1) & 0xFF;
    CYCLES(5);
    break;
case 0x23: /**** RC ****/
    if (carry != 0) RETURN();
    CYCLES(4);
    break;
case 0x24: /**** ANI @1 ****/
    carry = 0;
    FETCH();
    MB &= A;
    A = pszValue = MB;
    CYCLES(8);
    break;
case 0x25: /**** RST 20 ****/
    MA = 0x20;
    CALL();
    CYCLES(5);
    break;
case 0x26: /**** MVI E,@1 ****/
    FETCH();
    E = MB;
    CYCLES(8);
    break;
case 0x27: /**** RET ****/
    RETURN();
    CYCLES(5);
    break;
case 0x28: /**** INR H ****/
    pszValue = H = (H + 1) & 0xFF;
    CYCLES(5);
    break;
case 0x29: /**** DCR H ****/
    pszValue = H = (H - 1) & 0xFF;
    CYCLES(5);
    break;
case 0x2b: /**** RZ ****/
    if (pszValue == 0) RETURN();
    CYCLES(4);
    break;
case 0x2c: /**** XRI @1 ****/
    carry = 0;
    FETCH();
    MB ^= A;
    A = pszValue = MB;
    CYCLES(8);
    break;
case 0x2d: /**** RST 28 ****/
    MA = 0x28;
    CALL();
    CYCLES(5);
    break;
case 0x2e: /**** MVI H,@1 ****/
    FETCH();
    H = MB;
    CYCLES(8);
    break;
case 0x2f: /**** RET ****/
    RETURN();
    CYCLES(5);
    break;
case 0x30: /**** INR L ****/
    pszValue = L = (L + 1) & 0xFF;
    CYCLES(5);
    break;
case 0x31: /**** DCR L ****/
    pszValue = L = (L - 1) & 0xFF;
    CYCLES(5);
    break;
case 0x33: /**** RM ****/
    if ((pszValue & 0x80) != 0) RETURN();
    CYCLES(4);
    break;
case 0x34: /**** ORI @1 ****/
    carry = 0;
    FETCH();
    MB |= A;
    A = pszValue = MB;
    CYCLES(8);
    break;
case 0x35: /**** RST 30 ****/
    MA = 0x30;
    CALL();
    CYCLES(5);
    break;
case 0x36: /**** MVI L,@1 ****/
    FETCH();
    L = MB;
    CYCLES(8);
    break;
case 0x37: /**** RET ****/
    RETURN();
    CYCLES(5);
    break;
case 0x3b: /**** RPE ****/
    if (_IsParityEven(pszValue) != 0) RETURN();
    CYCLES(4);
    break;
case 0x3c: /**** CPI @1 ****/
    carry = 0;
    FETCH();
    _BinarySubtract();
    pszValue = MB;
    CYCLES(8);
    break;
case 0x3d: /**** RST 38 ****/
    MA = 0x38;
    CALL();
    CYCLES(5);
    break;
case 0x3e: /**** MVI M,@1 ****/
    FETCH();
    MA = (H << 8)|L;
    WRITE();
    CYCLES(9);
    break;
case 0x3f: /**** RET ****/
    RETURN();
    CYCLES(5);
    break;
case 0x40: /**** JNC @2 ****/
    FETCHWORD();
    if (carry == 0) JUMP();
    CYCLES(10);
    break;
case 0x41: /**** IN 00 ****/
    MB = 0;
    INPORT00();
    A = MB;
    CYCLES(8);
    break;
case 0x42: /**** CNC @2 ****/
    FETCHWORD();
    if (carry == 0) CALL();
    CYCLES(10);
    break;
case 0x43: /**** IN 01 ****/
    MB = 0;
    INPORT01();
    A = MB;
    CYCLES(8);
    break;
case 0x44: /**** JMP @2 ****/
    FETCHWORD();
    JUMP();
    CYCLES(11);
    break;
case 0x45: /**** IN 02 ****/
    MB = 0;
    INPORT02();
    A = MB;
    CYCLES(8);
    break;
case 0x46: /**** CALL @2 ****/
    FETCHWORD();
    CALL();
    CYCLES(11);
    break;
case 0x47: /**** IN 03 ****/
    MB = 0;
    INPORT03();
    A = MB;
    CYCLES(8);
    break;
case 0x48: /**** JNZ @2 ****/
    FETCHWORD();
    if (pszValue != 0) JUMP();
    CYCLES(10);
    break;
case 0x49: /**** IN 04 ****/
    MB = 0;
    INPORT04();
    A = MB;
    CYCLES(8);
    break;
case 0x4a: /**** CNZ @2 ****/
    FETCHWORD();
    if (pszValue != 0) CALL();
    CYCLES(10);
    break;
case 0x4b: /**** IN 05 ****/
    MB = 0;
    INPORT05();
    A = MB;
    CYCLES(8);
    break;
case 0x4c: /**** JMP @2 ****/
    FETCHWORD();
    JUMP();
    CYCLES(11);
    break;
case 0x4d: /**** IN 06 ****/
    MB = 0;
    INPORT06();
    A = MB;
    CYCLES(8);
    break;
case 0x4e: /**** CALL @2 ****/
    FETCHWORD();
    CALL();
    CYCLES(11);
    break;
case 0x4f: /**** IN 07 ****/
    MB = 0;
    INPORT07();
    A = MB;
    CYCLES(8);
    break;
case 0x50: /**** JP @2 ****/
    FETCHWORD();
    if ((pszValue & 0x80) == 0) JUMP();
    CYCLES(10);
    break;
case 0x51: /**** OUT 08 ****/
    MB = A;
    OUTPORT08();
    CYCLES(6);
    break;
case 0x52: /**** CP @2 ****/
    FETCHWORD();
    if ((pszValue & 0x80) == 0) CALL();
    CYCLES(10);
    break;
case 0x53: /**** OUT 09 ****/
    MB = A;
    OUTPORT09();
    CYCLES(6);
    break;
case 0x54: /**** JMP @2 ****/
    FETCHWORD();
    JUMP();
    CYCLES(11);
    break;
case 0x55: /**** OUT 0A ****/
    MB = A;
    OUTPORT0A();
    CYCLES(6);
    break;
case 0x56: /**** CALL @2 ****/
    FETCHWORD();
    CALL();
    CYCLES(11);
    break;
case 0x57: /**** OUT 0B ****/
    MB = A;
    OUTPORT0B();
    CYCLES(6);
    break;
case 0x58: /**** JPO @2 ****/
    FETCHWORD();
    if (_IsParityEven(pszValue) == 0) JUMP();
    CYCLES(10);
    break;
case 0x59: /**** OUT 0C ****/
    MB = A;
    OUTPORT0C();
    CYCLES(6);
    break;
case 0x5a: /**** CPO @2 ****/
    FETCHWORD();
    if (_IsParityEven(pszValue) == 0) CALL();
    CYCLES(10);
    break;
case 0x5b: /**** OUT 0D ****/
    MB = A;
    OUTPORT0D();
    CYCLES(6);
    break;
case 0x5c: /**** JMP @2 ****/
    FETCHWORD();
    JUMP();
    CYCLES(11);
    break;
case 0x5d: /**** OUT 0E ****/
    MB = A;
    OUTPORT0E();
    CYCLES(6);
    break;
case 0x5e: /**** CALL @2 ****/
    FETCHWORD();
    CALL();
    CYCLES(11);
    break;
case 0x5f: /**** OUT 0F ****/
    MB = A;
    OUTPORT0F();
    CYCLES(6);
    break;
case 0x60: /**** JC @2 ****/
    FETCHWORD();
    if (carry != 0) JUMP();
    CYCLES(10);
    break;
case 0x61: /**** OUT 10 ****/
    MB = A;
    OUTPORT10();
    CYCLES(6);
    break;
case 0x62: /**** CC @2 ****/
    FETCHWORD();
    if (carry != 0) CALL();
    CYCLES(10);
    break;
case 0x63: /**** OUT 11 ****/
    MB = A;
    OUTPORT11();
    CYCLES(6);
    break;
case 0x64: /**** JMP @2 ****/
    FETCHWORD();
    JUMP();
    CYCLES(11);
    break;
case 0x65: /**** OUT 12 ****/
    MB = A;
    OUTPORT12();
    CYCLES(6);
    break;
case 0x66: /**** CALL @2 ****/
    FETCHWORD();
    CALL();
    CYCLES(11);
    break;
case 0x67: /**** OUT 13 ****/
    MB = A;
    OUTPORT13();
    CYCLES(6);
    break;
case 0x68: /**** JZ @2 ****/
    FETCHWORD();
    if (pszValue == 0) JUMP();
    CYCLES(10);
    break;
case 0x69: /**** OUT 14 ****/
    MB = A;
    OUTPORT14();
    CYCLES(6);
    break;
case 0x6a: /**** CZ @2 ****/
    FETCHWORD();
    if (pszValue == 0) CALL();
    CYCLES(10);
    break;
case 0x6b: /**** OUT 15 ****/
    MB = A;
    OUTPORT15();
    CYCLES(6);
    break;
case 0x6c: /**** JMP @2 ****/
    FETCHWORD();
    JUMP();
    CYCLES(11);
    break;
case 0x6d: /**** OUT 16 ****/
    MB = A;
    OUTPORT16();
    CYCLES(6);
    break;
case 0x6e: /**** CALL @2 ****/
    FETCHWORD();
    CALL();
    CYCLES(11);
    break;
case 0x6f: /**** OUT 17 ****/
    MB = A;
    OUTPORT17();
    CYCLES(6);
    break;
case 0x70: /**** JM @2 ****/
    FETCHWORD();
    if ((pszValue & 0x80) != 0) JUMP();
    CYCLES(10);
    break;
case 0x71: /**** OUT 18 ****/
    MB = A;
    OUTPORT18();
    CYCLES(6);
    break;
case 0x72: /**** CM @2 ****/
    FETCHWORD();
    if ((pszValue & 0x80) != 0) CALL();
    CYCLES(10);
    break;
case 0x73: /**** OUT 19 ****/
    MB = A;
    OUTPORT19();
    CYCLES(6);
    break;
case 0x74: /**** JMP @2 ****/
    FETCHWORD();
    JUMP();
    CYCLES(11);
    break;
case 0x75: /**** OUT 1A ****/
    MB = A;
    OUTPORT1A();
    CYCLES(6);
    break;
case 0x76: /**** CALL @2 ****/
    FETCHWORD();
    CALL();
    CYCLES(11);
    break;
case 0x77: /**** OUT 1B ****/
    MB = A;
    OUTPORT1B();
    CYCLES(6);
    break;
case 0x78: /**** JPE @2 ****/
    FETCHWORD();
    if (_IsParityEven(pszValue) != 0) JUMP();
    CYCLES(10);
    break;
case 0x79: /**** OUT 1C ****/
    MB = A;
    OUTPORT1C();
    CYCLES(6);
    break;
case 0x7a: /**** CPE @2 ****/
    FETCHWORD();
    if (_IsParityEven(pszValue) != 0) CALL();
    CYCLES(10);
    break;
case 0x7b: /**** OUT 1D ****/
    MB = A;
    OUTPORT1D();
    CYCLES(6);
    break;
case 0x7c: /**** JMP @2 ****/
    FETCHWORD();
    JUMP();
    CYCLES(11);
    break;
case 0x7d: /**** OUT 1E ****/
    MB = A;
    OUTPORT1E();
    CYCLES(6);
    break;
case 0x7e: /**** CALL @2 ****/
    FETCHWORD();
    CALL();
    CYCLES(11);
    break;
case 0x7f: /**** OUT 1F ****/
    MB = A;
    OUTPORT1F();
    CYCLES(6);
    break;
case 0x80: /**** ADD A ****/
    carry = 0;
    MB = A;
    _BinaryAdd();
    A = pszValue = MB;
    CYCLES(5);
    break;
case 0x81: /**** ADD B ****/
    carry = 0;
    MB = B;
    _BinaryAdd();
    A = pszValue = MB;
    CYCLES(5);
    break;
case 0x82: /**** ADD C ****/
    carry = 0;
    MB = C;
    _BinaryAdd();
    A = pszValue = MB;
    CYCLES(5);
    break;
case 0x83: /**** ADD D ****/
    carry = 0;
    MB = D;
    _BinaryAdd();
    A = pszValue = MB;
    CYCLES(5);
    break;
case 0x84: /**** ADD E ****/
    carry = 0;
    MB = E;
    _BinaryAdd();
    A = pszValue = MB;
    CYCLES(5);
    break;
case 0x85: /**** ADD H ****/
    carry = 0;
    MB = H;
    _BinaryAdd();
    A = pszValue = MB;
    CYCLES(5);
    break;
case 0x86: /**** ADD L ****/
    carry = 0;
    MB = L;
    _BinaryAdd();
    A = pszValue = MB;
    CYCLES(5);
    break;
case 0x87: /**** ADD M ****/
    carry = 0;
    MA = (H << 8)|L;
    READ();
    _BinaryAdd();
    A = pszValue = MB;
    CYCLES(8);
    break;
case 0x88: /**** ADC A ****/
    MB = A;
    _BinaryAdd();
    A = pszValue = MB;
    CYCLES(5);
    break;
case 0x89: /**** ADC B ****/
    MB = B;
    _BinaryAdd();
    A = pszValue = MB;
    CYCLES(5);
    break;
case 0x8a: /**** ADC C ****/
    MB = C;
    _BinaryAdd();
    A = pszValue = MB;
    CYCLES(5);
    break;
case 0x8b: /**** ADC D ****/
    MB = D;
    _BinaryAdd();
    A = pszValue = MB;
    CYCLES(5);
    break;
case 0x8c: /**** ADC E ****/
    MB = E;
    _BinaryAdd();
    A = pszValue = MB;
    CYCLES(5);
    break;
case 0x8d: /**** ADC H ****/
    MB = H;
    _BinaryAdd();
    A = pszValue = MB;
    CYCLES(5);
    break;
case 0x8e: /**** ADC L ****/
    MB = L;
    _BinaryAdd();
    A = pszValue = MB;
    CYCLES(5);
    break;
case 0x8f: /**** ADC M ****/
    MA = (H << 8)|L;
    READ();
    _BinaryAdd();
    A = pszValue = MB;
    CYCLES(8);
    break;
case 0x90: /**** SUB A ****/
    carry = 0;
    MB = A;
    _BinarySubtract();
    A = pszValue = MB;
    CYCLES(5);
    break;
case 0x91: /**** SUB B ****/
    carry = 0;
    MB = B;
    _BinarySubtract();
    A = pszValue = MB;
    CYCLES(5);
    break;
case 0x92: /**** SUB C ****/
    carry = 0;
    MB = C;
    _BinarySubtract();
    A = pszValue = MB;
    CYCLES(5);
    break;
case 0x93: /**** SUB D ****/
    carry = 0;
    MB = D;
    _BinarySubtract();
    A = pszValue = MB;
    CYCLES(5);
    break;
case 0x94: /**** SUB E ****/
    carry = 0;
    MB = E;
    _BinarySubtract();
    A = pszValue = MB;
    CYCLES(5);
    break;
case 0x95: /**** SUB H ****/
    carry = 0;
    MB = H;
    _BinarySubtract();
    A = pszValue = MB;
    CYCLES(5);
    break;
case 0x96: /**** SUB L ****/
    carry = 0;
    MB = L;
    _BinarySubtract();
    A = pszValue = MB;
    CYCLES(5);
    break;
case 0x97: /**** SUB M ****/
    carry = 0;
    MA = (H << 8)|L;
    READ();
    _BinarySubtract();
    A = pszValue = MB;
    CYCLES(8);
    break;
case 0x98: /**** SBB A ****/
    MB = A;
    _BinarySubtract();
    A = pszValue = MB;
    CYCLES(5);
    break;
case 0x99: /**** SBB B ****/
    MB = B;
    _BinarySubtract();
    A = pszValue = MB;
    CYCLES(5);
    break;
case 0x9a: /**** SBB C ****/
    MB = C;
    _BinarySubtract();
    A = pszValue = MB;
    CYCLES(5);
    break;
case 0x9b: /**** SBB D ****/
    MB = D;
    _BinarySubtract();
    A = pszValue = MB;
    CYCLES(5);
    break;
case 0x9c: /**** SBB E ****/
    MB = E;
    _BinarySubtract();
    A = pszValue = MB;
    CYCLES(5);
    break;
case 0x9d: /**** SBB H ****/
    MB = H;
    _BinarySubtract();
    A = pszValue = MB;
    CYCLES(5);
    break;
case 0x9e: /**** SBB L ****/
    MB = L;
    _BinarySubtract();
    A = pszValue = MB;
    CYCLES(5);
    break;
case 0x9f: /**** SBB M ****/
    MA = (H << 8)|L;
    READ();
    _BinarySubtract();
    A = pszValue = MB;
    CYCLES(8);
    break;
case 0xa0: /**** ANA A ****/
    carry = 0;
    MB = A;
    MB &= A;
    A = pszValue = MB;
    CYCLES(5);
    break;
case 0xa1: /**** ANA B ****/
    carry = 0;
    MB = B;
    MB &= A;
    A = pszValue = MB;
    CYCLES(5);
    break;
case 0xa2: /**** ANA C ****/
    carry = 0;
    MB = C;
    MB &= A;
    A = pszValue = MB;
    CYCLES(5);
    break;
case 0xa3: /**** ANA D ****/
    carry = 0;
    MB = D;
    MB &= A;
    A = pszValue = MB;
    CYCLES(5);
    break;
case 0xa4: /**** ANA E ****/
    carry = 0;
    MB = E;
    MB &= A;
    A = pszValue = MB;
    CYCLES(5);
    break;
case 0xa5: /**** ANA H ****/
    carry = 0;
    MB = H;
    MB &= A;
    A = pszValue = MB;
    CYCLES(5);
    break;
case 0xa6: /**** ANA L ****/
    carry = 0;
    MB = L;
    MB &= A;
    A = pszValue = MB;
    CYCLES(5);
    break;
case 0xa7: /**** ANA M ****/
    carry = 0;
    MA = (H << 8)|L;
    READ();
    MB &= A;
    A = pszValue = MB;
    CYCLES(8);
    break;
case 0xa8: /**** XRA A ****/
    carry = 0;
    MB = A;
    MB ^= A;
    A = pszValue = MB;
    CYCLES(5);
    break;
case 0xa9: /**** XRA B ****/
    carry = 0;
    MB = B;
    MB ^= A;
    A = pszValue = MB;
    CYCLES(5);
    break;
case 0xaa: /**** XRA C ****/
    carry = 0;
    MB = C;
    MB ^= A;
    A = pszValue = MB;
    CYCLES(5);
    break;
case 0xab: /**** XRA D ****/
    carry = 0;
    MB = D;
    MB ^= A;
    A = pszValue = MB;
    CYCLES(5);
    break;
case 0xac: /**** XRA E ****/
    carry = 0;
    MB = E;
    MB ^= A;
    A = pszValue = MB;
    CYCLES(5);
    break;
case 0xad: /**** XRA H ****/
    carry = 0;
    MB = H;
    MB ^= A;
    A = pszValue = MB;
    CYCLES(5);
    break;
case 0xae: /**** XRA L ****/
    carry = 0;
    MB = L;
    MB ^= A;
    A = pszValue = MB;
    CYCLES(5);
    break;
case 0xaf: /**** XRA M ****/
    carry = 0;
    MA = (H << 8)|L;
    READ();
    MB ^= A;
    A = pszValue = MB;
    CYCLES(8);
    break;
case 0xb0: /**** ORA A ****/
    carry = 0;
    MB = A;
    MB |= A;
    A = pszValue = MB;
    CYCLES(5);
    break;
case 0xb1: /**** ORA B ****/
    carry = 0;
    MB = B;
    MB |= A;
    A = pszValue = MB;
    CYCLES(5);
    break;
case 0xb2: /**** ORA C ****/
    carry = 0;
    MB = C;
    MB |= A;
    A = pszValue = MB;
    CYCLES(5);
    break;
case 0xb3: /**** ORA D ****/
    carry = 0;
    MB = D;
    MB |= A;
    A = pszValue = MB;
    CYCLES(5);
    break;
case 0xb4: /**** ORA E ****/
    carry = 0;
    MB = E;
    MB |= A;
    A = pszValue = MB;
    CYCLES(5);
    break;
case 0xb5: /**** ORA H ****/
    carry = 0;
    MB = H;
    MB |= A;
    A = pszValue = MB;
    CYCLES(5);
    break;
case 0xb6: /**** ORA L ****/
    carry = 0;
    MB = L;
    MB |= A;
    A = pszValue = MB;
    CYCLES(5);
    break;
case 0xb7: /**** ORA M ****/
    carry = 0;
    MA = (H << 8)|L;
    READ();
    MB |= A;
    A = pszValue = MB;
    CYCLES(8);
    break;
case 0xb8: /**** CMP A ****/
    carry = 0;
    MB = A;
    _BinarySubtract();
    pszValue = MB;
    CYCLES(5);
    break;
case 0xb9: /**** CMP B ****/
    carry = 0;
    MB = B;
    _BinarySubtract();
    pszValue = MB;
    CYCLES(5);
    break;
case 0xba: /**** CMP C ****/
    carry = 0;
    MB = C;
    _BinarySubtract();
    pszValue = MB;
    CYCLES(5);
    break;
case 0xbb: /**** CMP D ****/
    carry = 0;
    MB = D;
    _BinarySubtract();
    pszValue = MB;
    CYCLES(5);
    break;
case 0xbc: /**** CMP E ****/
    carry = 0;
    MB = E;
    _BinarySubtract();
    pszValue = MB;
    CYCLES(5);
    break;
case 0xbd: /**** CMP H ****/
    carry = 0;
    MB = H;
    _BinarySubtract();
    pszValue = MB;
    CYCLES(5);
    break;
case 0xbe: /**** CMP L ****/
    carry = 0;
    MB = L;
    _BinarySubtract();
    pszValue = MB;
    CYCLES(5);
    break;
case 0xbf: /**** CMP M ****/
    carry = 0;
    MA = (H << 8)|L;
    READ();
    _BinarySubtract();
    pszValue = MB;
    CYCLES(8);
    break;
case 0xc0: /**** MOV A,A ****/
    A = A;
    CYCLES(5);
    break;
case 0xc1: /**** MOV A,B ****/
    A = B;
    CYCLES(5);
    break;
case 0xc2: /**** MOV A,C ****/
    A = C;
    CYCLES(5);
    break;
case 0xc3: /**** MOV A,D ****/
    A = D;
    CYCLES(5);
    break;
case 0xc4: /**** MOV A,E ****/
    A = E;
    CYCLES(5);
    break;
case 0xc5: /**** MOV A,H ****/
    A = H;
    CYCLES(5);
    break;
case 0xc6: /**** MOV A,L ****/
    A = L;
    CYCLES(5);
    break;
case 0xc7: /**** MOV A,M ****/
    MA = (H << 8)|L;
    READ();
    A = MB;
    CYCLES(8);
    break;
case 0xc8: /**** MOV B,A ****/
    B = A;
    CYCLES(5);
    break;
case 0xc9: /**** MOV B,B ****/
    B = B;
    CYCLES(5);
    break;
case 0xca: /**** MOV B,C ****/
    B = C;
    CYCLES(5);
    break;
case 0xcb: /**** MOV B,D ****/
    B = D;
    CYCLES(5);
    break;
case 0xcc: /**** MOV B,E ****/
    B = E;
    CYCLES(5);
    break;
case 0xcd: /**** MOV B,H ****/
    B = H;
    CYCLES(5);
    break;
case 0xce: /**** MOV B,L ****/
    B = L;
    CYCLES(5);
    break;
case 0xcf: /**** MOV B,M ****/
    MA = (H << 8)|L;
    READ();
    B = MB;
    CYCLES(8);
    break;
case 0xd0: /**** MOV C,A ****/
    C = A;
    CYCLES(5);
    break;
case 0xd1: /**** MOV C,B ****/
    C = B;
    CYCLES(5);
    break;
case 0xd2: /**** MOV C,C ****/
    C = C;
    CYCLES(5);
    break;
case 0xd3: /**** MOV C,D ****/
    C = D;
    CYCLES(5);
    break;
case 0xd4: /**** MOV C,E ****/
    C = E;
    CYCLES(5);
    break;
case 0xd5: /**** MOV C,H ****/
    C = H;
    CYCLES(5);
    break;
case 0xd6: /**** MOV C,L ****/
    C = L;
    CYCLES(5);
    break;
case 0xd7: /**** MOV C,M ****/
    MA = (H << 8)|L;
    READ();
    C = MB;
    CYCLES(8);
    break;
case 0xd8: /**** MOV D,A ****/
    D = A;
    CYCLES(5);
    break;
case 0xd9: /**** MOV D,B ****/
    D = B;
    CYCLES(5);
    break;
case 0xda: /**** MOV D,C ****/
    D = C;
    CYCLES(5);
    break;
case 0xdb: /**** MOV D,D ****/
    D = D;
    CYCLES(5);
    break;
case 0xdc: /**** MOV D,E ****/
    D = E;
    CYCLES(5);
    break;
case 0xdd: /**** MOV D,H ****/
    D = H;
    CYCLES(5);
    break;
case 0xde: /**** MOV D,L ****/
    D = L;
    CYCLES(5);
    break;
case 0xdf: /**** MOV D,M ****/
    MA = (H << 8)|L;
    READ();
    D = MB;
    CYCLES(8);
    break;
case 0xe0: /**** MOV E,A ****/
    E = A;
    CYCLES(5);
    break;
case 0xe1: /**** MOV E,B ****/
    E = B;
    CYCLES(5);
    break;
case 0xe2: /**** MOV E,C ****/
    E = C;
    CYCLES(5);
    break;
case 0xe3: /**** MOV E,D ****/
    E = D;
    CYCLES(5);
    break;
case 0xe4: /**** MOV E,E ****/
    E = E;
    CYCLES(5);
    break;
case 0xe5: /**** MOV E,H ****/
    E = H;
    CYCLES(5);
    break;
case 0xe6: /**** MOV E,L ****/
    E = L;
    CYCLES(5);
    break;
case 0xe7: /**** MOV E,M ****/
    MA = (H << 8)|L;
    READ();
    E = MB;
    CYCLES(8);
    break;
case 0xe8: /**** MOV H,A ****/
    H = A;
    CYCLES(5);
    break;
case 0xe9: /**** MOV H,B ****/
    H = B;
    CYCLES(5);
    break;
case 0xea: /**** MOV H,C ****/
    H = C;
    CYCLES(5);
    break;
case 0xeb: /**** MOV H,D ****/
    H = D;
    CYCLES(5);
    break;
case 0xec: /**** MOV H,E ****/
    H = E;
    CYCLES(5);
    break;
case 0xed: /**** MOV H,H ****/
    H = H;
    CYCLES(5);
    break;
case 0xee: /**** MOV H,L ****/
    H = L;
    CYCLES(5);
    break;
case 0xef: /**** MOV H,M ****/
    MA = (H << 8)|L;
    READ();
    H = MB;
    CYCLES(8);
    break;
case 0xf0: /**** MOV L,A ****/
    L = A;
    CYCLES(5);
    break;
case 0xf1: /**** MOV L,B ****/
    L = B;
    CYCLES(5);
    break;
case 0xf2: /**** MOV L,C ****/
    L = C;
    CYCLES(5);
    break;
case 0xf3: /**** MOV L,D ****/
    L = D;
    CYCLES(5);
    break;
case 0xf4: /**** MOV L,E ****/
    L = E;
    CYCLES(5);
    break;
case 0xf5: /**** MOV L,H ****/
    L = H;
    CYCLES(5);
    break;
case 0xf6: /**** MOV L,L ****/
    L = L;
    CYCLES(5);
    break;
case 0xf7: /**** MOV L,M ****/
    MA = (H << 8)|L;
    READ();
    L = MB;
    CYCLES(8);
    break;
case 0xf8: /**** MOV M,A ****/
    MA = (H << 8)|L;
    MB = A;
    WRITE();
    CYCLES(7);
    break;
case 0xf9: /**** MOV M,B ****/
    MA = (H << 8)|L;
    MB = B;
    WRITE();
    CYCLES(7);
    break;
case 0xfa: /**** MOV M,C ****/
    MA = (H << 8)|L;
    MB = C;
    WRITE();
    CYCLES(7);
    break;
case 0xfb: /**** MOV M,D ****/
    MA = (H << 8)|L;
    MB = D;
    WRITE();
    CYCLES(7);
    break;
case 0xfc: /**** MOV M,E ****/
    MA = (H << 8)|L;
    MB = E;
    WRITE();
    CYCLES(7);
    break;
case 0xfd: /**** MOV M,H ****/
    MA = (H << 8)|L;
    MB = H;
    WRITE();
    CYCLES(7);
    break;
case 0xfe: /**** MOV M,L ****/
    MA = (H << 8)|L;
    MB = L;
    WRITE();
    CYCLES(7);
    break;
case 0xff: /**** HLT ****/
    HaltFlag = 1;
    CYCLES(4);
    break;

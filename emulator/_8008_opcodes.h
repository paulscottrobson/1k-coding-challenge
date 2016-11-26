case 0x00: // *** hlt ***
    Halt = 1;break;
case 0x01: // *** hlt ***
    Halt = 1;break;
case 0x02: // *** rlc ***
    Carry = (A >> 7) & 1;A = ((A << 1) & 0xFE) | Carry;break;
case 0x03: // *** rnc ***
    if (Carry==0) { RETURN(); };break;
case 0x04: // *** adi $1 ***
    FETCH();ADD(MB,0);A = pszValue;break;
case 0x05: // *** rst 00 ***
    temp16 = 0x00;CALL();;break;
case 0x06: // *** mvi a,$1 ***
    FETCH();A = MB;break;
case 0x07: // *** ret ***
    RETURN;;break;
case 0x08: // *** inr b ***
    B = pszValue = (B+1) & 255;break;
case 0x09: // *** dcr b ***
    B = pszValue = (B-1) & 255;break;
case 0x0a: // *** rrc ***
    Carry = A & 1;A = ((A >> 1) & 0x7F) | (Carry << 7);break;
case 0x0b: // *** rnz ***
    if (pszValue != 0) { RETURN(); };break;
case 0x0c: // *** aci $1 ***
    FETCH();ADD(MB,Carry);A = pszValue;break;
case 0x0d: // *** rst 08 ***
    temp16 = 0x08;CALL();;break;
case 0x0e: // *** mvi b,$1 ***
    FETCH();B = MB;break;
case 0x0f: // *** ret ***
    RETURN;;break;
case 0x10: // *** inr c ***
    C = pszValue = (C+1) & 255;break;
case 0x11: // *** dcr c ***
    C = pszValue = (C-1) & 255;break;
case 0x12: // *** ral ***
    temp16 = (A << 1) | Carry;A = temp16;Carry = temp16 >> 8;break;
case 0x13: // *** rp ***
    if ((pszValue & 0x80) == 0) { RETURN(); };break;
case 0x14: // *** sui $1 ***
    FETCH();SUB(MB,0);A = pszValue;break;
case 0x15: // *** rst 10 ***
    temp16 = 0x10;CALL();;break;
case 0x16: // *** mvi c,$1 ***
    FETCH();C = MB;break;
case 0x17: // *** ret ***
    RETURN;;break;
case 0x18: // *** inr d ***
    D = pszValue = (D+1) & 255;break;
case 0x19: // *** dcr d ***
    D = pszValue = (D-1) & 255;break;
case 0x1a: // *** rar ***
    temp16 = A | (Carry << 8);A = temp16 >> 1;Carry = temp16 & 1;break;
case 0x1b: // *** rpo ***
    if (isEvenParity() == 0) { RETURN(); };break;
case 0x1c: // *** sbi $1 ***
    FETCH();SUB(MB,Carry);A = pszValue;break;
case 0x1d: // *** rst 18 ***
    temp16 = 0x18;CALL();;break;
case 0x1e: // *** mvi d,$1 ***
    FETCH();D = MB;break;
case 0x1f: // *** ret ***
    RETURN;;break;
case 0x20: // *** inr e ***
    E = pszValue = (E+1) & 255;break;
case 0x21: // *** dcr e ***
    E = pszValue = (E-1) & 255;break;
case 0x23: // *** rc ***
    if (Carry!=0) { RETURN(); };break;
case 0x24: // *** ani $1 ***
    FETCH();A = pszValue = A & MB;Carry = 0;;break;
case 0x25: // *** rst 20 ***
    temp16 = 0x20;CALL();;break;
case 0x26: // *** mvi e,$1 ***
    FETCH();E = MB;break;
case 0x27: // *** ret ***
    RETURN;;break;
case 0x28: // *** inr h ***
    H = pszValue = (H+1) & 255;break;
case 0x29: // *** dcr h ***
    H = pszValue = (H-1) & 255;break;
case 0x2b: // *** rz ***
    if (pszValue == 0) { RETURN(); };break;
case 0x2c: // *** xri $1 ***
    FETCH();A = pszValue = A ^ MB;Carry = 0;;break;
case 0x2d: // *** rst 28 ***
    temp16 = 0x28;CALL();;break;
case 0x2e: // *** mvi h,$1 ***
    FETCH();H = MB;break;
case 0x2f: // *** ret ***
    RETURN;;break;
case 0x30: // *** inr l ***
    L = pszValue = (L+1) & 255;break;
case 0x31: // *** dcr l ***
    L = pszValue = (L-1) & 255;break;
case 0x33: // *** rm ***
    if ((pszValue & 0x80) != 0) { RETURN(); };break;
case 0x34: // *** ori $1 ***
    FETCH();A = pszValue = A | MB;Carry = 0;;break;
case 0x35: // *** rst 30 ***
    temp16 = 0x30;CALL();;break;
case 0x36: // *** mvi l,$1 ***
    FETCH();L = MB;break;
case 0x37: // *** ret ***
    RETURN;;break;
case 0x3b: // *** rpe ***
    if (isEvenParity() != 0) { RETURN(); };break;
case 0x3c: // *** cpi $1 ***
    FETCH();SUB(MB,0);break;
case 0x3d: // *** rst 38 ***
    temp16 = 0x38;CALL();;break;
case 0x3e: // *** mvi m,$1 ***
    FETCH();MAHL();WRITE();break;
case 0x3f: // *** ret ***
    RETURN;;break;
case 0x40: // *** jnc $2 ***
    FETCH16();if (Carry==0) { BRANCH(); };break;
case 0x41: // *** in 00 ***
    A = INPORT00();break;
case 0x42: // *** cnc $2 ***
    FETCH16();if (Carry==0) { CALL(); };break;
case 0x43: // *** in 01 ***
    A = INPORT01();break;
case 0x44: // *** jmp $2 ***
    FETCH16();BRANCH();;break;
case 0x45: // *** in 02 ***
    A = INPORT02();break;
case 0x46: // *** call $2 ***
    FETCH16();CALL();;break;
case 0x47: // *** in 03 ***
    A = INPORT03();break;
case 0x48: // *** jnz $2 ***
    FETCH16();if (pszValue != 0) { BRANCH(); };break;
case 0x49: // *** in 04 ***
    A = INPORT04();break;
case 0x4a: // *** cnz $2 ***
    FETCH16();if (pszValue != 0) { CALL(); };break;
case 0x4b: // *** in 05 ***
    A = INPORT05();break;
case 0x4c: // *** jmp $2 ***
    FETCH16();BRANCH();;break;
case 0x4d: // *** in 06 ***
    A = INPORT06();break;
case 0x4e: // *** call $2 ***
    FETCH16();CALL();;break;
case 0x4f: // *** in 07 ***
    A = INPORT07();break;
case 0x50: // *** jp $2 ***
    FETCH16();if ((pszValue & 0x80) == 0) { BRANCH(); };break;
case 0x51: // *** out 08 ***
    OUTPORT08(A);break;
case 0x52: // *** cp $2 ***
    FETCH16();if ((pszValue & 0x80) == 0) { CALL(); };break;
case 0x53: // *** out 09 ***
    OUTPORT09(A);break;
case 0x54: // *** jmp $2 ***
    FETCH16();BRANCH();;break;
case 0x55: // *** out 0a ***
    OUTPORT0A(A);break;
case 0x56: // *** call $2 ***
    FETCH16();CALL();;break;
case 0x57: // *** out 0b ***
    OUTPORT0B(A);break;
case 0x58: // *** jpo $2 ***
    FETCH16();if (isEvenParity() == 0) { BRANCH(); };break;
case 0x59: // *** out 0c ***
    OUTPORT0C(A);break;
case 0x5a: // *** cpo $2 ***
    FETCH16();if (isEvenParity() == 0) { CALL(); };break;
case 0x5b: // *** out 0d ***
    OUTPORT0D(A);break;
case 0x5c: // *** jmp $2 ***
    FETCH16();BRANCH();;break;
case 0x5d: // *** out 0e ***
    OUTPORT0E(A);break;
case 0x5e: // *** call $2 ***
    FETCH16();CALL();;break;
case 0x5f: // *** out 0f ***
    OUTPORT0F(A);break;
case 0x60: // *** jc $2 ***
    FETCH16();if (Carry!=0) { BRANCH(); };break;
case 0x61: // *** out 10 ***
    OUTPORT10(A);break;
case 0x62: // *** cc $2 ***
    FETCH16();if (Carry!=0) { CALL(); };break;
case 0x63: // *** out 11 ***
    OUTPORT11(A);break;
case 0x64: // *** jmp $2 ***
    FETCH16();BRANCH();;break;
case 0x65: // *** out 12 ***
    OUTPORT12(A);break;
case 0x66: // *** call $2 ***
    FETCH16();CALL();;break;
case 0x67: // *** out 13 ***
    OUTPORT13(A);break;
case 0x68: // *** jz $2 ***
    FETCH16();if (pszValue == 0) { BRANCH(); };break;
case 0x69: // *** out 14 ***
    OUTPORT14(A);break;
case 0x6a: // *** cz $2 ***
    FETCH16();if (pszValue == 0) { CALL(); };break;
case 0x6b: // *** out 15 ***
    OUTPORT15(A);break;
case 0x6c: // *** jmp $2 ***
    FETCH16();BRANCH();;break;
case 0x6d: // *** out 16 ***
    OUTPORT16(A);break;
case 0x6e: // *** call $2 ***
    FETCH16();CALL();;break;
case 0x6f: // *** out 17 ***
    OUTPORT17(A);break;
case 0x70: // *** jm $2 ***
    FETCH16();if ((pszValue & 0x80) != 0) { BRANCH(); };break;
case 0x71: // *** out 18 ***
    OUTPORT18(A);break;
case 0x72: // *** cm $2 ***
    FETCH16();if ((pszValue & 0x80) != 0) { CALL(); };break;
case 0x73: // *** out 19 ***
    OUTPORT19(A);break;
case 0x74: // *** jmp $2 ***
    FETCH16();BRANCH();;break;
case 0x75: // *** out 1a ***
    OUTPORT1A(A);break;
case 0x76: // *** call $2 ***
    FETCH16();CALL();;break;
case 0x77: // *** out 1b ***
    OUTPORT1B(A);break;
case 0x78: // *** jpe $2 ***
    FETCH16();if (isEvenParity() != 0) { BRANCH(); };break;
case 0x79: // *** out 1c ***
    OUTPORT1C(A);break;
case 0x7a: // *** cpe $2 ***
    FETCH16();if (isEvenParity() != 0) { CALL(); };break;
case 0x7b: // *** out 1d ***
    OUTPORT1D(A);break;
case 0x7c: // *** jmp $2 ***
    FETCH16();BRANCH();;break;
case 0x7d: // *** out 1e ***
    OUTPORT1E(A);break;
case 0x7e: // *** call $2 ***
    FETCH16();CALL();;break;
case 0x7f: // *** out 1f ***
    OUTPORT1F(A);break;
case 0x80: // *** add a ***
    ADD(A,0);A = pszValue;break;
case 0x81: // *** add b ***
    ADD(B,0);A = pszValue;break;
case 0x82: // *** add c ***
    ADD(C,0);A = pszValue;break;
case 0x83: // *** add d ***
    ADD(D,0);A = pszValue;break;
case 0x84: // *** add e ***
    ADD(E,0);A = pszValue;break;
case 0x85: // *** add h ***
    ADD(H,0);A = pszValue;break;
case 0x86: // *** add l ***
    ADD(L,0);A = pszValue;break;
case 0x87: // *** add m ***
    MAHL();READ();ADD(MB,0);A = pszValue;break;
case 0x88: // *** adc a ***
    ADD(A,Carry);A = pszValue;break;
case 0x89: // *** adc b ***
    ADD(B,Carry);A = pszValue;break;
case 0x8a: // *** adc c ***
    ADD(C,Carry);A = pszValue;break;
case 0x8b: // *** adc d ***
    ADD(D,Carry);A = pszValue;break;
case 0x8c: // *** adc e ***
    ADD(E,Carry);A = pszValue;break;
case 0x8d: // *** adc h ***
    ADD(H,Carry);A = pszValue;break;
case 0x8e: // *** adc l ***
    ADD(L,Carry);A = pszValue;break;
case 0x8f: // *** adc m ***
    MAHL();READ();ADD(MB,Carry);A = pszValue;break;
case 0x90: // *** sub a ***
    SUB(A,0);A = pszValue;break;
case 0x91: // *** sub b ***
    SUB(B,0);A = pszValue;break;
case 0x92: // *** sub c ***
    SUB(C,0);A = pszValue;break;
case 0x93: // *** sub d ***
    SUB(D,0);A = pszValue;break;
case 0x94: // *** sub e ***
    SUB(E,0);A = pszValue;break;
case 0x95: // *** sub h ***
    SUB(H,0);A = pszValue;break;
case 0x96: // *** sub l ***
    SUB(L,0);A = pszValue;break;
case 0x97: // *** sub m ***
    MAHL();READ();SUB(MB,0);A = pszValue;break;
case 0x98: // *** sbb a ***
    SUB(A,Carry);A = pszValue;break;
case 0x99: // *** sbb b ***
    SUB(B,Carry);A = pszValue;break;
case 0x9a: // *** sbb c ***
    SUB(C,Carry);A = pszValue;break;
case 0x9b: // *** sbb d ***
    SUB(D,Carry);A = pszValue;break;
case 0x9c: // *** sbb e ***
    SUB(E,Carry);A = pszValue;break;
case 0x9d: // *** sbb h ***
    SUB(H,Carry);A = pszValue;break;
case 0x9e: // *** sbb l ***
    SUB(L,Carry);A = pszValue;break;
case 0x9f: // *** sbb m ***
    MAHL();READ();SUB(MB,Carry);A = pszValue;break;
case 0xa0: // *** ana a ***
    A = pszValue = A & A;Carry = 0;;break;
case 0xa1: // *** ana b ***
    A = pszValue = A & B;Carry = 0;;break;
case 0xa2: // *** ana c ***
    A = pszValue = A & C;Carry = 0;;break;
case 0xa3: // *** ana d ***
    A = pszValue = A & D;Carry = 0;;break;
case 0xa4: // *** ana e ***
    A = pszValue = A & E;Carry = 0;;break;
case 0xa5: // *** ana h ***
    A = pszValue = A & H;Carry = 0;;break;
case 0xa6: // *** ana l ***
    A = pszValue = A & L;Carry = 0;;break;
case 0xa7: // *** ana m ***
    MAHL();READ();A = pszValue = A & MB;Carry = 0;;break;
case 0xa8: // *** xra a ***
    A = pszValue = A ^ A;Carry = 0;;break;
case 0xa9: // *** xra b ***
    A = pszValue = A ^ B;Carry = 0;;break;
case 0xaa: // *** xra c ***
    A = pszValue = A ^ C;Carry = 0;;break;
case 0xab: // *** xra d ***
    A = pszValue = A ^ D;Carry = 0;;break;
case 0xac: // *** xra e ***
    A = pszValue = A ^ E;Carry = 0;;break;
case 0xad: // *** xra h ***
    A = pszValue = A ^ H;Carry = 0;;break;
case 0xae: // *** xra l ***
    A = pszValue = A ^ L;Carry = 0;;break;
case 0xaf: // *** xra m ***
    MAHL();READ();A = pszValue = A ^ MB;Carry = 0;;break;
case 0xb0: // *** ora a ***
    A = pszValue = A | A;Carry = 0;;break;
case 0xb1: // *** ora b ***
    A = pszValue = A | B;Carry = 0;;break;
case 0xb2: // *** ora c ***
    A = pszValue = A | C;Carry = 0;;break;
case 0xb3: // *** ora d ***
    A = pszValue = A | D;Carry = 0;;break;
case 0xb4: // *** ora e ***
    A = pszValue = A | E;Carry = 0;;break;
case 0xb5: // *** ora h ***
    A = pszValue = A | H;Carry = 0;;break;
case 0xb6: // *** ora l ***
    A = pszValue = A | L;Carry = 0;;break;
case 0xb7: // *** ora m ***
    MAHL();READ();A = pszValue = A | MB;Carry = 0;;break;
case 0xb8: // *** cmp a ***
    SUB(A,0);break;
case 0xb9: // *** cmp b ***
    SUB(B,0);break;
case 0xba: // *** cmp c ***
    SUB(C,0);break;
case 0xbb: // *** cmp d ***
    SUB(D,0);break;
case 0xbc: // *** cmp e ***
    SUB(E,0);break;
case 0xbd: // *** cmp h ***
    SUB(H,0);break;
case 0xbe: // *** cmp l ***
    SUB(L,0);break;
case 0xbf: // *** cmp m ***
    MAHL();READ();SUB(MB,0);break;
case 0xc0: // *** mov a,a ***
    A = A;break;
case 0xc1: // *** mov a,b ***
    A = B;break;
case 0xc2: // *** mov a,c ***
    A = C;break;
case 0xc3: // *** mov a,d ***
    A = D;break;
case 0xc4: // *** mov a,e ***
    A = E;break;
case 0xc5: // *** mov a,h ***
    A = H;break;
case 0xc6: // *** mov a,l ***
    A = L;break;
case 0xc7: // *** mov a,m ***
    MAHL();READ();A = MB;break;
case 0xc8: // *** mov b,a ***
    B = A;break;
case 0xc9: // *** mov b,b ***
    B = B;break;
case 0xca: // *** mov b,c ***
    B = C;break;
case 0xcb: // *** mov b,d ***
    B = D;break;
case 0xcc: // *** mov b,e ***
    B = E;break;
case 0xcd: // *** mov b,h ***
    B = H;break;
case 0xce: // *** mov b,l ***
    B = L;break;
case 0xcf: // *** mov b,m ***
    MAHL();READ();B = MB;break;
case 0xd0: // *** mov c,a ***
    C = A;break;
case 0xd1: // *** mov c,b ***
    C = B;break;
case 0xd2: // *** mov c,c ***
    C = C;break;
case 0xd3: // *** mov c,d ***
    C = D;break;
case 0xd4: // *** mov c,e ***
    C = E;break;
case 0xd5: // *** mov c,h ***
    C = H;break;
case 0xd6: // *** mov c,l ***
    C = L;break;
case 0xd7: // *** mov c,m ***
    MAHL();READ();C = MB;break;
case 0xd8: // *** mov d,a ***
    D = A;break;
case 0xd9: // *** mov d,b ***
    D = B;break;
case 0xda: // *** mov d,c ***
    D = C;break;
case 0xdb: // *** mov d,d ***
    D = D;break;
case 0xdc: // *** mov d,e ***
    D = E;break;
case 0xdd: // *** mov d,h ***
    D = H;break;
case 0xde: // *** mov d,l ***
    D = L;break;
case 0xdf: // *** mov d,m ***
    MAHL();READ();D = MB;break;
case 0xe0: // *** mov e,a ***
    E = A;break;
case 0xe1: // *** mov e,b ***
    E = B;break;
case 0xe2: // *** mov e,c ***
    E = C;break;
case 0xe3: // *** mov e,d ***
    E = D;break;
case 0xe4: // *** mov e,e ***
    E = E;break;
case 0xe5: // *** mov e,h ***
    E = H;break;
case 0xe6: // *** mov e,l ***
    E = L;break;
case 0xe7: // *** mov e,m ***
    MAHL();READ();E = MB;break;
case 0xe8: // *** mov h,a ***
    H = A;break;
case 0xe9: // *** mov h,b ***
    H = B;break;
case 0xea: // *** mov h,c ***
    H = C;break;
case 0xeb: // *** mov h,d ***
    H = D;break;
case 0xec: // *** mov h,e ***
    H = E;break;
case 0xed: // *** mov h,h ***
    H = H;break;
case 0xee: // *** mov h,l ***
    H = L;break;
case 0xef: // *** mov h,m ***
    MAHL();READ();H = MB;break;
case 0xf0: // *** mov l,a ***
    L = A;break;
case 0xf1: // *** mov l,b ***
    L = B;break;
case 0xf2: // *** mov l,c ***
    L = C;break;
case 0xf3: // *** mov l,d ***
    L = D;break;
case 0xf4: // *** mov l,e ***
    L = E;break;
case 0xf5: // *** mov l,h ***
    L = H;break;
case 0xf6: // *** mov l,l ***
    L = L;break;
case 0xf7: // *** mov l,m ***
    MAHL();READ();L = MB;break;
case 0xf8: // *** mov m,a ***
    MB=A;MAHL();WRITE();;break;
case 0xf9: // *** mov m,b ***
    MB=B;MAHL();WRITE();;break;
case 0xfa: // *** mov m,c ***
    MB=C;MAHL();WRITE();;break;
case 0xfb: // *** mov m,d ***
    MB=D;MAHL();WRITE();;break;
case 0xfc: // *** mov m,e ***
    MB=E;MAHL();WRITE();;break;
case 0xfd: // *** mov m,h ***
    MB=H;MAHL();WRITE();;break;
case 0xfe: // *** mov m,l ***
    MB=L;MAHL();WRITE();;break;
case 0xff: // *** hlt ***
    Halt = 1;break;

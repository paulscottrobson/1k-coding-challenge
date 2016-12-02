case 0x00: /***** idl *****/
    ;;
    break;

case 0x01: /***** ldn r1 *****/
    MA = R[1];READ();D = MB;
    break;

case 0x02: /***** ldn r2 *****/
    MA = R[2];READ();D = MB;
    break;

case 0x03: /***** ldn r3 *****/
    MA = R[3];READ();D = MB;
    break;

case 0x04: /***** ldn r4 *****/
    MA = R[4];READ();D = MB;
    break;

case 0x05: /***** ldn r5 *****/
    MA = R[5];READ();D = MB;
    break;

case 0x06: /***** ldn r6 *****/
    MA = R[6];READ();D = MB;
    break;

case 0x07: /***** ldn r7 *****/
    MA = R[7];READ();D = MB;
    break;

case 0x08: /***** ldn r8 *****/
    MA = R[8];READ();D = MB;
    break;

case 0x09: /***** ldn r9 *****/
    MA = R[9];READ();D = MB;
    break;

case 0x0a: /***** ldn ra *****/
    MA = R[10];READ();D = MB;
    break;

case 0x0b: /***** ldn rb *****/
    MA = R[11];READ();D = MB;
    break;

case 0x0c: /***** ldn rc *****/
    MA = R[12];READ();D = MB;
    break;

case 0x0d: /***** ldn rd *****/
    MA = R[13];READ();D = MB;
    break;

case 0x0e: /***** ldn re *****/
    MA = R[14];READ();D = MB;
    break;

case 0x0f: /***** ldn rf *****/
    MA = R[15];READ();D = MB;
    break;

case 0x10: /***** inc r0 *****/
    R[0]++;
    break;

case 0x11: /***** inc r1 *****/
    R[1]++;
    break;

case 0x12: /***** inc r2 *****/
    R[2]++;
    break;

case 0x13: /***** inc r3 *****/
    R[3]++;
    break;

case 0x14: /***** inc r4 *****/
    R[4]++;
    break;

case 0x15: /***** inc r5 *****/
    R[5]++;
    break;

case 0x16: /***** inc r6 *****/
    R[6]++;
    break;

case 0x17: /***** inc r7 *****/
    R[7]++;
    break;

case 0x18: /***** inc r8 *****/
    R[8]++;
    break;

case 0x19: /***** inc r9 *****/
    R[9]++;
    break;

case 0x1a: /***** inc ra *****/
    R[10]++;
    break;

case 0x1b: /***** inc rb *****/
    R[11]++;
    break;

case 0x1c: /***** inc rc *****/
    R[12]++;
    break;

case 0x1d: /***** inc rd *****/
    R[13]++;
    break;

case 0x1e: /***** inc re *****/
    R[14]++;
    break;

case 0x1f: /***** inc rf *****/
    R[15]++;
    break;

case 0x20: /***** dec r0 *****/
    R[0]--;
    break;

case 0x21: /***** dec r1 *****/
    R[1]--;
    break;

case 0x22: /***** dec r2 *****/
    R[2]--;
    break;

case 0x23: /***** dec r3 *****/
    R[3]--;
    break;

case 0x24: /***** dec r4 *****/
    R[4]--;
    break;

case 0x25: /***** dec r5 *****/
    R[5]--;
    break;

case 0x26: /***** dec r6 *****/
    R[6]--;
    break;

case 0x27: /***** dec r7 *****/
    R[7]--;
    break;

case 0x28: /***** dec r8 *****/
    R[8]--;
    break;

case 0x29: /***** dec r9 *****/
    R[9]--;
    break;

case 0x2a: /***** dec ra *****/
    R[10]--;
    break;

case 0x2b: /***** dec rb *****/
    R[11]--;
    break;

case 0x2c: /***** dec rc *****/
    R[12]--;
    break;

case 0x2d: /***** dec rd *****/
    R[13]--;
    break;

case 0x2e: /***** dec re *****/
    R[14]--;
    break;

case 0x2f: /***** dec rf *****/
    R[15]--;
    break;

case 0x30: /***** br $1 *****/
    FETCH();SBRANCH();;
    break;

case 0x31: /***** bq $1 *****/
    FETCH();if (Q != 0) SBRANCH();
    break;

case 0x32: /***** bz $1 *****/
    FETCH();if (D == 0) SBRANCH();
    break;

case 0x33: /***** bdf $1 *****/
    FETCH();if (DF != 0) SBRANCH();
    break;

case 0x34: /***** b1 $1 *****/
    FETCH();if (EFLAG1() != 0) SBRANCH();
    break;

case 0x35: /***** b2 $1 *****/
    FETCH();if (EFLAG2() != 0) SBRANCH();
    break;

case 0x36: /***** b3 $1 *****/
    FETCH();if (EFLAG3() != 0) SBRANCH();
    break;

case 0x37: /***** b4 $1 *****/
    FETCH();if (EFLAG4() != 0) SBRANCH();
    break;

case 0x38: /***** skp *****/
    R[P]++;
    break;

case 0x39: /***** bnq $1 *****/
    FETCH();if (Q == 0) SBRANCH();
    break;

case 0x3a: /***** bnz $1 *****/
    FETCH();if (D != 0) SBRANCH();
    break;

case 0x3b: /***** bnf $1 *****/
    FETCH();if (DF == 0) SBRANCH();
    break;

case 0x3c: /***** bn1 $1 *****/
    FETCH();if (EFLAG1() == 0) SBRANCH();
    break;

case 0x3d: /***** bn2 $1 *****/
    FETCH();if (EFLAG2() == 0) SBRANCH();
    break;

case 0x3e: /***** bn3 $1 *****/
    FETCH();if (EFLAG3() == 0) SBRANCH();
    break;

case 0x3f: /***** bn4 $1 *****/
    FETCH();if (EFLAG4() == 0) SBRANCH();
    break;

case 0x40: /***** lda r0 *****/
    MA = R[0];READ();D = MB;R[0]++;
    break;

case 0x41: /***** lda r1 *****/
    MA = R[1];READ();D = MB;R[1]++;
    break;

case 0x42: /***** lda r2 *****/
    MA = R[2];READ();D = MB;R[2]++;
    break;

case 0x43: /***** lda r3 *****/
    MA = R[3];READ();D = MB;R[3]++;
    break;

case 0x44: /***** lda r4 *****/
    MA = R[4];READ();D = MB;R[4]++;
    break;

case 0x45: /***** lda r5 *****/
    MA = R[5];READ();D = MB;R[5]++;
    break;

case 0x46: /***** lda r6 *****/
    MA = R[6];READ();D = MB;R[6]++;
    break;

case 0x47: /***** lda r7 *****/
    MA = R[7];READ();D = MB;R[7]++;
    break;

case 0x48: /***** lda r8 *****/
    MA = R[8];READ();D = MB;R[8]++;
    break;

case 0x49: /***** lda r9 *****/
    MA = R[9];READ();D = MB;R[9]++;
    break;

case 0x4a: /***** lda ra *****/
    MA = R[10];READ();D = MB;R[10]++;
    break;

case 0x4b: /***** lda rb *****/
    MA = R[11];READ();D = MB;R[11]++;
    break;

case 0x4c: /***** lda rc *****/
    MA = R[12];READ();D = MB;R[12]++;
    break;

case 0x4d: /***** lda rd *****/
    MA = R[13];READ();D = MB;R[13]++;
    break;

case 0x4e: /***** lda re *****/
    MA = R[14];READ();D = MB;R[14]++;
    break;

case 0x4f: /***** lda rf *****/
    MA = R[15];READ();D = MB;R[15]++;
    break;

case 0x50: /***** str r0 *****/
    MA = R[0];MB = D;WRITE();
    break;

case 0x51: /***** str r1 *****/
    MA = R[1];MB = D;WRITE();
    break;

case 0x52: /***** str r2 *****/
    MA = R[2];MB = D;WRITE();
    break;

case 0x53: /***** str r3 *****/
    MA = R[3];MB = D;WRITE();
    break;

case 0x54: /***** str r4 *****/
    MA = R[4];MB = D;WRITE();
    break;

case 0x55: /***** str r5 *****/
    MA = R[5];MB = D;WRITE();
    break;

case 0x56: /***** str r6 *****/
    MA = R[6];MB = D;WRITE();
    break;

case 0x57: /***** str r7 *****/
    MA = R[7];MB = D;WRITE();
    break;

case 0x58: /***** str r8 *****/
    MA = R[8];MB = D;WRITE();
    break;

case 0x59: /***** str r9 *****/
    MA = R[9];MB = D;WRITE();
    break;

case 0x5a: /***** str ra *****/
    MA = R[10];MB = D;WRITE();
    break;

case 0x5b: /***** str rb *****/
    MA = R[11];MB = D;WRITE();
    break;

case 0x5c: /***** str rc *****/
    MA = R[12];MB = D;WRITE();
    break;

case 0x5d: /***** str rd *****/
    MA = R[13];MB = D;WRITE();
    break;

case 0x5e: /***** str re *****/
    MA = R[14];MB = D;WRITE();
    break;

case 0x5f: /***** str rf *****/
    MA = R[15];MB = D;WRITE();
    break;

case 0x60: /***** irx *****/
    R[X]++;
    break;

case 0x61: /***** out 1 *****/
    MA = R[X];READ();OUTPORT1(MB);R[X]++;
    break;

case 0x62: /***** out 2 *****/
    MA = R[X];READ();OUTPORT2(MB);R[X]++;
    break;

case 0x63: /***** out 3 *****/
    MA = R[X];READ();OUTPORT3(MB);R[X]++;
    break;

case 0x64: /***** out 4 *****/
    MA = R[X];READ();OUTPORT4(MB);R[X]++;
    break;

case 0x65: /***** out 5 *****/
    MA = R[X];READ();OUTPORT5(MB);R[X]++;
    break;

case 0x66: /***** out 6 *****/
    MA = R[X];READ();OUTPORT6(MB);R[X]++;
    break;

case 0x67: /***** out 7 *****/
    MA = R[X];READ();OUTPORT7(MB);R[X]++;
    break;

case 0x68: /***** db 68 *****/
    ;;
    break;

case 0x69: /***** inp 1 *****/
    MB = D = INPORT1();MA = R[X];WRITE();;
    break;

case 0x6a: /***** inp 2 *****/
    MB = D = INPORT2();MA = R[X];WRITE();;
    break;

case 0x6b: /***** inp 3 *****/
    MB = D = INPORT3();MA = R[X];WRITE();;
    break;

case 0x6c: /***** inp 4 *****/
    MB = D = INPORT4();MA = R[X];WRITE();;
    break;

case 0x6d: /***** inp 5 *****/
    MB = D = INPORT5();MA = R[X];WRITE();;
    break;

case 0x6e: /***** inp 6 *****/
    MB = D = INPORT6();MA = R[X];WRITE();;
    break;

case 0x6f: /***** inp 7 *****/
    MB = D = INPORT7();MA = R[X];WRITE();;
    break;

case 0x70: /***** ret *****/
    __Return();IE = 1;
    break;

case 0x71: /***** dis *****/
    __Return();IE = 0;
    break;

case 0x72: /***** ldxa *****/
    MA = R[X];READ();D = MB;R[X]++;
    break;

case 0x73: /***** stxd *****/
    MA = R[X];MB = D;WRITE();R[X]--;
    break;

case 0x74: /***** adc *****/
    MA = R[X];READ();ADD(DF);
    break;

case 0x75: /***** sdb *****/
    MA = R[X];READ();SUB(MB,D,DF);
    break;

case 0x76: /***** rshr *****/
    temp16 = D | (DF << 8);DF = D & 1;D = temp16 >> 1;
    break;

case 0x77: /***** smb *****/
    MA = R[X];READ();SUB(D,MB,DF);
    break;

case 0x78: /***** sav *****/
    MA = R[X];MB = T;WRITE();;
    break;

case 0x79: /***** mark *****/
    __Mark();;
    break;

case 0x7a: /***** req *****/
    Q = 0;OUTPORT0(0);
    break;

case 0x7b: /***** seq *****/
    Q = 1;OUTPORT0(1);
    break;

case 0x7c: /***** adci $1 *****/
    FETCH();ADD(DF);
    break;

case 0x7d: /***** sdbi $1 *****/
    FETCH();SUB(MB,D,DF);
    break;

case 0x7e: /***** rshl *****/
    temp16 = (D << 1) | DF;D = temp16;DF = temp16 >> 8;
    break;

case 0x7f: /***** smbi $1 *****/
    FETCH();SUB(D,MB,DF);
    break;

case 0x80: /***** glo r0 *****/
    D = R[0];
    break;

case 0x81: /***** glo r1 *****/
    D = R[1];
    break;

case 0x82: /***** glo r2 *****/
    D = R[2];
    break;

case 0x83: /***** glo r3 *****/
    D = R[3];
    break;

case 0x84: /***** glo r4 *****/
    D = R[4];
    break;

case 0x85: /***** glo r5 *****/
    D = R[5];
    break;

case 0x86: /***** glo r6 *****/
    D = R[6];
    break;

case 0x87: /***** glo r7 *****/
    D = R[7];
    break;

case 0x88: /***** glo r8 *****/
    D = R[8];
    break;

case 0x89: /***** glo r9 *****/
    D = R[9];
    break;

case 0x8a: /***** glo ra *****/
    D = R[10];
    break;

case 0x8b: /***** glo rb *****/
    D = R[11];
    break;

case 0x8c: /***** glo rc *****/
    D = R[12];
    break;

case 0x8d: /***** glo rd *****/
    D = R[13];
    break;

case 0x8e: /***** glo re *****/
    D = R[14];
    break;

case 0x8f: /***** glo rf *****/
    D = R[15];
    break;

case 0x90: /***** ghi r0 *****/
    D = R[0] >> 8;
    break;

case 0x91: /***** ghi r1 *****/
    D = R[1] >> 8;
    break;

case 0x92: /***** ghi r2 *****/
    D = R[2] >> 8;
    break;

case 0x93: /***** ghi r3 *****/
    D = R[3] >> 8;
    break;

case 0x94: /***** ghi r4 *****/
    D = R[4] >> 8;
    break;

case 0x95: /***** ghi r5 *****/
    D = R[5] >> 8;
    break;

case 0x96: /***** ghi r6 *****/
    D = R[6] >> 8;
    break;

case 0x97: /***** ghi r7 *****/
    D = R[7] >> 8;
    break;

case 0x98: /***** ghi r8 *****/
    D = R[8] >> 8;
    break;

case 0x99: /***** ghi r9 *****/
    D = R[9] >> 8;
    break;

case 0x9a: /***** ghi ra *****/
    D = R[10] >> 8;
    break;

case 0x9b: /***** ghi rb *****/
    D = R[11] >> 8;
    break;

case 0x9c: /***** ghi rc *****/
    D = R[12] >> 8;
    break;

case 0x9d: /***** ghi rd *****/
    D = R[13] >> 8;
    break;

case 0x9e: /***** ghi re *****/
    D = R[14] >> 8;
    break;

case 0x9f: /***** ghi rf *****/
    D = R[15] >> 8;
    break;

case 0xa0: /***** plo r0 *****/
    R[0] = (R[0] & 0xFF00) | D;
    break;

case 0xa1: /***** plo r1 *****/
    R[1] = (R[1] & 0xFF00) | D;
    break;

case 0xa2: /***** plo r2 *****/
    R[2] = (R[2] & 0xFF00) | D;
    break;

case 0xa3: /***** plo r3 *****/
    R[3] = (R[3] & 0xFF00) | D;
    break;

case 0xa4: /***** plo r4 *****/
    R[4] = (R[4] & 0xFF00) | D;
    break;

case 0xa5: /***** plo r5 *****/
    R[5] = (R[5] & 0xFF00) | D;
    break;

case 0xa6: /***** plo r6 *****/
    R[6] = (R[6] & 0xFF00) | D;
    break;

case 0xa7: /***** plo r7 *****/
    R[7] = (R[7] & 0xFF00) | D;
    break;

case 0xa8: /***** plo r8 *****/
    R[8] = (R[8] & 0xFF00) | D;
    break;

case 0xa9: /***** plo r9 *****/
    R[9] = (R[9] & 0xFF00) | D;
    break;

case 0xaa: /***** plo ra *****/
    R[10] = (R[10] & 0xFF00) | D;
    break;

case 0xab: /***** plo rb *****/
    R[11] = (R[11] & 0xFF00) | D;
    break;

case 0xac: /***** plo rc *****/
    R[12] = (R[12] & 0xFF00) | D;
    break;

case 0xad: /***** plo rd *****/
    R[13] = (R[13] & 0xFF00) | D;
    break;

case 0xae: /***** plo re *****/
    R[14] = (R[14] & 0xFF00) | D;
    break;

case 0xaf: /***** plo rf *****/
    R[15] = (R[15] & 0xFF00) | D;
    break;

case 0xb0: /***** phi r0 *****/
    R[0] = (R[0] & 0x00FF) | (D << 8);
    break;

case 0xb1: /***** phi r1 *****/
    R[1] = (R[1] & 0x00FF) | (D << 8);
    break;

case 0xb2: /***** phi r2 *****/
    R[2] = (R[2] & 0x00FF) | (D << 8);
    break;

case 0xb3: /***** phi r3 *****/
    R[3] = (R[3] & 0x00FF) | (D << 8);
    break;

case 0xb4: /***** phi r4 *****/
    R[4] = (R[4] & 0x00FF) | (D << 8);
    break;

case 0xb5: /***** phi r5 *****/
    R[5] = (R[5] & 0x00FF) | (D << 8);
    break;

case 0xb6: /***** phi r6 *****/
    R[6] = (R[6] & 0x00FF) | (D << 8);
    break;

case 0xb7: /***** phi r7 *****/
    R[7] = (R[7] & 0x00FF) | (D << 8);
    break;

case 0xb8: /***** phi r8 *****/
    R[8] = (R[8] & 0x00FF) | (D << 8);
    break;

case 0xb9: /***** phi r9 *****/
    R[9] = (R[9] & 0x00FF) | (D << 8);
    break;

case 0xba: /***** phi ra *****/
    R[10] = (R[10] & 0x00FF) | (D << 8);
    break;

case 0xbb: /***** phi rb *****/
    R[11] = (R[11] & 0x00FF) | (D << 8);
    break;

case 0xbc: /***** phi rc *****/
    R[12] = (R[12] & 0x00FF) | (D << 8);
    break;

case 0xbd: /***** phi rd *****/
    R[13] = (R[13] & 0x00FF) | (D << 8);
    break;

case 0xbe: /***** phi re *****/
    R[14] = (R[14] & 0x00FF) | (D << 8);
    break;

case 0xbf: /***** phi rf *****/
    R[15] = (R[15] & 0x00FF) | (D << 8);
    break;

case 0xc0: /***** lbr $2 *****/
    FETCH2();LBRANCH();;
    break;

case 0xc1: /***** lbq $2 *****/
    FETCH2();if (Q != 0) LBRANCH();
    break;

case 0xc2: /***** lbz $2 *****/
    FETCH2();if (D == 0) LBRANCH();
    break;

case 0xc3: /***** lbdf $2 *****/
    FETCH2();if (DF != 0) LBRANCH();
    break;

case 0xc4: /***** nop *****/
    Cycles--;
    break;

case 0xc5: /***** lsnq *****/
    Cycles--;if (Q == 0) LSKIP();
    break;

case 0xc6: /***** lsnz *****/
    Cycles--;if (D != 0) LSKIP();
    break;

case 0xc7: /***** lsnf *****/
    Cycles--;if (DF == 0) LSKIP();
    break;

case 0xc8: /***** lskp *****/
    Cycles--;LSKIP();;
    break;

case 0xc9: /***** lbnq $2 *****/
    FETCH2();if (Q == 0) LBRANCH();
    break;

case 0xca: /***** lbnz $2 *****/
    FETCH2();if (D != 0) LBRANCH();
    break;

case 0xcb: /***** lbnf $2 *****/
    FETCH2();if (DF == 0) LBRANCH();
    break;

case 0xcc: /***** lsie *****/
    Cycles--;if (IE != 0) LSKIP();
    break;

case 0xcd: /***** lsq *****/
    Cycles--;if (Q != 0) LSKIP();
    break;

case 0xce: /***** lsz *****/
    Cycles--;if (D == 0) LSKIP();
    break;

case 0xcf: /***** lsdf *****/
    Cycles--;if (DF != 0) LSKIP();
    break;

case 0xd0: /***** sep r0 *****/
    P = 0;
    break;

case 0xd1: /***** sep r1 *****/
    P = 1;
    break;

case 0xd2: /***** sep r2 *****/
    P = 2;
    break;

case 0xd3: /***** sep r3 *****/
    P = 3;
    break;

case 0xd4: /***** sep r4 *****/
    P = 4;
    break;

case 0xd5: /***** sep r5 *****/
    P = 5;
    break;

case 0xd6: /***** sep r6 *****/
    P = 6;
    break;

case 0xd7: /***** sep r7 *****/
    P = 7;
    break;

case 0xd8: /***** sep r8 *****/
    P = 8;
    break;

case 0xd9: /***** sep r9 *****/
    P = 9;
    break;

case 0xda: /***** sep ra *****/
    P = 10;
    break;

case 0xdb: /***** sep rb *****/
    P = 11;
    break;

case 0xdc: /***** sep rc *****/
    P = 12;
    break;

case 0xdd: /***** sep rd *****/
    P = 13;
    break;

case 0xde: /***** sep re *****/
    P = 14;
    break;

case 0xdf: /***** sep rf *****/
    P = 15;
    break;

case 0xe0: /***** sex r0 *****/
    X = 0;
    break;

case 0xe1: /***** sex r1 *****/
    X = 1;
    break;

case 0xe2: /***** sex r2 *****/
    X = 2;
    break;

case 0xe3: /***** sex r3 *****/
    X = 3;
    break;

case 0xe4: /***** sex r4 *****/
    X = 4;
    break;

case 0xe5: /***** sex r5 *****/
    X = 5;
    break;

case 0xe6: /***** sex r6 *****/
    X = 6;
    break;

case 0xe7: /***** sex r7 *****/
    X = 7;
    break;

case 0xe8: /***** sex r8 *****/
    X = 8;
    break;

case 0xe9: /***** sex r9 *****/
    X = 9;
    break;

case 0xea: /***** sex ra *****/
    X = 10;
    break;

case 0xeb: /***** sex rb *****/
    X = 11;
    break;

case 0xec: /***** sex rc *****/
    X = 12;
    break;

case 0xed: /***** sex rd *****/
    X = 13;
    break;

case 0xee: /***** sex re *****/
    X = 14;
    break;

case 0xef: /***** sex rf *****/
    X = 15;
    break;

case 0xf0: /***** ldx *****/
    MA = R[X];READ();D = MB;
    break;

case 0xf1: /***** or *****/
    MA = R[X];READ();D |= MB;
    break;

case 0xf2: /***** and *****/
    MA = R[X];READ();D &= MB;
    break;

case 0xf3: /***** xor *****/
    MA = R[X];READ();D ^= MB;
    break;

case 0xf4: /***** add *****/
    MA = R[X];READ();ADD(0);
    break;

case 0xf5: /***** sd *****/
    MA = R[X];READ();SUB(MB,D,1);
    break;

case 0xf6: /***** shr *****/
    DF = D & 1;D = (D >> 1) & 0x7F;
    break;

case 0xf7: /***** sm *****/
    MA = R[X];READ();SUB(D,MB,1);
    break;

case 0xf8: /***** ldi $1 *****/
    FETCH();D = MB;
    break;

case 0xf9: /***** ori $1 *****/
    FETCH();D |= MB;
    break;

case 0xfa: /***** ani $1 *****/
    FETCH();D &= MB;
    break;

case 0xfb: /***** xri $1 *****/
    FETCH();D ^= MB;
    break;

case 0xfc: /***** adi $1 *****/
    FETCH();ADD(0);
    break;

case 0xfd: /***** sdi $1 *****/
    FETCH();SUB(MB,D,1);
    break;

case 0xfe: /***** shl *****/
    DF = (D >> 7) & 1;D = D << 1;
    break;

case 0xff: /***** smi $1 *****/
    FETCH();SUB(D,MB,1);
    break;


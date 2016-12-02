static BYTE8  D,DF,MB,Q,IE,P,X,T;
static WORD16 R[16],Cycles,temp16,MA;
static void __1802Reset(void) {
 Q = 0;IE = 1;X = 0;P = 0;R[0] = 0;
 DF &= 1;
 OUTPORT0(0);
}
#define FETCH()   MA = R[P]++;READ()
#define ADD(c) temp16 = D + MB + (c);D = temp16;DF = (temp16 >> 8) & 1
#define SUB(a,b,c) temp16 = (a) + ((b)^0xFF) + (c);D = temp16;DF = (temp16 >> 8) & 1
#define SBRANCH()   { R[P] = (R[P] & 0xFF00) | MB; }
#define FETCH2()  { FETCH();temp16 = (MB << 8);FETCH();temp16 |= MB; Cycles--; }
#define LBRANCH()   { R[P] = temp16; }
#define LSKIP()   { R[P] = R[P] + 2; }
static void inline __Mark(void) {
 T = (X << 4) | P;
 MB = T;MA = R[2];WRITE();
 X = P;
 R[2]--;
}
static void inline __Return(void) {
 MA = R[X];READ();
 R[X]++;
 X = (MB >> 4);P = (MB & 0x0F);
}
static void __1802Interrupt(void) {
 if (IE != 0) {
  T = (X << 4) | P;
  P = 1;X = 2;
  IE = 0;
 }
}
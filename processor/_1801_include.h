#define ADD(v)  { temp16 = D + (v);D = temp16;DF = temp16 >> 8; }
#define SUB(a,b) { temp16 = (a) + ((b)^0xFF) + 1;D = temp16;DF = temp16 >> 8; }
#define FETCHBR() temp8 = FETCH();
#define BRANCH()  { R[P] = (R[P] & 0xFF00) | temp8; }
static void _1801Interrupt() {
 if (READ(R[P]) == 0) R[P]++;
 T = (X << 4) | P;
 P = 1;
 X = 2;
 IE = 0;
}
#define RETURN() { temp8 = READ(R[X]);R[X]++;X = temp8 >> 4;P = temp8 & 0x0F; }
static void _1801Reset() {
 P = 0;R[0] = 0;IE = 1;
 DF &= 1;
}
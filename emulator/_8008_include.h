static BYTE8      A,B,C,D,E,H,L,MB,PCIX,Carry,pszValue,Halt;
static WORD16      PC[8],MA,Cycles,temp16;
#define MAHL()     { MA = ((WORD16)(H << 8))|L; }
#define FETCH()     { MB = PC[PCIX];PC[PCIX] = (PC[PCIX]+1) & 0x3FFF;READ(); }
#define ADD(a,b)   temp16 = A+(a)+(b);pszValue = temp16;Carry = (temp16 >> 8) & 1
#define SUB(a,b)   temp16 = A-(a)-(b);pszValue = temp16;Carry = (temp16 >> 8) & 1
#define FETCH16()   { FETCH();temp16 = MB;FETCH();temp16 |= (MB << 8); }
#define BRANCH()   { PCTR[PCIX] = temp16 & 0x3FFF; }
#define CALL()   { PCIX = (PCIX+1) & 7;BRANCH(); }
#define RETURN()   { PCIX = (PCIX-1) & 7; }
static BYTE8 isEvenParity(void) {
 BYTE8 n = 0;
 BYTE8 v = pszValue;
 while (v != 0) {
  if ((v & 1) != 0) n++;
  v = v >> 1;
 }
 return (n & 1) == 0;
}
static void __8008Reset(void) {
 for (A = 0;A < 8;A++) PCTR[A] = 0;
 A = B = C = D = E = H = L = Carry = pszValue = Halt = PCIX = 0;
 Cycles = 0;
}
asl -L test.asm
p2bin -r 0-2047 -l 0 test.p
rm test.p
dist/Debug/GNU-Linux/emulator test.bin
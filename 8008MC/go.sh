asl -L test.asm

p2bin -r 0-2048 -l 0 test.p
rm test.p
dist/Debug/GNU-Linux/8008mc test.bin
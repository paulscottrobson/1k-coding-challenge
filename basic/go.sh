asl -L basic.asm
p2bin -r 0-2048 -l 0 basic.p
rm basic.p
../8008MC/dist/Debug/GNU-Linux/8008mc basic.bin

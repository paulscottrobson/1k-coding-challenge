#
#	Definition File Processor
#
import re

def process(s,opcode):
	s = s.replace("@F",str((opcode & 3)+1))
	s = s.replace("@X","{0:X}".format(opcode & 15))
	s = s.replace("@P",str(opcode & 7))
	s = s.replace("@R",str(opcode & 15))
	return s

mnemonics = [ None ] * 256
code = [ None ] * 256

lines = open("1802.def").readlines()														# read definition file.
lines = [x if x.find("//") < 0 else x[:x.find("//")] for x in lines]						# remove comments.
lines = [x.replace("\t"," ").strip() for x in lines]										# strip and remove spaces
lines = [x for x in lines if x != ""]														# remove empty lines.

open("__1802support.h","w").write("\n".join(x[1:] for x in lines if x[0] == ':'))			# output C
lines = [x for x in lines if x[0] != ":"]													# then remove it.

for l in lines:
	match = re.match("^([0-9A-F\-]+)\s+\"(.*?)\"\s+(.*)$",l)								# split up.
	assert(match is not None)
	oStart = oEnd = int(match.group(1)[:2],16)												# range of opcodes
	if len(match.group(1)) == 5:
		oEnd = int(match.group(1)[-2:],16)
	for opcode in range(oStart,oEnd+1):
		assert mnemonics[opcode] is None
		mnemonics[opcode] = process(match.group(2),opcode).lower()
		code[opcode] = process(match.group(3),opcode)
																							# Dump mnemonics
open("__1802mnemonics.h","w").write(",".join([('"'+x+'"').lower() for x in mnemonics]))

handle = open("__1802opcodes.h","w")
for i in range(0,256):
	handle.write("case 0x{0:02x}: /***** {1} *****/\n".format(i,mnemonics[i]))
	handle.write("    {0};\n".format(code[i]))
	handle.write("    break;\n\n")

handle = open("__1802ports.h","w")
for i in range(0,8):
	if i > 0:
		handle.write("#ifndef INPORT{0}\n".format(i))
		handle.write("#define INPORT{0}() (DEFAULT_BUS_VALUE)\n".format(i))
		handle.write("#endif\n")
	handle.write("#ifndef OUTPORT{0}\n".format(i))
	handle.write("#define OUTPORT{0}(n) {{}}\n".format(i))
	handle.write("#endif\n")
for i in range(1,5):
	handle.write("#ifndef EFLAG{0}\n".format(i))
	handle.write("#define EFLAG{0}() (0)\n".format(i))
	handle.write("#endif\n")

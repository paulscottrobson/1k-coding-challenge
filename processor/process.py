#
#		Process 1801.def into C include files.
#
import re

def process(txt,opc):
	txt = txt.replace("@H","{0:x}".format(opc & 15))
	txt = txt.replace("@R","{0}".format(opc & 15))
	txt = txt.replace("@F","{0:x}".format((opc & 3)+1))
	txt = txt.replace("@P","{0:x}".format((opc & 3)+1))
	return txt

src = open("1801.def","r").readlines()													# read file
src = [x if x.find("//") < 0 else x[:x.find("//")] for x in src]						# delete comments
src = [x.replace("\t"," ").strip() for x in src]										# spaces and tabs
src = [x for x in src if x != ""]														# remove blank lines

open("_1801_include.h","w").write("\n".join([x[1:] for x in src if x[0] == ':']))

mnemonics = [ None ] * 256																# mnemonics
codes = [ None ] * 256																	# executable codes.
for l in [x for x in src if x[0] != ':']:												# for each line.
	m = re.match('^([0-9A-F\\-]+)\\s*\\"(.*)\\"\s*(.*)$',l)								# check it
	assert m is not None,"Error "+l
	rg = m.group(1)
	if len(rg) == 2:																	# get from/to range
		rg = rg + "-"+rg
	for opcode in range(int(rg[:2],16),int(rg[-2:],16)+1):								# for each opcode
		assert mnemonics[opcode] is None
		mnemonics[opcode] = process(m.group(2),opcode-int(rg[:2],16)).lower()
		codes[opcode] = process(m.group(3),opcode-int(rg[:2],16))

for i in range(0,256):																	# fill in mnemonics
	if mnemonics[i] is None:
		mnemonics[i] = "byte {0:02x}".format(i)

open("_1801_disasm.h","w").write(",".join(['"'+m+'"' for m in mnemonics]))				# write out disassembly table

h = open("_1801_opcodes.h","w")
for i in range(0,256):
	if codes[i] is not None:
		h.write("case 0x{0:02x}: // *** {1} ***\n".format(i,mnemonics[i]))
		h.write("    {0};break;\n".format(codes[i]))

h = open("_1801_ports.h","w")
for i in range(0,8):
	h.write("#ifndef INPORT{0}\n".format(i))
	h.write("#define INPORT{0}() (0)\n".format(i))
	h.write("#endif\n")
	h.write("#ifndef OUTPORT{0}\n".format(i))
	h.write("#define OUTPORT{0}(v) {{}}\n".format(i))
	h.write("#endif\n")
for i in range(1,5):
	h.write("#ifndef EFLAG{0}\n".format(i))
	h.write("#define EFLAG{0}() (0)\n".format(i))
	h.write("#endif\n")
h.close()
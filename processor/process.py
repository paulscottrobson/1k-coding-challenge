#
#		Process 8008.def into C include files.
#
import re

def process(txt,ofst,opc):
	txt = txt.replace("@R","ABCDEHLM"[ofst & 7])
	txt = txt.replace("@C",["NC","NZ","P","PO","C","Z","M","PE"][ofst & 7])
	t = [ "Carry==0","pszValue != 0","(pszValue & 0x80) == 0","isEvenParity() == 0", \
		  "Carry!=0","pszValue == 0","(pszValue & 0x80) != 0","isEvenParity() != 0"]
	txt = txt.replace("@T",t[ofst & 7])		
	txt = txt.replace("@P","{0:02X}".format((opc >> 1) & 0x1F))
	txt = txt.replace("@X","{0:02X}".format(opc & 0x38))
	return txt

src = open("8008.def","r").readlines()													# read file
src = [x if x.find("//") < 0 else x[:x.find("//")] for x in src]						# delete comments
src = [x.replace("\t"," ").strip() for x in src]										# spaces and tabs
src = [x for x in src if x != ""]														# remove blank lines

open("_8008_include.h","w").write("\n".join([x[1:] for x in src if x[0] == ':']))

mnemonics = [ None ] * 256																# mnemonics
codes = [ None ] * 256																	# executable codes.

for l in [x for x in src if x[0] != ':']:												# for each line.
	m = re.match('^([0-9A-F\\-\\,]+)\\s*(\\d+)\\s*\\"(.*)\\"\s*(.*)$',l)							# check it
	assert m is not None,"Error "+l
	rg = m.group(1)
	if len(rg) == 2:																	# get from/to range
		rg = rg + "-"+rg
	if len(rg) == 5:
		rg = rg + ",1"
	step = int(rg[-1])
	for opcode in range(int(rg[:2],16),int(rg[3:5],16)+1,step):							# for each opcode
		assert mnemonics[opcode] is None
		offset = int(opcode/step)
		mnemonics[opcode] = process(m.group(3),offset,opcode).lower()
		codes[opcode] = process(m.group(4),offset,opcode)

for i in range(0,256):																	# fill in mnemonics
	if mnemonics[i] is None:
		mnemonics[i] = "byte {0:02x}".format(i)

open("_8008_disasm.h","w").write(",".join(['"'+m+'"' for m in mnemonics]))				# write out disassembly table

h = open("_8008_opcodes.h","w")
for i in range(0,256):
	if codes[i] is not None:
		h.write("case 0x{0:02x}: // *** {1} ***\n".format(i,mnemonics[i]))
		h.write("    {0};break;\n".format(codes[i]))

h = open("_8008_ports.h","w")
for i in range(0,8):
	h.write("#ifndef INPORT{0:02X}\n".format(i))
	h.write("#define INPORT{0:02X}() (0)\n".format(i))
	h.write("#endif\n")
for i in range(8,32):
	h.write("#ifndef OUTPORT{0:02X}\n".format(i))
	h.write("#define OUTPORT{0:02X}(v) {{}}\n".format(i))
	h.write("#endif\n")
h.close()
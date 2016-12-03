# *******************************************************************************************************************************
# *******************************************************************************************************************************
#
#		Name:		sys_debug_system.h
#		Purpose:	Debugger Code (System Dependent) Header
#		Created:	3rd December 2016
#		Author:		Paul Robson (paul@robsons.org.uk)
#
# *******************************************************************************************************************************
# *******************************************************************************************************************************

import re

def process(s,opcode):
	s = s.replace("%S","ABCDEHLM"[opcode % 8])
	s = s.replace("%D","ABCDEHLM"[int(opcode/8) % 8])
	s = s.replace("%P","{0:02X}".format(int(opcode / 2) % 32))
	s = s.replace("%R","{0:02X}".format(opcode & 0o070))
	s = s.replace("%MAHL","MA = (H << 8)|L")
	s = s.replace("%C",["NC","NZ","P","PO","C","Z","M","PE"][int(opcode / 8) % 8])
	s = s.replace("%T",["carry == 0","pszValue != 0","(pszValue & 0x80) == 0","_IsParityEven(pszValue) == 0","carry != 0","pszValue == 0","(pszValue & 0x80) != 0","_IsParityEven(pszValue) != 0"][int(opcode / 8) % 8])
	return s

source = open("8008.def").readlines()
source = [x.strip() if x.find("//") < 0 else x[:x.find("//")].strip() for x in source]
source = [x.replace("\t"," ") for x in source if x != ""]

mnemonics = [ None ] * 256
code = [ None ] * 256

for l in source:
	#print(l)
	m = re.match("^([0-9A-F\-\,]+)\s*\"([A-Z\s\@12\%\,]+)\"\s*([0-9]+)\s*(.*)$",l)
	assert m is not None

	m2 = re.match("^([0-9A-F\-]+)(.*)$",m.group(1))
	assert m2 is not None 
	step = 1 if m2.group(2) == "" else int(m2.group(2)[-1])
	m2 = re.match("^([0-9A-F]+)\-([0-9A-F]+)",m2.group(1)+"-"+m2.group(1))
	assert m2 is not None

	opcode = int(m2.group(1),16)
	lastOpcode = int(m2.group(2),16)
	assert (lastOpcode - opcode) % step == 0

	while opcode <= lastOpcode:
		assert mnemonics[opcode] is None
		mnemonics[opcode] = process(m.group(2),opcode)
		code[opcode] = process(m.group(4),opcode)+";CYCLES("+m.group(3)+");break;"
		opcode += step

for i in range(0,256):
	if mnemonics[i] == None:
		mnemonics[i] = "db {0:02x}".format(i)

open("__8008_mnemonics.h","w").write(",".join('"'+x.lower()+'"' for x in mnemonics))

ports = [(("INPORT" if r < 8 else "OUTPORT")+"{0:02X}").format(r) for r in range(0,32)]
ports = ["#ifndef {0}\n#define {0}() {{}}\n#endif".format(p.upper()) for p in ports]
open("__8008_ports.h","w").write("\n".join(ports))

handle = open("__8008_opcodes.h","w")
for i in range(0,256):
	if code[i] is not None:
		handle.write("case 0x{0:02x}: /**** {1} ****/\n".format(i,mnemonics[i]))
		fcode = code[i].replace(";",";#").split("#")
		fcode = ["    "+x for x in fcode if x != "" and x != ";"]
		handle.write("\n".join(fcode)+"\n");

print("8008 core built.")

import Image,ImageDraw
im = Image.open("font.tiff")
draw = ImageDraw.Draw(im)
print(im.size)
font = [ 0 ] * (128*9)
for ch in range(0,128):
	xc = ch % 16
	yc = ch / 16
	x = xc * (88*4+3)/4 + 9 - yc * 38 / 100
	y = yc * 215 / 2 + 10 + xc / 5

	for xp in range(0,7):
		for yp in range(0,9):
			x2 = x + xp * 10
			y2 = y + yp * 11
			count = 0
			for x3 in range(0,8):
				for y3 in range(0,8):
					c = im.getpixel((x2+x3,y2+y3))
					c = (c[0]+c[1]+c[2])/3
					if c > 128:
						count = count + 1

			s = 1
			on = count < 45
			on = on or (ch == 0 and xp == 6 and yp == 8)
			on = on or (ch == 6 and xp == 5 and yp == 7)
			on = on or (ch == 13 and xp == 5 and yp == 7)
			on = on or (ch == 70 and xp == 0 and yp == 8)
			on = on or (ch == ord('M') and xp == 6 and yp >= 3)
			on = on or (ch == ord('O') and xp >= 2 and xp <= 4 and yp == 8)
			on = on or (ch == 95 and yp == 8)
			on = on or (ch == ord('m') and xp == 6 and yp >= 3)
			on = on or (ch == ord('o') and xp >= 1 and xp <= 4 and yp == 8)
			on = on or (ch == ord('o') and xp == 0 and yp == 7)

			off = (ch == 23 and yp < 3)
			off = off or (ch == 52 and xp == 4 and (yp == 2 or yp == 3))
			off = off or (ch == 54 and xp == 3 and (yp == 2 or yp == 1))
			off = off or (ch == 55 and yp == 2 and xp == 3)
			off = off or (ch == 38 and yp == 1 and xp == 3)
			off = off or (ch == 56 and yp == 2 and xp == 3)
			off = off or (ch == 67 and xp == 5 and yp == 3)
			off = off or (ch == 68 and xp == 4 and yp == 3)
			off = off or (ch == ord('H') and xp == 5 and yp == 3)
			off = off or (ch == ord('Q') and xp == 3 and yp == 3)
			off = off or (ch == ord('W') and xp == 5 and yp == 4)
			off = off or (ch == ord('Y') and xp == 4 and yp == 4)
			off = off or (ch == 95 and yp == 0)
			off = off or (ch == ord('e') and yp <= 2)
			off = off or (ch == ord('g') and xp == 6 and yp == 2)
			off = off or (ch == ord('j') and xp == 4 and yp == 1)
			off = off or (ch == ord('m') and yp <= 2)
			off = off or (ch == ord('m') and xp == 6 and yp == 3)
			off = off or (ch == ord('u') and xp == 4 and yp == 5)

			if on and (not off):
				draw.rectangle((x2,y2,x2+10-s,y2+11-s),fill = (128,0,0))
				font[ch * 9 + yp] = font[ch * 9 + yp] + (128 >> xp)
			else:
				draw.rectangle((x2,y2,x2+10-s,y2+11-s),fill = (0,255,255))



#im.show()
font = [str(x) for x in font]
code = ",".join(font)
code = "static BYTE8 _mcm6571font[] = { " + code + "};"
h = open("mcmfont.h","w")
h.write(code+"\n")
h.close()

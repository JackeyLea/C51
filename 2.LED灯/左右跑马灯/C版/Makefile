file = horse#文件名，需要在make时指定

all:
	sdcc $(file).c #编译
	packihx $(file).ihx > $(file).hex #格式转换
	makebin -p $(file).hex > $(file).bin #格式转换
	rm -rf *.asm *.lst *.mem *.rst *.lnk *.rel *.sym *.ihx *.hex *.map *.lk #清理文件
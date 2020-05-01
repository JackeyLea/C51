file = led#文件名，需要在make时指定

all:
	sdcc $(file).c #编译
	packihx $(file).ihx > $(file).hex #格式转换
	makebin -p $(file).hex > $(file).bin #格式转换

clean:
	rm -rf *.asm *.lst *.mem *.rst *.lnk *.rel *.sym *.ihx *.hex *.map *.lk *.bin #清理文件
CC = cl
L = link
CFLAGS = /c /W3 /nologo /Iparser/

all: mini-shell.exe

mini-shell.exe: mini-shell.obj parser/parser.tab.obj parser/parser.yy.obj
	$(L) /nologo $**

mini-shell.obj: mini-shell.c utils.h
	$(CC) $(CFLAGS) mini-shell.c 

parser/parser.tab.obj parser/parser.yy.obj:
	cd parser && nmake -f Makefile

.IGNORE:
clean:
	del /Q /S /F *.obj mini-shell.exe

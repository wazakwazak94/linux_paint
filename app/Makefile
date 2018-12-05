CC = gcc
APP = linux_paint
LIB = -L../lib -lpainter
HEADER = -I../include
GTKFLAGS = `pkg-config --cflags gtk+-3.0`
GTKLIBS = `pkg-config --libs gtk+-3.0`
CFLAGS = -g -Wall
.PHONY = all clean

all: ${APP}

${APP}: main.c
	gcc ${GTKFLAGS} -o $@ $< ${CFLAGS} ${LIB} ${HEADER} ${GTKLIBS}

clean:
	rm ${APP}
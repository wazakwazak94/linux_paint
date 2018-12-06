CC = gcc
GTKFLAGS = `pkg-config --cflags gtk+-3.0`
GTKLIBS = `pkg-config --libs gtk+-3.0`
CFLAGS = -g -Wall
HEADER = -I../include
OBJS = 	activate.o	\
		brush.o 	\
		thickness.o \
		erase.o		\
		flood.o		\
		save.o		\
		open.o		
				
.PHONY = all clean

all: ${OBJS}

%.o: %.c
	gcc ${GTKFLAGS} -o $@ $< ${CLFAGS} -c ${HEADER} ${GTKLIBS}

clean:
	rm ${OBJS}

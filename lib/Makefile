LIBS = libpainter.a
DIRS = ../src
OBJS = ${DIRS}/activate.o ${DIRS}/brush.o ${DIRS}/thickness.o ${DIRS}/erase.o
.PHONY = all clean

all: ${LIBS}

${LIBS}: ${OBJS}
	ar rv $@ ${OBJS} 

clean:
	rm ${LIBS}
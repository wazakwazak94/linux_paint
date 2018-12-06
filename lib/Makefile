LIBS = libpainter.a
DIRS = ../src
OBJS = ${DIRS}/activate.o	\
	   ${DIRS}/brush.o 		\
	   ${DIRS}/thickness.o 	\
	   ${DIRS}/erase.o 		\
	   ${DIRS}/flood.o 		\
	   ${DIRS}/open.o 		\
	   ${DIRS}/save.o
	   
.PHONY = all clean

all: ${LIBS}

${LIBS}: ${OBJS}
	ar rv $@ ${OBJS} 

clean:
	rm ${LIBS}

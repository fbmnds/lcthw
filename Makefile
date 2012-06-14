CFLAGS=-Wall -g -std=c99 #-pedantic
CC=llvm-gcc

#all: clean ex1 ex3 ex7 ex8 ex10 ex11 ex13 ex15 ex16 ex17 ex18
all: clean dbg.h ex18

#ex13: clean ex13.c

ex16: ex16.c ex16-lib.c ex16.h

ex17: ex17.c ex17-lib.c ex17-run.c ex17.h

ex18: ex18.c

clean:
	rm ex? || rm ex?? || echo
#	touch *.c
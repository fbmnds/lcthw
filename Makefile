CFLAGS=-Wall -g -std=c99 #-pedantic
CC=llvm-gcc

#all: clean ex1 ex3 ex7 ex8 ex10 ex11 ex13 ex15 ex16 ex17 ex18 ex19 ex22 ex24
all: clean dbg.h ex24

#ex13: clean ex13.c

ex16: ex16.c ex16-lib.c ex16.h

ex17: ex17.c ex17-lib.c ex17-run.c ex17.h

ex18: ex18.c

ex19: ex19.c ex19-obj.c ex19-obj.h ex19.h

ex22: ex22.c ex22-main.c ex22.h

ex24: ex24.c

clean:
	@echo "FIXME rm ex? -f || rm -f ex?? || rm -rf *.dSYM || echo"
	@echo "FIXME do not remove directory 'ex29'"
#	touch *.c

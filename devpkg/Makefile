DESTDIR=
PREFIX=/usr/local
INCLUDES=-I${PREFIX}/apr/include/apr-1/  -I${PREFIX}/include/apr-1/
CFLAGS=-Wall -g -std=c99 ${INCLUDES} #-pedantic
LDFLAGS=-L${PREFIX}/apr/lib -lapr-1 -pthread -laprutil-1
CC=llvm-gcc

#all: clean ex1 ex3 ex7 ex8 ex10 ex11 ex13 ex15 ex16 ex17 ex18 ex19 ex22 ex24
all: clean devpkg

devpkg: bstrlib.o db.o shell.o commands.o

install: all 
	install -d $(DESTDIR)/$(PREFIX)/bin/ 
	install devpkg $(DESTDIR)/$(PREFIX)/bin/

beautify:
	astyle -A2 *.[ch]
clean:
	rm -rf *.dSYM
	rm -f *.o
	rm -f devpkg
#	touch *.c

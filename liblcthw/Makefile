CFLAGS=-std=c99 -g -O2 -Wall -Wextra -Isrc -Itests -Lbuild -DNDEBUG $(OPTFLAGS)
LIBS=-ldl $(OPTLIBS)
PREFIX?=/usr/local
SHELL=/bin/sh

SOURCES=$(wildcard src/**/*.c src/*.c)
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))

TEST_SRC=$(wildcard tests/**/*_tests.c tests/*_tests.c)
TESTS=$(patsubst %.c,%,$(TEST_SRC))
LOGS=$(wildcard tests/**/*.log tests/*.log)

TARGET=build/liblcthw.a
SO_TARGET=$(patsubst %.a,%.so,$(TARGET))

# the target build:
all: clean $(TARGET) $(SO_TARGET) tests

dev:CFLAGS=-std=c99 -g -Wall -Wextra -Isrc -Itests -Lbuild $(OPTFLAGS)
dev: all

ifneq ($(shell echo $(OSTYPE)),cygwin)
$(TARGET): CFLAGS += -fPIC
endif
$(TARGET): build $(OBJECTS)
	ar rcs $@ $(OBJECTS)
	ranlib $@

$(SO_TARGET): $(TARGET) $(OBJECTS)
	$(CC) -shared -o $@ $(OBJECTS)

build:
	@mkdir -p build
	@mkdir -p bin

# the unit tests:
.PHONY: tests
tests: CFLAGS += $(SO_TARGET) 
tests: $(TESTS)
	@echo
	sh ./tests/runtests.sh

valgrind:
	VALGRIND="valgrind --log-file=./tests/valgrind-%p.log " $(MAKE)

#the cleaner:
clean:
	rm -rf build $(OBJECTS) $(TESTS)
	rm -f $(LOGS)
	find . -name "*.gc*" -exec rm {} \; || echo
	rm -rf `find . -name "*.dSYM" -print`
	rm -rf `find . -name "*~" -print`
	rm -rf `find . -name "*dump" -print`
	gtags

#the install:
install: all
	install -d $(DESTDIR)/$(PREFIX)/lib/
	install $(TARGET) $(DESTDIR)/$(PREFIX)/lib

#the checker:
BADFUNCS='[^_.>a-zA-Z0-9](str(n?cpy|n?cat|xfrm|n?dup|str|pbrk|tok|_)|stpn?cpy|a?sn?printf))'
check:
ifeq ($(strip $(SOURCES)),)
	@echo No sources files to check.
else
	@echo Files with potentially dangerous functions:
	@egrep $(BADFUNCS) $(SOURCES) || true
	@echo "(check for dangerous functions done.)"
endif

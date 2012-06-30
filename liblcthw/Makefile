CFLAGS=-std=c89 -g -O2 -Wall -Wextra -Isrc -DNDEBUG $(OPTFLAGS)
LIBS=-ldl $(OPTLIBS)
PREFIX?=/usr/local

SOURCES=$(wildcard src/**/*.c src/*.c)
OBJECTS=$(patsubst %.c,%.o,$(SOURCES))

TEST_SRC=$(wildcard tests/**/*_tests.c tests/*_tests.c)
TESTS=$(patsubst %.c,%,$(TEST_SRC))
LOGS=$(wildcard tests/**/*.log tests/*.log)

TARGET=build/liblcthw.a
SO_TARGET=$(patsubst %.a,%.so,$(TARGET))

# the target build:
all: clean $(TARGET) $(SO_TARGET) tests

dev:CFLAGS=-std=c89 -g -Wall -Wextra -Isrc $(OPTFLAGS)
dev: all

$(TARGET): CFLAGS += -fPIC
$(TARGET): build $(OBJECTS)
	ar -rS $@ $(OBJECTS)
	ranlib $@

$(SO_TARGET): $(TARGET) $(OBJECTS)
	$(CC) -shared -o $@ $(OBJECTS)

build:
	@mkdir -p build
	@mkdir -p bin

# the unit tests:
.PHONY: tests
tests: CFLAGS += $(TARGET)
tests: $(TESTS)
	@echo
	sh ./tests/runtests.sh

valgrind:
	VALGRIND="valgrind --log-file=./tests/valgrind-%p.log " $(MAKE)

#the cleaner:
clean:
	rm -rf build $(OBJECTS) $(TESTS)
	rm -f $(LOGS)
	find . -name "*.gc*" -exec rm {} \;
	rm -rf `find . -name "*.dSYM" -print`

#the install:
install: all
	install -d $(DESTDIR)/$(PREFIX)/lib/
	install $(TARGET) $(DESTDIR)/$(PREFIX)/lib

#the checker:
BADFUNCS='[^_.>a-zA-Z0-9](str(n?cpy|n?cat|xfrm|n?dup|str|pbrk|tok|_)|stpn?cpy|a?sn?printf)'
check:
ifeq ($(strip $(SOURCES)),)
	@echo No sources files to check.
else
	@echo Files with potentially dangerous functions:
	@egrep $(BADFUNCS) $(SOURCES) || true
	@echo "(check for dangerous functions done.)"
endif
#!/bin/sh

echo "Running unit tests:"

if test $OSTYPE = "cygwin"
then
    PATH=$PATH:build
    EXECS=tests/*/*_tests.exe
else
    EXECS=tests/*/*_tests
    VALGRIND=`which valgrind`
    if  ! test -x $VALGRIND
    then
	VALGRIND=
    fi
fi

for i in $EXECS
do
    if test -f $i 
    then
	if $VALGRIND ./$i 2>> tests/tests.log 
	then
	    echo $i PASS
	else
            echo "ERROR in test $i: here's tests/tests.log"
            echo "------"
            tail tests/tests.log
            exit 1
	fi
    fi
done

grep "==" tests/tests.log

echo "(unit tests done.)"
echo 

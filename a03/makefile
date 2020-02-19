# CXX Make variable for compiler
CC=gcc
# Make variable for compiler options
#	-std=c++11  C/C++ variant to use, e.g. C++ 2011
#	-g          include information for symbolic debugger e.g. gdb 
CCFLAGS=-std=c11 -g -lpthread

MYFLAGS=-lpthread

# Rules format:
# target : dependency1 dependency2 ... dependencyN
#     Command to make target, uses default rules if not specified

# First target is the one executed if you just type make
# make target specifies a specific target
# $^ is an example of a special variable.  It substitutes all dependencies
#wordcount : wordcount.c
#	$(CC) wordcount.c -o wordcount $(MYFLAGS)

wordcount : wordcount.c
	$(CC) wordcount.c -o wordcount $(CCFLAGS)

run:
	./wordcount big.txt

clean :
	rm *.o
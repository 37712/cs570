# CXX Make variable for compiler
CC=gcc
# Make variable for compiler options
#	-std=c++11  C/C++ variant to use, e.g. C++ 2011
#	-g          include information for symbolic debugger e.g. gdb 
CCFLAGS=-std=c11 -g

# Rules format:
# target : dependency1 dependency2 ... dependencyN
#     Command to make target, uses default rules if not specified

# First target is the one executed if you just type make
# make target specifies a specific target
# $^ is an example of a special variable.  It substitutes all dependencies
spellcheck : dictionary.o spellcheck.o
	$(CC) $(CCFLAGS) -o dictionary $^

#To produce only the compiled code (without any linking), use the -C option.
dictionary.o : dictionary.h dictionary.c
	$(CC) $(CCFLAGS) -c -o dictionary.o dictionary.c

spellcheck.o : dictionary.h spellcheck.c
	$(CC) $(CCFLAGS) -c -o spellcheck.o spellcheck.c

run:
	./dictionary Austen-Pride-and-Prejudice.txt aspell_list_en.txt

clean :
	rm *.o


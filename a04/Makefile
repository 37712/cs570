#
# CS570, spring 2020, Marie Roch
#
# Carlos Gamino Reyes
# misc0230@edoras.sdsu.edu
# 819230978
#
# Tan Truong
# misc0308@edoras.sdsu.edu
# 821006778
#

# gcc options:
#			-o name // specify name of output file
#			-c 		// compiles source without linking, produces a .o object file
#			-Wall // enables all the warnings

CC = gcc
CCFLAGS=-std=c11

pagetable: main.c pagetable.o level.o map.o byutr.o
	${CC} ${CCFLAGS} -g -o pagetable -Wall main.c pagetable.o level.o map.o byutr.o
	
pagetable.o: pagetable.c pagetable.h
	${CC} ${CCFLAGS} -Wall -c pagetable.c
	
level.o: level.c level.h
	${CC} ${CCFLAGS} -Wall -c level.c
	
map.o: map.c map.h
	${CC} ${CCFLAGS} -Wall -c map.c

byutr.o: byu_tracereader.c byutr.h
	${CC} ${CCFLAGS} -o byutr.o -c byu_tracereader.c
	
run:
	./pagetable -p write.txt trace.sample.tr 8 7 4

run2:
	./pagetable –n 10000 –p page.txt -t trace.sample.tr 8 7 4
	
clean:
	rm *.o
	rm *.stackdump

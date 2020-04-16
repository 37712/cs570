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
CCFLAGS=-std=c11 -g -Wall

pagetable: main.c pagetable.o level.o map.o byutr.o
	${CC} -o pagetable main.c pagetable.o level.o map.o byutr.o ${CCFLAGS}
	
pagetable.o: pagetable.c pagetable.h
	${CC} -c pagetable.c ${CCFLAGS}
	
level.o: level.c level.h
	${CC} -c level.c ${CCFLAGS}
	
map.o: map.c map.h
	${CC} -c map.c ${CCFLAGS}

byutr.o: byu_tracereader.c byutr.h
	${CC} -o byutr.o -c byu_tracereader.c ${CCFLAGS}
	
run:
	./pagetable -p write.txt trace.sample.tr 8 7 4

run2:
	./pagetable –n 10000 –p page.txt -t trace.sample.tr 8 7 4
	
clean:
	rm *.o
	rm *.stackdump

#
# Carlos Gamino
# CS570, spring 2020
#
# Carlos Gamino Reyes
# misc0230@edoras.sdsu.edu
# 819230978
#
# Tan Truong
# misc0308@edoras.sdsu.edu
# 821006778
#

CC = gcc
CCFLAGS=-std=c11

pagetable: pagetable.o level.o map.o byu.o
	${CC} ${CCFLAGS} -o pagetable pagetable.o level.o map.o byu.o
	
byu.o: byu.c byu.h
	${CC} ${CCFLAGS} -o byu.o -c byu.c
	
pagetable.o: pagetable.c pagetable.h
	${CC} ${CCFLAGS} -c pagetable.c
	
level.o: level.c level.h
	${CC} ${CCFLAGS} -c level.c
	
map.o: map.c map.h
	${CC} ${CCFLAGS} -c map.c
	
clean:
	rm *.o pagetable
	rm *.stackdump

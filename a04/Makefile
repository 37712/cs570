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

CC = gcc
CCFLAGS=-std=c11

pagetable: main.c pagetable.o level.o map.o byutr.o
	${CC} ${CCFLAGS} -o pagetable main.c pagetable.o level.o map.o byu.o
	
byutr.o: byu_tracereader.c byutr.h
	${CC} ${CCFLAGS} -o byutr.o -c byu_tracereader.c
	
pagetable.o: pagetable.c pagetable.h
	${CC} ${CCFLAGS} -c pagetable.c
	
level.o: level.c level.h
	${CC} ${CCFLAGS} -c level.c
	
map.o: map.c map.h
	${CC} ${CCFLAGS} -c map.c
	
run:
	./pagetable trace.sample.tr 8 12

run2:
	./pagetable –n 3000000 –p page.txt trace.sample.tr 8 7 4
	
clean:
	rm *.o
	rm *.stackdump

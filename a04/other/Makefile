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

pagetable: sample_read.c byutr.o
	${CC} ${CCFLAGS} sample_read.c byutr.o
	
byutr.o: byu_tracereader.c byutr.h
	${CC} ${CCFLAGS} -o byutr.o -c byu_tracereader.c
	
run:
	./a

clean:
	rm *.o
	rm *.stackdump

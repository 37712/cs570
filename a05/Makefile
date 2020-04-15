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

# semaphores must include the POSIX real time library -lrt while compiling

CC = gcc
CCFLAGS=-std=c11 -g -Wall -lpthread -lrt

# factory_controller.cpp producers.cpp consumers.cpp

default: main.c producer.o consumer.o belt.o
	${CC} ${CCFLAGS} -o mizzo main.c producer.o consumer.o belt.o

producer.o: producer.c producer.h
	${CC} ${CCFLAGS} -c producer.c
	
consumer.o: consumer.c consumer.h
	${CC} ${CCFLAGS} -c consumer.c
	
belt.o: belt.c belt.h
	${CC} ${CCFLAGS} -c belt.c

run:
	./mizzo -E 1000 -L 1200 -f 3000 -e 100

clean:
	rm *.o
	rm *.stackdump

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
CCFLAGS= -Wall -lpthread -lrt

# factory_controller.cpp producers.cpp consumers.cpp

default: main.c producer.o consumer.o belt.o
	${CC} -o mizzo main.c producer.o consumer.o belt.o ${CCFLAGS}

producer.o: producer.c producer.h
	${CC} -c producer.c ${CCFLAGS}
	
consumer.o: consumer.c consumer.h
	${CC} -c consumer.c ${CCFLAGS}
	
belt.o: belt.c belt.h
	${CC} -c belt.c ${CCFLAGS}

# run command works on linux only
run:
	./mizzo -E 1000 -L 3000 -f 600 -e 400

clean:
	rm *.o
	rm *.stackdump

FLAGS = -ansi -Wall -Wextra -Werror -pedantic-errors -g
LIBS = -lm

all: spmat.o linkedlist.o submat.o expmat.o powerIteration.o division.o modmax.o util.o prog.o   
	gcc $(FLAGS) spmat.o linkedlist.o submat.o expmat.o powerIteration.o division.o modmax.o util.o prog.o -o cluster $(LIBS)
clean:
	rm -rf *.o cluster

spmat.o: spmat.c
	gcc $(FLAGS) -c spmat.c
linkedlist.o: linkedlist.c
	gcc $(FLAGS) -c linkedlist.c
submat.o: submat.c
	gcc $(FLAGS) -c submat.c
expmat.o: expmat.c
	gcc $(FLAGS) -c expmat.c
powerIteration.o: powerIteration.c
	gcc $(FLAGS) -c powerIteration.c
division.o: division.c
	gcc $(FLAGS) -c division.c
modmax.o: modmax.c
	gcc $(FLAGS) -c modmax.c
util.o: util.c
	gcc $(FLAGS) -c util.c
prog.o: prog.c
	gcc $(FLAGS) -c prog.c


all: bst run clean

bst: bst.c program6.c
	gcc -c bst.c program6.c
	gcc -o program6 bst.o program6.o

run: program6
	./program6

memcheck: 
	valgrind ./program6

clean:
	rm program6 bst.o program6.o




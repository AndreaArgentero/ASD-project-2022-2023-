simulation: compile
	clear

compile:    Skiplist_Algoritm

clean:
	ipcrm -a
	rm bin/main_ex2
	clear

run:
	clear
	./bin/main_ex2 tmp/data/dictionary.txt tmp/data/correctme.txt 20

test:    Skiplist_Test
	./Skiplist_Test

#=============================================================

CC = gcc 

#=============================================================
Skiplist_Algoritm: SkiplistMain.c
	${CC}    SkiplistMain.c Skiplist.c -o bin/main_ex2

Skiplist_Test: Skiplist_Test.c
	${CC}    Skiplist_Test.c Skiplist.c unity.c -o Skiplist_Test
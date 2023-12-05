simulation: compile
	clear

compile:	Merge_Binary

clean:
	ipcrm -a
	rm bin/main_Ex1
	clear

run:
	clear
	./bin/main_Ex1 tmp/data/records.csv tmp/data/sorted.csv 27 1

test:	Merge_Binary_Test
	clear
	./MergeTest

#=============================================================

CC = gcc 

#=============================================================
Merge_Binary: main_Ex1.c
	${CC}	main_Ex1.c MergeBinary.c -o bin/main_Ex1

Merge_Binary_Test: MergeBinary_Test.c
	${CC}	MergeBinary_Test.c MergeBinary.c unity.c -o MergeTest
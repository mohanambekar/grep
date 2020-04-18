project: grepfinal.o files1.o
	cc -Wall grepfinal.o files1.o -o project
grepfinal.o: grepfinal.c grep.h
	cc -c grepfinal.c
files1.o: grep.h files1.c
	cc -c files1.c 	
	

all: mshell

mshell: mshell.o job.o
	gcc -o mshell mshell.o job.o

mshell.o: mshell.c job.h
	gcc -c mshell.c

job.o: job.c job.h
	gcc -c job.c

clear:
	rm -f *.o

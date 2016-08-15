all: mshell

mshell: mshell.o job.o func.o
	gcc -o mshell mshell.o job.o func.o

mshell.o: mshell.c job.h func.h
	gcc -c mshell.c

func.o: func.h job.h
	gcc -c func.c

job.o: job.c job.h
	gcc -c job.c

clear:
	rm -f *.o *.txt

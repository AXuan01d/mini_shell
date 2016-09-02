all: test_read test_write test_append

test_write: test_write.o mstdio.o
	gcc -g -o test_write test_write.o mstdio.o

test_append: test_append.o mstdio.o
	gcc -o test_append test_append.o mstdio.o

test_read: test_read.o mstdio.o
	gcc -o test_read test_read.o mstdio.o

test_read.o: test_read.c mstdio.h
	gcc -c test_read.c

test_write.o: test_write.c mstdio.h
	gcc -c test_write.c

test_append.o: test_append.c mstdio.h
	gcc -c test_append.c

mstdio.o: mstdio.h
	gcc -c mstdio.c

clean:
	rm -f *.o

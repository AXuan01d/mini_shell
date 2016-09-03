.PHONY:clean
all:minishell clean
CC=gcc
CFLAGS=-Wall -g
BIN=minishell
OBJS=main.o parse.o execute.o init.o 

$(BIN):$(OBJS)
	$(CC) $(CFLAGS) -o $@  $^ 

%.o:%.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o
	
	

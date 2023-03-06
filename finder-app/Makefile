CC=$(CROSS_COMPILE)gcc
CFLAGS= -g -Wall
SOURCE=$(wildcard *.c)
OBJS=$(SOURCE:.c=.o)


.PHONY: all writer clean

all: clean writer

writer:
	$(CC) $(CFLAGS) -o $@ $@.c

clean:
	@rm -rf writer $(OBJS)

CC=$(CROSS_COMPILE)gcc
CUR_PATH=$(dir $(abspath $(MAKEFILE_LIST)))
CFLAGS= -g -Wl,-rpath=$(CUR_PATH) 
#-fsanitize=address,leak
LDLIBS= -lm -lpthread -lfile_manipulate -lsig_func
OBJS=$(filter-out aesdsocket.o, $(patsubst %.c, %.o, $(wildcard *.c)))

.PHONY: all aesdsocket clean

all: aesdsocket

aesdsocket: libfile_manipulate.so libsig_func.so
	$(CC) $(CFLAGS) -o $@ $(@).c -L$(CUR_PATH)  $(LDLIBS)

libfile_manipulate.so: file_manipulate
	$(CC) $(CFLAGS) -shared -o $@ $<.o

libsig_func.so: sig_func
	$(CC) $(CFLAGS) -shared -o $@ $<.o 

file_manipulate:
	$(CC) $(CFLAGS) -fPIC -c $@.c $(LDLIBS) 

sig_func:
	$(CC) $(CFLAGS) -fPIC -c $@.c $(LDLIBS) 

clean:
	$(RM) aesdsocket $(wildcard *.o) $(wildcard *.so)

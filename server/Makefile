CC=$(CROSS_COMPILE)gcc
CUR_PATH=$(dir $(abspath $(MAKEFILE_LIST)))
CFLAGS= -g
#-fsanitize=address,leak
LDLIBS= -lm -lpthread -lfile_manipulate -lsig_func
OBJS=$(filter-out aesdsocket.o, $(patsubst %.c, %.o, $(wildcard *.c)))
LIBS_TYPE=""


.PHONY: all aesdsocket clean

all: aesdsocket

#aesdsocket: libfile_manipulate.$(LIBS_TYPE) libsig_func.$(LIBS_TYPE)
#	$(CC) $(CFLAGS) -o $@ $(@).c -L$(CUR_PATH)  $(LDLIBS)

ifneq ($(STATIC_LIBS), true)
LIBS_TYPE="so"
CFLAGS+= -Wl,-rpath=$(CUR_PATH)
libfile_manipulate.$(LIBS_TYPE): file_manipulate
	$(CC) $(CFLAGS) -shared -o $@ $<.o

libsig_func.$(LIBS_TYPE): sig_func
	$(CC) $(CFLAGS) -shared -o $@ $<.o
else
LIBS_TYPE="a"
libfile_manipulate.$(LIBS_TYPE): file_manipulate
	$(AR) -rc $@ $<.o

libsig_func.$(LIBS_TYPE): sig_func
	$(AR) -rc $@ $<.o
endif

aesdsocket: libfile_manipulate.$(LIBS_TYPE) libsig_func.$(LIBS_TYPE)
	$(CC) $(CFLAGS) -o $@ $(@).c -L$(CUR_PATH)  $(LDLIBS)

file_manipulate:
	$(CC) $(CFLAGS) -fPIC -c $@.c $(LDLIBS)

sig_func:
	$(CC) $(CFLAGS) -fPIC -c $@.c $(LDLIBS)

clean:
	$(RM) aesdsocket $(wildcard *.o) $(wildcard *.so) $(wildcard *.a)

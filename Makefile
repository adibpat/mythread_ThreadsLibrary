 #/* Single Author Info:
 #*   smnaik Sanskruti M Naik
 #* Group Info:
 #*   abpatwar Aditya B Patwardhan
 #*   smnaik Sanskruti M Naik
 #*   slbist Saurabh L Bist
 #*/


#This make file is referred from the GNU Make and Github.com 

SRCS =  mythread_create.c mythread_self.c mythread_wrapper.c mythread_yield.c mythread_join.c mythread_exit.c myqueue.c mythread_attributes.c futex.c
INC = futex.h  futex_inline.h  myatomic.h  mythread.h  myqueue.h
OBJS = $(SRCS:.c=.o)
TEST_SRCS = test.c
TEST_OBJS = $(TEST_SRCS:.c=.o)
DEBUG=0

CFLAGS = -I. -g
LDFLAGS = -L.
LIB = mythreadlib.a

AR = /usr/bin/ar
CC = gcc

ifeq ($(DEBUG),1)
EXTRA_CFLAGS += -DDEBUG
endif

.PHONY: all lib clean test a5
a5:	all
all: lib test

lib: $(LIB)

mythreadlib.a: $(OBJS) $(INC)
	$(AR) rcs $(LIB) $(OBJS)

%.o: %.c $(INC)
	$(CC) $(CFLAGS) $(EXTRA_CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TEST_OBJS) $(LIB) *~ test


test:	$(TEST_OBJS) $(INC) lib
	$(CC) -o test $(CFLAGS) $(EXTRA_CFLAGS) $(TEST_OBJS) $(LIB)
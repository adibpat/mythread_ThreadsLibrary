/* Single Author Info:
 *   abpatwar Aditya B Patwardhan
 * Group Info:
 *   abpatwar Aditya B Patwardhan
 *   smnaik Sanskruti M Naik
 *   slbist Saurabh L Bist
 */

/*
 * mythread.h -- interface of user threads library
 */

#ifndef MYTHREAD_H
#define MYTHREAD_H

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

#ifndef READY
#define READY 0
#endif

#ifndef RUNNING
#define RUNNING 1
#endif

#ifndef BLOCKED
#define BLOCKED 2
#endif

#ifndef DETACHED
#define DETACHED 3
#endif

#include <sys/types.h>
#include "futex.h"
#include<signal.h>

typedef int mythread_key_t;

typedef struct mythread_attr {    /* thread attributes */
  int stacksize;                  /* stack size in bytes */
  void* stackbase;
} mythread_attr_t;

typedef struct mythread_queue{
	void * tid;
	struct mythread_queue * next;
	struct mythread_queue * prev;
} * mythread_queue_t;

typedef struct mythread {         /* thread control block */
  pid_t tid;
  void * (*start_func)(void*);    /* thread_func to be called */
  void *arg;                      /* thread_arg arguments of thread_func */
  mythread_queue_t joinq;        /* Q of threads waiting for my return */
  void *returnValue;              /* Pointer to the detached function's return value */
  struct futex futex;
  int state;                      /* state of execution */
  mythread_attr_t attr;
} *mythread_t;

#include"myqueue.h" /* Queue declared after the declaration of mythread_t */

extern struct futex global_futex;

extern mythread_queue_t head_ptr;
extern mythread_queue_t head_ptr_idle;
extern mythread_queue_t wait_ptr;
/*
 * mythread_self - thread id of running thread
 */
mythread_t mythread_self(void);

/*
 * mythread_create - prepares context of new_thread_ID as start_func(arg),
 * attr is ignored right now.
 * Threads are activated (run) according to the number of available LWPs
 * or are marked as ready.
 */
int mythread_create(mythread_t *new_thread_ID,
		    mythread_attr_t *attr,
		    void * (*start_func)(void *),
		    void *arg);

/*
 * mythread_yield - switch from running thread to the next ready one
 */
int mythread_yield(void);

/*
 * mythread_join - suspend calling thread if target_thread has not finished,
 * enqueue on the join Q of the target thread, then dispatch ready thread;
 * once target_thread finishes, it activates the calling thread / marks it
 * as ready.
 */
int mythread_join(mythread_t target_thread, void **status);

/* 
 *Internal Queues for holding the threads that wait on a given thread 
 */
void join_queue (mythread_t tid,mythread_queue_t ptr);
int mythread_change_status(mythread_queue_t ptr);

/*
 * mythread_exit - exit thread, awakes joiners on return
 * from thread_func and dequeue itself from run Q before dispatching run->next
 */
void mythread_exit(void *retval);

int mythread_attr_init(mythread_attr_t *attr);

int mythread_attr_destroy(mythread_attr_t *attr);

int mythread_attr_getstack(const mythread_attr_t *attr,
			   void **stackaddr,
			   size_t *stacksize);

int mythread_attr_setstack(mythread_attr_t *attr, void *stackaddr,
			   size_t stacksize);

int mythread_attr_getstacksize(const mythread_attr_t *attr, 
			       size_t *stacksize);

int mythread_attr_setstacksize(mythread_attr_t *attr, size_t stacksize);

int mythread_ready(mythread_t self);

#endif /* MYTHREAD_H */

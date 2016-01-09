/* Single Author Info:
 *   abpatwar Aditya B Patwardhan
 * Group Info:
 *   abpatwar Aditya B Patwardhan
 *   smnaik Sanskruti M Naik
 *   slbist Saurabh L Bist
*/

#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sched.h>
#include"mythread.h"
#include<sys/syscall.h>

int mythread_wrapper(void *);

pid_t mythread_gettid(void) {
  return (pid_t) syscall(SYS_gettid);
}

/* this is the global external head pointer of the queue */

mythread_queue_t head_ptr; 
mythread_queue_t head_ptr_idle;

struct futex global_futex;   /* Referred to Github.com for the need of global futex */

/* Idle thread */

mythread_t idle_thread; 

static int create_main_tcb(){

  mythread_t main_tcb = (mythread_t)malloc(sizeof(struct mythread));

  if(main_tcb == NULL){
    return -1;
  }

  /* Initialize main TCB */

  main_tcb -> tid = (pid_t) mythread_gettid();
  main_tcb -> start_func = NULL;
  main_tcb -> arg = NULL;
  main_tcb -> returnValue = NULL;
  main_tcb -> state = READY;
  

  /* Initialize futex for main thread */
  futex_init(&main_tcb->futex,0);
 
  /* Addition of this entry into the global queue is required */
  queue_add(main_tcb);
  
  return 0;  
}

/*
void *idle_activity(void* param){
  /*mythread_t idle = mythread_self();
  head_ptr_idle = head_ptr->prev;
  mythread_queue_t check = head_ptr;
  while(1){
    while((mythread_t)check->tid != idle){
      mythread_t temp = (mythread_t)check->tid;
      if(temp->state != DETACHED){
        break;
      }
      check = check->next;
    }
    if((mythread_t)check->tid == idle){
      exit(0);
    }
    */
    //mythread_yield();
  //}
//}


int mythread_create_idle(mythread_t *new_thread_ID,
        mythread_attr_t *attr,
        void * (*start_func)(void *),
        void *arg){

  int stacksize;
  void*child_stack = NULL;
  if(attr == NULL){
    stacksize = SIGSTKSZ;
    posix_memalign(&child_stack,8,stacksize);   /*Alignment of stack at 64 bit boundary*/
  } 
  else{
    stacksize = attr->stacksize;
    child_stack = attr->stackbase;
  }
  
  if(child_stack == NULL){
      return -1;
    }
  else{
    child_stack = child_stack + stacksize - sizeof(sigset_t);
  }
  
  
  /* Initialization of local TCB to be sent to the generic wrapper function */

  mythread_t new_tcb = (mythread_t)malloc(sizeof(struct mythread));
  if(new_tcb == NULL){
    return -1;
  }
  
  new_tcb -> start_func = start_func;
  new_tcb -> arg = arg;
  new_tcb -> state = READY;
  new_tcb -> joinq = NULL;
  new_tcb -> returnValue = NULL;

  /* Initialize futex for new thread to 0 not 1*/
  futex_init(&new_tcb->futex,0);
 
  /* Add this TCB to the global queue */
  queue_add(new_tcb);
  
  pid_t tid;
  if((tid = clone(mythread_wrapper,child_stack,(CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND|CLONE_THREAD | CLONE_PARENT_SETTID | CLONE_CHILD_CLEARTID | CLONE_SYSVSEM),new_tcb))==-1){
    return -1;
  }

  /* Adding tid of thread to the TCB */
  new_tcb -> tid = tid;
  
  /* This is what the user will see as the TID */
  *new_thread_ID = new_tcb;

  //printf("The tid of thread as seen from the main is %ld \n",(long)new_thread_ID);
  
  return 0;        
}


/*
 * mythread_create - prepares context of new_thread_ID as start_func(arg),
 * attr is ignored right now.
 * Threads are activated (run) according to the number of available LWPs
 * or are marked as ready.
 */

int mythread_create(mythread_t *new_thread_ID,
		    mythread_attr_t *attr,
		    void * (*start_func)(void *),
		    void *arg){

  

  /* Call the create_main_tbc() funciton */
  
  if(head_ptr==NULL){
    if(create_main_tcb() != 0){
      return -1;
    }

    /* Futex to let the idle thread always runs along with another thread */
    futex_init(&global_futex,1);
    /*
    if((mythread_create_idle(&idle_thread,NULL,idle_activity,NULL)==-1)){
      return -1;
    } 
    */
  }

  
  /* Allocate Memory for Stack */
  
  int stacksize;
  void* child_stack = NULL;
  if(attr == NULL){
    stacksize = SIGSTKSZ;
    posix_memalign(&child_stack,8,stacksize);   /*Alignment of stack at 64 bit boundary*/
  } 
  else{
    stacksize = attr->stacksize;
    if(attr->stackbase==NULL){
      posix_memalign(&child_stack,8,stacksize);
    }
    else{
      child_stack = attr->stackbase;
    }
    
  }
  
  if(child_stack == NULL){
      return -1;
    }
  else{
    child_stack = child_stack + stacksize - sizeof(sigset_t);
  }
  
  
  /* Initialization of local TCB to be sent to the generic wrapper function */

  mythread_t new_tcb = (mythread_t)malloc(sizeof(struct mythread));
  if(new_tcb == NULL){
    return -1;
  }
  
  new_tcb -> start_func = start_func;
  new_tcb -> arg = arg;
  new_tcb -> state = READY;
  new_tcb -> returnValue = NULL;

  /* Initialize futex for new thread to 0 not 1*/
  futex_init(&new_tcb->futex,0);
 
  /* Add this TCB to the global queue */
  queue_add(new_tcb);
  
  pid_t tid;
  if((tid = clone(mythread_wrapper,(char*)child_stack,(CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND|CLONE_THREAD | CLONE_PARENT_SETTID | CLONE_CHILD_CLEARTID | CLONE_SYSVSEM),new_tcb))==-1){
    return -1;
  }
  
  /* Adding tid of thread to the TCB */
  new_tcb -> tid = tid;
  
  /* This is what the user will see as the TID */
  *new_thread_ID = new_tcb;

  //printf("The tid of thread as seen from the main is %ld \n",(long)new_thread_ID);
  
  return 0;    
}
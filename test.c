/* Single Author Info:
 *   smnaik Sanskruti M Naik
 * Group Info:
 *   abpatwar Aditya B Patwardhan
 *   smnaik Sanskruti M Naik
 *   slbist Saurabh L Bist
*/
#include<stdlib.h>
#include<stdio.h>
#include<sys/syscall.h>
#include<sys/types.h>
#include<unistd.h>
#include"futex.h"
#include"mythread.h"

 #define NUM_THREADS 3

void* myfunction1(){
  
  write(1,"I am the first thread in function 1 and going to yield\n",56);
  
  mythread_yield();

  write(1,"I am the first thread in function 1 and resumed\n",51);
  
  mythread_exit(NULL);
  return NULL;
}
 
void* myfunction2(){
  
  write(1,"I am the first thread in function 2 and going to yield\n",56);
  mythread_yield();
  write(1,"I am the first thread in function 2 and resumed\n",51);
  mythread_exit(NULL);
  return NULL;
}

void* myfunction3(){
  
  write(1,"I am the first thread in function 3 and going to yield\n",56);
  mythread_yield();
  write(1,"I am the first thread in function 3 and resumed\n",51);
  mythread_exit(NULL);
  return NULL;
}


int main()
{
  /* Definition of mythread_t which is a pointer to the TCB */
  mythread_t thread[NUM_THREADS];
  mythread_t threads;
  
  /* Attribute Test */

  mythread_attr_t attr;
  mythread_attr_init(&attr);
  printf("Default initialized stacksize: %d\n",attr.stacksize);
  printf("Default initialized stackbase: %ld\n",attr.stackbase);

  int stacksize = SIGSTKSZ + 50;
  mythread_attr_setstacksize(&attr,stacksize);
  printf("New set stacksize: %d\n",attr.stacksize);
  

  //mythread_attr_setstack(&attr
  printf("I am the parent with id %ld\n",(long)mythread_gettid());
  
  pid_t pid;

  pid = mythread_create(&thread[0],&attr,myfunction1,(void*)NULL);
  pid = mythread_create(&thread[1],&attr,myfunction2,(void*)NULL);
  pid = mythread_create(&thread[2],&attr,myfunction3,(void*)NULL);

  //pid = mythread_create(&t2,&attr,myfunction1,(void*)NULL);
  //pid = mythread_create(&t3,&attr,myfunction1,(void*)NULL);
  //queue_print();
  mythread_yield();
  printf("MAIN: I will yield to give other threads a chance\n");
  mythread_yield();
  //printf("MAIN: Waiting for threads to join\n");
  /*
  int i;
  for(i=0;i<3;i++){
    mythread_join(thread[i],NULL);
    printf("Thread %d joined\n",i);
  }
  */
  printf("The contents of the Queue are :\n");
  queue_print();
  //mythread_join(thread[0],NULL);
  //mythread_join(thread[1],NULL);
  //mythread_join(thread[2],NULL);
  //printf("tid of t2 is %ld\n",(long)t2->tid);
  //printf("tid of t3 is %ld\n",(long)t3->tid);
  printf("\nThreads scheduled successfully in FIFO fashion. Now exiting...\n");
  
  //mythread_yield();

  
  //pid = mythread_create(&t2,&attr,myfunction1,(void*)NULL);
  //mythread_yield();
  //mythread_yield();
  //mythread_join(t2,(void**)&status);
  //mythread_join(t3,(void**)&status);
  
  
  return 0;
}

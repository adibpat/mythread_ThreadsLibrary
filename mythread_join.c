/* Single Author Info:
 *   abpatwar Aditya B Patwardhan
 * Group Info:
 *   abpatwar Aditya B Patwardhan
 *   smnaik Sanskruti M Naik
 *   slbist Saurabh L Bist
*/

#include"mythread.h"
#include<stdlib.h>

mythread_queue_t wait_ptr;

/* Function to allocate a new node to the TCB's wait queue */

void join_queue(mythread_t waiter,mythread_queue_t ptr){
  


  mythread_queue_t qNode = (mythread_queue_t)malloc(sizeof(struct mythread_queue));
  
  if(qNode==NULL){
    return;
  }
  
  qNode->tid = waiter;
  
  if(ptr == NULL){
      ptr = qNode;
      qNode->next = qNode;
      qNode->prev = qNode;
      return;
  }
  else{
    qNode->next = ptr;
    qNode->prev = ptr->prev;
    (ptr->prev)->next = qNode;
    ptr->prev = qNode;
    return;
  } 
}



/*
 * mythread_join - suspend calling thread if target_thread has not finished,
 * enqueue on the join Q of the target thread, then dispatch ready thread;
 * once target_thread finishes, it activates the calling thread / marks it
 * as ready.
 */

int mythread_join(mythread_t target_thread, void **status){
  mythread_t self = (mythread_t)mythread_self();
  mythread_t target = target_thread;
  
  /* Check of the thread is waiting for self - Deadlock condition */
  if(self == target){
    return -1;
  }
  
  /* Check if target thread is already detached */
  if(target->state==DETACHED){
    *status = target->returnValue;
    return 0;
  }
  
  
  /* Add the caller to the wait queue of the target */
  join_queue(self,target->joinq);
  
  /* Change state of the caller to blocked 'changed it to block from ready'*/
  self->state = BLOCKED;
  
  /* Go to suspended state and wait till the threads finish their work */
  mythread_yield();
  
  /* When the caller resumes */
  *status = target->returnValue;


  return 0;
}

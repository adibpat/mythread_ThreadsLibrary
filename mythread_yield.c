/*Single Author Info:
 *  Aditya B Patwardhan
 *Group Info:
 *  abpatwar Aditya B Patwardhan
 *  smnaik Sanskruti M Naik
 *  slbist Saurabh L Bist
*/

#include"mythread.h"

mythread_queue_t head_ptr;
struct futex global_futex;

int mythread_ready(mythread_t self){

  mythread_t curr = self;
  
  mythread_queue_t myptr = NULL;
  myptr = myqptr(curr);
  
  mythread_t dispatch = NULL;
  mythread_queue_t ptr = myptr->next;
  
  do{
    dispatch = (mythread_t)(ptr->tid);
    if(dispatch->state == READY){
      
      futex_up(&dispatch->futex);
      return 0;
    }
    ptr = ptr->next;
    
  }
  while(ptr != head_ptr);
  
  
  return -1;
}


/*
 * mythread_yield - switch from running thread to the next ready one
 */

int mythread_yield(){

  mythread_t self = (mythread_t)mythread_self();
  
  /* Global FUTEX put to down to allow only one thread in yield function to avoid deadlock */
  futex_down(&global_futex);

  mythread_ready(self);

  futex_up(&global_futex);
  
  futex_down(&self->futex);

  return 0;
}

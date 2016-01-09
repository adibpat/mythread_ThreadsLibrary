/* Single Author Info:
 *   smnaik Sanskruti M Naik
 * Group Info:
 *   abpatwar Aditya B Patwardhan
 *   smnaik Sanskruti M Naik
 *   slbist Saurabh L Bist
*/
 
#include <signal.h>
#include <stdlib.h>
#include"mythread.h"
#include<sys/syscall.h>

/* Change the status of the waiting threads */

int mythread_change_status(mythread_queue_t ptr){
  mythread_queue_t temp = ptr;
  mythread_t t=NULL;
  do{
    t = temp->tid;
    if(t->state==BLOCKED){
    t->state = READY;
  }
    temp = temp->next;
  }while(temp != ptr);
  return 0;
}


void mythread_exit(void *retval)
{
  

  mythread_t curr = NULL;
  
  curr = mythread_self(); /* Pointer to the thread you want to kill */

  
  curr->returnValue = retval; /* Save return value in TCB */

    /* Check for threads waiting on the current thread */
  if(curr->joinq != NULL)
    {
      mythread_change_status(curr->joinq);
    }
  
  curr->state = DETACHED;  /* Change state to detached */
  write(1,"THREAD EXITING\n",16);
  /* Schedule next READY thread */
    
  mythread_ready(curr);
  
  /* Kill the current thread */
  
  syscall(SYS_exit,0 );
   
}




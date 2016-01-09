/*Single Author Info:
 *  Aditya B Patwardhan
 *Group Info:
 *  abpatwar Aditya B Patwardhan
 *  smnaik Sanskruti M Naik
 *  slbist Saurabh L Bist
*/


#include<unistd.h>
#include<stdlib.h>
#include"mythread.h"
#include"futex.h"

int mythread_wrapper(void* otcb){

  mythread_t ntcb = (mythread_t)otcb;

  /* Initialize futex for the thread */
  
  //futex_init(&ntcb->futex,0);
  
  
  
  /* Suspend first before dispatch */
  futex_down(&ntcb->futex);
  
  ntcb->start_func(ntcb->arg);

  return 0;
}

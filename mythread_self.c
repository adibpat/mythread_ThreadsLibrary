/* Single Author Info:
 *   smnaik Sanskruti M Naik
 * Group Info:
 *   abpatwar Aditya B Patwardhan
 *   smnaik Sanskruti M Naik
 *   slbist Saurabh L Bist
*/
 
#include <sys/syscall.h>
#include <sys/types.h>
#include "mythread.h"

static pid_t gettid(void) {
  return (pid_t) syscall(SYS_gettid);
}

mythread_t mythread_self(){
  pid_t mypid;
  mypid = gettid();

  /* Search the address of tid in the user queue */
  mythread_t found = queue_search(mypid);
  return found;
}

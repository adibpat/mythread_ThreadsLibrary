/* Single Author Info:
 *   smnaik Sanskruti M Naik
 * Group Info:
 *   abpatwar Aditya B Patwardhan
 *   smnaik Sanskruti M Naik
 *   slbist Saurabh L Bist
*/
#include <sys/types.h>
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include"mythread.h"


int mythread_attr_init(mythread_attr_t *attr){
  
  if(attr==NULL){
    mythread_attr_t *attribute;
    attribute = (mythread_attr_t*)malloc(sizeof(mythread_attr_t));
    if(attribute==NULL){return -1;}
    attribute->stacksize = SIGSTKSZ;
    attribute->stackbase = NULL;
    attr = attribute;
    return (0);
  }
  else{
  attr-> stacksize = SIGSTKSZ;
  attr-> stackbase = NULL ;
  }
  
  return (0);
}

int mythread_attr_destroy(mythread_attr_t *attr){
  
  mythread_attr_t * attribute = attr;
 
  if(attribute==NULL){
    return -1;
  }
  attribute->stacksize = 0;
  attribute->stackbase = NULL;
  free(attribute);
  attribute = NULL;
  
  return (0);
  
}

int mythread_attr_getstack(const mythread_attr_t *attr,
			   void **stackaddr,
			   size_t *stacksize){
  if(attr==NULL){
    return -1;
  }  
  *stacksize =(size_t)attr->stacksize;
  *stackaddr = attr->stackbase;
  
  return( 0);
  
}

int mythread_attr_setstack(mythread_attr_t *attr, void *stackaddr,
			   size_t stacksize){

  mythread_attr_t *attribute = attr;
  attribute->stacksize = stacksize;
  attribute->stackbase =(char *) stackaddr;

  return (0);
  
}


int mythread_attr_getstacksize(const mythread_attr_t *attr, 
			       size_t *stacksize){
  if(attr==NULL){
    return -1;
  }
  size_t size =(size_t)( attr->stacksize);
  
  *stacksize = size;  
  return (0);
}


int mythread_attr_setstacksize( mythread_attr_t *attr, 
			       size_t stacksize){
  if(attr==NULL){
    return -1;
  }
  mythread_attr_t *attribute = attr;
  attribute->stacksize=(int)stacksize;

  return (0);
	
}


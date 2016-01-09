/* Single Author Info: 
 *   abpatwar Aditya B Patwardhan
 * Group Name:
 *   abpatwar Aditya B Patwardhan
 *   smnaik Sanskruti M Naik
 *   slbist Saurabh L Bist
*/

#include<stdio.h>
#include <stdlib.h>
#include"mythread.h"

/* the global head pointer of the queue declared in myqueue.h */

mythread_queue_t head_ptr;

/* Function to allocate a new node to the global queue */ 
void queue_add (mythread_t tid){
  
  mythread_queue_t qNode = (mythread_queue_t)malloc(sizeof(struct mythread_queue));
  if(qNode==NULL){
    return;
  }
  qNode->tid = tid;
  if(head_ptr == NULL){
      head_ptr = qNode;
      qNode->next = qNode;
      qNode->prev = qNode;
      return;
  }else{
    qNode->next = head_ptr;
    qNode->prev = head_ptr->prev;
    (head_ptr->prev)->next = qNode;
    head_ptr->prev = qNode;
    return;
  }  
}


/* Search the location of TCB based on the tid */

mythread_t queue_search(pid_t tid){
  mythread_queue_t temp = head_ptr;
  mythread_t t;
  if(head_ptr!=NULL){
  do{
    t = temp->tid;
    if((long)(t->tid)==tid){
      return t;
    }
    temp = temp->next;
  }
  while(temp != head_ptr);
  return NULL;
   }
  return NULL;
}

/* Print Queue Elements - tid */

void queue_print(){
  mythread_queue_t temp = head_ptr;
  mythread_t t;
  do{
    t = temp->tid;
    printf("Element of a queue - tid - %ld\n",(long)t->tid);
    temp = temp->next;
  }
  while(temp!=head_ptr);
  return;
}

mythread_queue_t myqptr(mythread_t self){
  mythread_queue_t temp = head_ptr;
  while(temp->tid != self){
    temp = temp->next;
  }
  return temp;
}


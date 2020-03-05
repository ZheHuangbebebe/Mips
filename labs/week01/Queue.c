// ADT for a FIFO queue
// COMP1521 17s2 Week01 Lab Exercise
// Written by John Shepherd, July 2017
// Modified by ...

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "Queue.h"

typedef struct QueueNode {
   int jobid;  // unique job ID
   int size;   // size/duration of job
   struct QueueNode *next;
} QueueNode;

struct QueueRep {
   int nitems;      // # of nodes
   QueueNode *head; // first node
   QueueNode *tail; // last node
};



// TODO:
// remove the #if 0 and #endif
// once you've added code to use this function

// create a new node for a Queue
static
QueueNode *makeQueueNode(int id, int size)
{
   QueueNode *new;
   new = malloc(sizeof(struct QueueNode));
   assert(new != NULL);
   new->jobid = id;
   new->size = size;
   new->next = NULL;
   return new;
}




// make a new empty Queue
Queue makeQueue()
{
   Queue new;
   new = malloc(sizeof(struct QueueRep));
   assert(new != NULL);
   new->nitems = 0; new->head = new->tail = NULL;
   return new;
}

// release space used by Queue
void  freeQueue(Queue q)
{
    assert(q != NULL);
	struct QueueNode *delete;
	struct QueueNode *x;
	delete = q->head;
	x = q->head->next;
	free(delete);
	while(x != NULL)
	{
		delete = x;
		x = x->next;
		free(delete);
	}
	free(q);
   // TODO
}

// add a new item to tail of Queue
void  enterQueue(Queue q, int id, int size)
{
    assert(q != NULL);
	if(q->head == NULL)
	{
		q->head = makeQueueNode(id, size);
		q->tail = q->head;
		q->nitems++;
	}
	else
	{
		q->tail->next = makeQueueNode(id, size);
		q->tail = q->tail->next;
		q->nitems++;
	}
   // TODO
}

// remove item on head of Queue
int   leaveQueue(Queue q)
{
    assert(q != NULL);
	struct QueueNode *delete;
	int id;
	if(q->head == NULL)
	{
		return 0;
	}
	else if(q->head->next != NULL)
	{
		id = q->head->jobid;
		delete = q->head;
		q->head = q->head->next;
		free(delete);
		q->nitems--;
	}
	else
	{
		id = q->head->jobid;
		delete = q->head;
		q->head = NULL;
		free(delete);
		q->nitems--;
	}
   // TODO
   return id; // replace this statement
}

// count # items in Queue
int   lengthQueue(Queue q)
{
   assert(q != NULL);
   return q->nitems;
}

// return total size in all Queue items
int   volumeQueue(Queue q)
{
   assert(q != NULL);
   // TODO
	int sum = 0;
	struct QueueNode *x;
	if(q->head == NULL)
	{
		return 0;
	}
	x = q->head;
	for(x = q->head;x != NULL; x = x->next)
	{
		sum = sum + x->size;
	}
   return sum; // replace this statement
}

// return size/duration of first job in Queue
int   nextDurationQueue(Queue q)
{
   assert(q != NULL);
	if(q->head == NULL)
	{
		return 0;
	}
	int size = q->head->size;
   // TODO
   return size; // replace this statement
}


// display jobid's in Queue
void showQueue(Queue q)
{
   QueueNode *curr;
   curr = q->head;
   while (curr != NULL) {
      printf(" (%d,%d)", curr->jobid, curr->size);
      curr = curr->next;
   }
}

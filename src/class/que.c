/*************
 * Ce fichier implémente des listes FIFO appelés QUE_Elem ou QUE_Obj (équivalent)
 * ou QUE_Handle (pointeur sur les précédents) .
 * Ces listes servent à manger les trames en les mettant dans pendingBuffQue
 * **************/

/*
*  Copyright 2012 by Jean-Christophe Billard.
*  All rights reserved. Jean-Christophe Billard.
*  Restricted rights to use, duplicate or disclose are strictly
*  forbidden.
*
*/
/*
*  ============================= que.c =============================
*
*  Implement QUE manipulation for buffer passing from app through drivers.
*
*/

#include "class/que.h"


/*
*  ============ QUE_dequeue insert element to the head of the queue ============
*/
void QUE_enqueue(QUE_Handle queue, Ptr elem)
{
  QUE_Obj *prevElt = queue->prev;

  ((QUE_Elem *)elem)->next 	= (QUE_Elem *)queue;
  ((QUE_Elem *)elem)->prev 	= prevElt;

  ((QUE_Elem *)prevElt)->next  = (QUE_Elem *)elem;
  queue->prev = (QUE_Elem *)elem;

  return;
}

/*
*  ======== QUE_dequeue return the next element in a queue while removing it reference  ========
*/
Ptr QUE_dequeue(QUE_Handle queue)
{
  QUE_Handle head;

  head = queue->next;

  queue->next = head->next; 	        // Point to the furthermost elt
  (queue->next)->prev = queue; 	// Point prev of new next elt to the tail

  // Make extracted element to point to himself
  head->next = head;
  head->prev = head;

  return head;
}

/*
*  ======== QUE_remove removes reference of a given element in the QUE at an arbitrarily position  ========
*/
void QUE_remove(QUE_Handle elem)
{

  ((QUE_Elem *)((QUE_Elem *)elem)->prev)->next = ((QUE_Elem *)elem)->next;
  ((QUE_Elem *)((QUE_Elem *)elem)->next)->prev = ((QUE_Elem *)elem)->prev;

  ((QUE_Elem *)elem)->prev = elem;
  ((QUE_Elem *)elem)->next = elem;

  return;
}


/* -------------------------------------------------------------------------------------------
* Get first element from the QUE. Object still belonging to the QUE
* ------------------------------------------------------------------------------------------- */
Ptr QUE_peek(QUE_Handle queue)
{
  QUE_Obj *nextElt = ((QUE_Elem *)queue)->next;
  return nextElt;
}

/* -------------------------------------------------------------------------------------------
* Take last element from the QUE. Object reference still belonging to the queue.
* ------------------------------------------------------------------------------------------- */
Ptr QUE_peekTail(QUE_Handle queue)
{
  QUE_Handle lastElt = ((QUE_Elem *)queue)->prev;
  return lastElt;
}


/* -------------------------------------------------------------------------------------------
* Reset a QUE by wrapping it around. -> QUE point to itself
* ------------------------------------------------------------------------------------------- */
void QUE_reset(QUE_Handle queue)
{
  // Reset QUE by looping around
  ((QUE_Elem *)queue)->next = ((QUE_Elem *)queue);
  ((QUE_Elem *)queue)->prev = ((QUE_Elem *)queue);

  return;
}

/* -------------------------------------------------------------------------------------------
* Returns Queue length -> Should be used only for small queue length (resource consuming)
* ------------------------------------------------------------------------------------------- */
unsigned char QUE_length(QUE_Handle queue)
{
  QUE_Handle	elem = queue;
  unsigned char 	queueLength = 0;

  // Count number of elts in queue
  while(TRUE)
  {
    elem = QUE_peek(elem);

    if(elem == queue)
      return queueLength;

    queueLength++;
  }
}

/* -------------------------------------------------------------------------------------------
* Check if Queue is not empty
* ------------------------------------------------------------------------------------------- */
unsigned char QUE_isEmpty(QUE_Handle queue)
{
  // Get element from queue, and test if not queue itself. Returns true if different
  Ptr elem = QUE_peek(queue);

  if(elem == queue)
    return TRUE;

  return FALSE;
}

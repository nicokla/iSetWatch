/*
 * que.h
 *
 *  Created on: 16 f�vr. 2013
 *      Author: JC
 */

#ifndef QUE_H_
#define QUE_H_

#include <stdio.h>
#include "globalVar.h"
#include "init.h" // pour true et false

typedef void*           Ptr;

typedef struct QUE_Elem{
	struct QUE_Elem    *next; 		// Ptr to next element in QUE
	struct QUE_Elem    *prev;		// .....  prev ...........
}QUE_Elem, *QUE_Handle;

typedef QUE_Elem QUE_Obj;


/* Application passes buffers to the driver layer, which stores them in a QUE
	When in acquisition mode, driver request an element in the QUE. If nothing available,
	runs an overflow to the app for recovery. When it gets a valid ptr to buffer form a
	non empty QUE, it fills it with fresh data.
	Once buffer is full, it passes it back for access by the app.
*/

/*
 *  ======== QUE_new, initializes a queue as empty ========
 */
#define QUE_new(elem)           (elem)->next = (elem)->prev = (elem)

/*
 *  ======== QUE_next ========
 */
#define QUE_next(elem)          ((Ptr)((QUE_Elem *)(elem))->next)

/*
 *  ======== QUE_prev ========
 */
#define QUE_prev(elem)          ((Ptr)((QUE_Elem *)(elem))->prev)



void 	QUE_enqueue(QUE_Handle queue, Ptr elem); 	// Enqueue element in the queue
Ptr 	QUE_dequeue(QUE_Handle elem);	 			// Dequeue element from the queue
void    QUE_remove(QUE_Handle elem);

Ptr 	QUE_peek(QUE_Handle queue); 				// Peek head element of the queue
Ptr 	QUE_peekTail(QUE_Handle queue); 			// Get tail element of the queue
void 	QUE_reset(QUE_Handle queue); 				// Reset queue to its empty state
unsigned char 	QUE_length(QUE_Handle queue); 				// Counts number of elements from the queue
unsigned char 	QUE_isEmpty(QUE_Handle queue); 				// Determine if a queue is of length = 0


#endif /* QUE_H_ */

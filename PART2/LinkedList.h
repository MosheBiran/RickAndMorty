/*
 * LinkedList.h
 *
 *  Created on: Dec 11, 2019
 *      Author: ise
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Defs.h"

typedef struct Node_t Node;
typedef struct LinkedList_t* LinkedList;




//creates a LinkedList
LinkedList createLinkedList(CopyFunction copyFunction,FreeFunction freeList,EqualFunction equalFunction,PrintFunction printFunction);
status destroyList(LinkedList LinkedList);
status appendNode(LinkedList list,Element val);
status deleteNode(LinkedList list,Element val);
status displayList(LinkedList list);
Element searchByKeylnList(LinkedList list,Element key);
Element getDataByIndex(LinkedList list,int index);
int getLengthList(LinkedList list);
LinkedList copyList(LinkedList list);
bool equalList(LinkedList A,LinkedList B);





#endif /* LINKEDLIST_H_ */

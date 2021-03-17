/*
 * LinkedList.c
 *
 *  Created on: Dec 11, 2019
 *      Author: ise
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "LinkedList.h"



struct LinkedList_t
{
	int list_size;
	struct Node_t* head;
	struct Node_t* tail;
	CopyFunction copyFunction;
	FreeFunction freeFunction;
	EqualFunction equalFunction;
	PrintFunction printFunction;
};


struct Node_t
{
	Element val;
	struct Node_t* next;
};


LinkedList createLinkedList(CopyFunction copyFunction,FreeFunction freeList,EqualFunction equalFunction,PrintFunction printFunction)
{
	//Check the function*
	if(copyFunction==NULL || freeList==NULL || equalFunction==NULL || printFunction==NULL)
			return NULL;

	//Allocate a memory for LinkedList
	LinkedList  new_LinkedList_t = (LinkedList)malloc(sizeof( struct LinkedList_t));
	if(new_LinkedList_t==NULL)
		return NULL;


	//initialize
	new_LinkedList_t->list_size=0;
	new_LinkedList_t->head=NULL;
	new_LinkedList_t->tail=NULL;
	new_LinkedList_t->copyFunction=copyFunction;
	new_LinkedList_t->freeFunction=freeList;
	new_LinkedList_t->equalFunction=equalFunction;
	new_LinkedList_t->printFunction=printFunction;


	return new_LinkedList_t;
}


status destroyList(LinkedList list)
{
	if (list== NULL)
	{
		return failure;
	}

	if(list->head==NULL)
	{
		free(list);
		return success;
	}

	Node* temp;
	Node* cur=list->head;

	while(cur != NULL)
	{
		temp=cur->next;
		list->freeFunction(cur->val);
		free(cur);
		cur=temp;

	}
	free(list);
	list=NULL;
	return success;
}

status appendNode(LinkedList list,Element val)
{
	if(val==NULL)
		return failure;

	Node* new_node = (Node*)malloc(sizeof(struct Node_t));
	if(new_node==NULL)
		return failure;

	new_node->next=NULL;

	//case: if the list is empty
	if(list->head==NULL)
	{
		new_node->val=val;
		list->head=new_node;
		list->tail=new_node;
		list->list_size++;
		return success;
	}


	Node* temp = list->tail;

	temp->next=new_node;
	new_node->val=val;

	//update the tail pointer to be the new node
	list->tail=new_node;

	//update the size of list
	list->list_size++;

	return success;
}




status deleteNode(LinkedList list,Element val)
{
	if(list==NULL || val==NULL || list->head==NULL)
		return failure;


	Node* temp = list->head;

	//if its the head
	if(list->equalFunction(temp->val,val)==true)
	{
		list->head=temp->next;
		if(list->head==NULL)
			list->tail=NULL;
		list->list_size--;
		list->freeFunction(temp->val);
		free(temp);
		temp=NULL;
		return success;
	}

	while(temp!=NULL)
	{
		if(list->equalFunction(temp->next->val,val)==true)
		{
			Node* t=temp->next;
			temp->next=temp->next->next;

			list->list_size--;
			list->freeFunction(t->val);
			free(t);
			if(temp->next==NULL)
				list->tail=temp;
//			free(temp);
			return success;
		}
		temp=temp->next;
	}
//	free(temp);
	return failure;
}


status displayList(LinkedList list)
{

	//if the list is empty
	if(list==NULL || list->head==NULL)
		return failure;

	Node* temp=list->head;
	int size = 0;

	while(size!=list->list_size)
	{
		list->printFunction(temp->val);
		temp=temp->next;
		size++;
	}
	return success;
}


Element searchByKeylnList(LinkedList list,Element key)
{
	if(list==NULL || key==NULL || list->head==NULL)
		return NULL;

	Node* temp = list->head;
	while(temp!=NULL)
	{
		if(list->equalFunction(temp->val,key)==true)
		{
			return temp->val;
		}
		temp=temp->next;
	}
	return NULL;
}


Element getDataByIndex(LinkedList list,int index)
{
	if(list==NULL || index<1 || list->list_size<index)
		return NULL;
	Node* temp = list->head;
	int i=1;
	while(i<index)
	{
		temp=temp->next;
		i++;
	}
	return temp->val;
}

int getLengthList(LinkedList list)
{
	if(list==NULL)
		return -1;
	return list->list_size;
}

LinkedList copyList(LinkedList list){
	return list;
}

bool equalList(LinkedList strA,LinkedList strB){
	if(strA==NULL || strB==NULL)
		return false;

	if (getLengthList(strA)!=getLengthList(strB))
		return false;
	for(int i=1;i<getLengthList(strA);i++){
		if(getDataByIndex(strA,i)!=getDataByIndex(strB,i))
			return false;
	}
	return true;

}

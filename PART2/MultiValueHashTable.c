/*
 * MultiValueHashTable.c
 *
 *  Created on: Dec 2, 2020
 *      Author: ise
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HashTable.h"
#include "LinkedList.h"
#include "KeyValuePair.h"
#include "MultiValueHashTable.h"

struct MultiValueHashTable_s
{
	hashTable hashTable;
	int hashNumber;

	CopyFunction copyKey;
	CopyFunction copyValue;
	FreeFunction freeKey;
	FreeFunction freeValue;
	PrintFunction printKey;
	PrintFunction printValue;
	EqualFunction equalKey;
	TransformIntoNumberFunction transformIntoNumber;
};

static status printElemList(Element E){
	if(E==NULL)
		return failure;
	LinkedList list = (LinkedList)E;
	displayList(list);
	return success;

}

static status FreeElemList(Element E){
	if(E==NULL)
		return failure;

	LinkedList list = (LinkedList)E;
	destroyList(list);
	return success;

}

static Element copyElemlList(Element A){
	if(A==NULL)
		return NULL;
	return copyList(A);
}

MValHashTable createMultiValueHashTable(int hashNumber,CopyFunction copyKey,CopyFunction copyValue,FreeFunction freeKey,FreeFunction freeValue,PrintFunction printKey,PrintFunction printValue,EqualFunction equalKey,TransformIntoNumberFunction transformIntoNumber)
{
	//sanity check
	if(copyKey==NULL || freeKey==NULL ||printKey==NULL || copyValue==NULL || freeValue==NULL || printValue==NULL || equalKey==NULL || transformIntoNumber==NULL || hashNumber<=0)
		return NULL;


	hashTable newHash = createHashTable(copyKey, freeKey, printKey, copyElemlList, FreeElemList, printElemList, equalKey, transformIntoNumber, hashNumber);
	if(newHash==NULL)
		return NULL;


	MValHashTable mValHashTable = (MValHashTable)malloc(sizeof(struct MultiValueHashTable_s));
	if(mValHashTable==NULL)
		return NULL;

	mValHashTable->hashTable=newHash;
	mValHashTable->freeValue=freeValue;
	mValHashTable->copyValue=copyValue;
	mValHashTable->printValue=printValue;
	mValHashTable->freeKey=freeKey;
	mValHashTable->copyKey=copyKey;
	mValHashTable->printKey=printKey;
	mValHashTable->equalKey=equalKey;

	return mValHashTable;
}
status destroyMultiValueHashTable(MValHashTable mValHashTable)
{
	if(mValHashTable==NULL)
		return failure;
	destroyHashTable(mValHashTable->hashTable);
	mValHashTable->hashTable=NULL;
	free(mValHashTable);
	mValHashTable=NULL;
	return success;

}

//addToMultiValueHashTable(mValHashTable ,key : pc-Name , value : Jerry* )

status addToMultiValueHashTable(MValHashTable mValHashTable,Element key,Element value)
{
	if(mValHashTable==NULL || key==NULL || value==NULL)
		return failure;

	//the slot in the hase table is empty
	Element LinkListInfo =lookupInMultiValueHashTable(mValHashTable,key);
	if(LinkListInfo!=NULL){
		appendNode(LinkListInfo,value);
		return success;
	}


    LinkedList keyVperList = createLinkedList(mValHashTable->copyValue, mValHashTable->freeValue, mValHashTable->equalKey, mValHashTable->printValue);
	if (keyVperList==NULL){
		return failure;
	}

	appendNode(keyVperList,value);
	addToHashTable(mValHashTable->hashTable,key,keyVperList);
	return success;

}


Element lookupInMultiValueHashTable(MValHashTable mValHashTable,Element key)
{
	if(mValHashTable==NULL || key==NULL)
		return NULL;
	Element elem = lookupInHashTable(mValHashTable->hashTable, key);
	if(elem==NULL)
		return NULL;
	return elem;
}
status removeFromMultiValueHashTable(MValHashTable mValHashTable,Element key,Element value)
{
	if(mValHashTable==NULL || key==NULL || value==NULL)
		return failure;
	Element ValueIn=lookupInMultiValueHashTable(mValHashTable, key);
	if(ValueIn!=NULL){

		if(deleteNode(ValueIn, value)==success)
		{
			if(getLengthList(ValueIn)==0)
			{
				removeFromHashTable(mValHashTable->hashTable,key);
				ValueIn=NULL;
			}

			return success;
		}
	}
	return failure;
}
status displayMultiValueHashElementsByKey(MValHashTable mValHashTable,Element key)
{
	if(mValHashTable==NULL || key==NULL)
		return failure;
	Element elem = lookupInHashTable(mValHashTable->hashTable, key);
	if(elem==NULL)
		return failure;
	mValHashTable->printKey(key);
	displayList(elem);
	return success;
}



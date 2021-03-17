/*
 * HashTable.c
 *
 *  Created on: Nov 30, 2020
 *      Author: ise
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "HashTable.h"
#include "LinkedList.h"
#include "KeyValuePair.h"


struct hashTable_s
{
	LinkedList* hashArr;
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


int HashFuncSol(hashTable hashTable,Element key)
{
	return hashTable->transformIntoNumber(key) % hashTable->hashNumber;
}




hashTable createHashTable(CopyFunction copyKey, FreeFunction freeKey, PrintFunction printKey, CopyFunction copyValue, FreeFunction freeValue, PrintFunction printValue, EqualFunction equalKey, TransformIntoNumberFunction transformIntoNumber, int hashNumber)
{
	//sanity check
	if(copyKey==NULL || freeKey==NULL ||printKey==NULL || copyValue==NULL || freeValue==NULL || printValue==NULL || equalKey==NULL || transformIntoNumber==NULL || hashNumber<=0)
		return NULL;

	hashTable newHash = (hashTable)malloc(sizeof(struct hashTable_s));
	if(newHash==NULL)
		return NULL;


	newHash->copyKey=copyKey;
	newHash->copyValue=copyValue;
	newHash->freeKey=freeKey;
	newHash->freeValue=freeValue;
	newHash->equalKey=equalKey;
	newHash->printKey=printKey;
	newHash->printValue=printValue;
	newHash->transformIntoNumber=transformIntoNumber;

	newHash->hashNumber=hashNumber;
	newHash->hashArr= (LinkedList*)malloc(hashNumber*sizeof(LinkedList));
	if (newHash->hashArr == NULL) {
		free(newHash);
		return NULL;
	}

	for(int i=0;i<hashNumber;i++)
		newHash->hashArr[i]= NULL;


	return newHash;
}
status destroyHashTable(hashTable hashTable)
{
	for(int i=0;i<hashTable->hashNumber;i++)
		destroyList(hashTable->hashArr[i]);
	free(hashTable->hashArr);
	hashTable->hashArr=NULL;
	free(hashTable);
	hashTable=NULL;
	return success;
}

//calculate the hash function solution for the key.

//-------------------Shell Functions------------------------------------------
//-------------------Assuming the node is KeyValPair--------------------------
bool equalKeyToStr(Element keyValPair,Element key)
{
	return isEqualKey(keyValPair, key);
}

status displayNodeVal(Element node)
{
	displayKey(node);
	return displayValue(node);
}

status destroyNode(Element node)
{
	return destroyKeyValuePair(node);
}

Element getNodeinfo(Element nodeVal)
{
	return getValue((KeyValuePair)nodeVal);
}

//----------------------------------------------------------------------------


status addToHashTable(hashTable hashTable, Element key,Element value)
{
	//check also if the key exist
	if( key==NULL || value==NULL || lookupInHashTable(hashTable, key)!=NULL)
		return failure;

	int hashFuncSol = HashFuncSol(hashTable, key);
	Element cpyKey= hashTable->copyKey(key);

	KeyValuePair keyValPair= createKeyValuePair(cpyKey,value,hashTable->copyKey,hashTable->copyValue,hashTable->freeKey,hashTable->freeValue,hashTable->printKey,hashTable->printValue,hashTable->equalKey);
	if(keyValPair==NULL)
		return failure;

	if(hashTable->hashArr[hashFuncSol]==NULL)
	{
		hashTable->hashArr[hashFuncSol]=createLinkedList(hashTable->copyValue, destroyNode, equalKeyToStr, displayNodeVal);
		if(hashTable->hashArr[hashFuncSol]==NULL)
			return failure;
	}

	appendNode(hashTable->hashArr[hashFuncSol], keyValPair);
	return success;
}
Element lookupInHashTable(hashTable hashTable, Element key)
{
	if(hashTable==NULL || key==NULL)
		return NULL;
	int hashFuncSol = HashFuncSol(hashTable, key);
	Element elem=searchByKeylnList(hashTable->hashArr[hashFuncSol], key);
	if(elem==NULL)
		return NULL;
	return getNodeinfo(elem);
}
status removeFromHashTable(hashTable hashTable, Element key)
{
	if(hashTable==NULL || key==NULL || lookupInHashTable(hashTable, key)==NULL)
		return failure;
	int hashFuncSol = HashFuncSol(hashTable, key);
	if(deleteNode(hashTable->hashArr[hashFuncSol], key)==success)
	{
		if(getLengthList(hashTable->hashArr[hashFuncSol])==0)

		{
			destroyList(hashTable->hashArr[hashFuncSol]);
			hashTable->hashArr[hashFuncSol]=NULL;
		}

		return success;
	}
	return failure;
}
status displayHashElements(hashTable hashTable)
{
	if(hashTable==NULL)
		return failure;
	for(int i=0;i<hashTable->hashNumber;i++)
	{
		displayList(hashTable->hashArr[i]);
	}
	return success;
}




/*
 * KeyValuePair.c
 *
 *  Created on: Nov 30, 2020
 *      Author: ise
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "KeyValuePair.h"



struct KeyValuePair_s
{
	Element key;
	Element value;
	CopyFunction copyKey;
	CopyFunction copyValue;
	FreeFunction freeKey;
	FreeFunction freeValue;
	PrintFunction printKey;
	PrintFunction printValue;
	EqualFunction equalKey;
};

KeyValuePair createKeyValuePair(Element key,Element value,CopyFunction copyKey,CopyFunction copyValue,FreeFunction freeKey,FreeFunction freeValue,PrintFunction printKey,PrintFunction printValue,EqualFunction equalKey)
{
	if(key==NULL || value==NULL || copyKey==NULL || copyValue==NULL || freeKey==NULL || freeValue==NULL || printKey==NULL || printValue==NULL || equalKey==NULL)
		return NULL;

	KeyValuePair newKeyValPair = (KeyValuePair)malloc(sizeof( struct KeyValuePair_s));
	if(newKeyValPair==NULL)
		return NULL;

	newKeyValPair->copyKey=copyKey;
	newKeyValPair->copyValue=copyValue;
	newKeyValPair->freeKey=freeKey;
	newKeyValPair->freeValue=freeValue;
	newKeyValPair->equalKey=equalKey;
	newKeyValPair->printKey=printKey;
	newKeyValPair->printValue=printValue;

	newKeyValPair->key=key;
	newKeyValPair->value=value;
	return newKeyValPair;
}
status destroyKeyValuePair(KeyValuePair keyValPair)
{
	if(keyValPair==NULL)
		return failure;

	keyValPair->freeKey(keyValPair->key);
	keyValPair->key=NULL;
	keyValPair->freeValue(keyValPair->value);
	keyValPair->value=NULL;

	free(keyValPair);
	keyValPair=NULL;
	return success;
}
status displayValue(KeyValuePair keyValPair)
{
	if(keyValPair==NULL)
		return failure;
	keyValPair->printValue(keyValPair->value);
	return success;
}
status displayKey(KeyValuePair keyValPair)
{
	if(keyValPair==NULL)
		return failure;
	keyValPair->printKey(keyValPair->key);
	return success;
}

Element getValue(KeyValuePair keyValPair) {return keyValPair->value;}
Element getKey(KeyValuePair keyValPair) {return keyValPair->key;}

bool isEqualKey(KeyValuePair keyValPair,Element key)
{
	if(keyValPair==NULL || key==NULL)
		return false;
	if(keyValPair->equalKey(getKey(keyValPair),key)==true)
		return true;
	return false;
}



/*
 * MultiValueHashTable.h
 *
 *  Created on: Nov 30, 2020
 *      Author: ise
 */

#ifndef MULTIVALUEHASHTABLE_H_
#define MULTIVALUEHASHTABLE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Defs.h"

typedef struct MultiValueHashTable_s* MValHashTable;

MValHashTable createMultiValueHashTable(int hashNumber,CopyFunction copyKey,CopyFunction copyValue,FreeFunction freeKey,FreeFunction freeValue,PrintFunction printKey,PrintFunction printValue,EqualFunction equalKey,TransformIntoNumberFunction transformIntoNumber);
status destroyMultiValueHashTable(MValHashTable mValHashTable);
status addToMultiValueHashTable(MValHashTable mValHashTable,Element key,Element value);
Element lookupInMultiValueHashTable(MValHashTable mValHashTable,Element key);
status removeFromMultiValueHashTable(MValHashTable mValHashTable,Element key,Element value);
status displayMultiValueHashElementsByKey(MValHashTable mValHashTable,Element key);

#endif /* MULTIVALUEHASHTABLE_H_ */

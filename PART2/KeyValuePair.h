/*
 * KeyValuePair.h
 *
 *  Created on: Nov 30, 2020
 *      Author: ise
 */

#ifndef KEYVALUEPAIR_H_
#define KEYVALUEPAIR_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Defs.h"

typedef struct KeyValuePair_s* KeyValuePair;

KeyValuePair createKeyValuePair(Element key,Element value,CopyFunction copyKey,CopyFunction copyValue,FreeFunction freeKey,FreeFunction freeValue,PrintFunction printKey,PrintFunction printValue,EqualFunction equalKey);
status destroyKeyValuePair(KeyValuePair keyValPair);
status displayValue(KeyValuePair keyValPair);
status displayKey(KeyValuePair keyValPair);
Element getValue(KeyValuePair keyValPair);
Element getKey(KeyValuePair keyValPair);
bool isEqualKey(KeyValuePair keyValPair,Element key);


#endif /* KEYVALUEPAIR_H_ */

/*
 * Jerry.h
 *
 *  Created on: Nov 13, 2020
 *      Author: ise
 */

#ifndef JERRY_H_
#define JERRY_H_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Defs.h"

typedef struct planet{
	char *PlanetName;
	float X;
	float Y;
	float Z;
}planet;

typedef struct Origin{
	struct planet *MyHomePlanet;
	char *dimension;
}Origin;

typedef struct PhysicalCharacteristics{
	char *Name;
	float Value;
}PhysicalInfo;

typedef struct Jerry{
	char *ID;
	int happinessLevel;
	struct Origin *myOrigin;
	struct PhysicalCharacteristics **PhysicalInfo;
	int numOfPhysicalInfo;
}Jerry;


planet* CreatePlanet(char*,float,float,float);
Origin* CreateOrigin(char*,planet*);
Jerry* CreateJerry(char*,int,Origin*);
PhysicalInfo* CreatePhysicalCharacteristics(char*,float);
bool IsPhysicalExists(Jerry* , char*);
status AddPhysicalCharacteristics(Jerry*, char*,float);
status DeletPhysicalCharacteristics(Jerry*, char*);
status PrintJerry(Jerry*);
status PrintPlanet(planet*);
status PrintOrigin(Origin*);
status PrintPhysicalCharacteristics(Jerry*);


#endif /* JERRY_H_ */

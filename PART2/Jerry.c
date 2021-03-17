
#include "Jerry.h"
#include "Defs.h"

Planet* CreatePlanet(char *PName,float X, float Y ,float Z)//Creates a planet-type object
{
	if(PName == NULL)//Sanity test (checks that the values obtained make sense)
		return NULL;

	Planet *Myplanet = (Planet*)malloc(sizeof(Planet)); // Allocating memory for planet
	if(Myplanet == NULL)
		{
			//Check that the memory has been assigned
			return NULL;
		}
	Myplanet->PlanetName=(char*)malloc(sizeof(char)*(strlen(PName)+1));
	if(Myplanet->PlanetName == NULL)//Check that the memory has been assigned
			{
				free(Myplanet);//freeing the Allocating memory for planet
				return NULL;
			}
	strcpy(Myplanet->PlanetName,PName);
	Myplanet->X=X;
	Myplanet->Y=Y;
	Myplanet->Z=Z;
	return Myplanet;
}
Origin* CreateOrigin(char *DName,Planet *MyPlanet)//Creates a Origin-type object
{
	if(DName == NULL || MyPlanet==NULL)//Sanity test (checks that the values obtained make sense)
			return NULL;

	Origin *MyOrigin = (Origin*)malloc(sizeof(Origin)); // Allocating memory for Origin
	if(MyOrigin == NULL)//Check that the memory has been assigned
		{

			return NULL;
		}
	MyOrigin->dimension=(char*)malloc(sizeof(char)*(strlen(DName)+1));//Allocating memory for dimension
	if(MyOrigin->dimension == NULL)//Check that the memory has been assigned
		{

			free(MyOrigin);//freeing the Allocating memory for MyOrigin
			return NULL;
		}

	strcpy(MyOrigin->dimension,DName);//copying the name of the dimension
	MyOrigin->MyHomePlanet=MyPlanet;
	return MyOrigin;

}
Jerry* CreateJerry(char* Jid,int happinessLevel,Origin* MyOrigin)//Creates a Jerry-type object
{
	if(Jid == NULL || happinessLevel<0 ||MyOrigin==NULL)//Sanity test (checks that the values obtained make sense)
		return NULL;
	Jerry *NewJerry = (Jerry*)malloc(sizeof(Jerry));// Allocating memory for type
	if(NewJerry == NULL)
	{
		return NULL;
	}
	NewJerry->ID=(char*)malloc(sizeof(char)*(strlen(Jid)+1));// Allocating memory for Jid
	if(NewJerry->ID == NULL)
	{
		free(NewJerry);
		return NULL;
	}
	strcpy(NewJerry->ID,Jid);
	NewJerry->PhysicalInfo=NULL;
	NewJerry->happinessLevel=happinessLevel;
	NewJerry->myOrigin=MyOrigin;
	NewJerry->numOfPhysicalInfo=0;
	return NewJerry;

}
PhysicalInfo* CreatePhysicalCharacteristics(char* PhysicalName,float PhysicalVal)//Creates a PhysicalInfo-type object
{
	if(PhysicalName == NULL || PhysicalVal<0)//Sanity test (checks that the values obtained make sense)
	{
		return NULL;
	}
	PhysicalInfo *MyPhysicalInfo = (PhysicalInfo*)malloc(sizeof(PhysicalInfo)); // Allocating memory for type PhysicalInfo*
	if(MyPhysicalInfo == NULL)
		{

			return NULL;
		}
	MyPhysicalInfo->Name=(char*)malloc(sizeof(char)*(strlen(PhysicalName)+1));// Allocating memory for PhysicalName
	if(MyPhysicalInfo->Name == NULL)
		{

			free(MyPhysicalInfo);
			return NULL;
		}
	strcpy(MyPhysicalInfo->Name,PhysicalName);

	MyPhysicalInfo->Value=PhysicalVal;

	return MyPhysicalInfo;
}
bool IsPhysicalExists(Jerry* MyJerry, char* PhysicalName)//Checks if an object exists in my array and returns a Boolean value
{
	if(MyJerry == NULL || PhysicalName==NULL || MyJerry->numOfPhysicalInfo==0)//Sanity test (checks that the values obtained make sense)
	{
		return false;
	}


	for(int i=0;i<MyJerry->numOfPhysicalInfo;i++)//Go over the list and look for the object with the same name
	{
		if(strcmp(MyJerry->PhysicalInfo[i]->Name,PhysicalName)==0)
		{
			return true;
		}
	}
	return false;
}
status AddPhysicalCharacteristics(Jerry* MyJerry, char *PhysicalName,float PhysicalVal)//Adds PhysicalInfo to a Jerry
{
	if(MyJerry == NULL || PhysicalName==NULL ||PhysicalVal<0 || IsPhysicalExists(MyJerry,PhysicalName)==true)//Sanity test (checks that the values obtained make sense)
	{
		return failure;
	}

	if(MyJerry->PhysicalInfo==NULL)//If Jerry has no PhysicalInfo at all
	{
		MyJerry->PhysicalInfo = (PhysicalInfo**)malloc(sizeof(PhysicalInfo*));// Allocating memory for type
		if (MyJerry->PhysicalInfo == NULL) // Checks if the allocation succeed
		{
			return failure;
		}
		MyJerry->PhysicalInfo[0]=CreatePhysicalCharacteristics(PhysicalName,PhysicalVal);
		if(MyJerry->PhysicalInfo[0]==NULL)
		{
			return failure;
		}
		MyJerry->numOfPhysicalInfo++;


	}
	else
	{
		MyJerry->numOfPhysicalInfo++;

		MyJerry->PhysicalInfo= (PhysicalInfo**)realloc(MyJerry->PhysicalInfo,(MyJerry->numOfPhysicalInfo)* sizeof(PhysicalInfo*));//Resize the existing list
		if (MyJerry->PhysicalInfo == NULL) // Checks if the allocation succeed
		{
			return failure;
		}
		MyJerry->PhysicalInfo[MyJerry->numOfPhysicalInfo-1] = CreatePhysicalCharacteristics(PhysicalName,PhysicalVal);
		if (MyJerry->PhysicalInfo[MyJerry->numOfPhysicalInfo-1] == NULL) // Checks if we Insert the type to the designated index
		{
			return failure;
		}

	}
//	MyJerry->numOfPhysicalInfo++;
	return success;

}
status DeletPhysicalCharacteristics(Jerry* MyJerry, char *PhysicalToDel)
{
	if(MyJerry == NULL || PhysicalToDel==NULL || MyJerry->numOfPhysicalInfo==0 || IsPhysicalExists(MyJerry,PhysicalToDel)!=true )//Sanity test (checks that the values obtained make sense)
		{
			return failure;
		}
	for(int i=0;i<MyJerry->numOfPhysicalInfo;i++)//Goes through the list and searches for the object with the same name
	{
			if(strcmp(MyJerry->PhysicalInfo[i]->Name,PhysicalToDel)==0)
			{
				// Once we arrived to the type we want to delete, we will re-order the array by moving the types to the left, for putting the NULL in the last index

				PhysicalInfo* tempPhysicalInfo;
				free(MyJerry->PhysicalInfo[i]->Name);//Before we lose it, we release the name of the object
				for (int j = i  ; i < MyJerry->numOfPhysicalInfo ; j++)
				{
					if(j==MyJerry->numOfPhysicalInfo -1)
						break;
					tempPhysicalInfo = MyJerry->PhysicalInfo[j];//Move forward all objects in an array from an object that we want to delete
					MyJerry->PhysicalInfo[j] = MyJerry->PhysicalInfo[j+1];
					MyJerry->PhysicalInfo[j+1] = tempPhysicalInfo;
				}
				MyJerry->numOfPhysicalInfo--;
				free(MyJerry->PhysicalInfo[MyJerry->numOfPhysicalInfo]);// Freeing the last index in the array
				MyJerry->PhysicalInfo[MyJerry->numOfPhysicalInfo]=NULL;
				//MyJerry->PhysicalInfo= (PhysicalInfo**)realloc(MyJerry->PhysicalInfo,sizeof(MyJerry->PhysicalInfo)* sizeof(PhysicalInfo*));
				// In case we deleted the only type left on the list, we will free also the list itself
				if(MyJerry->numOfPhysicalInfo== 0)
				{
					free(MyJerry->PhysicalInfo);
					MyJerry->PhysicalInfo = NULL;
					return success;
				}
				return success;
			}

		}

	return failure;
}


status PrintJerry(Jerry* MyJerry)
{
	if(MyJerry == NULL)//Sanity test (checks that the values obtained make sense)
		return failure;

	printf("Jerry , ID - %s : \n",MyJerry->ID);
	printf("Happiness level : %d \n",MyJerry->happinessLevel);
	PrintOrigin(MyJerry->myOrigin);
	PrintPhysicalCharacteristics(MyJerry);
	return success;
}



status PrintPlanet(Planet* myPlanet)
{
	if(myPlanet == NULL)//Sanity test (checks that the values obtained make sense)
		return failure;

	printf("Planet : %s (%.2f,%.2f,%.2f) \n",myPlanet->PlanetName,myPlanet->X,myPlanet->Y,myPlanet->Z);
	return success;

}
status PrintOrigin(Origin* MyOrigin)
{
	if(MyOrigin == NULL || MyOrigin->dimension == NULL)//Sanity test (checks that the values obtained make sense)
		return failure;

	printf("Origin : %s \n",MyOrigin->dimension);
	PrintPlanet(MyOrigin->MyHomePlanet);
	return success;

}
status PrintPhysicalCharacteristics(Jerry* MyJerry)
{
	if(MyJerry==NULL || MyJerry->PhysicalInfo == NULL)//Sanity test (checks that the values obtained make sense)
		return failure;

	printf("Jerry's physical Characteristics available : \n");
	printf("\t");
	for(int i=0;i<MyJerry->numOfPhysicalInfo;i++)
	{
		printf("%s : %.2f",MyJerry->PhysicalInfo[i]->Name,MyJerry->PhysicalInfo[i]->Value);
		if(i != MyJerry->numOfPhysicalInfo-1)
		{
			printf(" , ");
		}
		if(i == MyJerry->numOfPhysicalInfo-1)
		{
			printf(" \n");
		}
	}
	return success;

}

status DeletJerry(Jerry* MyJerry)//Jerry Destructor
{
	if(MyJerry==NULL)
		return failure;

	DeletOrigin(MyJerry->myOrigin);
	MyJerry->myOrigin=NULL;
	int size=MyJerry->numOfPhysicalInfo;
	for(int i=0;i<size;i++){
		DeletPhysicalCharacteristics(MyJerry,MyJerry->PhysicalInfo[0]->Name);
	}
	free(MyJerry->ID);
	MyJerry->ID=NULL;
	free(MyJerry);
	return success;
}



status DeletOrigin(Origin* MyOrigin)//Origin Destructor
{
	if(MyOrigin==NULL)
		return failure;


	free(MyOrigin->dimension);
	MyOrigin->dimension=NULL;
	//DeletPlanet(MyOrigin->MyHomePlanet);
	MyOrigin->MyHomePlanet=NULL;
	free(MyOrigin);
	return success;


}
status DeletPlanet(Planet* Myplanet)//Planet Destructor
{
	if(Myplanet==NULL)
		return failure;

	free(Myplanet->PlanetName);
	Myplanet->PlanetName=NULL;
	free(Myplanet);
	return success;


}

//-----------------------------------functions for work part 2--------------------------------




bool EqualJerry(Jerry* myJerry, Jerry* toCompareJerry)
{
	if(myJerry == NULL || toCompareJerry == NULL){
		return false;
	}
	if(strcmp(myJerry->ID,toCompareJerry->ID)==0)
		return true;
	return false;
}

Jerry* copyJerry(Jerry* myJerry)
{
	if(myJerry == NULL)
		return NULL;
	Jerry* cpyJerry = CreateJerry(myJerry->ID,myJerry->happinessLevel,myJerry->myOrigin);
//	cpyJerry->numOfPhysicalInfo=myJerry->numOfPhysicalInfo;
	for(int i=0;i<myJerry->numOfPhysicalInfo;i++){
		AddPhysicalCharacteristics(cpyJerry,myJerry->PhysicalInfo[i]->Name,myJerry->PhysicalInfo[i]->Value);
	}
	return cpyJerry;
}




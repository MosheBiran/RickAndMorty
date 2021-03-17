/*
 * JerryBoreeMain.c
 *
 *  Created on: Nov 30, 2020
 *      Author: ise
 */
#include "Defs.h"
#include "Jerry.h"
#include "HashTable.h"
#include "LinkedList.h"
#include "KeyValuePair.h"
#include "MultiValueHashTable.h"
#include <math.h>

//for the findTheBestHashNumber func.
int roundNo(float num)
{
    return num < 0 ? num - 0.5 : num + 0.5;
}

//multiply the number with 1.3 and finds the closest prime number
int findTheBestHashNumber(int num)
{
	float newNum = num*1.3;
	newNum = roundNo(newNum);
	int newNum2 = (int)newNum;
	bool isPrime = true;
	while(isPrime==true)
	{
		for(int i=2;i<newNum2-1;i++ )
		{
			if(newNum2%i==0)
				isPrime=false;
		}
		if(isPrime==true)
			return newNum2;
		isPrime = true;
		newNum2++;
	}
	return 0;
}



Planet* FindMyPlant(char* MyPlanet,Planet** array_of_planets,int num_planets)
{
	if(num_planets==0)
	{
		return NULL;
	}
	for(int i=0;i<num_planets;i++)
	{
		if (strcmp(array_of_planets[i]->PlanetName,MyPlanet)==0){
			return array_of_planets[i];
		}
	}
	return NULL;
}

int transformIntoNumber(Element str)
{
	int num=0;
	int i=0;
	char* str1 = (char*)str;
	while(str1[i]!='\0')
	{
		num+=str1[i];
		i++;
	}
	return num;
}

int switchCaseInt(){
	char inString[300];
	scanf("%s",inString);
	if(strlen(inString)>1)
		return 0;
	return atoi(inString);


}
//-----------------------Functions assuming the key is a string---------------------------
status freeKey(Element key)
{
	if(key==NULL)
		return failure;
	free(key);
	key=NULL;
	return success;
}

Element copyKey(Element key)
{
	if(key==NULL)
		return NULL;
	Element elem = (char*)malloc(sizeof(char)*(strlen(key)+1));
	strcpy(elem,key);
	return elem;
}

status printKey(Element key)
{
	if(key==NULL)
		return failure;
	char* str = (char*)key;
	printf("%s : \n",str);
	return success;
}

bool equalKey(Element key1,Element key2)
{
	if(key1==NULL || key2==NULL)
		return false;
	if(strcmp((char*)key1,(char*)key2)==0)
		return true;
	return false;
}
/*-------------------J'erry Shell function----------------------------*/
Element copyJerryShell(Element elem)
{
	if(elem == NULL)
		return NULL;
	Jerry* cpyJerry = (Jerry*)elem;
	return copyJerry(cpyJerry);
}

bool equalJerriesShell(Element elem1,Element elem2)
{
	if(elem1==NULL || elem2==NULL)
		return false;
	Jerry * jerry1 = (Jerry*)elem1;
	Jerry * jerry2 = (Jerry*)elem2;
	return EqualJerry(jerry1,jerry2);

}

status DeletJerryShell(Element MyJerry)//Jerry Destructor
{
	if(MyJerry==NULL)
		return failure;
	return DeletJerry((Jerry*)MyJerry);
}
status PrintJerryShell(Element MyJerry)
{
	if(MyJerry == NULL)//Sanity test (checks that the values obtained make sense)
		return failure;

	return PrintJerry((Jerry*)MyJerry);
}

status DeletJerryToList(Element elem){
	elem=NULL;
	return success;
}
/*----------------------help function--------------------------------*/

float getPhysicalByName(Jerry* MyJerry, char* PhysicalName)//Checks if an object exists in my array and returns a Boolean value
{
	if(MyJerry == NULL || PhysicalName==NULL || MyJerry->numOfPhysicalInfo==0)//Sanity test (checks that the values obtained make sense)
	{
		return 0.0;
	}

	for(int i=0;i<MyJerry->numOfPhysicalInfo;i++)//Go over the list and look for the object with the same name
	{
		if(strcmp(MyJerry->PhysicalInfo[i]->Name,PhysicalName)==0)
		{
			return MyJerry->PhysicalInfo[i]->Value;
		}
	}
	return 0.0;
}

Jerry* JerryRumble(LinkedList list,int val,char* key){
	if (list==NULL || key==NULL){
		return NULL;
	}
	Jerry* bestJerry=(Jerry*)getDataByIndex(list,1);
	float currJerryPcVal= getPhysicalByName(bestJerry,key);
	int bastscore=abs(val-currJerryPcVal);
	int myscore=0;

	for(int i=2;i<=getLengthList(list);i++){
		Jerry* currJerry=(Jerry*)getDataByIndex(list,i);
		currJerryPcVal= getPhysicalByName(currJerry,key);
		myscore=abs(val- currJerryPcVal);
		if(myscore<bastscore){
			bastscore=myscore;
			bestJerry=currJerry;
		}
	}
	return bestJerry;
}

Jerry* sadestJerry(LinkedList list){
	if (list==NULL){
		return NULL;
	}
	Jerry* bestJerry=(Jerry*)getDataByIndex(list,1);
	int bastscore=bestJerry->happinessLevel;;
	int myscore=0;
	for(int i=2;i<=getLengthList(list);i++){
		Jerry* currJerry=(Jerry*)getDataByIndex(list,i);
		myscore=currJerry->happinessLevel;
		if(myscore<bastscore){
			bastscore=myscore;
			bestJerry=currJerry;
		}
	}
	return bestJerry;
}
status switch8helper(LinkedList listOfJerries,int smallerthen,int smaullDicrec ,int bigIncrec){
	for(int i=1;i<=getLengthList(listOfJerries);i++){
			Jerry* currJerry=(Jerry*)getDataByIndex(listOfJerries,i);
			if(currJerry->happinessLevel<smallerthen){
				currJerry->happinessLevel-=smaullDicrec;
			}
			else{
				currJerry->happinessLevel+=bigIncrec;
			}
			if(currJerry->happinessLevel<0){
				currJerry->happinessLevel=0;
			}
			if(100<currJerry->happinessLevel){
				currJerry->happinessLevel=100;
			}

	}
	displayList(listOfJerries);
	return success;
}


void deletElemFromAll(Jerry* JerryInList,hashTable JerrysIDhash,LinkedList listOfJerries,MValHashTable JerrysPhysicalHash)
{
	removeFromHashTable(JerrysIDhash,JerryInList->ID);

	for(int i=0;i<JerryInList->numOfPhysicalInfo;i++){
		removeFromMultiValueHashTable(JerrysPhysicalHash,JerryInList->PhysicalInfo[i]->Name,JerryInList);
	}

	deleteNode(listOfJerries,JerryInList);


}


//-------------------------------------------------------------------------------------------
int main(int argc , char* argv[])
{

	size_t line_buf_size = 0;
	ssize_t line_size;
	char *line_buf=NULL;//The current line
	int num_planets = atoi(argv[1]);

	/*---------------------------------------------------read file------------------------------------------------------------*/
	FILE *fp = fopen(argv[2], "r");
	if (!fp)
	{
		fprintf(stderr, "Error opening file '%s'\n", argv[3]);
		return EXIT_FAILURE;
	}
	line_size = getline(&line_buf, &line_buf_size, fp);
	Planet** array_of_planets = (Planet**) malloc(sizeof(Planet*)*num_planets);//allocate memory to array of planets
	if ( array_of_planets==NULL )
	{
		printf("Memory Problem");
		free(array_of_planets);
		array_of_planets=NULL;
		exit(-1);
	}


	LinkedList listOfJerries = createLinkedList(copyJerryShell, DeletJerryShell, equalJerriesShell, PrintJerryShell);
	//to count the PhysChar overall for the multi hash number
	LinkedList listOfPhysChar = createLinkedList(copyKey, freeKey, equalKey , printKey);
	if( listOfJerries==NULL || listOfPhysChar==NULL )
	{
		printf("Memory Problem");
		destroyList(listOfJerries);
		destroyList(listOfPhysChar);
		listOfJerries=NULL;
		listOfPhysChar=NULL;
		exit(-1);
	}

	/*---------------------------------------------------Planets------------------------------------------------------------*/

	if ((((strcmp(strtok(line_buf,",\r\n\" "),"Planets"))))==0)
	{

		for(int i=0;i<num_planets;i++)
		{
			char *PlanetsName;
			float X;
			float Y;
			float Z;
			line_size = getline(&line_buf, &line_buf_size, fp);
			PlanetsName=strtok(line_buf,",");
			X = atof(strtok(NULL,","));
			Y = atof(strtok(NULL,","));
			Z = atof(strtok(NULL,","));
			array_of_planets[i]=CreatePlanet(PlanetsName,X,Y,Z);
			if(array_of_planets[i]==NULL)
			{
				/*------------if we Failed to allocate memory to one of the Planets---------------*/

				if(i>0)//if the array is not empty
				{
					for(int j=0;j<i;j++)
					{
						DeletPlanet(array_of_planets[j]);
						array_of_planets[j]=NULL;
					}
				}
				free(array_of_planets);
				array_of_planets=NULL;
				destroyList(listOfJerries);
				listOfJerries=NULL;
				printf("Memory Problem");
				exit(-1);//close
				/*---------------------------------------------------------------------------------*/
			}
		}
	}


	line_size = getline(&line_buf, &line_buf_size, fp);

	/*---------------------------------------------------J'erries------------------------------------------------------------*/

	if ((((strcmp(strtok(line_buf,",\r\n\" "),"Jerries"))))==0)
	{

		char *ID;
		char *MyOrigin;
		char *MyPlanet;
		int happinessLevel;
		char* ret;
		char* line;
		line_size = getline(&line_buf, &line_buf_size, fp);

		while(!feof(fp))
		{
			ID=strtok(line_buf,",");
			MyOrigin = strtok(NULL,",");
			MyPlanet = strtok(NULL,",");
			happinessLevel = atoi(strtok(NULL,","));
			Planet* tempPlanet=FindMyPlant(MyPlanet,array_of_planets,num_planets);
			Origin* tempOrigin=CreateOrigin(MyOrigin,tempPlanet);
			Jerry* jerry = CreateJerry(ID,happinessLevel,tempOrigin);

			if(jerry==NULL)
			{
				/*------------if we Failed to allocate memory to one of the J'errys---------------*/

				DeletJerry(jerry);
				jerry=NULL;
				destroyList(listOfJerries);
				for(int indexP = 0 ; indexP < num_planets ; indexP++ )
				{
					DeletPlanet(array_of_planets[indexP]);
					array_of_planets[indexP]=NULL;
				}

				free(array_of_planets);
				array_of_planets=NULL;

				listOfJerries=NULL;

				printf("Memory Problem");
				exit(-1);//close
				/*---------------------------------------------------------------------------------*/
			}
			line_size = getline(&line_buf, &line_buf_size, fp);
			ret=strchr(line_buf,'\t');

			while((ret!=NULL) && (line_size!=-1))
			{
				line=strtok(line_buf,"\t");
				char* PinfoName=strtok(line," : ");
				float VinfoName=atof(strtok(NULL,"\r\n\" "));

				status stat=AddPhysicalCharacteristics(jerry,PinfoName,VinfoName);
				if(stat!=success)
				{
					/*------------if we Failed to allocate memory to one of the Physical Characteristics---------------*/
					DeletJerry(jerry);
					jerry=NULL;
					destroyList(listOfJerries);

					for(int indexP = 0 ; indexP < num_planets ; indexP++ )
					{
						DeletPlanet(array_of_planets[indexP]);
						array_of_planets[indexP]=NULL;
					}

					free(array_of_planets);
					array_of_planets=NULL;

					listOfJerries=NULL;

					printf("Memory Problem");
					exit(-1);//close
					/*---------------------------------------------------------------------------------*/
				}
				//add to the listOfPhysChar to count the physChar overall.
				char* cpyPinfoName = copyKey(PinfoName);
				Element isExist = searchByKeylnList(listOfPhysChar, cpyPinfoName);
				if(isExist==NULL)
					appendNode(listOfPhysChar, cpyPinfoName);
				else
					freeKey(cpyPinfoName);

				isExist=NULL;
				line_size = getline(&line_buf, &line_buf_size, fp);
				ret=strchr(line_buf,'\t');
			}
			appendNode(listOfJerries, jerry);
		}
	}

	free(line_buf);//freeing the line pointer
	line_buf = NULL;
	fclose(fp);//closing the file

	int hashNumber =findTheBestHashNumber(getLengthList(listOfJerries));
	int multiHashNumber =findTheBestHashNumber(getLengthList(listOfPhysChar));

	destroyList(listOfPhysChar);
	listOfPhysChar=NULL;

	hashTable JerrysIDhash=createHashTable(copyKey, freeKey, printKey , copyJerryShell, DeletJerryToList, PrintJerryShell, equalKey, transformIntoNumber, hashNumber);
	MValHashTable JerrysPhysicalHash=createMultiValueHashTable(multiHashNumber,copyKey,copyJerryShell,freeKey,DeletJerryToList,printKey,PrintJerryShell,equalKey,transformIntoNumber);

	if(JerrysIDhash==NULL || JerrysPhysicalHash==NULL){
		if(JerrysIDhash!=NULL)
			destroyHashTable(JerrysIDhash);

		if(JerrysPhysicalHash!=NULL)
			destroyMultiValueHashTable(JerrysPhysicalHash);

		destroyList(listOfJerries);

		for(int indexP = 0 ; indexP < num_planets ; indexP++ )
		{
			DeletPlanet(array_of_planets[indexP]);
			array_of_planets[indexP]=NULL;
		}

		free(array_of_planets);
		array_of_planets=NULL;

		listOfJerries=NULL;

		printf("Memory Problem");
		exit(-1);//close
	}

	//adding info in to JerrysIDhash

	for(int i=1;i<=getLengthList(listOfJerries);i++){
		Jerry* tempJerry=getDataByIndex(listOfJerries,i);
		addToHashTable(JerrysIDhash,tempJerry->ID,tempJerry);
		for(int j=0;j<tempJerry->numOfPhysicalInfo;j++){
			char* pcName=tempJerry->PhysicalInfo[j]->Name;
			addToMultiValueHashTable(JerrysPhysicalHash,pcName,tempJerry);
		}
	}


	char JerrysID[300];
	char MyPlanet[300];
	char MyOrigin[300];
	char stringToken[300];

	int intToken;
	float floteToken;

	Jerry* JerryPointr;

	status sToken;
	Element element;

	int ch = 1;
	int ch2 = 1;

	while(ch != 9)
	{
		printf("Welcome Rick, what are your Jerry's needs today ? \n");
		printf("1 : Take this Jerry away from me \n");
		printf("2 : I think I remember something about my Jerry \n");
		printf("3 : Oh wait. That can't be right \n");
		printf("4 : I guess I will take back my Jerry now \n");
		printf("5 : I can't find my Jerry. Just give me a similar one \n");
		printf("6 : I lost a bet. Give me your saddest Jerry \n");
		printf("7 : Show me what you got \n");
		printf("8 : Let the Jerries play \n");
		printf("9 : I had enough. Close this place \n");
		ch = switchCaseInt();
		switch(ch)
		{
			case 1://1---------------------------------------------------------------------------------------------------------
			{
						printf("What is your Jerry's ID ? \n");
				  	  	scanf("%s",JerrysID);

				  	  	/*------------------------checks if the JerrysID exits--------------------------*/

				  	  	element=lookupInHashTable(JerrysIDhash,JerrysID);
				  	    if (element!=NULL){
				  	    	printf("Rick did you forgot ? you already left him here ! \n");
				  	    	break;
				  	    }
				  	    else{
				  	    /*------------------------if the JerrysID dosen't exits--------------------------*/
							printf("What planet is your Jerry from ? \n");
							scanf("%s",MyPlanet);
							Planet* myHomePlanet= FindMyPlant(MyPlanet,array_of_planets,num_planets);

					  	    if (myHomePlanet==NULL){
					  	    	printf("%s is not a known planet ! \n",MyPlanet);
					  	    	break;
					  	    }
							printf("What is your Jerry's dimension ? \n");
							scanf("%s",MyOrigin);

							printf("How happy is your Jerry now ? \n");
							scanf("%d",&intToken);

							Origin* tempOrigin=CreateOrigin(MyOrigin,myHomePlanet);

							Jerry* newJerry=CreateJerry(JerrysID,intToken,tempOrigin);

							if(newJerry==NULL || tempOrigin==NULL){

							/*-----------------if we Failed to allocate memory to newJerry---------------*/
								if(tempOrigin!=NULL)
									DeletOrigin(tempOrigin);


								destroyMultiValueHashTable(JerrysPhysicalHash);
								destroyHashTable(JerrysIDhash);

								for(int indexP = 0 ; indexP < num_planets ; indexP++ )
								{
									DeletPlanet(array_of_planets[indexP]);
									array_of_planets[indexP]=NULL;
								}

								free(array_of_planets);
								array_of_planets=NULL;

								listOfJerries=NULL;

								destroyList(listOfJerries);

								printf("Memory Problem");
								exit(-1);//close

							}
							appendNode(listOfJerries, newJerry);
							addToHashTable(JerrysIDhash,newJerry->ID,newJerry);
							PrintJerry(newJerry);
					  	    break;

				  	    }


		}
			case 2://2--------------------------------------------------------------------------------------------------------
			{
						printf("What is your Jerry's ID ? \n");
						scanf("%s",JerrysID);

						/*------------------------checks if the JerrysID exits--------------------------*/

						element=lookupInHashTable(JerrysIDhash,JerrysID);
						if (element==NULL){
							printf("Rick this Jerry is not in the daycare ! \n");
							break;
						}

						/*---------------- checks if the J'erry have this physical characteristic--------------*/

						printf("What physical characteristic can you add to Jerry - %s ? \n",JerrysID);
						scanf("%s",stringToken);

						JerryPointr=(Jerry*)element;

						sToken=IsPhysicalExists(JerryPointr,stringToken);

						if(sToken!=success){
							printf("The information about his %s already available to the daycare ! \n",stringToken);
							break;
						}
						printf("What is the value of his %s ? \n",stringToken);
						scanf("%f",&floteToken);
						sToken = AddPhysicalCharacteristics(JerryPointr,stringToken,floteToken);

						if(sToken!=success)
						{
							/*------------if we Failed to allocate memory to one of the Physical Characteristics---------------*/

							destroyMultiValueHashTable(JerrysPhysicalHash);
							destroyHashTable(JerrysIDhash);

							for(int indexP = 0 ; indexP < num_planets ; indexP++ )
							{
								DeletPlanet(array_of_planets[indexP]);
								array_of_planets[indexP]=NULL;
							}
							free(array_of_planets);
							array_of_planets=NULL;

							destroyList(listOfJerries);

							listOfJerries=NULL;
							JerrysPhysicalHash=NULL;
							JerrysIDhash=NULL;
							printf("Memory Problem");
							exit(-1);//close
						}
						addToMultiValueHashTable(JerrysPhysicalHash,stringToken,JerryPointr);
						displayMultiValueHashElementsByKey(JerrysPhysicalHash,stringToken);
						break;
		}
			case 3://3--------------------------------------------------------------------------------------------------------*/
			{
								printf("What is your Jerry's ID ? \n");
								scanf("%s",JerrysID);

								/*------------------------checks if the JerrysID exits--------------------------*/

								element=lookupInHashTable(JerrysIDhash,JerrysID);
								if (element==NULL){
									printf("Rick this Jerry is not in the daycare ! \n");
									break;
								}

								/*---------------- checks if the J'erry have this physical characteristic--------------*/

								printf("What physical characteristic do you want to remove from Jerry - %s ? \n",JerrysID);
								scanf("%s",stringToken);
								JerryPointr=(Jerry*)element;

								sToken=DeletPhysicalCharacteristics(JerryPointr,stringToken);

								if(sToken!=success){
									printf("The information about his %s not available to the daycare ! \n",stringToken);
									break;
								}
								removeFromMultiValueHashTable(JerrysPhysicalHash,stringToken,JerryPointr);
								PrintJerry(JerryPointr);
						break;
			}
			case 4://4------------------------------------------------------------------------------------------------------------*/
			{
					printf("What is your Jerry's ID ? \n");
					scanf("%s",JerrysID);

					/*------------------------checks if the JerrysID exits--------------------------*/

					element=lookupInHashTable(JerrysIDhash,JerrysID);
					if (element==NULL || getLengthList(listOfJerries)==0){
						printf("Rick this Jerry is not in the daycare ! \n");
						break;
					}
					JerryPointr=(Jerry*)element;

					deletElemFromAll(JerryPointr, JerrysIDhash, listOfJerries, JerrysPhysicalHash);
					printf("Rick thank you for using our daycare service ! Your Jerry awaits ! \n");

					break;
			}
			case 5://5------------------------------------------------------------------------------------------------------------*/
			{
					printf("What do you remember about your Jerry ? \n");
					scanf("%s",stringToken);

					/*------------------------checks if the JerrysID exits--------------------------*/

					element =lookupInMultiValueHashTable(JerrysPhysicalHash,stringToken);
					if (element==NULL){
						printf("Rick we can not help you - we do not know any Jerry's %s ! \n",stringToken);
						break;
					}

					printf("What do you remember about the value of his %s ? \n",stringToken);
					scanf("%d",&intToken);

					printf("Rick this is the most suitable Jerry we found : \n");

					JerryPointr = JerryRumble((LinkedList)element,intToken,stringToken);
					PrintJerry(JerryPointr);
					deletElemFromAll(JerryPointr, JerrysIDhash, listOfJerries, JerrysPhysicalHash);
					printf("Rick thank you for using our daycare service ! Your Jerry awaits ! \n");
					break;
			}
			case 6://6----------------------------------------------------------------------------------------------------------------*/
			{
					if(getLengthList(listOfJerries)==0){
						printf("Rick we can not help you - we currently have no Jerries in the daycare ! \n");
					}
					else{
						printf("Rick this is the most suitable Jerry we found : \n");
						JerryPointr=sadestJerry(listOfJerries);
						PrintJerry(JerryPointr);
						deletElemFromAll(JerryPointr, JerrysIDhash, listOfJerries, JerrysPhysicalHash);
						printf("Rick thank you for using our daycare service ! Your Jerry awaits ! \n");
					}
					break;
			}
			case 7://7----------------------------------------------------------------------------------------*/
						{
							printf("What information do you want to know ? \n");
							printf("1 : All Jerries \n");
							printf("2 : All Jerries by physical characteristics \n");
							printf("3 : All known planets \n");
							ch2 = switchCaseInt();
							if((ch2==1 || ch2==2) && getLengthList(listOfJerries)==0){
								printf("Rick we can not help you - we currently have no Jerries in the daycare ! \n");
								break;
							}
							if(!(0<ch2 && ch2<4)){
								printf("Rick this option is not known to the daycare ! \n");
							}
							switch(ch2)
							{
								case 1://1
								{
									displayList(listOfJerries);
									break;
								}
								case 2://2
								{
									printf("What physical characteristics ? \n");
									scanf("%s",stringToken);
									element=lookupInMultiValueHashTable(JerrysPhysicalHash,stringToken);
									if(element==NULL){
										printf("Rick we can not help you - we do not know any Jerry's %s ! \n",stringToken);

									}

									displayMultiValueHashElementsByKey(JerrysPhysicalHash,stringToken);
									break;
								}
								case 3://3
								{

									for(int i=0;i<num_planets;i++)//print planets
									{
										PrintPlanet(array_of_planets[i]);
									}
									break;
								}
								default:// ---------------------------not valid input------------------------------------------
									break;

					      }
							break;
						}


			case 8://8--------------------------------------------------------------------------------*/
			{

							if(getLengthList(listOfJerries)==0){
								printf("Rick we can not help you - we currently have no Jerries in the daycare ! \n");
								break;
							}

							printf("What activity do you want the Jerries to partake in ? \n");
							printf("1 : Interact with fake Beth \n");
							printf("2 : Play golf \n");
							printf("3 : Adjust the picture settings on the TV \n");
							ch2 = switchCaseInt();
							if(ch2==1 || ch2==2 || ch2==3){
								printf("The activity is now over ! \n");
							}
							else{
								printf("Rick this option is not known to the daycare ! \n");

							}
							switch(ch2)
							{
								case 1://1
								{
									switch8helper(listOfJerries,20,5,15);
									break;
								}
								case 2://2
								{
									switch8helper(listOfJerries,50,10,10);
									break;
								}
								case 3://3
								{
									switch8helper(listOfJerries,0,0,20);
									break;
								}
								default:// ---------------------------not valid input------------------------------------------
									break;
								}
						break;
						}
			case 9://9
					{
						destroyMultiValueHashTable(JerrysPhysicalHash);
						destroyHashTable(JerrysIDhash);
						for(int indexP = 0 ; indexP < num_planets ; indexP++ )
						{
							DeletPlanet(array_of_planets[indexP]);
							array_of_planets[indexP]=NULL;
						}
						free(array_of_planets);
						array_of_planets=NULL;
						JerrysPhysicalHash=NULL;
						JerrysIDhash=NULL;
						destroyList(listOfJerries);
						listOfJerries=NULL;
						printf("The daycare is now clean and close ! \n");

						break;
					}
			default:// ----------------------------------not valid input----------------------------------------
				printf("Rick this option is not known to the daycare ! \n");


	}


	}
	return 0;

}

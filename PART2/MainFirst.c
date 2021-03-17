
#include "Defs.h"
#include "Jerry.h"

void DeletPlanet(planet*);
void DeletOrigin(Origin*);
void DeletAllPhysicalChar(Jerry*);
void DeletJerry(Jerry*);

//tarminal gcc
//./ManageJerries  3 4 /home/ise/eclipse-workspace/ManageJerries/configuration_file.txt
//valgrind --leak-check=full ./ManageJerries   3 4 /home/ise/eclipse-workspace/ManageJerries/configuration_file.txt

void DeletJerry(Jerry* MyJerry)//Jerry Destructor
{
	if(MyJerry==NULL)
		return;

	DeletOrigin(MyJerry->myOrigin);
	MyJerry->myOrigin=NULL;
	DeletAllPhysicalChar(MyJerry);
	free(MyJerry->ID);
	MyJerry->ID=NULL;
	free(MyJerry);
}
void DeletOrigin(Origin* MyOrigin)//Origin Destructor
{
	if(MyOrigin==NULL)
		return;


	free(MyOrigin->dimension);
	MyOrigin->dimension=NULL;
	//DeletPlanet(MyOrigin->MyHomePlanet);
	MyOrigin->MyHomePlanet=NULL;
	free(MyOrigin);


}
void DeletPlanet(planet* Myplanet)//Planet Destructor
{
	if(Myplanet==NULL)
		return;

	free(Myplanet->PlanetName);
	Myplanet->PlanetName=NULL;
	free(Myplanet);


}
void DeletAllPhysicalChar(Jerry* MyJerry)//PhysicalChar Destructor

{
	if(MyJerry==NULL || MyJerry->numOfPhysicalInfo==0)
		return;
	int size=MyJerry->numOfPhysicalInfo;
	for(int i=0;i<size;i++){
		DeletPhysicalCharacteristics(MyJerry,MyJerry->PhysicalInfo[0]->Name);
	}


}
//Gets an array and object, returns a pointer to the object if it exists in the array
planet* FindMyPlant(char* MyPlanet,planet** array_of_planets,int num_planets){
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
//Get array of objects and deletes them, and returning it empty
void DeletAllPlanets(planet** array_of_planets,int size)
{

	for(int j=0;j<size;j++)
	{
		DeletPlanet(array_of_planets[j]);
		array_of_planets[j]=NULL;
	}

}
//Get array of objects and deletes them, and returning it empty
void DeletAllJerrys(Jerry** array_of_Jerrys ,int size)
{
	for(int j=0;j<size;j++)
	{
		DeletJerry(array_of_Jerrys[j]);
		array_of_Jerrys[j]=NULL;
	}
}
//Turns a word into capital letters
void Uppernizer(char* word)
{
	int j =0;
	 while (word[j])
	 {
		  if(word[j] >= 'a' && word[j] <= 'z')
		  {
			  word[j]=word[j]-32;
		  }
		  j++;
	 }
}

int main(int argc , char* argv[]){

	size_t line_buf_size = 0;
	size_t line_size;
	char *line_buf=NULL;//The current line
	int num_planets = atoi(argv[1]);
	int num_Jerrys = atoi(argv[2]);

	/*---------------------------------------------------read file------------------------------------------------------------*/
	FILE *fp = fopen(argv[3], "r");
	if (!fp)
	{
	    fprintf(stderr, "Error opening file '%s'\n", argv[3]);
	    return EXIT_FAILURE;
	}
	line_size = getline(&line_buf, &line_buf_size, fp);
	planet** array_of_planets = (planet**) malloc(sizeof(planet*)*num_planets);//allocate memory to array of planets
	Jerry** array_of_Jerrys = (Jerry**) malloc(sizeof(Jerry*)*num_Jerrys);//allocate memory to array of Jerrys

	//if we Failed to allocate memory to both arrays
	if ( array_of_planets==NULL || array_of_Jerrys==NULL)
	{
		if ( array_of_planets==NULL && array_of_Jerrys==NULL )
			{
					printf("Memory Problem");
					exit(-1);
			}
		//if we Failed to allocate memory to one of the arrays
		if ( array_of_planets!=NULL && array_of_Jerrys==NULL )
			{
					free(array_of_planets);//free the other one
			}
		if ( array_of_planets==NULL && array_of_Jerrys!=NULL )
			{
					free(array_of_Jerrys);//free the other one
			}
		printf("Memory Problem");
		exit(-1);//close
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
				free(array_of_Jerrys);
				printf("Memory Problem");
				exit(-1);//close
				/*---------------------------------------------------------------------------------*/
			}

		}
	}


	line_size = getline(&line_buf, &line_buf_size, fp);//

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


		for(int i=0 ; i < num_Jerrys && line_size!=-1;i++)
		{
			ID=strtok(line_buf,",");
			MyOrigin = strtok(NULL,",");
			MyPlanet = strtok(NULL,",");
			happinessLevel = atoi(strtok(NULL,","));
			planet* tempPlanet=FindMyPlant(MyPlanet,array_of_planets,num_planets);
			Origin* tempOrigin=CreateOrigin(MyOrigin,tempPlanet);
			array_of_Jerrys[i]=CreateJerry(ID,happinessLevel,tempOrigin);
			if(array_of_Jerrys[i]==NULL)
			{
				/*------------if we Failed to allocate memory to one of the J'errys---------------*/

				if(i>0)//if the array is not empty
				{
					for( int indexJ = 0 ; indexJ < i ; indexJ++ )//Goes through the array of j'errys and deletes all the ones we created so far
					{
						DeletJerry(array_of_Jerrys[indexJ]);
						array_of_Jerrys[indexJ]=NULL;
					}
				}
				for(int indexP = 0 ; indexP < num_planets ; indexP++ )
				{
					DeletPlanet(array_of_planets[indexP]);
					array_of_planets[indexP]=NULL;
				}

				free(array_of_planets);
				array_of_planets=NULL;

				free(array_of_Jerrys);
				array_of_Jerrys=NULL;

				printf("Memory Problem");
				exit(-1);//close
				/*---------------------------------------------------------------------------------*/
			}
			line_size = getline(&line_buf, &line_buf_size, fp);
			ret=strchr(line_buf,'\t');
			//printf("%c",line_buf[0]);
			while((ret!=NULL) && (line_size!=-1))
			{
				line=strtok(line_buf,"\t");
				char* PinfoName=strtok(line," : ");
				float VinfoName=atof(strtok(NULL,"\r\n\" "));

				status stat=AddPhysicalCharacteristics(array_of_Jerrys[i],PinfoName,VinfoName);

				if(stat!=success)
				{
					/*------------if we Failed to allocate memory to one of the Physical Characteristics---------------*/
					for(int indexJ = 0 ; indexJ < num_Jerrys ; indexJ++ )
					{
						DeletJerry(array_of_Jerrys[indexJ]);
						array_of_Jerrys[indexJ]=NULL;
					}

					for(int indexP = 0 ; indexP < num_planets ; indexP++ )
					{
						DeletPlanet(array_of_planets[indexP]);
						array_of_planets[indexP]=NULL;
					}

					free(array_of_planets);
					array_of_planets=NULL;

					free(array_of_Jerrys);
					array_of_Jerrys=NULL;

					printf("Memory Problem");
					exit(-1);//close
					/*---------------------------------------------------------------------------------*/
				}
				line_size = getline(&line_buf, &line_buf_size, fp);
				ret=strchr(line_buf,'\t');
			}
		}
	}

	free(line_buf);//freeing the line pointer
	line_buf = NULL;
	fclose(fp);//closing the file

	/*---------------------------------------------------MainFirst------------------------------------------------------------*/
	char JerrysID[300];
	char PinfoName[300];
	float VinfoName;
	int index;
	bool isExist;
	bool flag;

	char ch = 49;
		  while(ch != 55 )
		  {
			  printf("AW JEEZ RICK, what do you want to do now ? \n");
			  printf("1 : Print all Jerries \n");
			  printf("2 : Print all Planets \n");
			  printf("3 : Add physical characteristic to Jerry \n");
			  printf("4 : Remove physical characteristic from Jerry \n");
			  printf("5 : Print Jerries by a planet \n");
			  printf("6 : Print Jerries by a physical characteristic \n");
			  printf("7 : Go home \n");
			  scanf("%s",&ch);

			  switch(ch)
			  {
			  case(49): // 1----------------------------------------------------------Print all Jerries---------------------------------------------------------------------
					for(int i=0;i<num_Jerrys;i++)//print Jerrys
					{
						PrintJerry(array_of_Jerrys[i]);
					}
			  	  	  break;

			  case(50):// 2-----------------------------------------------------------Print all Planets--------------------------------------------------------------------
					for(int i=0;i<num_planets;i++)//print planets
					{
						PrintPlanet(array_of_planets[i]);
					}
			  	  	  break;

			  case(51):// 3----------------------------------------------------------Add physical characteristic to Jerry----------------------------------------------------


					index=0;

			  	  	printf("What is your Jerry's ID ? \n");
			  	  	scanf("%s",JerrysID);
			  	  	flag=true;
			  	  	while(index<num_Jerrys)
					{
						if(strcmp(array_of_Jerrys[index]->ID,JerrysID)==0){
							flag=false;//If we did find the object
							break;
						}
						index++;//Saves the position of the object
					}
			  	  	if(flag)
			  	  	{
			  	  		printf("OH NO! I CAN'T FIND HIM RICK ! \n");
			  	  		break;
			  	  	}
			  	  	printf("What physical characteristic can you add to Jerry - %s ? \n",JerrysID);

			  	  	scanf("%s",PinfoName);

			  	  	isExist=IsPhysicalExists(array_of_Jerrys[index],PinfoName);//Check if the Physical exists

			  	  	if(isExist==true)
			  	  	{

			  	  		Uppernizer(PinfoName);
						printf("RICK I ALREADY KNOW HIS %s ! \n",PinfoName);
						break;
			  	  	}
			  	  	printf("What is the value of his %s ? \n",PinfoName);
			  	  	scanf("%f",&VinfoName);

						status stat=AddPhysicalCharacteristics(array_of_Jerrys[index],PinfoName,VinfoName);

						if(stat!=success)
						{
							/*------------if we Failed to allocate memory to one of the Physical Characteristics---------------*/

							for(int indexJ = 0 ; indexJ < num_Jerrys ; indexJ++ )
							{
								DeletJerry(array_of_Jerrys[indexJ]);
								array_of_Jerrys[indexJ]=NULL;
							}
							for(int indexP = 0 ; indexP < num_planets ; indexP++ )
							{
								DeletPlanet(array_of_planets[indexP]);
								array_of_planets[indexP]=NULL;
							}
							free(array_of_planets);
							array_of_planets=NULL;
							free(array_of_Jerrys);
							array_of_Jerrys=NULL;
							printf("Memory Problem");
							exit(-1);//close
						}
					PrintJerry(array_of_Jerrys[index]);
			  	  	break;

			  case (52):// 4--------------------------------------Remove physical characteristic from Jerry------------------------------------------------
							index=0;
							printf("What is your Jerry's ID ? \n");
					  	  	scanf("%s",JerrysID);
					  	  	flag=true;
					  	  	while(index<num_Jerrys)
							{
								if(strcmp(array_of_Jerrys[index]->ID,JerrysID)==0){
										flag=false;
										break;
									}
								index++;
							}
					  	  	if(flag)
					  	  	{
					  	  		printf("OH NO! I CAN'T FIND HIM RICK ! \n");
					  	  		break;
					  	  	}
					  	  	printf("What physical characteristic do you want to remove from Jerry - %s ? \n",JerrysID);

					  	  	scanf("%s",PinfoName);

					  	  	isExist=IsPhysicalExists(array_of_Jerrys[index],PinfoName);

					  	  	if(isExist!=true)
					  	  	{
					  	  		Uppernizer(PinfoName);
								printf("RICK I DON'T KNOW HIS %s ! \n",PinfoName);
								break;
					  	  	}
					  	  	DeletPhysicalCharacteristics(array_of_Jerrys[index],PinfoName);
							PrintJerry(array_of_Jerrys[index]);
					  	  	break;
	  	  	  	  	break;

			  case(53):// 5-----------------------------------------Print Jerries by a planet----------------------------------------------------
							printf("What planet is your Jerry from ? \n");
							scanf("%s",PinfoName);
							int i=0;
							int j=0;
							flag=true;
							bool flag2=true;

							for(;i<num_planets;i++)//Passesing over the array the planets
							{
								if(strcmp(PinfoName,array_of_planets[i]->PlanetName)==0)//If we found the desired planet
								{
									flag=false;
									for(;j<num_Jerrys;j++)//Passesing over the array the Jerrys
									{
										if(strcmp(array_of_Jerrys[j]->myOrigin->MyHomePlanet->PlanetName,array_of_planets[i]->PlanetName)==0)//If we found a Jerrys from thet planet
										{
											PrintJerry(array_of_Jerrys[j]);
											flag2=false;
										}

									}
									break;
								}
							}
							if(flag2 && !flag)//If the planet exists and we haven't  found any one from this planet
							{
								Uppernizer(PinfoName);
								printf("OH NO! I DON'T KNOW ANY JERRIES FROM %s ! \n",PinfoName);
							}
							if(flag){//If the planet dos not exists
								Uppernizer(PinfoName);
								printf("RICK I NEVER HEARD ABOUT %s ! \n",PinfoName);
							}
					  	  	break;

			  case(54)://6------------------------------------Print Jerries by a physical characteristic-----------------------------------------------
					printf("What do you know about your Jerry ? \n");
					scanf("%s",PinfoName);
					flag=true;
					for(int i=0;i<num_Jerrys;i++)//
					{
							for(int j=0;j<array_of_Jerrys[i]->numOfPhysicalInfo;j++)//print Jerrys
							{
								if(strcmp(array_of_Jerrys[i]->PhysicalInfo[j]->Name,PinfoName)==0)
								{
									PrintJerry(array_of_Jerrys[i]);
									flag=false;
								}
							}
					}
					if(flag){
						Uppernizer(PinfoName);
						printf("OH NO! I DON'T KNOW ANY JERRY'S %s ! \n",PinfoName);
					}
					break;

			  case(55)://7--------------------------------------------------------Go home----------------------------------------------------------------

					for(int i=0;i<num_Jerrys;i++)//Delet All Jerry
					{
						DeletJerry(array_of_Jerrys[i]);
						array_of_Jerrys[i]=NULL;
					}
					free(array_of_Jerrys);
					array_of_Jerrys=NULL;

					for(int i=0;i<num_planets;i++)//Delet All planets
					{
						DeletPlanet(array_of_planets[i]);
						array_of_planets[i]=NULL;
					}

					free(array_of_planets);
					array_of_planets=NULL;

					printf("AW JEEZ RICK, ALL THE JERRIES GOT FREE ! \n");
					break;

			  default:// ------------------------------------------------------not valid input--------------------------------------------------------
				  printf("RICK WE DON'T HAVE TIME FOR YOUR GAMES ! \n");

			  }
		  }
	return 0;
}

#include "game.h"

void InitialiseAllLocations(location arrayOfRooms[NUMBEROFROOMS])
{
	// Initialize all locations
	for (int i = 0; i < NUMBEROFROOMS; i++)
	{
		char roomName[2]={0};
		switch (i)
		{
			case 0 :
				strcpy(roomName, "0");
				break;
			case 1 :
				strcpy(roomName, "1");
				break;
			case 2 :
				strcpy(roomName, "2");
				break;
			case 3 :
				strcpy(roomName, "3");
				break;
		}
		InitLocation(&arrayOfRooms[i], roomName);
	}
}

void GetAction(char **verb, char **object, char *currentInput)
{
	char *strToken = NULL;
	strToken = strtok(currentInput, " ");
	*verb = strToken;

	strToken = strtok(NULL, " ");
	*object = strToken;
}


int EntranceRoom(location *currentRoom, int *indexRoom, int *indexObject, char *verb, char *object, char tempConsoleAnswer[SIZE_MAX])
//we compare it to our list of verbs and to our list of objects
{
	for (int i = 0; i < currentRoom->numberOfVerbs; i++)
	{
		for (int j = 0 ; j < currentRoom->numberOfObjects; j++)
		{
			// If the verb and the object exists, then we check for the combinaison of both
			if (!strcmp(verb, currentRoom->tab_verbs[i].tag) && !strcmp(object, currentRoom->tab_objects[j].tag))
			{
				//EXAMINE DOOR
				if (!strcmp(verb, "examine") && !strcmp(object, "door"))
				{
					strcpy(tempConsoleAnswer, "There is a lever that seems to be linked to the door.\n\n");
					return 1;
				}
				//PULL LEVER
				else if (!strcmp(verb, "pull") && !strcmp(object, "lever"))
				{
					strcpy(tempConsoleAnswer, "You pull the lever. Nothing seems to happen... Suddendly, the ground shakes and as you hear a mecanism, the door is opening.\n\n");
					currentRoom->tab_objects[j].isTriggered = 1;
					*indexObject = j;
					return 1;
				}
				//GO NORTH
				else if (!strcmp(verb, "go") && !strcmp(object, "north") )
				{
					if (currentRoom->tab_objects[*indexObject].isTriggered)
					{
						strcpy(tempConsoleAnswer, "You decide to go through the door. When you enter in the new room, the door locks itself behind you.\n\n");
						*indexRoom = 1;
						return 1;
					}
					else
					{
						strcpy(tempConsoleAnswer, "The door is locked. Maybe you can find something to open this door !\n\n");
						return 1;
					}
				}
				else
				{
					strcpy(tempConsoleAnswer, "You can't do that !\n\n");
					return 1;
				}
			}
		}
	}

	strcpy(tempConsoleAnswer, "Sorry, I didn't understand\n\n");
	return 1;
}

int BookRoom(location *currentRoom, int *indexRoom, int *indexObject, char *verb, char *object, char tempConsoleAnswer[SIZE_MAX])
//we compare it to our list of verbs and to our list of objects
{
	for (int i = 0; i < currentRoom->numberOfVerbs; i++)
	{
		for (int j = 0 ; j < currentRoom->numberOfObjects; j++)
		{
			// If the verb and the object exists, then we check for the combinaison of both
			if (!strcmp(verb, currentRoom->tab_verbs[i].tag) && !strcmp(object, currentRoom->tab_objects[j].tag))
			{
				//EXAMINE ROOM
				if (!strcmp(verb, "examine") && !strcmp(object, "room"))
				{
					strcpy(tempConsoleAnswer, "In this room, there are two doors : one to the east of the room and the other one is at the opposite side. You also notice a dusty old book, laying on the ground...\n\n");
					return 1;
				}
				//EXAMINE BOOK
				else if (!strcmp(verb, "examine") && !strcmp(object, "book") )
				{
					strcpy(tempConsoleAnswer, "As you're sweeping through the pages, you find an ancient scroll ripped on the edges.\n\n");
					currentRoom->tab_objects[j].isTriggered = 1;
					*indexObject = j;
					return 1;
				}
				//READ SCROLL
				else if (!strcmp(verb, "read") && !strcmp(object, "scroll") && (currentRoom->tab_objects[*indexObject].isTriggered))
				{
					strcpy(tempConsoleAnswer, "Part 2 : 3MP\n\n");
					return 1;
				}
				//GO EAST
				else if (!strcmp(verb, "go") && !strcmp(object, "east"))
				{
					strcpy(tempConsoleAnswer, "You go east\n\n");
					*indexRoom = 2;
					return 1;
				}
				//GO WEST
				else if (!strcmp(verb, "go") && !strcmp(object, "west"))
				{
					strcpy(tempConsoleAnswer, "You go west\n\n");
					*indexRoom = 3;
					return 1;
				}
				else if (!strcmp(verb, "go") && !strcmp(object, "south"))
				{
					strcpy(tempConsoleAnswer, "The door leading to the entrance is locked.\n\n");
					*indexRoom = 3;
					return 1;
				}
				else
				{
					strcpy(tempConsoleAnswer, "You can't do that !\n\n");
					return 1;
				}
			}
		}
	}

	strcpy(tempConsoleAnswer, "Sorry, I didn't understand\n\n");
	return 1;
}

int SkeletonRoom(location *currentRoom, int *indexRoom, int *indexObject, char *verb, char *object, char tempConsoleAnswer[SIZE_MAX])
//we compare it to our list of verbs and to our list of objects
{
	for (int i = 0; i < currentRoom->numberOfVerbs; i++)
	{
		for (int j = 0 ; j < currentRoom->numberOfObjects; j++)
		{
			// If the verb and the object exists, then we check for the combinaison of both
			if (!strcmp(verb, currentRoom->tab_verbs[i].tag) && !strcmp(object, currentRoom->tab_objects[j].tag))
			{
				//EXAMINE ROOM
				if (!strcmp(verb, "examine") && !strcmp(object, "room"))
				{
					strcpy(tempConsoleAnswer, "It's a dead end. There is a skeleton looking at you that makes you unconfortable.\n\n");
					return 1;
				}
				//GO WEST
				else if (!strcmp(verb, "go") && !strcmp(object, "west") )
				{
					strcpy(tempConsoleAnswer, "You go west.\n\n");
					*indexRoom = 1;
					return 1;
				}
				else if (!strcmp(verb, "examine") && !strcmp(object, "skeleton") )
				{
					strcpy(tempConsoleAnswer, "You examine the skeleton. It has another piece of scroll in its hand.\n\n");
					currentRoom->tab_objects[j].isTriggered = 1;
					*indexObject = j;
					return 1;
				}
				//READ SCROLL
				else if (!strcmp(verb, "read") && !strcmp(object, "scroll") && (currentRoom->tab_objects[*indexObject].isTriggered))
				{
					strcpy(tempConsoleAnswer, "Part 1 : 635!M\n\n");
					return 1;
				}
				else
				{
					strcpy(tempConsoleAnswer, "You can't do that !\n\n");
					return 1;
				}
			}
		}
	}

	strcpy(tempConsoleAnswer, "Sorry, I didn't understand\n\n");
	return 1;
}

int RuneRoom(location *currentRoom, int *indexRoom, int *indexObject, char *verb, char *object, char tempConsoleAnswer[SIZE_MAX], int *gameOver)
//we compare it to our list of verbs and to our list of objects
{
	for (int i = 0; i < currentRoom->numberOfVerbs; i++)
	{
		for (int j = 0 ; j < currentRoom->numberOfObjects; j++)
		{
			// If the verb and the object exists, then we check for the combinaison of both
			if (!strcmp(verb, currentRoom->tab_verbs[i].tag) && !strcmp(object, currentRoom->tab_objects[j].tag))
			{
				//EXAMINE ROOM
				if (!strcmp(verb, "examine") && !strcmp(object, "room"))
				{
					strcpy(tempConsoleAnswer, "In the middle of the room, you can see the coveted Rune of Mal'Oc ! However, it is protected by a magical barrier...\nThere is an old device with instructions that looks like Paskhal, the ancetral language you know from your researches.\n\n");
					currentRoom->tab_objects[j].isTriggered = 1;
					*indexObject = j;

					return 1;
				}
				//EXAMINE DEVICE
				else if (!strcmp(verb, "examine") && !strcmp(object, "device") && (currentRoom->tab_objects[*indexObject].isTriggered))
				{
					strcpy(tempConsoleAnswer, "It is written : \"G=5; E=3; I=!; B=6 ; D=P ; N=M\"\n\n");
					return 1;
				}
				//GO WEST
				else if (!strcmp(verb, "go") && !strcmp(object, "east") )
				{
					strcpy(tempConsoleAnswer, "You go east.\n\n");
					*indexRoom = 1;
					return 1;
				}
				else if (!strcmp(verb, "BEGIN") && !strcmp(object, "END") )
				{
					strcpy(tempConsoleAnswer, "The barrier collapses ! You slowly approach the powerful Rune of Mal'Oc and as you touch it, you are teleported into...\n\n\nTo be continued...\n\n");
					*gameOver = 1;
					return 1;
				}
				else
				{
					strcpy(tempConsoleAnswer, "You can't do that !\n\n");
					return 1;
				}
			}
		}
	}

	strcpy(tempConsoleAnswer, "Sorry, I didn't understand\n\n");
	return 1;
}

void InitLocation(location *location, char c_name[SIZE_MAX])
//Initiate the location with all the verbs and objects it has.
//PARAMETERS : *location : pointer on the the location we're initialising ; c_name : Name of the location (used for the file)
{
	location->tab_verbs = NULL;
	location->tab_objects = NULL;

	//______________________________TO DO : Maybe we should split it into 2 functions______________________________//

	FILE *fileToOpen=NULL;

	strcpy(location->name, c_name);

	// We concatenate the name with _verbs.txt to associate the name of the room + the list of verbs available for it
	char c_fileName[SIZE_MAX]={0};
	strcat(c_fileName, c_name);
	strcat(c_fileName, "_verbs.txt");

	char c_saisie[SIZE_MAX];
	int errnum=0;
	int i = 0;
	location->numberOfVerbs = 0;

	//Open the file in read mode
	if((fileToOpen=fopen(c_fileName,"r"))==NULL)
	{
		//handle errors if we cant open the file
		fprintf(stderr,"Erreur ouverture fichier :%s\n",strerror(errnum));
	}
	else
	{
		while (fgets(c_saisie,SIZE_MAX,fileToOpen) != NULL)
		{
			//reminder : location.tab_verbs = NULL, so we realloc i+2 because the 2nd available space is gonna be a NULL ptr to mark the end
			//ex : i = 0 so basically we allocate 2
			//so tab_verbs[1].tag = NULL (end marker)
			//and we allocate what we need for tab_verbs[0].tag
			if ((location->tab_verbs = (verb*)realloc(location->tab_verbs,sizeof(verb)*(i+2))) != NULL)
			{
				location->tab_verbs[i + 1].tag = NULL;
				location->tab_verbs[i].tag = (char*)calloc(strlen(c_saisie),sizeof(char));
			}
			//this allows us to copy the verb in the allocated space without the \n
			for (int j = 0; j < strlen(c_saisie)-1; j++)
			{
				location->tab_verbs[i].tag[j] = c_saisie[j];
			}
			i++;
			location->numberOfVerbs++;
		}
	}
	fclose(fileToOpen);

	fileToOpen=NULL;
	//we put the name into location.name
	strcpy(location->name,c_name);
	memset(c_fileName, 0, SIZE_MAX);
	//we concatenate the name with _verbs.txt to associate the name of the room + the list of verbs available for it
	strcat(c_fileName, c_name);
	strcat(c_fileName, "_objects.txt");

	errnum=0;
	i = 0;
	location->numberOfObjects = 0;

	//we open the file in read mode
	if((fileToOpen=fopen(c_fileName,"r"))==NULL)
	{
		//handle errors if we cant open the file
		fprintf(stderr,"Erreur ouverture fichier :%s\n",strerror(errnum));
	}
	else
	{
		while (fgets(c_saisie,SIZE_MAX,fileToOpen) != NULL)
		{
			//reminder : location.tab_verbs = NULL, so we realloc i+2 because the 2nd available space is gonna be a NULL ptr to mark the end
			//ex : i = 0 so basically we allocate 2
			//so tab_verbs[1].tag = NULL (end marker)
			//and we allocate what we need for tab_verbs[0].tag
			if ((location->tab_objects = (object*)realloc(location->tab_objects,sizeof(object)*(i+2))) != NULL)
			{
				location->tab_objects[i + 1].tag = NULL;
				location->tab_objects[i].tag = (char*)calloc(strlen(c_saisie),sizeof(char));
			}
			//this allows us to copy the object in the allocated space without the \n
			for (int j = 0; j < strlen(c_saisie)-1; j++)
			{
				location->tab_objects[i].tag[j] = c_saisie[j];
			}
			location->tab_objects[i].isTriggered = 0;
			i++;
			location->numberOfObjects++;
		}
	}
	fclose(fileToOpen);
}

void DisplayVerbs(location *currentRoom, char tempConsoleAnswer[SIZE_MAX])
{
	strcat(tempConsoleAnswer, "In this room, you can : ");
	for (int i = 0; i < currentRoom->numberOfVerbs; i++)
	{
		if (strcmp(currentRoom->tab_verbs[i].tag,"BEGIN") != 0)
		{
			strcat(tempConsoleAnswer, currentRoom->tab_verbs[i].tag);
			if ((i != currentRoom->numberOfVerbs - 1) && (strcmp(currentRoom->tab_verbs[i+1].tag, "BEGIN") != 0))
				strcat(tempConsoleAnswer, ", ");
			else
				strcat(tempConsoleAnswer, "\n");
		}
	}
}


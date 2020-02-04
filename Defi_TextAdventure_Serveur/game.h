#ifndef GAME_H_DEFINE
#define GAME_H_DEFINE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define NUMBEROFVERBS 10
#define SIZE_MAX 1024
#define NUMBEROFROOMS 4

typedef struct verb
{
	char* tag;
}verb;

typedef struct object
{
	char* tag;
	int isTriggered;
}object;

typedef struct location
{
	char name[SIZE_MAX];

	verb *tab_verbs;
	int numberOfVerbs;

	object *tab_objects;
	int numberOfObjects;
}location;

extern void InitLocation(location *location,char c_name[SIZE_MAX]);
extern void InitialiseAllLocations(location arrayOfRooms[NUMBEROFROOMS]);
extern void GetAction(char **verb, char **object, char *currentInput);
extern int EntranceRoom(location *currentRoom, int *indexRoom, int *indexObject, char *verb, char *object, char tempConsoleAnswer[SIZE_MAX]);
extern int BookRoom(location *currentRoom, int *indexRoom, int *indexObject, char *verb, char *object, char tempConsoleAnswer[SIZE_MAX]);
extern int SkeletonRoom(location *currentRoom, int *indexRoom, int *indexObject, char *verb, char *object, char tempConsoleAnswer[SIZE_MAX]);
extern int RuneRoom(location *currentRoom, int *indexRoom, int *indexObject, char *verb, char *object, char tempConsoleAnswer[SIZE_MAX], int *gameOver);
extern void DisplayVerbs(location *currentRoom, char tempConsoleAnswer[SIZE_MAX]);

#endif
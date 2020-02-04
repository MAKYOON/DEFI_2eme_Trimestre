#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include <string.h>
#include "game.h"

#define PORT 23
#define NUMBEROFVERBS 10
#define SIZE_MAX 1024
#define NUMBEROFROOMS 4

//this is for storing the size of structures of type sockaddr_in
typedef int socklen_t;


int main()
{
	//____________VARIABLE DECLARATIONS_____________//

	WSADATA WSAData;
	int error;

	// Server's socket and adress space
	SOCKADDR_IN sin;
	SOCKET listen_sock;
	socklen_t recsize = sizeof(sin);

	// Client's socket adress space
	SOCKADDR_IN csin;
	SOCKET csock;
	socklen_t crecsize = sizeof(csin);

	char bufferGet[SIZE_MAX]; //this is the temporary array in which we will store the result of recv()
	char tempConsoleAnswer[SIZE_MAX]; //this is the temporary array in which we will store the message sent to the client

	//char *currentInput = NULL; //this is what we malloc according to what we received in bufferGet (so we only take the space needed)
	char *consoleAnswer = NULL; //this is what we malloc according to the length of the tempConsoleAnswer

	int sock_err; //variable used to check if sockets functions work or not
	int n; //will be used to store the number of octets given by recv() to check if we actually received something or if there's an error
	int indexObject = 0; //allows us to get the index of an object that sometimes needs to be triggered to be use-able
	int indexRoom = 0; //index of the room in which the player is currently in
	int gameOver = 0;

	location currentRoom[NUMBEROFROOMS]; //array containing all of our locations

	//________________END VARIABLE DECLARATIONS_________________//

	InitialiseAllLocations(currentRoom); //inialise all the rooms of the game

	error = WSAStartup(MAKEWORD(2,2), &WSAData); //initiate Winsock DLL

	//If the initiation worked
	if(!error)
	{
		// Socket's Creation
		listen_sock = socket(AF_INET, SOCK_STREAM, 0);

		// Verify that the socket is valid
		if(listen_sock != INVALID_SOCKET)
		{
			printf("Socket number %d is now open in TCP/IP mode\n", listen_sock);

			// Configuration
			sin.sin_addr.s_addr = htonl(INADDR_ANY);   // Automatic IP adress
			sin.sin_family = AF_INET;                 // Protocol Family(IP)
			sin.sin_port = htons(PORT);               // Listing port
			sock_err = bind(listen_sock, (SOCKADDR*)&sin, recsize); //binding socket

			// If the socket works
			if(sock_err != SOCKET_ERROR)
			{
				// activating listening
				sock_err = listen(listen_sock, 5);
				printf("Listing port number %d...\n", PORT);

				// If the listen function works we accept the connection
				if(sock_err != SOCKET_ERROR)
					csock = accept(listen_sock, (SOCKADDR *)&csin, &crecsize);
				//game loop
				while (!gameOver)
				{
					//We empty the arrays
					memset(bufferGet, 0, SIZE_MAX);
					memset(tempConsoleAnswer, 0, SIZE_MAX);
					//according to the room, displays the room's name and the possible actions
					switch (indexRoom)
					{
						case 0 :
							sprintf(tempConsoleAnswer, "Current room : Entrance\n");
							DisplayVerbs(&currentRoom[indexRoom], tempConsoleAnswer);
							break;
						case 1 :
							sprintf(tempConsoleAnswer, "Current room : Book's room\n");
							DisplayVerbs(&currentRoom[indexRoom], tempConsoleAnswer);
							 break;
						case 2 :
							sprintf(tempConsoleAnswer, "Current room : Skeleton's room\n");
							DisplayVerbs(&currentRoom[indexRoom], tempConsoleAnswer);
							 break;
						case 3 :
							sprintf(tempConsoleAnswer, "Current room : Rune's room\n");
							DisplayVerbs(&currentRoom[indexRoom], tempConsoleAnswer);
							 break;
					}
					//just making sure we actually sent to the client
					if (send(csock, tempConsoleAnswer, strlen(tempConsoleAnswer), 0) > 0)
						printf("Room's index send.\n");

					//recv returns the number of octets received
					n = recv(csock, bufferGet, sizeof(bufferGet), 0);

					//We switch the \n from the "Enter" key in the user input with a '\0'
					bufferGet[n-1] = '\0';

					//We split the message received in 2 part : verb and object
					char *verb = NULL;
					char *object = NULL;
					GetAction(&verb, &object, bufferGet);
					//if the user inputs nothing, we put an empty string to avoid crashing
					if (verb == NULL || object == NULL)
					{
						verb = " ";
						object = " ";
					}

					// If the message received isnt empty (= contains at least 1 octet)
					if(n > 0)
					{	
						//then we call the according function (corresponding to the room)
						switch (indexRoom)
						{
							case 0:
								error = EntranceRoom(&currentRoom[indexRoom], &indexRoom, &indexObject, verb, object, tempConsoleAnswer);
								break;
							case 1:
								error = BookRoom(&currentRoom[indexRoom], &indexRoom, &indexObject, verb, object, tempConsoleAnswer);
								break;
							case 2:
								error = SkeletonRoom(&currentRoom[indexRoom], &indexRoom, &indexObject, verb, object, tempConsoleAnswer);
								break;
							case 3:
								error = RuneRoom(&currentRoom[indexRoom], &indexRoom, &indexObject, verb, object, tempConsoleAnswer, &gameOver);
								break;
						}
						//our Room functions return 1 if they succeeded, and 0 if they didnt
						//so here we check that it succeeded
						if (error)
						{
							// The console sends the feedback to the client
							consoleAnswer = (char *) calloc(strlen(tempConsoleAnswer), sizeof(char));
							strcpy(consoleAnswer, tempConsoleAnswer);

							if (send(csock, consoleAnswer, strlen(consoleAnswer), 0) > 0)
								printf("Send successful\n");

							//we send the gameOver variable for the client to check if the game has to end or not
							send(csock, (char*)&gameOver, sizeof(int), 0);


						}
						else
							printf("Erreur : impossible d'envoyer tempConsoleAnswer");
					}
				}
			}
			else
				perror("bind");

			printf("Shutting down socket server\n");
			closesocket(listen_sock);
			printf("Server is shut down\n");
		}
		else
			perror("socket");


			WSACleanup();
	}
	return EXIT_SUCCESS;

}

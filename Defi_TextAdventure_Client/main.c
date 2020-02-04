#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>

#define PORT 23
#define SIZE_MAX 1024

//this type is used for storing the size of structures of type sockaddr_in
typedef int socklen_t;

void DisplayMap();

int main(void)
{
	#if defined (WIN32)
		WSADATA WSAData;
		int erreur = WSAStartup(MAKEWORD(2,2), &WSAData);
	#else
		int erreur = 0;
	#endif

	SOCKET sock;
	SOCKADDR_IN sin;

	char bufferSend[SIZE_MAX];
	char bufferGet[SIZE_MAX];

	int gameOver = 0;

	if(!erreur)
	{
		// creating socket
		sock = socket(AF_INET, SOCK_STREAM, 0);

		// configurating connexion
		sin.sin_addr.s_addr = inet_addr("172.20.10.9");
		sin.sin_family = AF_INET;
		sin.sin_port = htons(PORT);

		//checking if the client connects
		if(connect(sock, (SOCKADDR*)&sin, sizeof(sin)) == SOCKET_ERROR)
			printf("Failed to connect\n");

		//beginning of game
		printf("After investigating the mysterious rune of Mal'oc, you've managed to locate its position in old ruins named Poin'Ter.\n");
		printf("While venturing through these ancient remains, you come across a first room. As you enter, the door shuts behind you. \n");
		printf("Trapped, you look around.\n");
		printf("At the north of the room, there is a door. What do you do ?\n\n");
		//game loop
		while (!gameOver)
		{
			DisplayMap();
			int n = 0;

			//Current room
			if ((n = recv(sock, bufferGet, sizeof(bufferGet) - 1, 0)) > 0)
			{
				bufferGet[n] = '\0';
				printf(bufferGet);
			}

			//Sending input
			fgets(bufferSend,SIZE_MAX,stdin);
			if(!(send(sock, bufferSend, strlen(bufferSend), 0) > 0) )
				printf("Transmission error\n");

			//Receiving feedback
			n = 0;
			if ((n = recv(sock, bufferGet, sizeof(bufferGet) - 1, 0)) > 0)
			{
				bufferGet[n] = '\0';
				printf(bufferGet);
			}
			//receiving gameOver variable. if it's 0 we keep on going, and if it's 1 we quit
			recv(sock, (char*)&gameOver, sizeof(gameOver), 0);

			printf("Press ENTER to continue\n");
			getchar();
			fflush(stdin);
			system("cls");


		}


		// On ferme la socket précédemment ouverte
		closesocket(sock);

		#if defined (WIN32)
			WSACleanup();
		#endif
	}
	return EXIT_SUCCESS;
}

void DisplayMap()
{
	FILE* f_entree = NULL;
	int errnum = 0;
	char buffer[SIZE_MAX];

	printf("RUINS' MAP :\n");
	//opening file to read
	f_entree = fopen("map.txt", "r");
	if (f_entree != NULL)
	{
		int i = 0;
		while (fread(buffer, sizeof(char), 1, f_entree) && !feof(f_entree))
		{
			printf("%s", buffer);
			i++;
		}
	}
	else
		fprintf(stderr, "Erreur ouverture fichier :%s\n", strerror(errnum));

	fclose(f_entree);
}

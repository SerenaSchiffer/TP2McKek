#include <stdio.h>
#include <winsock.h>
#include <iostream>
#include <fstream>

#include "Server.h"

using namespace std;

//Define buffer size
#define BUFF_SIZE 9

//Define error message
#define PRINTERROR(s)	cout<<"\n"<<s<<":"<<WSAGetLastError()

Serveur::Serveur()
{
	cpt = 0;
}

void Serveur::ServeurConnect(int noPort)
{
	char sizebuff[1024];

	//Créer un socket TCP/IP
	//SOCKET socketServeur;

	socketServeur = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (socketServeur == INVALID_SOCKET)
	{
		PRINTERROR("socket()");
		return;
	}

	//Remplir la structure d'adresse
	SOCKADDR_IN socAdrServeur;

	socAdrServeur.sin_family = AF_INET;
	socAdrServeur.sin_addr.s_addr = INADDR_ANY;
	socAdrServeur.sin_port = htons(noPort);

	int nRet;

	nRet = bind(socketServeur, (LPSOCKADDR)&socAdrServeur, sizeof(struct sockaddr));

	if (nRet == SOCKET_ERROR)
	{
		PRINTERROR("bind()");
		closesocket(socketServeur);
		return;
	}

	//Afficher l'adresse du serveur
	int nLen;
	nLen = sizeof(SOCKADDR);

	nRet = gethostname(sizebuff, sizeof(sizebuff));

	if (nRet == SOCKET_ERROR)
	{
		PRINTERROR("gethostname()");
		closesocket(socketServeur);
		return;
	}

	//Afficher le nom du serveur et le numéro de port

	cout << "Serveur : " << sizebuff << "ecoute sur le port : " << noPort;

	//Faire écouter le socket serveur

	cout << "\nlisten()";
	nRet = listen(socketServeur, SOMAXCONN);

	if (nRet == SOCKET_ERROR)
	{
		PRINTERROR("listen()");
		closesocket(socketServeur);
		return;
	}

	//Attendre qu'un client se connecte

	cout << "\nBloque à accept()";

	socketDistant[cpt++] = accept(socketServeur, NULL, NULL);

	if (cpt >= 2)
		socketDistant[cpt].~SOCKET();

	if (socketDistant[cpt-1] == INVALID_SOCKET)
	{
		PRINTERROR("accept()");
		closesocket(socketServeur);
		return;
	}
}

void Serveur::Send(char* message)
{
	char sizebuff[BUFF_SIZE];

	nRet = send(socketDistant[playerId], message, sizeof(message), 0);

	if (nRet = SOCKET_ERROR)
	{
		PRINTERROR("send()");
		closesocket(socketServeur);
		closesocket(socketDistant[playerId]);
		return;
	}
}

void Serveur::Receive()
{
	char buffer[BUFF_SIZE];

	memset(buffer, 0, sizeof(buffer));
	nRet = recv(socketDistant[playerId], buffer, sizeof(buffer), 0);

	if (nRet == INVALID_SOCKET)
	{
		PRINTERROR("recv()");
		closesocket(socketServeur);
		closesocket(socketDistant[playerId]);
		return;
	}

	if (playerId == 1)
		playerId = 0;
	else
		playerId = 1;

	Send(buffer);
}

void main()
{
	WORD wsVersionRequested = MAKEWORD(1, 1);
	WSADATA wsaData;
	short numPort = 1234; //Mettre le numéro de port à 1234
	int nRet;

	nRet = WSAStartup(wsVersionRequested, &wsaData);
	if (wsaData.wVersion != wsVersionRequested)
	{
		cout << "Mauvaise version";
		return;
	}

	Serveur* server = new Serveur();

	//Appeler la fonction Serveur
	server->ServeurConnect(numPort);

	//Fermer le winsock
	WSACleanup();

	getchar();

	return;
}
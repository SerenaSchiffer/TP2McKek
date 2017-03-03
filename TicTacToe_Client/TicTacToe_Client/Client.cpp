#include "Client.h"
#include <stdio.h>
#include <iostream>
#include <fstream>

using namespace std;

//Définit la grandeur du buffer
#define BUFF_SIZE 1024

//Définit le message d'erreur
#define PRINTERROR(s)	cout<<"\n"<<s<<":"<<WSAGetLastError()

Client::Client()
{
	nbPort = 1234;
	server = "127.0.0.1";
	socketClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
}

void Client::Test()
{
}

void Client::Connect()
{
	char sizeBuff[BUFF_SIZE];

	cout << "Le client se connecte au serveur :" << server << " sur le port " << nbPort << endl;

	//Aller chercher le serveur
	LPHOSTENT lphostent;

	lphostent = gethostbyname(server);
	if (lphostent == NULL)
	{
		PRINTERROR("gethostbyname()");
		return;
	}

	if (socketClient == INVALID_SOCKET)
	{
		PRINTERROR("socket()");
		return;
	}

	//Remplir la structure d'adresse
	SOCKADDR_IN socAdrServeur;

	socAdrServeur.sin_family = AF_INET;
	socAdrServeur.sin_addr = *((LPIN_ADDR)*lphostent->h_addr_list);
	socAdrServeur.sin_port = htons(nbPort);

	// Le client se connecte au serveur

	int nRet;

	nRet = connect(socketClient, (LPSOCKADDR)&socAdrServeur, sizeof(struct sockaddr));

	if (nRet == SOCKET_ERROR)
	{
		PRINTERROR("socket()");
		closesocket(socketClient);
		return;
	}
}

void Client::SendData(char* data)
{
	int nRet;
	nRet = send(Client::socketClient, data, strlen(data), 0);

	if (nRet == SOCKET_ERROR)
	{
		PRINTERROR("send()");
		closesocket(socketClient);
		return;
	}
}

void Client::ReceiveData(char* data)
{
	int nRet;
	nRet = recv(socketClient, data, sizeof(data), 0);
	if (nRet == SOCKET_ERROR)
	{
		PRINTERROR("recv()");
		closesocket(socketClient);
		return;
	}
}

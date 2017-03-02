/*
	Serveur.cpp

	Application simple mettant en oeuvre un protocole FTP simplifi�

	Ce programme est la partie serveur de l'application, elle devra
	donc accepter la connection d'un client, recevoir le nom du fichier, et l'envoyer au client

	pour ex�cuter le programme : Serveur_lab3

	Programme r�alis� par Pierre-Andr� Savard

*/

#include <stdio.h>
#include <winsock.h>
#include <iostream>
#include <fstream>

using namespace std;

//D�finit la grandeur du buffer
#define BUFF_SIZE 1024

//D�finit le message d'erreur
#define PRINTERROR(s)	cout<<"\n"<<s<<":"<<WSAGetLastError()

void ServeurStr(short numPort);

void main(int argc, char **argv)
{
	WORD wsVersionRequested = MAKEWORD(1,1);
	WSADATA wsaData;
	short numPort = 5214; //Mettre le num�ro de port � 5214
	int nRet;

	nRet = WSAStartup(wsVersionRequested,&wsaData);
	if(wsaData.wVersion != wsVersionRequested)
	{
		cout<<"Mauvaise version";
		return;
	}

	//Appeler la fonction Serveur
	ServeurStr(numPort);

	//Fermer le winsock
	WSACleanup();

	getchar();


}

void ServeurStr(short numPort)
{
	char sizebuff[BUFF_SIZE];

	//Cr�er un socket TCP/IP
	SOCKET socketServeur;

	socketServeur = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

	if (socketServeur == INVALID_SOCKET)
	{
		PRINTERROR("socket()");
		return;
	}

	//Remplir la structure d'adresse
	SOCKADDR_IN socAdrServeur;

	socAdrServeur.sin_family = AF_INET;
	socAdrServeur.sin_addr.s_addr = INADDR_ANY;
	socAdrServeur.sin_port = htons(numPort);

	//Bind le socket

	int nRet;

	nRet = bind(socketServeur,(LPSOCKADDR) &socAdrServeur, sizeof(struct sockaddr));

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

	//Afficher le nom du serveur et le num�ro de port

	cout << "Serveur : " << sizebuff << "ecoute sur le port : " << numPort;

	//Faire �couter le socket serveur

	cout<< "\nlisten()";
	nRet = listen(socketServeur,SOMAXCONN);

	if (nRet == SOCKET_ERROR)
	{
        PRINTERROR("listen()");
		closesocket(socketServeur);
        return;
    }

	//Attendre qu'un client se connecte
	
	SOCKET socketDistant;

	cout<<"\nBloque � accept()";

	socketDistant = accept(socketServeur,NULL,NULL);

	if (socketDistant == INVALID_SOCKET) 
	{
            PRINTERROR("accept()");
			closesocket(socketServeur);
            return;
    }

	//Le serveur est maintenant connect� au client

	//Recevoir le message du client (nom du fichier)

	memset(sizebuff, 0, sizeof(sizebuff));
	nRet = recv(socketDistant, sizebuff, sizeof(sizebuff),0);

	if (nRet == INVALID_SOCKET) 
	{
        PRINTERROR("recv()");
		closesocket(socketServeur);
		closesocket(socketDistant);
        return;
    }

	//Afficher le nom du fichier
	cout << "Le nom du fichier est : " << sizebuff;

	//D�claration d'un fstream pour lire le fichier binaire
	ifstream fs;
	fs.open(sizebuff, ios::in | ios::binary);

	// Aller chercher la taille du fichier
	 fs.seekg (0, ios::end);
	 int filesize = fs.tellg();
	 fs.seekg (0, ios::beg);

	 //Envoyer le nom du fichier au serveur
	char sizeFile[10];
	_itoa_s(filesize,sizeFile,10);
	nRet = send(socketDistant,sizeFile,strlen(sizeFile),0);

	if(nRet == SOCKET_ERROR)
	{
		PRINTERROR("send()");
		closesocket(socketServeur);
		closesocket(socketDistant);
		return;
	}

	//Envoyer le fichier au client
	int totalByte = 0;
	while(totalByte < filesize)
	{
		if(filesize - totalByte >= 1024)
		{
			fs.read(sizebuff,BUFF_SIZE);
			nRet = send(socketDistant,sizebuff,BUFF_SIZE,0);
		}
		else
		{
			fs.read(sizebuff,filesize - totalByte);
			nRet = send(socketDistant,sizebuff,filesize - totalByte,0);
		}
		totalByte += nRet;
		if(nRet == SOCKET_ERROR)
		{
			PRINTERROR("send()");
			closesocket(socketServeur);
			closesocket(socketDistant);
			return;
		}
	}

	closesocket(socketDistant);
	closesocket(socketServeur);
	return;

}
/*
	Client.cpp

	Application simple mettant en oeuvre un protocole FTP simplifié

	Ce programme est la partie client de l'application, elle devra
	donc se connecter au serveur et demander de lui envoyer un fichier

	Mettre l'adresse du serveur dans la ligne de commande et le nom  du fichier à récupérer

	exemple : Client_lab3 127.0.0.1 exemple.png

	Programme réalisé par Pierre-André Savard

*/

#include <stdio.h>
#include <winsock.h>
#include <iostream>
#include <fstream>

using namespace std;

//Définit la grandeur du buffer
#define BUFF_SIZE 1024

//Définit le message d'erreur
#define PRINTERROR(s)	cout<<"\n"<<s<<":"<<WSAGetLastError()

void ClientStr(char *Serveur, short numPort, char *nomFichier);

void main(int argc, char **argv)
{
	WORD wsVersionRequested = MAKEWORD(1,1);
	WSADATA wsaData;
	short numPort = 5214; //Mettre le numéro de port à 5214
	int nRet;

	if (argc != 3)	{
		cout<<"\nSyntax: client nomServeur nomFichier";
		cout<<endl;
		return;
	}

	nRet = WSAStartup(wsVersionRequested,&wsaData);
	if(wsaData.wVersion != wsVersionRequested)
	{
		cout<<"Mauvaise version";
		return;
	}

	//Appeler la fonction Client 
	ClientStr(argv[1], numPort, argv[2]);

	//Fermer le winsock
	WSACleanup();

	getchar();
}

void ClientStr(char *Serveur, short numPort, char *nomFichier)
{
	char sizeBuff[BUFF_SIZE];

	cout<<"Le client se connecte au serveur :" << Serveur << " sur le port " << numPort << endl;

	//Aller chercher le serveur
	LPHOSTENT lphostent;

	lphostent = gethostbyname(Serveur);
	if(lphostent == NULL)
	{
		PRINTERROR("gethostbyname()");
		return;
	}

	//Créer un socket TCP/IP
	SOCKET socketClient;

	socketClient = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

	if (socketClient == INVALID_SOCKET)
	{
		PRINTERROR("socket()");
		return;
	}

	//Remplir la structure d'adresse
	SOCKADDR_IN socAdrServeur;

	socAdrServeur.sin_family = AF_INET;
	socAdrServeur.sin_addr = *((LPIN_ADDR) *lphostent->h_addr_list);
	socAdrServeur.sin_port = htons(numPort);

	// Le client se connecte au serveur

	int nRet;

	nRet = connect(socketClient,(LPSOCKADDR) &socAdrServeur, sizeof( struct sockaddr));

	if(nRet == SOCKET_ERROR)
	{
		PRINTERROR("socket()");
		closesocket(socketClient);
		return;
	}

	//Envoyer le nom du fichier au serveur

	strcpy_s(sizeBuff, nomFichier);
	nRet = send(socketClient,sizeBuff,strlen(sizeBuff),0);

	if(nRet == SOCKET_ERROR)
	{
		PRINTERROR("send()");
		closesocket(socketClient);
		return;
	}

	//Le client reçoit la taille du fichier
	int fileSize = 0;

	nRet = recv(socketClient,sizeBuff,sizeof(sizeBuff),0);
	fileSize = atoi(sizeBuff);
	cout << fileSize;
	if (nRet == SOCKET_ERROR)
	{
        PRINTERROR("recv()");
		closesocket(socketClient);
        return;
	}
	
	//Déclaration d'un ofstream pour écrire mon fichier binaire
	ofstream os;
	os.open(nomFichier,ios::binary | ios::out | ios::trunc);


	// Le client reçoit le contenu du fichier
	int totalByte = 0;
	while(totalByte < fileSize)
	{
		nRet = recv(socketClient,sizeBuff,sizeof(sizeBuff),0);
		totalByte += nRet;
		os.write(sizeBuff,nRet);
	}


	//Afficher le fichier

	closesocket(socketClient);
	return;
}

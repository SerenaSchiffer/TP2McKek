/*

Serveur.cpp

Receive and execute different command lines from client.cpp
Act as a scapegoat

Made by Emile Fortin, FORE19039509, 2016.
Program based on source code offered by Daniel Audet
*/

#include <stdio.h>
#include <winsock.h>
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

#define BUFF_SIZE 1024 //LENGTH OF THE BUFFER

void StreamServer(short nPort);

// Macro used to display errors
#define PRINTERROR(s) cout <<"\n"<<s<<":"<<WSAGetLastError()
#pragma warning(disable:4996) // Compatibility with VS 2012 + 
#define PORT_NUMBER 12345

void Send(string message, SOCKET* sock)
{
	int nRet;
	char szBuff[BUFF_SIZE];

	/*Send the size of the binary file */
	int fileLength = message.length();

	//Convert the int FileLength to a char array in 2 steps
	std::string fileLengthString = std::to_string(fileLength);
	char const *fileLengthChar = fileLengthString.c_str();
	strcpy_s(szBuff, fileLengthChar);

	nRet = send(*sock /* Connected Socket */, szBuff /* Data Buffer */, strlen(szBuff) /* Length of Data */, 0 /* Default Flag */);

	if (nRet == SOCKET_ERROR){
		PRINTERROR("send()");
		return; // Exits Send
	}

	/* Send the binary file */
	cout << "Sending message ..." << endl;
	int cumul = 0; //Sent length
	while (cumul < fileLength) {
		if (fileLength - cumul >= 1024)
		{
			message.copy(szBuff, 1024, cumul);
			nRet = send(*sock /* Connected Host */, szBuff /* Sent Element Buffer */, BUFF_SIZE /* Size of the buffer */, 0 /* Default Flag */);
		}
		else
		{
			message.copy(szBuff, fileLength - cumul, cumul);
			nRet = send(*sock /* Connected Host */, szBuff /* Sent Element Buffer */, fileLength - cumul /* Only send up to end of file */, 0 /* Default Flag */);
		}
		cumul += nRet; // Add the sent data size to the total
	}

	// Close listening socket and client socket

	Sleep(1000);
	cout << "Message Sent Succesfully !" << endl;
}

void SendFile(string fileName, SOCKET* sock)
{
	ifstream input; // Declare an input file stream
	int fileLength; // Size of the binary file
	char* fileBuffer; // Binary file content

	/* Open File */
	input.open(fileName, ios::binary|ios::ate); // Find the binary file at specified location and position to the end

	if(input.is_open()) // Checks if the File is Open
	{
		/* Find File Length */
		fileLength = input.tellg(); // Get Position of last element in file
		input.seekg(0, ios::beg); // Go back to start of file to prepare to read
	}
	else
	{
		cout << "File Cannot be Opened, make sure the name is correct";
		return;
	}
	
	char szBuff[BUFF_SIZE];
	int nRet;
	/*Send the size of the binary file */
	//Convert the int FileLength to a char array in 2 steps
	std::string fileLengthString = std::to_string(fileLength);
	char const *fileLengthChar = fileLengthString.c_str();
	strcpy_s(szBuff, fileLengthChar);

	nRet = send(*sock /* Connected Socket */, szBuff /* Data Buffer */, strlen(szBuff) /* Length of Data */, 0 /* Default Flag */);

	Sleep(1000);


	if(nRet == SOCKET_ERROR){
		PRINTERROR("send()");
		return; 
	}

	/* Send the binary file */
	cout << "Sending file ..." << endl;

	int cumul = 0; //Sent length
	while(cumul < fileLength) {
		if(fileLength - cumul >= 1024)
		{
			input.read(szBuff, BUFF_SIZE);
			nRet = send(*sock /* Connected Host */, szBuff /* Sent Element Buffer */, BUFF_SIZE /* Size of the buffer */, 0 /* Default Flag */);
		}
		else 
		{
			input.read(szBuff, fileLength - cumul); // Only read up to end of file
			nRet = send(*sock /* Connected Host */, szBuff /* Sent Element Buffer */, fileLength - cumul /* Only send up to end of file */, 0 /* Default Flag */);
		}
        cumul += nRet; // Add the sent data size to the total
    }

	input.close();

	Sleep(1000);
	cout << "File sent successfully !" << endl;
}

string Receive(SOCKET* sock)
{
	// Receive file length
	int nRet;
	char szBuff[BUFF_SIZE];

	nRet = recv(*sock /* Connected Host */, szBuff /* Receive Buffer */, sizeof(szBuff) /* Size of the buffer */, 0 /* Default Flag */);

	if (nRet == SOCKET_ERROR){
		PRINTERROR("recv()");
		return "";
	}

	int fileLength;
	fileLength = atoi(szBuff);

	cout << "Preparing to receive file of size : " << fileLength << endl;

	/* Receive the Binary File & Write it to External File*/
	int cumul = 0; // Received Size
	string output;

	while (cumul < fileLength) {
		nRet = recv(*sock /* Connected Host */, szBuff /* Receive Buffer */, sizeof(szBuff) /* Size of the buffer */, 0 /* Default Flag */);
		cumul += nRet; // Add the receive data size to the total
		output.append(szBuff, nRet); // Add this data to the binary file
	}

	// Close connection
	cout << "Message received" << endl;
	return output;
}

void ReceiveFile(SOCKET* sock, string fileName)
{
	// Receive file length
	int nRet;
	char szBuff[BUFF_SIZE];
	nRet = recv(*sock /* Connected Host */, szBuff /* Receive Buffer */, sizeof(szBuff) /* Size of the buffer */, 0 /* Default Flag */);
	
	if(nRet == SOCKET_ERROR){
		PRINTERROR("recv()");
		return; // Return to main function
	}

	int fileLength;
	fileLength = atoi(szBuff);

	/* Receive the Binary File & Write it to External File*/
	int cumul=0; // Received Size
	ofstream output;
	string dest = fileName;

	output.open(dest, ios::trunc | ios::binary); // Write to the specified destination

	if(output.is_open())
	{
		
		while(cumul< fileLength) {
			nRet = recv(*sock /* Connected Host */, szBuff /* Receive Buffer */, sizeof(szBuff) /* Size of the buffer */, 0 /* Default Flag */);
			cumul += nRet; // Add the receive data size to the total
			output.write(szBuff, nRet); // Add this data to the binary file
		}
	}
	else
	{
		cout << "File cannot be opened..." << endl;
		return ;
	}

	// Close connection
	cout << "Data received, closing connection" << endl;
	output.close();
}

SOCKET* Accept()
{
	// Create a TCP/IP stream socket to listen with ( TCP is used instead of UDP since the binary file has to be transfered perfectly )

	SOCKET listenSocket; // Socket used to listen with

	listenSocket = socket(AF_INET /* Adress Family */, SOCK_STREAM /* Socket Type */, IPPROTO_TCP /* Used Protocol */);

	if (listenSocket == INVALID_SOCKET){
		PRINTERROR("socket()");
		return nullptr; // Returns to main since the Socket is invalid
	}

	// Fill in the address structure

	SOCKADDR_IN saServer;

	saServer.sin_family = AF_INET;
	saServer.sin_addr.s_addr = INADDR_ANY; // WinSock will take care of supplying an address
	saServer.sin_port = htons(PORT_NUMBER); // Use a specified port

	// bind the name to the socket

	int nRet;
	nRet = bind(listenSocket /* Socket */, (LPSOCKADDR)&saServer /* Our address */, sizeof(struct sockaddr) /* Size of the address struct */);

	if (nRet == SOCKET_ERROR){
		PRINTERROR("bind()");
		closesocket(listenSocket);
		return nullptr; // Returns to main
	}

	/* Not required, but we print the informations so you can connect a client more easily */

	int nLen;
	nLen = sizeof(SOCKADDR);
	char szBuff[BUFF_SIZE];

	nRet = gethostname(szBuff, sizeof(szBuff));
	if (nRet == SOCKET_ERROR){
		PRINTERROR("gethostname()");
		closesocket(listenSocket);
		return nullptr; // Returns to main
	}

	// Show the server name and port number

	cout << "\nServer named " << szBuff << "listening on port " << PORT_NUMBER;

	// Start listening

	nRet = listen(listenSocket /* The socket that will listen */, SOMAXCONN /* Number of connection request queue */);
	if (nRet == SOCKET_ERROR){
		PRINTERROR("listen()");
		closesocket(listenSocket);
		return nullptr; // Returns to main
	}

	// Wait for an incoming request

	SOCKET* remoteSocket = new SOCKET; // Socket used to transfer data to the client

	cout << "\nBlocking at accept()";
	*remoteSocket = accept(listenSocket /* Listening Socket */, NULL, NULL /* Optional client address + length */);
	if (*remoteSocket == INVALID_SOCKET){
		PRINTERROR("accept()");
		closesocket(listenSocket);
		return nullptr; // Returns to main
	}

	// Now connected to client. New socket descriptor return already has client address
	return remoteSocket;
}

void ShowDir(SOCKET* client)
{
	system("dir > res.txt");
	SendFile("res.txt", client);
	remove("res.txt");
}

void ChangeDir(SOCKET* client)
{
	string entry = Receive(client);
	SetCurrentDirectory(entry.c_str());
}

void MakeDir(SOCKET* client)
{
	string entry = Receive(client);
	entry = "mkdir " + entry;
	system(entry.c_str());
}

void RemoveDir(SOCKET* client)
{
	string entry = Receive(client);
	entry = "rmdir " + entry;
	system(entry.c_str());
}

void DelFile(SOCKET* client)
{
	string entry = Receive(client);
	entry = "del " + entry;
	system(entry.c_str());
}

void RecvFile(SOCKET* client)
{
	string fileName = Receive(client);
	ReceiveFile(client, fileName);
}

void SndFile(SOCKET* client)
{
	string fileName= Receive(client);
	SendFile(fileName, client);
}

void Start(SOCKET* client)
{
	string fileName= Receive(client);
	fileName = "start " + fileName;
	system(fileName.c_str());
}

void MainLoop(SOCKET* client)
{
	while(true)
	{
		string message = Receive(client);
		if(message == "dir")
			ShowDir(client);

		if(message == "cd")
			ChangeDir(client);

		if(message == "mkdir")
			MakeDir(client);

		if(message == "rmdir")
			RemoveDir(client);

		if(message == "del")
			DelFile(client);

		if(message == "send")
			RecvFile(client);

		if(message == "recv")
			SndFile(client);

		if(message == "start")
			Start(client);

		if(message == "EXIT")
			return;
	}
}

int main()
{
	WORD wVersionRequested = MAKEWORD(1, 1);
	WSADATA wsaData;
	int nRet;

	// Initialize WinSock and check the version
	nRet = WSAStartup(wVersionRequested, &wsaData);
	if (wsaData.wVersion != wVersionRequested){
		cout << "Wrong version of WinSock !";
		return 0;
	}

	// Do the client operations
	SOCKET* client = Accept();
	if (client == NULL)
		return 0;

	MainLoop(client);
	
	// Release WinSock
	WSACleanup();
	return 0;
}
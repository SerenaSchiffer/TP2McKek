/*

Client.cpp

Send and execute different command lines to server.cpp

Made by Emile Fortin, FORE19039509, 2016.
Program based on source code offered by Daniel Audet
*/

#include <stdio.h>
#include <winsock.h>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

#pragma warning(disable:4996) // Compatibility with VS2012 + 
#define BUFF_SIZE 1024 //LENGTH OF THE BUFFER
#define SERVER_NAME "172.16.13.33"
#define PORT_NUMBER 12345

void StreamServer(short nPort);

// Macro used to display errors

#define PRINTERROR(s) cout <<"\n"<<s<<":"<<WSAGetLastError()

int GetInt()
{
	while(true)
	{
		string entry;
		cin >> entry;
		try
		{
			int integer = stoi(entry);
			return integer;
		}
		catch(...)
		{
			cout << "Invalid entry, please enter an integer" << endl;
		}
	}
}

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

SOCKET* Connect()
{
	// Find the server
	LPHOSTENT lpHostEntry;

	lpHostEntry =  gethostbyname(SERVER_NAME);
	if (lpHostEntry == NULL)
	{
		PRINTERROR("gethostbymname()");
		return nullptr; // Return to previous function
	}

	// Create a TCP/IP Stream Socket
	SOCKET* theSocket = new SOCKET;

	*theSocket = socket(AF_INET /* Address Family */, SOCK_STREAM /* Socket Type */, IPPROTO_TCP /* Protocol */);
	if (*theSocket == INVALID_SOCKET){
		PRINTERROR("socket()");
		return nullptr; // Return to previous function
	}

	// Fill in the address structure

	SOCKADDR_IN saServer;

	saServer.sin_family = AF_INET;
	saServer.sin_addr = *((LPIN_ADDR)*lpHostEntry->h_addr_list); // Server's address
	saServer.sin_port = htons(PORT_NUMBER); // Defined Port

	// Connect to the server
	int nRet;
	nRet = connect(*theSocket /* Socket */, (LPSOCKADDR)&saServer /* Server Address */, sizeof(struct sockaddr) /* Length of server address struct */);
	if (nRet == SOCKET_ERROR){
		PRINTERROR("socket()");
		closesocket(*theSocket);
		return nullptr; // Return to main function
	}

	return theSocket;
}

void ShowDir(SOCKET* host)
{
	Send("dir", host);
	cout << Receive(host);
}

void ChangeDir(SOCKET* host)
{
	cout << "Where do you want to navigate ?" << endl;
	string entry;
	fflush(stdin);
	getline(cin, entry);
	Send("cd", host);
	Send(entry, host);
}

void CreateFolder(SOCKET* host)
{
	cout << "What is the name of this new folder ?" << endl;
	string entry;
	fflush(stdin);
	getline(cin, entry);
	Send("mkdir", host);
	Send(entry, host);
}

void DeleteFolder(SOCKET* host)
{
	cout << "What is the name of the folder to delete ?" << endl;
	string entry;
	fflush(stdin);
	getline(cin, entry);
	Send("rmdir", host);
	Send(entry, host);
}

void DelFile(SOCKET* host)
{
	cout << "What is the name of the file to delete ?" << endl;
	string entry;
	fflush(stdin);
	getline(cin, entry);
	Send("del", host);
	Send(entry, host);
}

void Send_File(SOCKET* host)
{
	cout << "What is the name of the file to send ?" << endl;
	string entry;
	fflush(stdin);
	getline(cin, entry);
	Send("send", host);
	Send(entry, host);
	SendFile(entry, host);
}

void Receive_File(SOCKET* host)
{
	cout << "What is the name of the file to receive ?" << endl;
	string entry;
	fflush(stdin);
	getline(cin, entry);
	Send("recv", host);
	Send(entry, host);
	ReceiveFile(host, entry);
}

void StartFile(SOCKET* host)
{
	cout << "What is the name of the file to start ?" << endl;
	string entry;
	fflush(stdin);
	getline(cin, entry);
	Send("start", host);
	Send(entry, host);
}

void ExitProgram(SOCKET* host)
{
	Send("EXIT", host);
}

void mainLoop(SOCKET* host)
{
	while(true)
	{
		cout << "Main Menu : Please enter one of the following options." << endl;
		cout << "1 - Show the current folder content ( dir )" << endl;
		cout << "2 - Changer the current directory ( cd )" << endl;
		cout << "3 - Create a folder ( mkdir )" << endl;
		cout << "4 - Delete a folder ( rmdir )" << endl;
		cout << "5 - Delete a File ( del )" << endl;
		cout << "6 - Send a File to the Current Folder" << endl;
		cout << "7 - Receive a File from the Current Folder" << endl;
		cout << "8 - Start an executable file" << endl;
		cout << "9 - Exit Program on Client and Server" << endl;
		int entry = GetInt();
		switch(entry)
		{
			case 1:
				ShowDir(host);
				break;
			case 2:
				ChangeDir(host);
				break;
			case 3:
				CreateFolder(host);
				break;
			case 4:
				DeleteFolder(host);
				break;
			case 5:
				DelFile(host);
				break;
			case 6:
				Send_File(host);
				break;
			case 7:
				Receive_File(host);
				break;
			case 8:
				StartFile(host);
				break;
			case 9:
				ExitProgram(host);
				return;
				break;
		}
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
	SOCKET* host = Connect();
	if (host == NULL)
		return 0;

	mainLoop(host);

	// Release WinSock
	WSACleanup();
	return 0;
}
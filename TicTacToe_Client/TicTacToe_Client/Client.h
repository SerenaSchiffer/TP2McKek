#include <winsock.h>
#include <iostream>
#pragma comment(lib, "Ws2_32.lib")
#pragma once
ref class Client
{
public:
	Client();
	static short nbPort;
	static char* server;
	static int flag;
	static SOCKET socketClient;
	static void Test();
	static void Connect();
	static void SendData(char* data);
	static std::string ReceiveData();

};


#pragma once

#pragma comment(lib, "Ws2_32.lib")

class Serveur
{
public:
	Serveur();

	void ServeurConnect(int noPort);
	void Send(char* message);
	void Receive();

private:
	int nRet;
	int cpt;
	int playerId;

	SOCKET socketServeur;
	SOCKET *socketDistant;
};

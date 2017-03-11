#pragma once

#pragma comment(lib, "Ws2_32.lib")

class Serveur
{
public:
	Serveur();

	void ServeurConnect(int noPort);
	void Send(char* message);
	void Receive();
	int playerId;

private:
	int nRet;
	int cpt;

	SOCKET socketServeur;
	SOCKET socketDistant[2];
};

#include "MainGame.h"
#include "Client.h"
#include <iostream>

using namespace System;
using namespace System::Windows::Forms;


[STAThread]
static void main2()
{
	Client leClient;
	std::cout << Client::nbPort << " " << Client::server;
}

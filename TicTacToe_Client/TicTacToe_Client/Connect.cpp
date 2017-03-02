#include "Connect.h"
#include "Client.h"

using namespace System;
using namespace System::Windows::Forms;


[STAThread]
void main2()
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Client qqch = Client();
	qqch.Test();
	TicTacToe_Client::Connect form;
	Application::Run(%form);
}

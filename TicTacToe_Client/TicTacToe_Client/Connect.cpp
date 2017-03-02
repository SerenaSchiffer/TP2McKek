#include "Connect.h"

using namespace System;
using namespace System::Windows::Forms;


[STAThread]
void main()
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	TicTacToe_Client::Connect form;
	Application::Run(%form);
}

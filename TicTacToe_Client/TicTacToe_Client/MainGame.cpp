#include "MainGame.h"

using namespace System;
using namespace System::Windows::Forms;


[STAThread]
void main()
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	TicTacToe_Client::MainGame form;
	Application::Run(%form);
}

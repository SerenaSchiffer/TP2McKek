# include <winsock2.h>
#include <iostream>
#include <string>
#include "Client.h"
#include "MainGame.h"
using namespace System::Runtime::InteropServices;

namespace TicTacToe_Client {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class Connect : public System::Windows::Forms::Form
	{
	public:
		Connect(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Connect()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^  tbIpAddress;
	protected:
	private: System::Windows::Forms::Label^  lblIpAddress;
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::Label^  lblPort;
	private: System::Windows::Forms::Button^  buttonConnexion;

	protected:

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->tbIpAddress = (gcnew System::Windows::Forms::TextBox());
			this->lblIpAddress = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->lblPort = (gcnew System::Windows::Forms::Label());
			this->buttonConnexion = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// tbIpAddress
			// 
			this->tbIpAddress->Location = System::Drawing::Point(59, 67);
			this->tbIpAddress->Name = L"tbIpAddress";
			this->tbIpAddress->Size = System::Drawing::Size(164, 22);
			this->tbIpAddress->TabIndex = 0;
			// 
			// lblIpAddress
			// 
			this->lblIpAddress->AutoSize = true;
			this->lblIpAddress->Location = System::Drawing::Point(100, 47);
			this->lblIpAddress->Name = L"lblIpAddress";
			this->lblIpAddress->Size = System::Drawing::Size(75, 17);
			this->lblIpAddress->TabIndex = 1;
			this->lblIpAddress->Text = L"Ip Address";
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(59, 143);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(164, 22);
			this->textBox1->TabIndex = 2;
			// 
			// lblPort
			// 
			this->lblPort->AutoSize = true;
			this->lblPort->Location = System::Drawing::Point(125, 123);
			this->lblPort->Name = L"lblPort";
			this->lblPort->Size = System::Drawing::Size(34, 17);
			this->lblPort->TabIndex = 3;
			this->lblPort->Text = L"Port";
			// 
			// buttonConnexion
			// 
			this->buttonConnexion->Location = System::Drawing::Point(180, 200);
			this->buttonConnexion->Name = L"buttonConnexion";
			this->buttonConnexion->Size = System::Drawing::Size(90, 41);
			this->buttonConnexion->TabIndex = 4;
			this->buttonConnexion->Text = L"Connexion";
			this->buttonConnexion->UseVisualStyleBackColor = true;
			this->buttonConnexion->Click += gcnew System::EventHandler(this, &Connect::buttonConnexion_Click);
			// 
			// Connect
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(282, 253);
			this->Controls->Add(this->buttonConnexion);
			this->Controls->Add(this->lblPort);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->lblIpAddress);
			this->Controls->Add(this->tbIpAddress);
			this->Name = L"Connect";
			this->Text = L"Connexion Screen";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void buttonConnexion_Click(System::Object^  sender, System::EventArgs^  e) {
		/* Socket C
		WSADATA wsadata;
		WSAStartup(MAKEWORD(2, 0), &wsadata);
		SOCKET * clientSocket;
		SOCKADDR_IN sin;
		sin.sin_addr.s_addr = inet_addr("127.0.0.1");
		sin.sin_family = AF_INET;
		sin.sin_port = htons(4554);
		*clientSocket = socket(AF_INET, SOCK_STREAM, 0);
		bind(*clientSocket, (SOCKADDR *)&sin, sizeof(sin));
		WSACleanup();
		*/

		String  ^ipAddr = tbIpAddress->Text;
		String ^port = textBox1->Text;
		IntPtr ptrNativeString = Marshal::StringToHGlobalAnsi(ipAddr);
		Client::nbPort = System::Int16::Parse(port);
		Client::server = static_cast<char*>(ptrNativeString.ToPointer());
		std::cout << Client::nbPort << std::endl;
		std::cout << Client::server << std::endl;

		Form::Visible = false;
		TicTacToe_Client::MainGame form;
		Form::ShowDialog(%form);
	}
};
}
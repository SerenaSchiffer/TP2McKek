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
			this->tbIpAddress->Location = System::Drawing::Point(44, 54);
			this->tbIpAddress->Margin = System::Windows::Forms::Padding(2);
			this->tbIpAddress->Name = L"tbIpAddress";
			this->tbIpAddress->Size = System::Drawing::Size(124, 20);
			this->tbIpAddress->TabIndex = 0;
			this->tbIpAddress->Text = L"127.0.0.1";
			this->tbIpAddress->TextChanged += gcnew System::EventHandler(this, &Connect::tbIpAddress_TextChanged);
			// 
			// lblIpAddress
			// 
			this->lblIpAddress->AutoSize = true;
			this->lblIpAddress->Location = System::Drawing::Point(75, 38);
			this->lblIpAddress->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->lblIpAddress->Name = L"lblIpAddress";
			this->lblIpAddress->Size = System::Drawing::Size(57, 13);
			this->lblIpAddress->TabIndex = 1;
			this->lblIpAddress->Text = L"Ip Address";
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(44, 116);
			this->textBox1->Margin = System::Windows::Forms::Padding(2);
			this->textBox1->Name = L"textBox1";
			this->textBox1->ReadOnly = true;
			this->textBox1->Size = System::Drawing::Size(124, 20);
			this->textBox1->TabIndex = 2;
			this->textBox1->Text = L"1234";
			// 
			// lblPort
			// 
			this->lblPort->AutoSize = true;
			this->lblPort->Location = System::Drawing::Point(94, 100);
			this->lblPort->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->lblPort->Name = L"lblPort";
			this->lblPort->Size = System::Drawing::Size(26, 13);
			this->lblPort->TabIndex = 3;
			this->lblPort->Text = L"Port";
			// 
			// buttonConnexion
			// 
			this->buttonConnexion->Location = System::Drawing::Point(135, 162);
			this->buttonConnexion->Margin = System::Windows::Forms::Padding(2);
			this->buttonConnexion->Name = L"buttonConnexion";
			this->buttonConnexion->Size = System::Drawing::Size(68, 33);
			this->buttonConnexion->TabIndex = 4;
			this->buttonConnexion->Text = L"Connexion";
			this->buttonConnexion->UseVisualStyleBackColor = true;
			this->buttonConnexion->Click += gcnew System::EventHandler(this, &Connect::buttonConnexion_Click);
			// 
			// Connect
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(212, 206);
			this->Controls->Add(this->buttonConnexion);
			this->Controls->Add(this->lblPort);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->lblIpAddress);
			this->Controls->Add(this->tbIpAddress);
			this->Margin = System::Windows::Forms::Padding(2);
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


		//Bout de code a enlever (enlever le send et le receive et le gérer a la bonne place)
		Form::Visible = false;
		Client::Connect();
		//Client::SendData("allo");
		//Client::ReceiveData();
		TicTacToe_Client::MainGame form;
		form.ShowDialog();
	}
private: System::Void tbIpAddress_TextChanged(System::Object^  sender, System::EventArgs^  e) {
}
};
}
#pragma once


#include <string>
#include <iostream>
#include "GameBoard.h"
#include "Client.h"

namespace TicTacToe_Client {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MainGame
	/// </summary>
	public ref class MainGame : public System::Windows::Forms::Form
	{
	public:
		GameBoard myGameBoard;
		array<String ^>^ picturesPaths;
		array<String ^>^ symboleNames;
	private: System::Windows::Forms::HelpProvider^  helpProvider1;
	public:
		Symboles joueurCourant;
		Symboles joueurClient;
		/*void OnReceive()
		{
			while()
		}*/
		MainGame(void)
		{
			InitializeComponent();
			picturesPaths = gcnew array<String ^>(3);
			picturesPaths[0] = "vide.png";
			picturesPaths[1] = "x.png";
			picturesPaths[2] = "o.png";
			symboleNames = gcnew array<String ^>(3);
			symboleNames[0] = " ";
			symboleNames[1] = "X";
			symboleNames[2] = "O";
			joueurCourant = Symboles::x;
			char* joueur = Client::ReceiveData();
			int joueurInt = atoi(joueur);
			if (joueurInt == 0)
			{
				joueurClient = Symboles::x;
			}
			else
			{
				joueurClient = Symboles::o;
			}
		}


	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainGame()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^  case1;
	private: System::Windows::Forms::PictureBox^  case2;
	private: System::Windows::Forms::PictureBox^  case3;
	private: System::Windows::Forms::PictureBox^  case4;

	private: System::Windows::Forms::PictureBox^  case6;
	private: System::Windows::Forms::PictureBox^  case7;
	private: System::Windows::Forms::PictureBox^  case8;
	private: System::Windows::Forms::PictureBox^  case5;
	private: System::Windows::Forms::PictureBox^  case9;
	private: System::Windows::Forms::PictureBox^  background;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  currentPlayer;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  playerSign;

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
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(MainGame::typeid));
			this->case1 = (gcnew System::Windows::Forms::PictureBox());
			this->case2 = (gcnew System::Windows::Forms::PictureBox());
			this->case3 = (gcnew System::Windows::Forms::PictureBox());
			this->case4 = (gcnew System::Windows::Forms::PictureBox());
			this->case6 = (gcnew System::Windows::Forms::PictureBox());
			this->case7 = (gcnew System::Windows::Forms::PictureBox());
			this->case8 = (gcnew System::Windows::Forms::PictureBox());
			this->case5 = (gcnew System::Windows::Forms::PictureBox());
			this->case9 = (gcnew System::Windows::Forms::PictureBox());
			this->background = (gcnew System::Windows::Forms::PictureBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->currentPlayer = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->playerSign = (gcnew System::Windows::Forms::Label());
			this->helpProvider1 = (gcnew System::Windows::Forms::HelpProvider());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->case1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->case2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->case3))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->case4))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->case6))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->case7))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->case8))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->case5))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->case9))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->background))->BeginInit();
			this->SuspendLayout();
			// 
			// case1
			// 
			this->case1->Cursor = System::Windows::Forms::Cursors::Hand;
			this->case1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"case1.Image")));
			this->case1->Location = System::Drawing::Point(10, 10);
			this->case1->Name = L"case1";
			this->case1->Size = System::Drawing::Size(150, 150);
			this->case1->TabIndex = 0;
			this->case1->TabStop = false;
			this->case1->Tag = L"1";
			this->case1->Click += gcnew System::EventHandler(this, &MainGame::case_Click);
			// 
			// case2
			// 
			this->case2->Cursor = System::Windows::Forms::Cursors::Hand;
			this->case2->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"case2.Image")));
			this->case2->Location = System::Drawing::Point(170, 10);
			this->case2->Name = L"case2";
			this->case2->Size = System::Drawing::Size(150, 150);
			this->case2->TabIndex = 1;
			this->case2->TabStop = false;
			this->case2->Click += gcnew System::EventHandler(this, &MainGame::case_Click);
			// 
			// case3
			// 
			this->case3->Cursor = System::Windows::Forms::Cursors::Hand;
			this->case3->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"case3.Image")));
			this->case3->Location = System::Drawing::Point(330, 10);
			this->case3->Name = L"case3";
			this->case3->Size = System::Drawing::Size(150, 150);
			this->case3->TabIndex = 2;
			this->case3->TabStop = false;
			this->case3->Click += gcnew System::EventHandler(this, &MainGame::case_Click);
			// 
			// case4
			// 
			this->case4->Cursor = System::Windows::Forms::Cursors::Hand;
			this->case4->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"case4.Image")));
			this->case4->Location = System::Drawing::Point(10, 170);
			this->case4->Name = L"case4";
			this->case4->Size = System::Drawing::Size(150, 150);
			this->case4->TabIndex = 3;
			this->case4->TabStop = false;
			this->case4->Click += gcnew System::EventHandler(this, &MainGame::case_Click);
			// 
			// case6
			// 
			this->case6->Cursor = System::Windows::Forms::Cursors::Hand;
			this->case6->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"case6.Image")));
			this->case6->Location = System::Drawing::Point(330, 170);
			this->case6->Name = L"case6";
			this->case6->Size = System::Drawing::Size(150, 150);
			this->case6->TabIndex = 5;
			this->case6->TabStop = false;
			this->case6->Click += gcnew System::EventHandler(this, &MainGame::case_Click);
			// 
			// case7
			// 
			this->case7->Cursor = System::Windows::Forms::Cursors::Hand;
			this->case7->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"case7.Image")));
			this->case7->Location = System::Drawing::Point(10, 330);
			this->case7->Name = L"case7";
			this->case7->Size = System::Drawing::Size(150, 150);
			this->case7->TabIndex = 6;
			this->case7->TabStop = false;
			this->case7->Click += gcnew System::EventHandler(this, &MainGame::case_Click);
			// 
			// case8
			// 
			this->case8->Cursor = System::Windows::Forms::Cursors::Hand;
			this->case8->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"case8.Image")));
			this->case8->Location = System::Drawing::Point(170, 330);
			this->case8->Name = L"case8";
			this->case8->Size = System::Drawing::Size(150, 150);
			this->case8->TabIndex = 7;
			this->case8->TabStop = false;
			this->case8->Click += gcnew System::EventHandler(this, &MainGame::case_Click);
			// 
			// case5
			// 
			this->case5->Cursor = System::Windows::Forms::Cursors::Hand;
			this->case5->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"case5.Image")));
			this->case5->Location = System::Drawing::Point(170, 170);
			this->case5->Name = L"case5";
			this->case5->Size = System::Drawing::Size(150, 150);
			this->case5->TabIndex = 4;
			this->case5->TabStop = false;
			this->case5->Click += gcnew System::EventHandler(this, &MainGame::case_Click);
			// 
			// case9
			// 
			this->case9->Cursor = System::Windows::Forms::Cursors::Hand;
			this->case9->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"case9.Image")));
			this->case9->Location = System::Drawing::Point(330, 330);
			this->case9->Name = L"case9";
			this->case9->Size = System::Drawing::Size(150, 150);
			this->case9->TabIndex = 8;
			this->case9->TabStop = false;
			this->case9->Click += gcnew System::EventHandler(this, &MainGame::case_Click);
			// 
			// background
			// 
			this->background->BackColor = System::Drawing::SystemColors::ActiveCaptionText;
			this->background->Location = System::Drawing::Point(10, 10);
			this->background->Name = L"background";
			this->background->Size = System::Drawing::Size(470, 470);
			this->background->TabIndex = 9;
			this->background->TabStop = false;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->BackColor = System::Drawing::Color::Transparent;
			this->label1->Font = (gcnew System::Drawing::Font(L"Lucida Console", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(486, 10);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(185, 19);
			this->label1->TabIndex = 10;
			this->label1->Text = L"Joueur Courant :";
			// 
			// currentPlayer
			// 
			this->currentPlayer->AutoSize = true;
			this->currentPlayer->BackColor = System::Drawing::Color::Transparent;
			this->currentPlayer->Font = (gcnew System::Drawing::Font(L"Lucida Console", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->currentPlayer->Location = System::Drawing::Point(486, 41);
			this->currentPlayer->Name = L"currentPlayer";
			this->currentPlayer->Size = System::Drawing::Size(20, 19);
			this->currentPlayer->TabIndex = 11;
			this->currentPlayer->Text = L"X";
			this->currentPlayer->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->BackColor = System::Drawing::Color::Transparent;
			this->label2->Font = (gcnew System::Drawing::Font(L"Lucida Console", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(486, 94);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(130, 19);
			this->label2->TabIndex = 12;
			this->label2->Text = L"Vous êtes :";
			// 
			// playerSign
			// 
			this->playerSign->AutoSize = true;
			this->playerSign->BackColor = System::Drawing::Color::Transparent;
			this->playerSign->Font = (gcnew System::Drawing::Font(L"Lucida Console", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->playerSign->Location = System::Drawing::Point(486, 123);
			this->playerSign->Name = L"playerSign";
			this->playerSign->Size = System::Drawing::Size(20, 19);
			this->playerSign->TabIndex = 13;
			this->playerSign->Text = L"X";
			this->playerSign->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// MainGame
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::ButtonHighlight;
			this->ClientSize = System::Drawing::Size(675, 493);
			this->Controls->Add(this->playerSign);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->currentPlayer);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->case9);
			this->Controls->Add(this->case8);
			this->Controls->Add(this->case7);
			this->Controls->Add(this->case6);
			this->Controls->Add(this->case5);
			this->Controls->Add(this->case4);
			this->Controls->Add(this->case3);
			this->Controls->Add(this->case2);
			this->Controls->Add(this->case1);
			this->Controls->Add(this->background);
			this->Name = L"MainGame";
			this->Text = L"MainGame";
			this->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &MainGame::MainGame_Paint);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->case1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->case2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->case3))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->case4))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->case6))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->case7))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->case8))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->case5))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->case9))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->background))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void case_Click(System::Object^  sender, System::EventArgs^  e) {
		//Déterminer on est sur quel controle
		int numCase = 0;
#pragma region chooseNumCase
		if (sender == case1)
			numCase = 1;

		if (sender == case2)
			numCase = 2;

		if (sender == case2)
			numCase = 2;

		if (sender == case3)
			numCase = 3;

		if (sender == case4)
			numCase = 4;

		if (sender == case5)
			numCase = 5;

		if (sender == case6)
			numCase = 6;

		if (sender == case7)
			numCase = 7;

		if (sender == case8)
			numCase = 8;

		if (sender == case9)
			numCase = 9;
#pragma endregion chooseNumCase

		//Tries to add symbol
		if (myGameBoard.cases[numCase - 1] == Symboles::vide &&joueurCourant == joueurClient)
		{
			myGameBoard.AddSymbole(numCase, joueurCourant);
			joueurCourant = (Symboles)(3 - joueurCourant); // Toggle entre x et o
			std::string s = std::to_string(numCase);
			char* msg = new char[s.length()];
			strcpy(msg, s.c_str());
			Client::SendData(msg);
		}

		if (myGameBoard.CheckWinner() != Symboles::vide) // Winner is decided
		{
			this->Invalidate();
			MessageBox::Show("Player " + symboleNames[myGameBoard.CheckWinner()] + " wins !");
			myGameBoard.ResetGame();
			joueurCourant = Symboles::x;
		}

		if (myGameBoard.isDraw()) // Draw game
		{
			this->Invalidate();
			MessageBox::Show("The game ends in a draw !");
			myGameBoard.ResetGame();
			joueurCourant = Symboles::x;
		}
		this->Invalidate();
	}
private: System::Void MainGame_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
	currentPlayer->Text = symboleNames[joueurCourant];
	playerSign->Text = symboleNames[joueurClient];

	case1->Image = Image::FromFile("Images\\" + picturesPaths[myGameBoard.cases[0]]);
	case2->Image = Image::FromFile("Images\\" + picturesPaths[myGameBoard.cases[1]]);
	case3->Image = Image::FromFile("Images\\" + picturesPaths[myGameBoard.cases[2]]);
	case4->Image = Image::FromFile("Images\\" + picturesPaths[myGameBoard.cases[3]]);
	case5->Image = Image::FromFile("Images\\" + picturesPaths[myGameBoard.cases[4]]);
	case6->Image = Image::FromFile("Images\\" + picturesPaths[myGameBoard.cases[5]]);
	case7->Image = Image::FromFile("Images\\" + picturesPaths[myGameBoard.cases[6]]);
	case8->Image = Image::FromFile("Images\\" + picturesPaths[myGameBoard.cases[7]]);
	case9->Image = Image::FromFile("Images\\" + picturesPaths[myGameBoard.cases[8]]);
}
};
}
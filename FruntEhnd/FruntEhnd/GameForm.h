#pragma once

#include <thread>
#include <chrono>
#include <string>
#include <msclr/marshal.h>
#include <msclr\marshal_cppstd.h>
#include "NetworkClient.h"

namespace FrontEnd {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Game
	/// </summary>
	public ref class GameForm : public System::Windows::Forms::Form
	{
	public:
		GameForm(NetworkClient^ networkClient): networkClient(networkClient)
		{
			InitializeComponent();
			networkThread = gcnew System::Threading::Thread(gcnew System::Threading::ThreadStart(this, &GameForm::receiveLoop));
			networkThread->Start();
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~GameForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		System::Threading::Thread^ networkThread;
		NetworkClient^ networkClient;
		msclr::interop::marshal_context context;
	private: System::Windows::Forms::Button^ btnFinish;
	private: System::Windows::Forms::TextBox^ txtLogs;
	private: System::Windows::Forms::TextBox^ txtCmd;
	private: System::Windows::Forms::Button^ btnSendPacket;

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
			this->btnFinish = (gcnew System::Windows::Forms::Button());
			this->txtLogs = (gcnew System::Windows::Forms::TextBox());
			this->txtCmd = (gcnew System::Windows::Forms::TextBox());
			this->btnSendPacket = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// btnFinish
			// 
			this->btnFinish->Location = System::Drawing::Point(115, 227);
			this->btnFinish->Name = L"btnFinish";
			this->btnFinish->Size = System::Drawing::Size(75, 23);
			this->btnFinish->TabIndex = 0;
			this->btnFinish->Text = L"Pull Out";
			this->btnFinish->UseVisualStyleBackColor = true;
			this->btnFinish->Click += gcnew System::EventHandler(this, &GameForm::btnFinish_Click);
			// 
			// txtLogs
			// 
			this->txtLogs->Location = System::Drawing::Point(12, 123);
			this->txtLogs->Multiline = true;
			this->txtLogs->Name = L"txtLogs";
			this->txtLogs->ReadOnly = true;
			this->txtLogs->Size = System::Drawing::Size(259, 71);
			this->txtLogs->TabIndex = 1;
			// 
			// txtCmd
			// 
			this->txtCmd->Location = System::Drawing::Point(13, 201);
			this->txtCmd->Name = L"txtCmd";
			this->txtCmd->Size = System::Drawing::Size(177, 20);
			this->txtCmd->TabIndex = 2;
			// 
			// btnSendPacket
			// 
			this->btnSendPacket->Location = System::Drawing::Point(196, 199);
			this->btnSendPacket->Name = L"btnSendPacket";
			this->btnSendPacket->Size = System::Drawing::Size(75, 23);
			this->btnSendPacket->TabIndex = 0;
			this->btnSendPacket->Text = L"Send";
			this->btnSendPacket->UseVisualStyleBackColor = true;
			this->btnSendPacket->Click += gcnew System::EventHandler(this, &GameForm::btnFinish_Click);
			// 
			// GameForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 261);
			this->Controls->Add(this->txtCmd);
			this->Controls->Add(this->txtLogs);
			this->Controls->Add(this->btnSendPacket);
			this->Controls->Add(this->btnFinish);
			this->Name = L"GameForm";
			this->Text = L"Game";
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &GameForm::GameForm_FormClosed);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void btnFinish_Click(System::Object^ sender, System::EventArgs^ e) {
		std::string rawAddr = context.marshal_as<std::string>(this->txtCmd->Text);
		this->log(System::String::Format("Sent: <{0}>", this->txtCmd->Text));
		networkClient->sendInfo(rawAddr);
	}
	private: System::Void GameForm_FormClosed(System::Object^ sender, System::Windows::Forms::FormClosedEventArgs^ e) {
		Application::Exit();
	}

	private: void receiveLoop() {
		for (;;) {
			std::string msg = networkClient->receiveInfo();
			this->log(msg);
		}
	}

	private: System::Void log(std::string msg) {
		this->log(gcnew System::String(msg.c_str()));
	}
	private: System::Void log(System::String^ msg) {
		this->txtLogs->AppendText(msg);
		this->txtLogs->AppendText("\n");
	}
};
}

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
			this->networkClient->onMessage += gcnew Del(this, &GameForm::GameForm_OnMessage);
			this->networkThread = gcnew System::Threading::Thread(gcnew System::Threading::ThreadStart(this, &GameForm::receiveLoop));
			this->networkThread->Start();

			System::Random r;
			this->graphPoints = gcnew System::Collections::Generic::List<int>();
			int x = 0;
			for (int i = 0; i < 25; i++) {
				int x = x + (int)(r.NextDouble() * 200) - 100;
				this->graphPoints->Add(x);
			}
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

	private: delegate void SafeMessageEventDelegate(System::String^ msg);
	private: System::Threading::Thread^ networkThread;
	private: NetworkClient^ networkClient;
	private: msclr::interop::marshal_context context;
	private: System::Collections::Generic::List<int>^ graphPoints;

	private: System::Windows::Forms::Button^ btnFinish;
	private: System::Windows::Forms::TextBox^ txtLogs;
	private: System::Windows::Forms::TextBox^ txtCmd;
	private: System::Windows::Forms::Button^ btnSendPacket;
	private: System::Windows::Forms::GroupBox^ groupBox1;
	private: System::Windows::Forms::Panel^ pnlGraph;

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
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->pnlGraph = (gcnew System::Windows::Forms::Panel());
			this->groupBox1->SuspendLayout();
			this->SuspendLayout();
			// 
			// btnFinish
			// 
			this->btnFinish->Location = System::Drawing::Point(110, 180);
			this->btnFinish->Name = L"btnFinish";
			this->btnFinish->Size = System::Drawing::Size(75, 23);
			this->btnFinish->TabIndex = 0;
			this->btnFinish->Text = L"Pull Out";
			this->btnFinish->UseVisualStyleBackColor = true;
			this->btnFinish->Click += gcnew System::EventHandler(this, &GameForm::btnFinish_Click);
			// 
			// txtLogs
			// 
			this->txtLogs->Location = System::Drawing::Point(8, 19);
			this->txtLogs->Multiline = true;
			this->txtLogs->Name = L"txtLogs";
			this->txtLogs->ReadOnly = true;
			this->txtLogs->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->txtLogs->Size = System::Drawing::Size(245, 71);
			this->txtLogs->TabIndex = 1;
			// 
			// txtCmd
			// 
			this->txtCmd->Location = System::Drawing::Point(9, 97);
			this->txtCmd->Name = L"txtCmd";
			this->txtCmd->Size = System::Drawing::Size(163, 20);
			this->txtCmd->TabIndex = 2;
			// 
			// btnSendPacket
			// 
			this->btnSendPacket->Location = System::Drawing::Point(192, 95);
			this->btnSendPacket->Name = L"btnSendPacket";
			this->btnSendPacket->Size = System::Drawing::Size(61, 23);
			this->btnSendPacket->TabIndex = 0;
			this->btnSendPacket->Text = L"Send";
			this->btnSendPacket->UseVisualStyleBackColor = true;
			this->btnSendPacket->Click += gcnew System::EventHandler(this, &GameForm::btnFinish_Click);
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->txtLogs);
			this->groupBox1->Controls->Add(this->txtCmd);
			this->groupBox1->Controls->Add(this->btnSendPacket);
			this->groupBox1->Location = System::Drawing::Point(13, 228);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(259, 146);
			this->groupBox1->TabIndex = 3;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Debug";
			// 
			// pnlGraph
			// 
			this->pnlGraph->Location = System::Drawing::Point(13, 13);
			this->pnlGraph->Name = L"pnlGraph";
			this->pnlGraph->Size = System::Drawing::Size(253, 145);
			this->pnlGraph->TabIndex = 4;
			this->pnlGraph->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &GameForm::GameForm_OnPaintGraph);
			// 
			// GameForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 386);
			this->Controls->Add(this->pnlGraph);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->btnFinish);
			this->Name = L"GameForm";
			this->Text = L"Game";
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &GameForm::GameForm_FormClosed);
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void btnFinish_Click(System::Object^ sender, System::EventArgs^ e) {
		std::string rawAddr = context.marshal_as<std::string>(this->txtCmd->Text);
		this->log(System::String::Format("Sent <{0}>", this->txtCmd->Text));
		networkClient->sendInfo(rawAddr);
	}
	private: System::Void GameForm_FormClosed(System::Object^ sender, System::Windows::Forms::FormClosedEventArgs^ e) {
		this->networkClient->stop();
		Application::Exit();
	}

	private: System::Void GameForm_OnMessage(System::String^ msg) {
		if (this->IsDisposed)
			return;
		if (!this->IsHandleCreated)
			this->CreateHandle();
		if (!this->Created)
			return;
		SafeMessageEventDelegate^ d = gcnew SafeMessageEventDelegate(this, &GameForm::GameForm_OnMessageSafe);
		this->Invoke(d, msg);
	}

	private: System::Void GameForm_OnMessageSafe(System::String^ msg) {
		this->log(System::String::Format("Received <{0}>", msg));
	}

	private: void receiveLoop() {
		networkClient->receiveInfo();
	}

	private: System::Void log(std::string msg) {
		this->log(gcnew System::String(msg.c_str()));
	}

	private: System::Void log(System::String^ msg) {
		this->txtLogs->AppendText(msg);
		this->txtLogs->AppendText("\n");
	}

	private: System::Void GameForm_OnPaintGraph(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ pe) {
		Graphics^ g = pe->Graphics;
		g->Clear(Color::AntiqueWhite);

		System::Drawing::Rectangle area = this->pnlGraph->ClientRectangle;
		Pen^ redPen = gcnew Pen(Color::Red);
		redPen->Width = 1;
		Pen^ blackPen = gcnew Pen(Color::Black);
		blackPen->Width = 1;

		double min = 0, max = 0, step = 0, scale=1;
		for each (int d in this->graphPoints) {
			if (d < min)
				min = d;
			if (d > max)
				max = d;
			step++;
		}
		step = area.Width/step;
		scale = 1/((max - min) / area.Height)/2;

		g->DrawLine(blackPen, 0, area.Height / 2, area.Width, area.Height / 2);
		int prevX = 0, prevY = area.Height / 2;
		for each (int d in this->graphPoints) {
			int scaledY = d * scale + area.Height / 2;
			g->DrawLine(redPen, prevX, prevY, prevX+step, scaledY);
			prevX += step;
			prevY = scaledY;
		}
	}
};
}

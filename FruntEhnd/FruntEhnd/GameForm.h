#pragma once

#include <thread>
#include <chrono>
#include <string>
#include <math.h>
#include <random>
#include <msclr/marshal.h>
#include <msclr\marshal_cppstd.h>
#include "NetworkClient.h"
#include "User.h"

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
		GameForm(NetworkClient^ networkClient, System::String^ username): networkClient(networkClient), username(username)
		{
			InitializeComponent();
			this->networkClient->onMessage += gcnew Del(this, &GameForm::GameForm_OnMessage);
			this->networkThread = gcnew System::Threading::Thread(gcnew System::Threading::ThreadStart(this, &GameForm::receiveLoop));
			this->users = gcnew System::Collections::Generic::List<User^>();
			this->networkThread->Start();
			this->generateGraphValues(1,1,1);
			this->refresh();
			this->updateOrCreateUser(this->username, this->money);
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

	private: System::String^ username;
	private: double money = 100;
	private: delegate void SafeMessageEventDelegate(System::String^ msg);
	private: System::Threading::Thread^ networkThread;
	private: NetworkClient^ networkClient;
	private: msclr::interop::marshal_context context;
	private: System::Collections::Generic::List<int>^ graphPoints;
	private: System::Windows::Forms::Button^ btnSell;
	private: System::Collections::Generic::List<User^>^ users;


	private: System::Windows::Forms::TextBox^ txtLogs;
	private: System::Windows::Forms::TextBox^ txtCmd;
	private: System::Windows::Forms::Button^ btnSendPacket;
	private: System::Windows::Forms::GroupBox^ groupBox1;
	private: System::Windows::Forms::Panel^ pnlGraph;
	private: System::Windows::Forms::Button^ btnNewGraph;
	private: System::Windows::Forms::Button^ btnDbgName;
	private: System::Windows::Forms::TextBox^ txtDbgUsername;
	private: System::Windows::Forms::Button^ btnDbgMoney;
	private: System::Windows::Forms::NumericUpDown^ nudDbgMoney;
	private: System::Windows::Forms::Timer^ timGraphTick;
	private: System::Windows::Forms::ListBox^ lstUsers;
	private: System::Windows::Forms::Label^ lblUsername;
	private: System::Windows::Forms::Label^ lblMoney;
	private: System::Windows::Forms::Button^ btnDbgFinish;
	private: System::ComponentModel::IContainer^ components;

		   /// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->btnSell = (gcnew System::Windows::Forms::Button());
			this->txtLogs = (gcnew System::Windows::Forms::TextBox());
			this->txtCmd = (gcnew System::Windows::Forms::TextBox());
			this->btnSendPacket = (gcnew System::Windows::Forms::Button());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->btnDbgName = (gcnew System::Windows::Forms::Button());
			this->txtDbgUsername = (gcnew System::Windows::Forms::TextBox());
			this->btnDbgMoney = (gcnew System::Windows::Forms::Button());
			this->nudDbgMoney = (gcnew System::Windows::Forms::NumericUpDown());
			this->pnlGraph = (gcnew System::Windows::Forms::Panel());
			this->btnNewGraph = (gcnew System::Windows::Forms::Button());
			this->timGraphTick = (gcnew System::Windows::Forms::Timer(this->components));
			this->lstUsers = (gcnew System::Windows::Forms::ListBox());
			this->lblUsername = (gcnew System::Windows::Forms::Label());
			this->lblMoney = (gcnew System::Windows::Forms::Label());
			this->btnDbgFinish = (gcnew System::Windows::Forms::Button());
			this->groupBox1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nudDbgMoney))->BeginInit();
			this->SuspendLayout();
			// 
			// btnSell
			// 
			this->btnSell->Location = System::Drawing::Point(287, 394);
			this->btnSell->Name = L"btnSell";
			this->btnSell->Size = System::Drawing::Size(75, 23);
			this->btnSell->TabIndex = 0;
			this->btnSell->Text = L"Sell";
			this->btnSell->UseVisualStyleBackColor = true;
			this->btnSell->Click += gcnew System::EventHandler(this, &GameForm::btnSell_Click);
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
			this->txtCmd->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &GameForm::txtCmd_KeyPress);
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
			this->groupBox1->Controls->Add(this->btnDbgFinish);
			this->groupBox1->Controls->Add(this->btnDbgName);
			this->groupBox1->Controls->Add(this->txtDbgUsername);
			this->groupBox1->Controls->Add(this->btnDbgMoney);
			this->groupBox1->Controls->Add(this->nudDbgMoney);
			this->groupBox1->Controls->Add(this->txtLogs);
			this->groupBox1->Controls->Add(this->txtCmd);
			this->groupBox1->Controls->Add(this->btnSendPacket);
			this->groupBox1->Location = System::Drawing::Point(13, 423);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(499, 146);
			this->groupBox1->TabIndex = 3;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Debug";
			// 
			// btnDbgName
			// 
			this->btnDbgName->Location = System::Drawing::Point(400, 47);
			this->btnDbgName->Name = L"btnDbgName";
			this->btnDbgName->Size = System::Drawing::Size(75, 23);
			this->btnDbgName->TabIndex = 6;
			this->btnDbgName->Text = L"Set Name";
			this->btnDbgName->UseVisualStyleBackColor = true;
			this->btnDbgName->Click += gcnew System::EventHandler(this, &GameForm::btnDbgName_Click);
			// 
			// txtDbgUsername
			// 
			this->txtDbgUsername->Location = System::Drawing::Point(274, 47);
			this->txtDbgUsername->Name = L"txtDbgUsername";
			this->txtDbgUsername->Size = System::Drawing::Size(120, 20);
			this->txtDbgUsername->TabIndex = 5;
			// 
			// btnDbgMoney
			// 
			this->btnDbgMoney->Location = System::Drawing::Point(400, 17);
			this->btnDbgMoney->Name = L"btnDbgMoney";
			this->btnDbgMoney->Size = System::Drawing::Size(75, 23);
			this->btnDbgMoney->TabIndex = 4;
			this->btnDbgMoney->Text = L"Set Money";
			this->btnDbgMoney->UseVisualStyleBackColor = true;
			this->btnDbgMoney->Click += gcnew System::EventHandler(this, &GameForm::btnDbgMoney_Click);
			// 
			// nudDbgMoney
			// 
			this->nudDbgMoney->Location = System::Drawing::Point(274, 20);
			this->nudDbgMoney->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1215752191, 23, 0, 0 });
			this->nudDbgMoney->Minimum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 999999999, 0, 0, System::Int32::MinValue });
			this->nudDbgMoney->Name = L"nudDbgMoney";
			this->nudDbgMoney->Size = System::Drawing::Size(120, 20);
			this->nudDbgMoney->TabIndex = 3;
			// 
			// pnlGraph
			// 
			this->pnlGraph->Location = System::Drawing::Point(13, 13);
			this->pnlGraph->Name = L"pnlGraph";
			this->pnlGraph->Size = System::Drawing::Size(655, 354);
			this->pnlGraph->TabIndex = 4;
			this->pnlGraph->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &GameForm::GameForm_OnPaintGraph);
			// 
			// btnNewGraph
			// 
			this->btnNewGraph->Location = System::Drawing::Point(593, 394);
			this->btnNewGraph->Name = L"btnNewGraph";
			this->btnNewGraph->Size = System::Drawing::Size(75, 23);
			this->btnNewGraph->TabIndex = 5;
			this->btnNewGraph->Text = L"New Data";
			this->btnNewGraph->UseVisualStyleBackColor = true;
			this->btnNewGraph->Click += gcnew System::EventHandler(this, &GameForm::btnNewGraph_Click);
			// 
			// lstUsers
			// 
			this->lstUsers->FormattingEnabled = true;
			this->lstUsers->Location = System::Drawing::Point(674, 68);
			this->lstUsers->Name = L"lstUsers";
			this->lstUsers->Size = System::Drawing::Size(153, 134);
			this->lstUsers->TabIndex = 6;
			// 
			// lblUsername
			// 
			this->lblUsername->AutoSize = true;
			this->lblUsername->Location = System::Drawing::Point(675, 25);
			this->lblUsername->Name = L"lblUsername";
			this->lblUsername->Size = System::Drawing::Size(67, 13);
			this->lblUsername->TabIndex = 7;
			this->lblUsername->Text = L"<Username>";
			// 
			// lblMoney
			// 
			this->lblMoney->AutoSize = true;
			this->lblMoney->Location = System::Drawing::Point(674, 42);
			this->lblMoney->Name = L"lblMoney";
			this->lblMoney->Size = System::Drawing::Size(51, 13);
			this->lblMoney->TabIndex = 8;
			this->lblMoney->Text = L"<Money>";
			// 
			// btnDbgFinish
			// 
			this->btnDbgFinish->Location = System::Drawing::Point(400, 76);
			this->btnDbgFinish->Name = L"btnDbgFinish";
			this->btnDbgFinish->Size = System::Drawing::Size(75, 23);
			this->btnDbgFinish->TabIndex = 9;
			this->btnDbgFinish->Text = L"Finish";
			this->btnDbgFinish->UseVisualStyleBackColor = true;
			this->btnDbgFinish->Click += gcnew System::EventHandler(this, &GameForm::btnDbgFinish_Click);
			// 
			// GameForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(839, 581);
			this->Controls->Add(this->lblMoney);
			this->Controls->Add(this->lblUsername);
			this->Controls->Add(this->lstUsers);
			this->Controls->Add(this->btnNewGraph);
			this->Controls->Add(this->pnlGraph);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->btnSell);
			this->Name = L"GameForm";
			this->Text = L"Game";
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &GameForm::GameForm_FormClosed);
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nudDbgMoney))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void btnSell_Click(System::Object^ sender, System::EventArgs^ e) {

	}

	private: System::Void btnFinish_Click(System::Object^ sender, System::EventArgs^ e) {
		executeCommand();
	}

	private: void executeCommand() {
		this->log(System::String::Format("Sent <{0}>", this->txtCmd->Text));
		networkClient->sendInfo(this->txtCmd->Text);
		this->txtCmd->Text = "";
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
		auto args = msg->Split();
		if (msg->Length > 5 && msg->Substring(0, 5) == "USER ") {
			this->updateOrCreateUser(args[1], System::Convert::ToDouble(args[2]));
		}
		if (msg->Length > 4 && msg->Substring(0, 5) == "KICK ") {
			this->kick(args[1]);
		}
	}

	private: System::Void updateOrCreateUser(System::String^ name, double money) {
		// update if exists
		for each (auto u in users) {
			if (u->username == name) {
				u->money = money;
				this->log(System::String::Format("Set <{0}> money to {1:C}", name, money));
				return;
			}
		}
		this->log(System::String::Format("Created user <{0}> with money {1:C}", name, money));
		User^ u = gcnew User(name, money);
		this->users->Add(u);
		rebuildPlayerList();
	}

	private: void rebuildPlayerList() {
		this->lstUsers->Items->Clear();
		for each (auto u in this->users) {
			if (u->username == this->username)
				continue;
			this->lstUsers->Items->Add(System::String::Format("<{0}> {1:C}", u->username, u->money));
		}
	}

	private: User^ getUser(System::String^ name) {
		for each (auto u in users)
			if (u->username == name)
				return u;
		return nullptr;
	}

	private: System::Boolean userExists(System::String^ name) {
		return this->getUser(name) == nullptr;
	}

	private: System::Void kick(System::String^ name) {
		User^ u;
		if (u = getUser(name)) {
			this->users->Remove(u);
			this->log(System::String::Format("Kicked <{0}>", name));
			return;
		}
		this->log(System::String::Format("Failed to kick <{0}>, doesn't exist", name));
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

	private: System::Void generateGraphValues(int randSeed, double ret, double volatility) {
		System::Random r(randSeed);
		this->graphPoints = gcnew System::Collections::Generic::List<int>();
		//
		//const int initValue = 1;
		//const double d = 0.002;
		//const double v = 0.01;

		//double stockQuote = initValue;
		//int crashChance = -10;
		//int deltaCrashChance = 0;

		//double drift = ret - (1 / 2) * (volatility * volatility);
		//double diffusion = 0;
		//double delta = 0;

		//std::default_random_engine generator;
		//std::normal_distribution<double> normalDistGen(0, 1);

		//int i = 0;
		//this->graphPoints->Add(1);

		//this->log(System::String::Format("Generating with seed {0}, ret {1}, vol {2}", randSeed, ret, volatility));
		//while (r.Next() % 10000 > (crashChance++ + deltaCrashChance) && i++ < 300) {
		//	deltaCrashChance = 0;
		//	stockQuote *= exp(5 * drift + diffusion);
		//	diffusion = (normalDistGen(generator) * volatility);
		//	this->graphPoints->Add(stockQuote);
		//	delta = (0.5 * delta) + this->graphPoints[i] - this->graphPoints[i - 1];

		//	if (delta < 0) {
		//		deltaCrashChance = delta * 10;
		//		//crashChance++;
		//	}
		//}
		double crashChance = 0.005;
		int x = 0;
		this->graphPoints->Add(1);
		for (int i = 0; i < 25 && r.NextDouble() > (crashChance*=1.1) ; i++) {
			int x = x + (int)(r.NextDouble() * 200) - 100;
			x = x < 0 ? 0 : x;
			this->graphPoints->Add(x);
		}
		this->pnlGraph->Refresh();
	}

	private: void refresh() {
		this->lblUsername->Text = this->username;
		this->lblMoney->Text = System::String::Format("{0:C}", this->money);
		this->Refresh();
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
		scale = area.Height/max;

		g->DrawLine(blackPen, 0, area.Height, area.Width, area.Height);
		int prevX = 0, prevY = area.Height -this->graphPoints[0] * scale;
		for each (int d in this->graphPoints) {
			int scaledY = area.Height-2 - (d * scale);
			g->DrawLine(redPen, prevX, prevY, prevX+step, scaledY);
			prevX += step;
			prevY = scaledY;
		}
	}
private: System::Void btnNewGraph_Click(System::Object^ sender, System::EventArgs^ e) {
	System::Random^ r = gcnew System::Random();
	this->generateGraphValues(r->Next(), r->Next(), r->NextDouble());
}
private: System::Void btnDbgMoney_Click(System::Object^ sender, System::EventArgs^ e) {
	this->money = System::Decimal::ToDouble(this->nudDbgMoney->Value);
	this->log(System::String::Format("Set money to {0:C}", this->money));
	this->refresh();
}
private: System::Void btnDbgName_Click(System::Object^ sender, System::EventArgs^ e) {
	this->username = this->txtDbgUsername->Text;
	this->log(System::String::Format("Set username to <{0}>", this->username));
	this->refresh();
}
private: System::Void txtCmd_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ kp) {
	//this->log(System::String::Format("pressed <{0}>, checking <{1}>", kp->KeyChar, Keys::Enter));
	if (kp->KeyChar == 13) {
		executeCommand();
	}
}
private: System::Void btnDbgFinish_Click(System::Object^ sender, System::EventArgs^ e) {
	this->networkClient->sendInfo(System::String::Format("FINISH {0}", this->username));
}
};
}

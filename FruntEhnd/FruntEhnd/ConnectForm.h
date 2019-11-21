#pragma once
#include <msclr/marshal.h>
#include <msclr\marshal_cppstd.h>
#include <string>
#include "GameForm.h"
#include "NetworkClient.h"
namespace FrontEnd {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Entrypoint
	/// </summary>
	public ref class ConnectForm : public System::Windows::Forms::Form
	{
	public:
		ConnectForm(void)
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
		~ConnectForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ btnJoin;
	protected:

	private: System::Windows::Forms::TextBox^ txtAddr;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::NumericUpDown^ nudPort;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Label^ label3;
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
			this->btnJoin = (gcnew System::Windows::Forms::Button());
			this->txtAddr = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->nudPort = (gcnew System::Windows::Forms::NumericUpDown());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nudPort))->BeginInit();
			this->SuspendLayout();
			// 
			// btnJoin
			// 
			this->btnJoin->Location = System::Drawing::Point(60, 99);
			this->btnJoin->Name = L"btnJoin";
			this->btnJoin->Size = System::Drawing::Size(75, 23);
			this->btnJoin->TabIndex = 0;
			this->btnJoin->Text = L"Join";
			this->btnJoin->UseVisualStyleBackColor = true;
			this->btnJoin->Click += gcnew System::EventHandler(this, &ConnectForm::btnJoin_Click);
			// 
			// txtAddr
			// 
			this->txtAddr->Location = System::Drawing::Point(98, 6);
			this->txtAddr->Name = L"txtAddr";
			this->txtAddr->Size = System::Drawing::Size(100, 20);
			this->txtAddr->TabIndex = 1;
			this->txtAddr->Text = L"127.0.0.1";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(79, 13);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Server Address";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(12, 33);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(60, 13);
			this->label2->TabIndex = 2;
			this->label2->Text = L"Server Port";
			// 
			// nudPort
			// 
			this->nudPort->Location = System::Drawing::Point(98, 33);
			this->nudPort->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10000, 0, 0, 0 });
			this->nudPort->Name = L"nudPort";
			this->nudPort->Size = System::Drawing::Size(100, 20);
			this->nudPort->TabIndex = 3;
			this->nudPort->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) { 2878, 0, 0, 0 });
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(98, 59);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(100, 20);
			this->textBox1->TabIndex = 1;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(12, 62);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(55, 13);
			this->label3->TabIndex = 2;
			this->label3->Text = L"Username";
			// 
			// ConnectForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(216, 133);
			this->Controls->Add(this->nudPort);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->txtAddr);
			this->Controls->Add(this->btnJoin);
			this->Name = L"ConnectForm";
			this->Text = L"Connect";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->nudPort))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
private: System::Void btnJoin_Click(System::Object^ sender, System::EventArgs^ e) {
	msclr::interop::marshal_context context;
	std::string rawAddr = context.marshal_as<std::string>(this->txtAddr->Text);
	std::string rawPort = context.marshal_as<std::string>(this->nudPort->Value.ToString());
	NetworkClient^ networkClient = gcnew NetworkClient();

	//todo: fail gracefully
	networkClient->start(rawAddr.c_str(), rawPort.c_str());
	if (!networkClient->isConnected()) {
		MessageBox::Show(System::String::Format("Failed to connect to {0}:{1}", this->txtAddr->Text, this->nudPort->Value), "Info", MessageBoxButtons::OK, MessageBoxIcon::Exclamation);
		return;
	}
	GameForm^ gameForm = gcnew GameForm(networkClient);
	gameForm->Show();
	this->Hide();
}
};
}

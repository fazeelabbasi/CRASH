#pragma once
ref class User {
public:
	System::String^ username;
	double money;
	User(System::String^ username, double money) : username(username), money(money) {};
};
#define WIN32_LEAN_AND_MEAN
#include "ConnectForm.h"

using namespace FrontEnd;
int main() {
	ConnectForm^ connectForm = gcnew ConnectForm();
	Application::Run(connectForm);
	return 0;
}
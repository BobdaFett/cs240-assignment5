#include "Form1.h"

using namespace System;
using namespace System::Threading;
using namespace System::Windows::Forms;
using namespace cs240assignment2;

int main(array<String^>^ argv) {
	Session^ consoleSession = gcnew Session();

	Thread^ console = gcnew Thread(gcnew ThreadStart(consoleSession, &Session::Console));
	console->Start();

	Application::EnableVisualStyles();
	Application::Run(gcnew Form1());

	

	return 0;
}
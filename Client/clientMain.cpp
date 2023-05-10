#include "Form1.h"

using namespace System;
using namespace System::Threading;
using namespace System::Windows::Forms;
using namespace System::Security::Cryptography;
using namespace cs240assignment5;

int main(array<String^>^ argv) {

	Application::EnableVisualStyles();
	Application::Run(gcnew Form1());

	return 0;
}
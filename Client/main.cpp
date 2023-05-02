#include "Form1.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace cs240assignment2;

int main(array<String^>^ argv) {
	Application::EnableVisualStyles();
	Application::Run(gcnew Form1());

	return 0;
}
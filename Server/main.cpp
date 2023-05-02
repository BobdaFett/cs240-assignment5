#include "Server.h"

using namespace System;

int main(array<String^>^ argv) {

	// Create the server object. This will also create the Bank and all other associated objects.
	Server^ server = gcnew Server();

	server->Start();

	return 0;
}

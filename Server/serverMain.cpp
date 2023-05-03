#include "Bank.h"

using namespace System;

int main(array<String^>^ argv) {

	// Create the server object. This will also create the Bank and all other associated objects.
	Bank^ theBank = gcnew Bank();

	theBank->Listen();  // only takes a single connection right now.

	return 0;
}

#pragma once

// Server includes
#include "BankInterface.h"

using namespace System;
using namespace System::Text;
using namespace System::IO;
using namespace System::Net;
using namespace System::Net::Sockets;

/// This will serve as our server object wrapper.
/// All of the data and functions required to run the server will be kept within this class.
ref class Bank : BankInterface {
private:
	array<CustomerRecord^>^ customers;
public:
	Bank();

	virtual Customer^ FindCustomer(int custNumber, int pin);
};

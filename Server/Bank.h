#pragma once

// Server includes
#include "BankData.h"

using namespace System;
using namespace System::Text;
using namespace System::IO;
using namespace System::Net;
using namespace System::Net::Sockets;

/// This will serve as our server object wrapper.
/// All of the data and functions required to run the server will be kept within this class.
ref class Bank {
private:
	BankData^ data;
	array<CustomerRecord^>^ customers;

	IPAddress^ ip;
	Socket^ listener;

public:
	Bank();

	Void Listen();
	
	

};

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
	Socket^ server;
	NetworkStream^ ns;
	BinaryReader^ reader;
	BinaryWriter^ writer;

public:
	Bank();

	Void Listen();
	
	/// Handles the GETACCOUNT command.
	Void GetAccount(Int32);

	/// Handles the GETCUSTOMER command.
	Void GetCustomer(Int32, Int32);

	/// Handles the SAVEBALANCE command.
	Void SaveBalance(Int32, Double);

};

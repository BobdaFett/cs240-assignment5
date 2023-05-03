#pragma once

#include "AccountRecord.h"
#include "CustomerRecord.h"
#include "BankData.h"

using namespace System;
using namespace System::IO;
using namespace System::Threading;
using namespace System::Net;
using namespace System::Net::Sockets;

ref class Service {
private:
	Socket^ server;
	NetworkStream^ ns;
	BinaryReader^ reader;
	BinaryWriter^ writer;

	BankData^ data;

public:
	Service(Socket^, BankData^);

	/// Main server loop.
	Void DoService();

	/// Handles the GETACCOUNT command.
	Void GetAccount(Int32);

	/// Handles the GETCUSTOMER command.
	Void GetCustomer(Int32, Int32);

	/// Handles the SAVEBALANCE command.
	Void SaveBalance(Int32, Double);
};


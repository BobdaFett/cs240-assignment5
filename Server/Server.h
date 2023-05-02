#pragma once

using namespace System;
using namespace System::IO;
using namespace System::Net;
using namespace System::Net::Sockets;
using namespace System::Runtime::Serialization::Formatters::Binary;

#include "Bank.h"

ref class Server {

private:
	IPAddress^ ip;
	Socket^ listener;

	// After connected
	Socket^ server;
	NetworkStream^ ns;
	BinaryReader^ reader;
	BinaryWriter^ writer;

	Bank^ bank;

public:
	Server();

	/// General server loop. Handles recieved commands and sending data.
	Void Start();

	template <class T> array<Byte>^ ToBytes(T object);
};


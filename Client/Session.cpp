#include "Session.h"
#include "BankAccount.h"

using namespace System;
using namespace System::IO;
using namespace System::Net;
using namespace System::Net::Sockets;

Session::Session() {
	// Create connection to server.
	port = 2345;
	ip = Dns::GetHostEntry("localhost")->AddressList[0];
	endpoint = gcnew IPEndPoint(ip, port);
	client = gcnew Socket(ip->AddressFamily, SocketType::Stream, ProtocolType::Tcp);
	client->Connect(endpoint);

	Console::WriteLine("Connected to server at {0}", ip);

	// Create stream read/write objects.
	ns = gcnew NetworkStream(client);
	reader = gcnew BinaryReader(ns);
	writer = gcnew BinaryWriter(ns);
}

BankAccount^ Session::CreateBankAccount(int accountNumber) {
	// Get information from the server and create a new BankAccount instance.
	// Create the message
	String^ message = "BANKACCOUNT " + accountNumber;

	// Send the message
	writer->Write(message);

	// Read the response and get data (accountNumber, balance)
	int accountNumber = reader->ReadInt32();
	double balance = reader->ReadDouble();

	// Create a new BankAccount object and return it.
	return gcnew BankAccount(accountNumber, balance);
}
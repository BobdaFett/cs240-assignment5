#include "Bank.h"
#include "Service.h"

using namespace System;
using namespace System::Threading;
using namespace System::Net;
using namespace System::Net::Sockets;

Bank::Bank() {
	BankData^ data = gcnew BankData();
	data->Init();
	this->customers = BankData::GetCustRecords();

	// Create and start server.
	int port = 2345;
	ip = Dns::GetHostEntry("localhost")->AddressList[0];
	IPEndPoint^ endpoint = gcnew IPEndPoint(ip, port);
	listener = gcnew Socket(ip->AddressFamily, SocketType::Stream, ProtocolType::Tcp);
	listener->Bind(endpoint);
}

Void Bank::Listen() {
	listener->Listen(1);
	Console::Write("Server is listening on {0}... ", ip);

	while (true) {
		Socket^ server = listener->Accept();
		Service^ service = gcnew Service(server, data);
		Thread^ t = gcnew Thread(gcnew ThreadStart(service, &Service::DoService));
		Console::WriteLine("New connection established.");
		t->Start();
	}
}
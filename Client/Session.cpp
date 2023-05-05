#include "Session.h"

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

Session::~Session() {
	// Disconnect and close connection
	client->Shutdown(SocketShutdown::Both);
	client->Close();
	ns->Close();
}

String^ Session::SendCommand(String^ command) {
	// Send command to the server
	writer->Write(command);

	// Perhaps check for received error here?
	array<String^>^ response = reader->ReadString()->Split(' ');
	if (response[0]->Contains("Error")) {
		// Do something.
	}

	// Return the response from the server for external processing.
	return reader->ReadString();
}

Void Session::Console() {
	String^ command = Console::ReadLine();

	SendCommand(command);
}
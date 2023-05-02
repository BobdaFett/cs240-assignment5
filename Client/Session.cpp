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
	// There's no check on if this is connected.
	// If this object got through the whole constructor without errors, then there's a good connection.

	// Send command to the server
	writer->Write(command);

	// Return the response from the server for external processing.
	return reader->ReadString();
}

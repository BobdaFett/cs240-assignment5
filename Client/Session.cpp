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

	// Initialize the cryptographic algorithm.
	rm = gcnew RijndaelManaged();
	rm->Key = gcnew array<unsigned char>{34, 248, 24, 253, 231, 95, 77, 74, 177, 8, 153, 114, 174, 152, 140, 58, 23, 188, 224, 240, 18, 92, 37, 21, 139, 86, 183, 234, 165, 152, 27, 249};
	rm->IV = gcnew array<unsigned char>{192, 208, 43, 85, 149, 250, 24, 194, 150, 88, 131, 71, 101, 35, 192, 229};
}

Session::~Session() {
	// Disconnect and close connection
	Console::Write("\nClosing connection... ");
	client->Shutdown(SocketShutdown::Both);
	client->Close();
	ns->Close();
	Console::WriteLine("Done.\n");
}

Void Session::SendCommand(String^ command) {
	// Create an encryptor object.
	ICryptoTransform^ encryptor = rm->CreateEncryptor();
	
	// Create a CryptoStream and StreamWriter in order to encrypt/write to the stream.
	CryptoStream^ cs = gcnew CryptoStream(ns, encryptor, CryptoStreamMode::Write);
	StreamWriter^ encryptedWriter = gcnew StreamWriter(cs);
	
	// Send the message through the stream - should automatically encrypt it.
	encryptedWriter->Write(command);
}

String^ Session::ReadCommand() {
	// Declare string to hold decrypted text.
	String^ response = nullptr;

	// Create a decryptor
	ICryptoTransform^ decryptor = rm->CreateDecryptor();

	// Create a CryptoStream and StreamReader in order to decrypt/read the stream
	CryptoStream^ cs = gcnew CryptoStream(ns, decryptor, CryptoStreamMode::Read);
	StreamReader^ decryptedReader = gcnew StreamReader(cs);

	// Read the message and place it into the string.
	response = decryptedReader->ReadToEnd();

	// Return the response for external processing.
	return response;
}

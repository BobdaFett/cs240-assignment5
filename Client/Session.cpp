#include "Session.h"

using namespace System;
using namespace System::Text;
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
	ns = gcnew NetworkStream(client);

	Console::WriteLine("Connected to server at {0}", ip);

	// Initialize the cryptographic algorithm.
	rm = gcnew RijndaelManaged();
	rm->Key = gcnew array<Byte>{34, 248, 24, 253, 231, 95, 77, 74, 177, 8, 153, 114, 174, 152, 140, 58, 23, 188, 224, 240, 18, 92, 37, 21, 139, 86, 183, 234, 165, 152, 27, 249};
	rm->IV = gcnew array<Byte>{192, 208, 43, 85, 149, 250, 24, 194, 150, 88, 131, 71, 101, 35, 192, 229};
}

Session::~Session() {
	// Disconnect and close connection
	Console::ForegroundColor = ConsoleColor::Yellow;
	Console::Write("\nClosing connection... ");
	client->Shutdown(SocketShutdown::Both);
	client->Close();
	Console::WriteLine("Done.\n");
	Console::ResetColor();
}

Void Session::SendCommand(String^ command) {
	// Get the digest of the message.
	SHA256Managed^ sha = gcnew SHA256Managed();
	UnicodeEncoding^ uni = gcnew UnicodeEncoding();
	array<Byte>^ digest = sha->ComputeHash(uni->GetBytes(command));
	Console::WriteLine("Got hash.");

	// Create an encryptor object.
	ICryptoTransform^ encryptor = rm->CreateEncryptor(rm->Key, rm->IV);
	
	// Create a CryptoStream and StreamWriter in order to encrypt/write to the stream.
	CryptoStream^ writeStream = gcnew CryptoStream(ns, encryptor, CryptoStreamMode::Write);
	BinaryWriter^ encryptedWriter = gcnew BinaryWriter(writeStream);

	/*CryptoStream^ readStream = gcnew CryptoStream(ns, rm->CreateDecryptor(), CryptoStreamMode::Read);
	BinaryReader^ decryptedReader = gcnew BinaryReader(readStream);*/

	// Send the message through the stream - should automatically encrypt it.
	// This worked with a simple binary Write and ReadString. Now it doesn't?
	encryptedWriter->Write(command);
	Console::WriteLine("Sent command.");
	//if (decryptedReader->ReadString() != "ACK") throw gcnew IOException("ACK failure.");

	//// Send the length of the digest through the stream.
	//encryptedWriter->Write(digest->Length);
	//Console::WriteLine("Sent digest length.");
	//if (decryptedReader->ReadString() != "ACK") throw gcnew IOException("ACK failure.");

	//// Send the digest through the stream - should automatically encrypt it.
	//encryptedWriter->Write(digest);
	//Console::WriteLine("Sent digest.");
	//if (decryptedReader->ReadString() != "ACK") throw gcnew IOException("ACK failure.");

	Console::WriteLine(command);
}

String^ Session::ReadCommand() {
	// Declare string to hold decrypted text and array to hold digest.
	String^ response = nullptr;
	array<Byte>^ digest = nullptr;

	// Create a decryptor
	ICryptoTransform^ decryptor = rm->CreateDecryptor(rm->Key, rm->IV);

	// Create a CryptoStream and StreamReader in order to decrypt/read the stream
	CryptoStream^ cs = gcnew CryptoStream(ns, decryptor, CryptoStreamMode::Read);
	BinaryReader^ decryptedReader = gcnew BinaryReader(cs);

	// Read the message and place it into the string.
	response = decryptedReader->ReadString();

	//// Get the length of the digest.
	//Int32 digestLength = decryptedReader->ReadInt32();

	//// Read the digest and place it into a new byte array.
	//digest = decryptedReader->ReadBytes(digestLength);
	//
	//// Ensure that the received message and received digest match.
	//UnicodeEncoding^ uni = gcnew UnicodeEncoding();
	//SHA256Managed^ sha = gcnew SHA256Managed();
	//array<Byte>^ hashedResponse = sha->ComputeHash(uni->GetBytes(response));

	//if (hashedResponse == digest) {
	//	// Return response for external processing.
	//	Console::WriteLine("Read: {0}", response);
	//	return response;
	//}

	//// throw an IOException and ignore the command.
	//PrintError("Corrupted packet detected.");
	//throw gcnew IOException("Corrupted packet detected.");

	return response;
	
}

Void Session::PrintError(String^ message) {
	Console::ForegroundColor = ConsoleColor::Red;
	Console::WriteLine(message);
	Console::ResetColor();
}

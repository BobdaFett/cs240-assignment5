#include "Server.h"

Server::Server() {
	// Initialize server object and create basic Bank object.
	int port = 2345;
	ip = Dns::GetHostEntry("localhost")->AddressList[0];
	IPEndPoint^ endpoint = gcnew IPEndPoint(ip, port);
	listener = gcnew Socket(ip->AddressFamily, SocketType::Stream, ProtocolType::Tcp);
	listener->Bind(endpoint);

	bank = gcnew Bank();
}

Void Server::Start() {
	listener->Listen(2);
	Console::Write("Server is listening on {0}... ", ip);

	server = listener->Accept();  // Accept one connection from the listener.
	listener->Close();
	Console::WriteLine("Connection established.");
	
	ns = gcnew NetworkStream(server);
	reader = gcnew BinaryReader(ns);
	writer = gcnew BinaryWriter(ns);

	try {
		array<String^>^ command;

		while (true) {
			// Get the command from the client.
			command = reader->ReadString()->Split(' ');
			if (command[0] == "Bank::FindCustomer") {
				// Get parameters
				int custNumber = Int32::Parse(command[1]);
				int pin = Int32::Parse(command[2]);

				// Call function
				Customer^ response = bank->FindCustomer(custNumber, pin);

				// Send response
				writer->Write(ToBytes(response));
			}
			else if (command[0] == "BankData::Init") {
				
			}
		}
	}
	catch (EndOfStreamException^) {
		Console::WriteLine("\n\nClient dropped the connection.");
	}
	catch (IOException^ e) {
		Console::WriteLine("An error has occurred:\n{0}", e);
	}
	finally {
		Console::Write("Closing connection... ");
		server->Shutdown(SocketShutdown::Both);
		server->Close();
		ns->Close();
		Console::WriteLine("Done.");
	}
}

template <class T> array<Byte>^ Server::ToBytes(T object) {
	MemoryStream^ ms = gcnew MemoryStream();
	BinaryFormatter^ fm = gcnew BinaryFormatter();
	fm->Serialize(ms, object);
	ms->Seek(0, SeekOrigin::Begin);
	return ms->ToArray();
}

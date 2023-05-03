#include "Bank.h"

using namespace System;
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
			if (command[0] == "GETCUSTOMER") {
				if (command->Length == 3) {
					// Get params
					Int32 custNumber = Int32::Parse(command[1]);
					Int32 pin = Int32::Parse(command[2]);

					// Run proper command
					GetCustomer(custNumber, pin);
				}
			}
			else if (command[0] == "GETACCOUNT") {
				if (command->Length == 2) {
					// Get params
					Int32 accountNumber = Int32::Parse(command[1]);

					// Run proper command
					GetAccount(accountNumber);
				}
			}
			else if (command[0] == "SAVEBALANCE") {
				if (command->Length == 3) {
					// Get params
					Int32 accountNumber = Int32::Parse(command[1]);
					Double newBalance = Double::Parse(command[2]);

					// Run proper command
					SaveBalance(accountNumber, newBalance);
				}
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
		Console::Write("\n\nPress any key to exit...");
		Console::ReadKey();
	}
}

Void Bank::GetAccount(Int32 accountNumber) {
	String^ response = data->GetBalance(accountNumber).ToString();

	Console::WriteLine("Sent response: " + response);
	writer->Write(response);
}

Void Bank::SaveBalance(Int32 accountNumber, Double newBalance) {
	AccountRecord^ temp = data->GetAccount(accountNumber);
	if (temp != nullptr) {
		temp->SetBalance(newBalance);
		String^ response = temp->GetBalance().ToString();

		Console::WriteLine("Sent response: " + response);
		writer->Write(response);
	}
	else {
		Console::WriteLine("Account not found.");
	}
}

Void Bank::GetCustomer(Int32 custNumber, Int32 pin) {
	// This will be a very slow search, but I don't think we're worried about that in this case.
	CustomerRecord^ cust = data->GetCustomer(custNumber);
	if (cust != nullptr) {
		if (cust->GetPin() == pin) {
			Console::WriteLine("Customer found!");

			// Get checking/savings numbers from the CustomerRecord.
			Int32 checkingNumber = cust->GetCheckingNumber();
			Int32 savingsNumber = cust->GetSavingsNumber();

			// Create response
			String^ response = checkingNumber + " " + savingsNumber;

			// Write response to stream
			Console::WriteLine("Sent response: " + response);
			writer->Write(response);
		}
		else {
			writer->Write("Incorrect pin.");
			Console::WriteLine("An incorrent pin was entered for customer {0}.", custNumber);
		}
	}
	else {
		writer->Write("Customer not found.");
		Console::WriteLine("Customer {0} not found.", custNumber);
	}
}

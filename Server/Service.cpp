#include "Service.h"

const Int32 SERVER_TIMEOUT = 2000;  // I think that 2 seconds is fairly reasonable. Especially since my program sends everything all at once.

using namespace System::Diagnostics;

Service::Service(Socket^ socket, BankData^ data) {
	this->server = socket;
	this->data = data;

	ns = gcnew NetworkStream(server);
	reader = gcnew BinaryReader(ns);
	writer = gcnew BinaryWriter(ns);
}

Void Service::DoService() {
	try {
		array<String^>^ command{};

		while (true) {
			// Get the command from the client.
			command = reader->ReadString()->Split(' ');
			if (command[0] == "GETCUSTOMER") {
				Int32 custNumber, pin;
				if (command->Length == 3) {  // check that all parameters are present.
					// Ensure that all parameters are the correct type.
					if (!Int32::TryParse(command[1], custNumber) || !Int32::TryParse(command[2], pin)) {
						Console::WriteLine("Received wrong parameter type - {0} is not a number.", command[2]);
						writer->Write("Error: Incorrect parameters on command GETCUSTOMER - needs to be (int, int)");
						continue;
					}

					// Run proper command
					GetCustomer(custNumber, pin);
				}
				else {
					// Allow about 2 seconds for fractured data.
					Stopwatch^ timeout = gcnew Stopwatch();
					timeout->Start();

					while (true) {
						// Try to check the stream for new data, assuming that timeout hasn't happened.
						if (timeout->ElapsedMilliseconds != SERVER_TIMEOUT) {
							if (ns->DataAvailable) {
								// Copy stream so that the command, if it's an error, doesn't disappear from reading.
								MemoryStream^ ms = gcnew MemoryStream();
								ns->CopyTo(ms);
								BinaryReader^ tempReader = gcnew BinaryReader(ms);

								// Validate that this data is new parameters.
								String^ newMessage = tempReader->ReadString();
								array<String^>^ newCommand = newMessage->Split(' ');
								if (newCommand->Length != 2) throw gcnew IOException("Incorrect number of parameters.");
								if (!Int32::TryParse(command[0], custNumber) || !Int32::TryParse(command[1], pin)) throw gcnew IOException("Parameter types were incorrect.");

								GetCustomer(custNumber, pin);
							}
						}
						else throw gcnew TimeoutException();
					}
				}

				//else {  // Wait for the parameters of the command. This will not support different amounts of time for different numbers of missing params.
				//	Thread::Sleep(1000);  // waits a full second before continuing.

				//	// Check length of stream.
				//	if (ns->Length > 0) {
				//		// Attempt to read the stream again
				//		array<String^>^ params = reader->ReadString()->Split(' ');

				//		Int32 custNumber, pin;

				//		if (!Int32::TryParse(params[0], custNumber) || !Int32::TryParse(command[1], pin)) {
				//			Console::WriteLine("Received wrong parameter type.");
				//			writer->Write("Error: Incorrect parameters on command GETCUSTOMER - needs to be (int, int)");
				//			continue;
				//		}

				//		GetCustomer(custNumber, pin);
				//	}
				//	else {
				//		// Error. Abort attempting to create this command.
				//		Console::WriteLine("Command incomplete.");
				//		writer->Write("Error: Command incomplete.");
				//	}
				//}
			}
			else if (command[0] == "GETACCOUNT") {  // check that all parameters are present.
				if (command->Length == 2) {
					// Get params
					Int32 accountNumber{};

					// Ensure that all parameters are the correct type.
					if (!Int32::TryParse(command[1], accountNumber)) {
						Console::WriteLine("Received wrong parameter type.");
						writer->Write("Error: Incorrect parameters on command GETACCOUNT - needs to be (int)");
						continue;
					}

					// Run proper command
					GetAccount(accountNumber);
				}
				else {  // Wait for the parameters of the command. This will not support different amounts of time for different numbers of missing params.
					Thread::Sleep(1000);  // waits a full second before continuing.

					// Check length of stream.
					if (ns->Length > 0) {
						// Attempt to read the stream again
						array<String^>^ params = reader->ReadString()->Split(' ');

						Int32 accountNumber;

						if (!Int32::TryParse(params[0], accountNumber)) {
							Console::WriteLine("Received wrong parameter type.");
							writer->Write("Error: Incorrect parameters on command GETACCOUNT - needs to be (int)");
							continue;
						}

						GetAccount(accountNumber);
					}
					else {
						// Error. Abort attempting to create this command.
						Console::WriteLine("Command incomplete.");
						writer->Write("Error: Command incomplete.");
					}
				}
			}
			else if (command[0] == "SAVEBALANCE") {  // check that all parameters are present.
				if (command->Length == 3) {
					// Get params
					Int32 accountNumber{};
					Double newBalance{};

					// Ensure that all parameters are the correct type.
					if (!Double::TryParse(command[2], newBalance) || !Int32::TryParse(command[1], accountNumber)) {
						Console::WriteLine("Received wrong parameter type.");
						writer->Write("Error: Incorrect parameters on command SAVEBALANCE - needs to be (int, double)");
						continue;
					}

					// Run proper command
					SaveBalance(accountNumber, newBalance);
				}
				else {  // Wait for the parameters of the command. This will not support different amounts of time for different numbers of missing params.
					Thread::Sleep(1000);  // waits a full second before continuing.

					// Check length of stream.
					if (ns->Length > 0) {
						// Attempt to read the stream again.
						array<String^>^ params = reader->ReadString()->Split(' ');

						Int32 accountNumber{};
						Double newBalance{};

						if (!Double::TryParse(command[2], newBalance) || !Int32::TryParse(command[1], accountNumber)) {
							Console::WriteLine("Received wrong parameter type.");
							writer->Write("Error: Incorrect parameters on command SAVEBALANCE - needs to be (int, double)");
						}

						SaveBalance(accountNumber, newBalance);
					}
					else {
						// Error. Abort attempting to create this command.
						Console::WriteLine("Command incomplete.");
						writer->Write("Error: Command incomplete.");
					}
				}
			}
			else {
				Console::WriteLine("Command {0} not found.", command[0]);
				writer->Write("Error: Command " + command[0] + " not found.");
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
		Console::WriteLine("Done.\n");
	}
}

Void Service::GetAccount(Int32 accountNumber) {
	AccountRecord^ temp = data->GetAccount(accountNumber);
	if (temp != nullptr) {
		String^ response = temp->GetBalance().ToString();

		Console::WriteLine("Sent response: " + response);
		writer->Write(response);
	}
	else {
		Console::WriteLine("Account was not found.");
		writer->Write("Error: Account not found.");
	}
}

Void Service::GetCustomer(Int32 custNumber, Int32 pin) {
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
		writer->Write("Error: Customer not found.");
		Console::WriteLine("Customer {0} not found.", custNumber);
	}
}

Void Service::SaveBalance(Int32 accountNumber, Double newBalance) {
	AccountRecord^ temp = data->GetAccount(accountNumber);
	if (temp != nullptr) {
		temp->SetBalance(newBalance);
		String^ response = temp->GetBalance().ToString();

		Console::WriteLine("Sent response: " + response);
		writer->Write(response);
	}
	else {
		Console::WriteLine("Error: Account not found.");
		writer->Write("Error: Account not found.");
	}
}
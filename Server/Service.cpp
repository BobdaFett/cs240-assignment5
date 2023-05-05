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

		try {
			while (true) {
				// Get the command from the client.
				command = reader->ReadString()->Split(' ');
				if (command[0] == "GETCUSTOMER") {
					Int32 custNumber, pin;
					if (command->Length == 3) {  // check that all parameters are present.
						// Ensure that all parameters are the correct type.
						if (!Int32::TryParse(command[1], custNumber) || !Int32::TryParse(command[2], pin)) {
							throw gcnew IOException("Error: Wrong parameter types for GETCUSTOMER. Required types: (int, int)");
							continue;
						}

						// Run proper command
						GetCustomer(custNumber, pin);
					}
					else {  // Command length does not have proper parameters.
						// Allow about 2 seconds for fractured data.
						Console::Write("Waiting for extra information... ");
						writer->Write("Server: partial data received.");

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

									Console::WriteLine("Received data.");

									// Validate that this data is new parameters.
									String^ newMessage = tempReader->ReadString();
									array<String^>^ newCommand = newMessage->Split(' ');

									// Check for errors.
									if (newCommand->Length != 2) throw gcnew IOException("Error: Incorrect number of parameters.");
									if (!Int32::TryParse(command[0], custNumber) || !Int32::TryParse(command[1], pin)) throw gcnew IOException("Error: Parameter types were incorrect.");

									// Actually read the stream if this is functional - removes the command from the stream to prevent duplicate commands.
									newMessage = reader->ReadString();  // This can be a discarded value.

									// Execute command.
									GetCustomer(custNumber, pin);
								}
							}
							else throw gcnew TimeoutException();
						}
					}
				}
				else if (command[0] == "GETACCOUNT") {  // check that all parameters are present.
					Int32 accountNumber;
					if (command->Length == 2) {
						// Ensure that all parameters are the correct type.
						if (!Int32::TryParse(command[1], accountNumber)) {
							throw gcnew IOException("Error: Wrong parameter type for GETACCOUNT. Required types: (int)");
							continue;
						}

						// Run proper command
						GetAccount(accountNumber);
					}
					else {  // Command length does not have proper parameters.
						// Allow about 2 seconds for fractured data.
						Console::Write("Waiting for extra information... ");
						writer->Write("Server: partial data received.");

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

									Console::WriteLine("Received data.");

									// Validate that this data is new parameters.
									String^ newMessage = tempReader->ReadString();
									array<String^>^ newCommand = newMessage->Split(' ');

									// Check for errors.
									if (newCommand->Length != 2) throw gcnew IOException("Error: Incorrect number of parameters.");
									if (!Int32::TryParse(command[0], accountNumber)) throw gcnew IOException("Error: Parameter types were incorrect.");

									// Actually read the stream if this is functional - removes the command from the stream to prevent duplicate commands.
									newMessage = reader->ReadString();  // This can be a discarded value.

									// Excute command.
									GetAccount(accountNumber);
								}
							}
							else throw gcnew TimeoutException();
						}
					}
				}
				else if (command[0] == "SAVEBALANCE") {  // check that all parameters are present.
					Int32 accountNumber;
					Double newBalance;
					if (command->Length == 3) {
						// Ensure that all parameters are the correct type.
						if (!Double::TryParse(command[2], newBalance) || !Int32::TryParse(command[1], accountNumber)) {
							throw gcnew IOException("Error: Wrong parameter types for SAVEBALANCE. Required types: (int, double)");
							continue;
						}

						// Run proper command
						SaveBalance(accountNumber, newBalance);
					}
					else {  // Command length does not have proper parameters.
						// Allow about 2 seconds for fractured data.
						Console::Write("Waiting for extra information... ");
						writer->Write("Server: partial data received.");

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

									Console::WriteLine("Received data.");

									// Validate that this data is new parameters.
									String^ newMessage = tempReader->ReadString();
									array<String^>^ newCommand = newMessage->Split(' ');

									// Check for errors.
									if (newCommand->Length != 2) throw gcnew IOException("Error: Incorrect number of parameters.");
									if (!Int32::TryParse(command[0], accountNumber) || !Double::TryParse(command[1], newBalance)) throw gcnew IOException("Error: Parameter types were incorrect.");

									// Actually read the stream if this is functional - removes the command from the stream to prevent duplicate commands.
									newMessage = reader->ReadString();  // This can be a discarded value.

									// Execute command.
									SaveBalance(accountNumber, newBalance);
								}
							}
							else throw gcnew TimeoutException();
						}
					}
				}
				else {
					throw gcnew IOException("Error: Command was not found.");
				}
			}
		}
		catch (IOException^ e) {
			Console::WriteLine(e);
			writer->Write(e->ToString());
		}
		catch (TimeoutException^ e) {
			Console::WriteLine(e);
			writer->Write(e->ToString());
		}
	}
	catch (EndOfStreamException^) {
		Console::WriteLine("\n\nClient dropped the connection.");
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
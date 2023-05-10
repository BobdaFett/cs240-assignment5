#include "BankAccount.h"

using namespace System;

// TODO Add timeout check and handling to BankAccount constructor.
BankAccount::BankAccount(Int32 accountNumber, Session^ session) : accountNumber(accountNumber), session(session) {
	// Get information from the server.
	session->SendCommand("GETACCOUNT " + accountNumber);
	String^ response = session->ReadCommand();

	// Process the response string
	array<String^>^ responseData = response->Split(' ');
	// Check for an error from the server.
	if (responseData[0]->Contains("Error") || responseData[0]->Contains("Server")) {
		Console::WriteLine(response);
		throw gcnew AccountCreationException(response);
	}

	if (!Double::TryParse(responseData[0], balance)) {
		throw gcnew AccountCreationException("Faulty data received from server.");
	}
}

// TODO Add timeout check and handling to StoreBalance method.
Void BankAccount::StoreBalance() {
	// Send the command to the server.
	session->SendCommand("SAVEBALANCE " + accountNumber + " " + balance);
	String^ response = session->ReadCommand();

	// Get the new balance and check it against the current balance.
	array<String^>^ responseData = response->Split(' ');
	if (responseData[0] == "Error:") {
		Console::WriteLine(response);
		throw gcnew AccountSaveException("Information was not saved.");
	}

	Double serverBalance;

	if (!Double::TryParse(responseData[0], serverBalance) || serverBalance != balance) {
		Console::WriteLine("An error occurred.");
		throw gcnew AccountSaveException("Communication error while saving.");
	}
	else {
		Console::WriteLine("Balance saved successfully.");
	}
}

Void BankAccount::Deposit(Double amount) {
	this->balance += amount;
}

Void BankAccount::Withdraw(Double amount) {
	this->balance -= amount;
}

Double BankAccount::GetBalance() {
	return this->balance;
}

Int32 BankAccount::GetNumber() {
	return this->accountNumber;
}

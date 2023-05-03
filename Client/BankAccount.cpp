#include "BankAccount.h"

using namespace System;

BankAccount::BankAccount(Int32 accountNumber, Session^ session) : accountNumber(accountNumber), session(session) {
	// Get information from the server.
	String^ response = session->SendCommand("GETACCOUNT " + accountNumber);
	
	// Process the response string
	array<String^>^ responseData = response->Split(' ');
	if (responseData[0] == "Error:") {
		Console::WriteLine(response);
		balance = 0;
	}
	
	if (!Double::TryParse(responseData[0], balance)) {
		Console::WriteLine("Faulty data received from server. Setting to default value...");
		balance = 0;
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

Boolean BankAccount::StoreBalance() {
	// Send a command to the server.
	String^ response = session->SendCommand("SAVEBALANCE " + accountNumber + " " + balance);

	// Get the new balance and check it against the current balance.
	array<String^>^ responseData = response->Split(' ');
	if (responseData[0] == "Error:") {
		Console::WriteLine(response);
		return false;
	}

	Double serverBalance;

	if (!Double::TryParse(responseData[0], serverBalance) || serverBalance != balance) {
		Console::WriteLine("An error occurred.");
		return false;
	} 
	else {
		Console::WriteLine("Balance saved successfully.");
	}
}
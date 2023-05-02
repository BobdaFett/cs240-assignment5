#include "BankAccount.h"

using namespace System;

BankAccount::BankAccount(Int32 accountNumber, Session^ session) : accountNumber(accountNumber), session(session) {
	// Get information from the server.
	String^ response = session->SendCommand("GETACCOUNT");
	
	// Process the response string
	array<String^>^ responseData = response->Split(' ');
	// TODO Replace this with Double::TryParse
	balance = Double::Parse(responseData[0]);
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

Void BankAccount::StoreBalance() {
	// Send a command to the server.
	String^ response = session->SendCommand("SAVEBALANCE " + accountNumber + " " + balance);

	// Get the new balance and check it against the current balance.
	array<String^>^ responseData = response->Split(' ');
	double serverBalance = Double::Parse(responseData[0]);

	if (serverBalance = balance) {
		Console::WriteLine("Balance saved successfully.");
	}
	else {
		Console::WriteLine("Error while attempting to save balance.");
		Console::WriteLine("Current balance in object: {0}\nBalance returned from server: {1}", this->balance, serverBalance);
	}
}
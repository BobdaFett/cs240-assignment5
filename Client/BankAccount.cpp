#include "BankAccount.h"

using namespace System;

BankAccount::BankAccount(int accountNumber, Session^ session) : accountNumber(accountNumber), session(session) {
	// Get information from the server.
	String^ response = session->SendCommand("GETACCOUNT");
	
	// Process the response string
	array<String^>^ responseData = response->Split(' ');
	// TODO Replace this with Double::TryParse
	balance = Double::Parse(responseData[0]);
}

void BankAccount::Deposit(double amount) {
	this->balance += amount;
}

void BankAccount::Withdraw(double amount) {
	this->balance -= amount;
}

double BankAccount::GetBalance() {
	return this->balance;
}

int BankAccount::GetNumber() {
	return this->accountNumber;
}

void BankAccount::StoreBalance() {
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
#include "Customer.h"

using namespace System;

Customer::Customer(int customerNumber, int pin, Session^ session) : customerNumber(customerNumber), session(session) {
	// Get information from the server
	String^ response = session->SendCommand("CUSTOMER " + customerNumber + " " + pin);
	// Process the response from the server.
	array<String^>^ responseData = response->Split(' ');
	// TODO Replace with Int32::TryParse
	int checkingNumber = Int32::Parse(responseData[0]);
	int savingsNumber = Int32::Parse(responseData[1]);

	// Initialize new BankAccount instances.
	checkingAccount = gcnew BankAccount(checkingNumber, session);
	savingsAccount = gcnew BankAccount(savingsNumber, session);
}

BankAccount^ Customer::GetCheckingAccount() {
	return this->checkingAccount;
}

BankAccount^ Customer::GetSavingsAccount() {
	return this->savingsAccount;
}
#include "Customer.h"

using namespace System;

// TODO Add timeout check and handling to Customer constructor.
Customer::Customer(int customerNumber, int pin, Session^ session) : customerNumber(customerNumber), session(session) {
	// Get information from the server
	String^ response = session->SendCommand("GETCUSTOMER " + customerNumber + " " + pin);
	// Process the response from the server.
	array<String^>^ responseData = response->Split(' ');
	// Check that this isn't an error from the server.
	if (responseData[0]->Contains("Error")) {
		// Throw an exception.
		throw gcnew CustomerCreationException("Customer number/pin was incorrect.");  // Error: Customer not found.
	}
	else {
		Int32 checkingNumber, savingsNumber;
		if (!Int32::TryParse(responseData[0], checkingNumber) || !Int32::TryParse(responseData[1], savingsNumber)) {
			// Error.
			Console::WriteLine("Couldn't find customer.");
			throw gcnew CustomerCreationException("Customer number/pin was incorrect.");
		}
		else {
			// Initialize new BankAccount instances.
			checkingAccount = gcnew BankAccount(checkingNumber, session);
			savingsAccount = gcnew BankAccount(savingsNumber, session);
		}
	}
}

BankAccount^ Customer::GetCheckingAccount() {
	return this->checkingAccount;
}

BankAccount^ Customer::GetSavingsAccount() {
	return this->savingsAccount;
}

Int32 Customer::GetNumber() {
	return this->customerNumber;
}
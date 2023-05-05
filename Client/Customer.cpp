#include "Customer.h"

using namespace System;

Customer::Customer(int customerNumber, int pin, Session^ session) : customerNumber(customerNumber), session(session) {
	// Get information from the server
	String^ response = session->SendCommand("GETCUSTOMER " + customerNumber + " " + pin);
	// Process the response from the server.
	array<String^>^ responseData = response->Split(' ');
	// Check that this isn't an error from the server.
	if (responseData[0] == "Error:") {
		// Throw an exception.
		throw gcnew CustomerCreationException(response);
	}
	else {
		Int32 checkingNumber, savingsNumber;
		if (!Int32::TryParse(responseData[0], checkingNumber) || !Int32::TryParse(responseData[1], savingsNumber)) {
			// Error.
			Console::WriteLine("Error: Server sent faulty information.");
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
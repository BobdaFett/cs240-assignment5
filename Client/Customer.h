#pragma once

#ifndef CUSTOMER

#include "BankAccount.h"

using namespace System;

ref class Customer {
private:
	int customerNumber;
	Session^ session;
	BankAccount^ checkingAccount;
	BankAccount^ savingsAccount;

public:

	/// A modification of the original constructor, but instead of a BankData object, this holds a Session reference.
	/// Needed to add a pin parameter due to the fact that we require the pin to use Bank::FindCustomer()
	/// Command: GETCUSTOMER int custNumber int pin
	/// Response: int checkingNumber int savingsNumber
	Customer(int customerNumber, int pin, Session^ session);

	/// \returns The savings account BankAccount that's associated with this object.
	BankAccount^ GetSavingsAccount();

	/// \returns The checking account BankAccount that's associated with this object.
	BankAccount^ GetCheckingAccount();

};

#endif // CUSTOMER
#pragma once

#ifndef CUSTOMER_H

#include "BankAccount.h"
#include "Session.h"

using namespace System;

ref class Customer {
private:
	int customerNumber;
	Session^ session;
	BankAccount^ checkingAccount;
	BankAccount^ savingsAccount;

public:

	/// Should get the data from the server. Needs to have something that will send/receive information from the server.
	/// Usually has a second parameter that directs this object to the BankData, however the server gives that information in this case.
	Customer(int customerNumber);

	/// A modification of the original constructor, but instead of a BankData object, this holds a Session reference.
	/// Needed to add a pin parameter due to the fact that we require the pin to use Bank::FindCustomer()
	Customer(int customerNumber, int pin, Session^ session);

	/// \returns The savings account BankAccount that's associated with this object.
	BankAccount^ GetSavingsAccount();

	/// \returns The checking account BankAccount that's associated with this object.
	BankAccount^ GetCheckingAccount();

};

#endif

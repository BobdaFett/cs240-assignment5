#pragma once

#include "BankAccount.h"

#ifndef CUSTOMER_H

using namespace System;

ref class Customer {
private:
	int customerNumber;
	BankAccount^ checkingAccount;
	BankAccount^ savingsAccount;

public:

	/// Should get the data from the server. Needs to have something that will send/receive information from the server.
	/// Usually has a second parameter that directs this object to the BankData, however the server gives that information in this case.
	Customer(int customerNumber);

	/// \returns The savings account BankAccount that's associated with this object.
	BankAccount^ GetSavingsAccount();

	/// \returns The checking account BankAccount that's associated with this object.
	BankAccount^ GetCheckingAccount();

};

#endif

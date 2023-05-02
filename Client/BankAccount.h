#pragma once

#ifndef BANKACCOUNT

#include "Session.h"

using namespace System;

ref class BankAccount {
private:
	Int32 accountNumber;
	Double balance;
	Session^ session;
	// BankData^ data  <-- Would be used in the original, instead we're going to function without it.
	// Perhaps reference the client, for use in calling a "send" function.

public:

	/// A modified version of the original constructor, adding a Session reference to get information from the server.
	BankAccount(Int32 accountNumber, Session^ session);

	/// Adds an amount of money to this BankAccount object.
	Void Deposit(Double amount);

	/// Removes an amount of money from this BankAccount object.
	Void Withdraw(Double amount);

	/// \returns The amount of money in this BankAccount object.
	Double GetBalance();

	/// \returns The account number of this BankAccount object.
	Int32 GetNumber();

	/// Sends the current data to the server for processing into the BankData.
	Void StoreBalance();

};

#endif // BANKACCOUNT
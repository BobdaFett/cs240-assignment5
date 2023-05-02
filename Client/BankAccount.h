#pragma once

#ifndef BANKACCOUNT_H

#include "Session.h"

using namespace System;

ref class BankAccount {
private:
	int accountNumber;
	double balance;
	Session^ session;
	// BankData^ data  <-- Would be used in the original, instead we're going to function without it.
	// Perhaps reference the client, for use in calling a "send" function.

public:

	/// A modified version of the original constructor, adding a Session reference to get information from the server.
	BankAccount(int accountNumber, Session^ session);

	/// Adds an amount of money to this BankAccount object.
	void Deposit(double amount);

	/// Removes an amount of money from this BankAccount object.
	void Withdraw(double amount);

	/// \returns The amount of money in this BankAccount object.
	double GetBalance();

	/// \returns The account number of this BankAccount object.
	int GetNumber();

	/// Sends the current data to the server for processing into the BankData.
	void StoreBalance();

};

#endif

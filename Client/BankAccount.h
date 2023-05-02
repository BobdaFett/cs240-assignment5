#pragma once

#ifndef BANKACCOUNT_H

using namespace System;

ref class BankAccount {
private:
	int accountNumber;
	double balance;
	// BankData^ data  <-- Would be used in the original, instead we're going to function without it.
	// Perhaps reference the client, for use in calling a "send" function.

public:

	/// Should get the data from the server. Needs to have something that will send/recieve information from said server.
	/// Usually has a second parameter that directed this object towards the BankData, however the server gives that information now.
	BankAccount(int accountNumber, Session session) : accountNumber(accountNumber) {}

	/// Creates a new BankAccount object.
	BankAccount(int accountNumber, double balance) : accountNumber(accountNumber), balance(balance) {}

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

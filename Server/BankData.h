#pragma once

// Server includes
#include "AccountRecord.h"
#include "CustomerRecord.h"

ref class BankData {
private:
	static array<AccountRecord^>^ accounts;
	static array<CustomerRecord^>^ customers;
public:

	/// Arrays should be initialized through the Init() method.
	BankData() {};

	/// Initializes the class-level arrays.
	static void Init();

	// TODO Create a method to insert new accounts.

	double GetBalance(int accountNumber);
	CustomerRecord^ GetCustomer(int custNumber);
	AccountRecord^ GetAccount(int accountNumber);
	static array<CustomerRecord^>^ GetCustRecords();
	
	void SetBalance(int accountNumber, double balance);
};

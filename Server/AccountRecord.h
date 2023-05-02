#pragma once
ref class AccountRecord {
private:
	int accountNumber;
	double balance;
public:

	/// Default constructor.
	AccountRecord();

	/// Creates an AccountRecord with the specified arguments.
	/// @param accountNumber The number of the account to be created.
	/// @param balance The starting balance of the account to be created.
	AccountRecord(int accountNumber, double balance);
	
	double GetBalance();
	int GetNumber();

	void SetBalance(double balance);
};


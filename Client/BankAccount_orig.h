#pragma once

// Server includes
#include "../Server/BankData.h"

ref class BankAccount {
private:
	int accountNumber;
	double balance;
	BankData^ data;
public:
	BankAccount(int accountNumber, BankData^ data);
	~BankAccount();

	double GetBalance();

	void Deposit(double amount);
	void Withdraw(double amount);
	void StoreBalance();
};


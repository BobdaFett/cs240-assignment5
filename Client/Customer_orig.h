#pragma once

// Client includes
#include "BankAccount.h"

ref class Customer {
private:
	int custNumber;
	BankAccount^ savings;
	BankAccount^ checking;
public:
	Customer(int custNumber, BankData^ data);

	BankAccount^ GetCheckingAccount();
	BankAccount^ GetSavingsAccount();
};


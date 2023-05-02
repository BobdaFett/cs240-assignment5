#include "BankAccount.h"

using System::Console;

BankAccount::BankAccount(int accountNumber, BankData^ data) {
	this->accountNumber = accountNumber;
	this->data = data;
	this->balance = data->GetBalance(accountNumber);
	Console::WriteLine("Created account: {0}, ${1}", accountNumber, balance);
}

BankAccount::~BankAccount() {
	Console::WriteLine("Deleted a BankAccount.");
}

double BankAccount::GetBalance() {
	return this->balance;
}

void BankAccount::Deposit(double amount) {
	this->balance += amount;
}

void BankAccount::Withdraw(double amount) {
	// TODO There should be some sort of safeguard against going negative.
	this->balance -= amount;
}

void BankAccount::StoreBalance() {
	this->data->SetBalance(this->accountNumber, this->balance);
}

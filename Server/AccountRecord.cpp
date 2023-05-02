#include "AccountRecord.h"

AccountRecord::AccountRecord() {
	this->accountNumber = 0;
	this->balance = 0;
}

AccountRecord::AccountRecord(int accountNumber, double balance) {
	this->accountNumber = accountNumber;
	this->balance = balance;
}

double AccountRecord::GetBalance() {
	return this->balance;
}

int AccountRecord::GetNumber() {
	return this->accountNumber; 
}

void AccountRecord::SetBalance(double balance) {
	this->balance = balance;
}
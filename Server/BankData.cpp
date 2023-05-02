#include "BankData.h"

using namespace System;

void BankData::Init() {
	accounts = gcnew array<AccountRecord^>(10);
	customers = gcnew array<CustomerRecord^>(5);

	// Just do it manually.
	for (int i = 0; i < 10; i++) {
		accounts[i] = gcnew AccountRecord(i, 0);
	}

	for (int i = 0; i < 5; i++) {
		customers[i] = gcnew CustomerRecord(i, i);
		customers[i]->SetCheckingNumber(2 * i);
		customers[i]->SetSavingsNumber((2 * i) + 1);
	}

	Console::WriteLine("Finished initialization.");
	for each (AccountRecord ^ acc in accounts) {
		Console::WriteLine("Account: {0}, ${1}", acc->GetNumber(), acc->GetBalance());
	}
	Console::WriteLine("");
	for each (CustomerRecord ^ cust in customers) {
		Console::WriteLine("Customer: {0}, pin: {3}, checking: {1}, savings: {2}", cust->GetCustNumber(), cust->GetCheckingNumber(), cust->GetSavingsNumber(), cust->GetPin());
	}
}

double BankData::GetBalance(int accountNumber) {
	if (accounts[accountNumber] == nullptr) {
		Console::WriteLine("Account {0} does not exist.", accountNumber);
		return -1;
	}
	Console::WriteLine("Account {0} exists, balance ${1}", accountNumber, accounts[accountNumber]->GetBalance());
	return accounts[accountNumber]->GetBalance();
}

CustomerRecord^ BankData::GetCustomer(int custNumber) {
	if (customers[custNumber] != nullptr) {
		return customers[custNumber];
	}
	else return nullptr;
}

AccountRecord^ BankData::GetAccount(int accountNumber) {
	for (int i = 0; i < accounts->Length; i++) {
		if (accounts[i]->GetNumber() == accountNumber) {
			return accounts[i];
		}
		else return nullptr;
	}
}

array<CustomerRecord^>^ BankData::GetCustRecords() {
	return customers;
}

void BankData::SetBalance(int accountNumber, double balance) {
	for (int i = 0; i < accounts->Length; i++) {
		if (accounts[i]->GetNumber() == accountNumber) {
			accounts[i]->SetBalance(balance);
		}
	}
}
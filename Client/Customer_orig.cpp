#include "Customer.h"

using System::Console;

Customer::Customer(int custNumber, BankData^ data) {
	this->custNumber = custNumber;
	CustomerRecord^ temp = data->GetCustomer(custNumber);

	// Create checking and savings BankAccounts.
	// These will eventually store their data into the BankData.
	// Should get the balance of the account through the constructor.
	checking = gcnew BankAccount(temp->GetCheckingNumber(), data);
	savings = gcnew BankAccount(temp->GetSavingsNumber(), data);
}

BankAccount^ Customer::GetCheckingAccount() {
	return checking;
}

BankAccount^ Customer::GetSavingsAccount() {
	return savings;
}
#include "ATM.h"

using namespace ATM;

ATMClass::ATMClass() {
	state = State::START;
	currentCustomer = nullptr;
	currentAccount = nullptr;
	session = nullptr;
}

void ATMClass::Reset() {
	this->state = State::START;
}

void ATMClass::SetCustomerNumber(int number) {
	this->customerNumber = number;
	this->state = State::PIN;
}

Customer^ ATMClass::SelectCustomer(int pin) {
	// Create a connection to the server.
	session = gcnew Session();

	// Initialize resources.
	currentCustomer = gcnew Customer(customerNumber, pin, session);
	if (currentCustomer != nullptr) this->state = State::ACCOUNT;
	else this->state = State::START;
	return this->currentCustomer;
}

void ATMClass::SelectAccount(AccType accountType) {
	switch (accountType) {
	case AccType::CHECKING:
		currentAccount = currentCustomer->GetCheckingAccount();  // TODO Returns a nullptr
		break;
	case AccType::SAVINGS:
		currentAccount = currentCustomer->GetSavingsAccount();
		break;
	}
	this->state = State::TRANSACT;
}

void ATMClass::Withdraw(double value) {
	// Run store data? Maybe when changing the state.
	this->currentAccount->Withdraw(value);
}

void ATMClass::Deposit(double value) {
	// Run store data? Maybe when changing the state.
	this->currentAccount->Deposit(value);
}

double ATMClass::GetBalance() {
	return this->currentAccount->GetBalance();
}

void ATMClass::Back() {
	// switch handles everything EXECPT State::START, because Application::Exit is better placed in the form itself.
	switch (state) {
	case State::ACCOUNT:
		state = State::START;
		break;
	case State::PIN:
		state = State::START;
		break;
	case State::TRANSACT:
		// Save data to the BankData before leaving the page.
		currentAccount->StoreBalance();
		state = State::ACCOUNT;
		break;
	}
}

State ATMClass::GetState() {
	return this->state;
}

void ATMClass::CloseAll() {
	// disconnect?
}
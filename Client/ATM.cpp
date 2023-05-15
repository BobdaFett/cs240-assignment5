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

Boolean ATMClass::SelectCustomer(int pin) {
	try {
		session = gcnew Session();
		currentCustomer = gcnew Customer(customerNumber, pin, session);
		this->state = State::ACCOUNT;
		return true;
	}
	catch (Exception^ e) {  // Customer or BankAccount didn't initialize properly, or Session couldn't connect.
		Console::ForegroundColor = ConsoleColor::Red;
		Console::WriteLine("Error: {0}", e->Message);
		this->state = State::START;
		Console::ForegroundColor = ConsoleColor::White;
		delete session;
		throw e;
	}
}

void ATMClass::SelectAccount(AccType accountType) {
	switch (accountType) {
	case AccType::CHECKING:
		currentAccount = currentCustomer->GetCheckingAccount();
		Console::WriteLine("Changed to checking account, account number {0}", currentAccount->GetNumber());
		break;
	case AccType::SAVINGS:
		currentAccount = currentCustomer->GetSavingsAccount();
		Console::WriteLine("Changed to savings account, account number {0}", currentAccount->GetNumber());
		break;
	}
	this->state = State::TRANSACT;
}

void ATMClass::Withdraw(double value) {
	this->currentAccount->Withdraw(value);
}

void ATMClass::Deposit(double value) {
	this->currentAccount->Deposit(value);
}

double ATMClass::GetBalance() {
	return this->currentAccount->GetBalance();
}

void ATMClass::Back() {
	switch (state) {
	case State::START:
		Environment::Exit(0);
	case State::ACCOUNT:
		CloseAll();  // When returning to the start window, we need to close the connection to start a new Session.
		state = State::START;
		break;
	case State::PIN:
		state = State::START;
		break;
	case State::TRANSACT:
		// Save data to the BankData before leaving the page.
		try {
			currentAccount->StoreBalance();
			state = State::ACCOUNT;
		}
		catch (Exception^) {
			// Block the user from going any farther in the window.
			state = State::TRANSACT;  // Just as a safeguard.
		}
		break;
	}
}

State ATMClass::GetState() {
	return this->state;
}

void ATMClass::CloseAll() {
	// disconnect?
	delete session;
}
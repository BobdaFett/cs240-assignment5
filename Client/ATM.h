#pragma once

// Client includes
#include "Customer.h"
#include "BankAccount.h"
#include "Session.h"
#include "Form1.h"

// Server includes - should be able to remove these.
#include "../Server/Bank.h"

namespace ATM {

	enum class State { START, PIN, ACCOUNT, TRANSACT };
	enum class AccType { CHECKING, SAVINGS };

	ref class ATMClass {
	private:
		State state;
		int customerNumber;
		Customer^ currentCustomer;
		BankAccount^ currentAccount;
		Session^ session;
		Bank^ theBank;

	public:
		/// Creates an ATM class that's registered with a Bank.
		/// @param bank The Bank object to use when doing all operations with this ATM.
		ATMClass(Bank^ bank);

		/// Resets the ATM to its initial state.
		void Reset();

		/// Sets the current customer number and sets state to PIN.
		/// @param number The customer number.
		void SetCustomerNumber(int number);

		/// Finds the customer in the bank.
		/// If foundand pin matches, sets state to ACCOUNT, if not then back to START.
		/// @param pin The pin for the customer. This must match.
		/// @returns The customer found, for chaining.
		Customer^ SelectCustomer(int pin);

		/// Sets the current account to checking or savings.
		/// Sets state to TRANSACT.=
		/// @param accountType The type of the account to get.
		void SelectAccount(AccType accountType);

		/// Withdraws an amount from the current account.
		/// @param value The amount to withdraw.
		void Withdraw(double value);

		/// Deposits an amount to the current account.
		/// @param value The amount to deposit.
		void Deposit(double value);

		/// Gets the balance of the current account.
		/// Really more of a bridge to the BankAccount->GetBalance() method.
		/// @returns The balance of the current BankAccount.
		double GetBalance();

		/// Moves back to the previous state.
		void Back();

		/// @returns The current state as a State enum.
		State GetState();

		/// Closes all used files.
		/// I don't personally think that this is necessary, because we're not
		/// dealing with any files right now and the handles are garbage collected.
		void CloseAll();
	};
}

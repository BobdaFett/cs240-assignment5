#include "Form1.h"
#include "Form2.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace cs240assignment2;

Void Form1::numButtonClick(Object^ o, EventArgs^ e) {
	String^ button_name = ((Button^)o)->Name;
	String^ button_text = ((Button^)o)->Text;

	if (button_name == "buttonClear") {
		textBox1->Clear();
		return;
	}
	if (button_name == "buttonA") {
		buttonA_Event();
		return;
	}
	if (button_name == "buttonB") {
		buttonB_Event();
		return;
	}
	if (button_name == "buttonC") {
		buttonC_Event();
		return;
	}

	// Will only execute should this if the button is a number button. These stay constant throughout every State.
	textBox1->AppendText(button_text);
}

Void Form1::buttonA_Event() {
	switch (current_atm->GetState()) {
	case State::START: {
		// Should store customer number into the ATM
		// Changes current_State to PIN
		Int32 cust_num{};  // equivalent to an Int32, not an Int16.
		Int32::TryParse(textBox1->Text, cust_num);  // put into if Statement later.
		if (Int32::TryParse(textBox1->Text, cust_num)) {
			current_atm->SetCustomerNumber(cust_num);
		}
		else {
			// Modal window with error message.
			// Clears textBox1.
			error_window("Please enter a valid number.");
		}
		break;
	}
	case State::PIN: {
		// Stores and sets customerPIN.
		// Changes current_State to ACCOUNT
		Int32 pin{};

		if (Int32::TryParse(textBox1->Text, pin)) {
			if (!current_atm->SelectCustomer(pin)) {
				error_window("Customer number or pin was not found.");
				current_atm->Back();
			}
		}
		else {
			// Modal window with error message.
			// Clears textBox1.
			error_window("Please enter a valid number.");
		}
		break;
	}
	case State::ACCOUNT: {
		// Sets current_account to CHECKING
		current_atm->SelectAccount(AccType::CHECKING);
		break;
	}
	case State::TRANSACT: {
		// Sets current account to SAVINGS
		Double trans_amount{};
		Double::TryParse(textBox1->Text, trans_amount);  // put into if Statement later. not sure why it's not working?
		if (Double::TryParse(textBox1->Text, trans_amount)) {
			current_atm->Withdraw(trans_amount);
		}
		else {
			// Modal window with error message.
			// Clears textBox1
			error_window("Please enter a valid dollar amount.");
		}
		break;
	}
	}
	change_formState();
}

Void Form1::buttonB_Event() {
	switch (current_atm->GetState()) {
	case State::ACCOUNT: {
		// Sets current_account to SAVINGS
		// Changes current_State to TRANSACT
		current_atm->SelectAccount(AccType::SAVINGS);
		break;
	}
	case State::TRANSACT: {
		// Sets current_transaction to DEPOSIT
		// Set transactionAmount to user entered number (parsed from string, handle errors accordingly.)
		// Changes current_State to ACCOUNT
		Double userAmount = 0.0;
		if (Double::TryParse(textBox1->Text, userAmount)) {
			current_atm->Deposit(userAmount);
		}
		else {
			// Modal window with error message.
			// Clears textBox1.
			error_window("Please enter a valid dollar amount.");
		}
		break;
	}
	}
	change_formState();
}

Void Form1::buttonC_Event() {

	if (current_atm->GetState() == State::START) Application::Exit();
	else current_atm->Back();

	change_formState();
}

Void Form1::change_formState() {
	switch (current_atm->GetState()) {
	case State::START: {
		// buttonA = "OK"
		// buttonB = null
		// buttonC = "Exit"
		// textBox2 = "Enter cust num and press OK"
		buttonA->Text = "OK";
		buttonB->Visible = false;
		buttonC->Text = "Exit";
		textBox2->Text = "Enter customer number and press OK.";
		break;
	}
	case State::PIN: {
		// buttonA = "OK"
		// buttonB = null
		// buttonC = null
		// textBox2 = "Enter PIN and press OK"
		buttonA->Text = "OK";
		buttonB->Visible = false;
		buttonC->Visible = false;
		textBox2->Text = "Enter PIN and press OK.";
		break;
	}
	case State::ACCOUNT: {
		// buttonA = "Checking"
		// buttonB = "Savings"
		// buttonC = "Cancel"
		// textBox2 = "Select Account"
		buttonA->Text = "Checking";
		buttonB->Visible = true;
		buttonB->Text = "Savings";
		buttonC->Visible = true;
		buttonC->Text = "Cancel";
		textBox2->Text = "Select account type.";
		break;
	}
	case State::TRANSACT: {
		// buttonA = "Withdraw"
		// buttonB = "Deposit"
		// buttonC = "Cancel"
		// textBox2 = "Balance... Enter amount and select transaction"
		Double currentBalance = current_atm->GetBalance();

		buttonA->Text = "Withdraw";
		buttonB->Visible = true;
		buttonB->Text = "Deposit";
		buttonC->Visible = true;
		buttonC->Text = "Back";
		textBox2->Text = "Balance: $" + currentBalance + "\r\nEnter amount and select transaction type.";
		break;
	}
	}
	textBox1->Clear();
}

Void Form1::error_window(String^ error_text) {
	Form2^ e = gcnew Form2();
	e->getLabel()->Text = error_text;
	e->ShowDialog();
	textBox1->Clear();
}

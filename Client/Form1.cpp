#include "Form1.h"
#include "Form2.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace cs240assignment5;

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
		Int32 cust_num{};
		if (Int32::TryParse(textBox1->Text, cust_num))
			current_atm->SetCustomerNumber(cust_num);
		else error_window("Please enter a valid number.");
		break;
	}

	case State::PIN: {
		Int32 pin{};
		if (Int32::TryParse(textBox1->Text, pin)) {
			try {
				current_atm->SelectCustomer(pin);
			}
			catch (Exception^ e) {
				// error window
				error_window(e->Message);
			}
		}
		else error_window("Please enter a valid number.");
		break;
	}

	case State::ACCOUNT: {
		current_atm->SelectAccount(AccType::CHECKING);
		break;
	}

	case State::TRANSACT: {
		Double trans_amount{};
		if (Double::TryParse(textBox1->Text, trans_amount))
			current_atm->Withdraw(trans_amount);
		else error_window("Please enter a valid dollar amount.");
		break;
	}
	}
	change_formState();
}

Void Form1::buttonB_Event() {
	switch (current_atm->GetState()) {
	case State::ACCOUNT:
		// Sets current_account to SAVINGS
		// Changes current_State to TRANSACT
		current_atm->SelectAccount(AccType::SAVINGS);
		break;

	case State::TRANSACT:
		Double userAmount{};
		if (Double::TryParse(textBox1->Text, userAmount))
			current_atm->Deposit(userAmount);
		else error_window("Please enter a valid dollar amount.");
		break;
	}
	change_formState();
}

Void Form1::buttonC_Event() {
	try {
		current_atm->Back();
		change_formState();
	}
	catch (Exception^ e) {
		// Show an error window and clear the text box.
		error_window(e->Message);
	}
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
		buttonC->Visible = true;
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

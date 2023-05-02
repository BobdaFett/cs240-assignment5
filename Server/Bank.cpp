#include "Bank.h"

using namespace System;
using namespace System::Net;
using namespace System::Net::Sockets;

Bank::Bank() {
	BankData^ data = gcnew BankData();
	data->Init();
	this->customers = BankData::GetCustRecords();
}

Customer^ Bank::FindCustomer(int custNumber, int pin) {
	// This will be a very slow search, but I don't think we're worried about that in this case.
	for (int i = 0; i < customers->Length; i++) {
		CustomerRecord^ cust = customers[i];
		if (cust->GetCustNumber() == custNumber) {
			Console::WriteLine("Found customer {0}", custNumber);
			if (cust->GetPin() == pin) {
				Console::WriteLine("PIN matched!");
				return gcnew Customer(custNumber, gcnew BankData());
			}
			else {
				Console::WriteLine("PIN did not match.");
			}
		}
	}
	return nullptr;
}

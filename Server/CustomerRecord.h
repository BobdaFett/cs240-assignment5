#pragma once
ref class CustomerRecord {
private:
	int custNumber{};
	int pin{};
	int checkingNumber{};
	int savingsNumber{};
public:

	/// Customer constructor.
	/// This object is only ever constructed from the server side, and as such will not require a Session handle.
	CustomerRecord();

	/// Customer constructor.
	/// This object is only ever constructed from the server side, and as such will not require a Session handle.
	/// @param custNumber - the customer number for the new object.
	/// @param pin - the pin for the new object.
	CustomerRecord(int custNumber, int pin);

	/// @returns The customer number for this object.
	int GetCustNumber();

	/// @returns The pin for this object.
	int GetPin();

	/// @returns The checking account number for this object.
	int GetCheckingNumber();

	/// @returns The savings account number for this object.
	int GetSavingsNumber();

	/// Sets the customer number for this object.
	/// @param custNumber - the new number for this customer.
	void SetCustNumber(int custNumber);

	/// Sets the pin for this object.
	/// @param pin - the new pin for this customer.
	void SetPin(int pin);

	/// Sets the checking account number for this object.
	/// @param checkingNumber - the new account number for the checking account associated with this customer.
	void SetCheckingNumber(int checkingNumber);

	/// Sets the savings account number for this object.
	/// @param savingsNumber - the new account number for the savings account associated with this customer.
	void SetSavingsNumber(int savingsNumber);
};

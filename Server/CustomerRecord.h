#pragma once
ref class CustomerRecord {
private:
	int custNumber{};
	int pin{};
	int checkingNumber{};
	int savingsNumber{};
public:
	CustomerRecord();  // default constructor
	CustomerRecord(int custNumber, int pin);

	int GetCustNumber();
	int GetPin();
	int GetCheckingNumber();
	int GetSavingsNumber();

	void SetCustNumber(int custNumber);
	void SetPin(int pin);
	void SetCheckingNumber(int checkingNumber);
	void SetSavingsNumber(int savingsNumber);
};

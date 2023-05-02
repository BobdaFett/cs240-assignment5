#include "CustomerRecord.h"

using System::Console;

CustomerRecord::CustomerRecord() {
	this->custNumber = 0;
	this->pin = 0;
	this->checkingNumber = 0;
	this->savingsNumber = 0;
}

CustomerRecord::CustomerRecord(int custNumber, int pin) {
	this->custNumber = custNumber;
	this->pin = pin;
	this->checkingNumber = 0;
	this->savingsNumber = 0;
}

int CustomerRecord::GetCustNumber() {
	return this->custNumber;
}

int CustomerRecord::GetPin() {
	return this->pin;
}

int CustomerRecord::GetCheckingNumber() {
	Console::WriteLine("Getting checking number...");
	return this->checkingNumber;
}

int CustomerRecord::GetSavingsNumber() {
	Console::WriteLine("Getting savings number...");
	return this->savingsNumber;
}

void CustomerRecord::SetCustNumber(int custNumber) {
	this->custNumber = custNumber;
}

void CustomerRecord::SetPin(int pin) {
	this->pin = pin;
}

void CustomerRecord::SetCheckingNumber(int checkingNumber) {
	this->checkingNumber = checkingNumber;
}

void CustomerRecord::SetSavingsNumber(int savingsNumber) {
	this->savingsNumber = savingsNumber;
}
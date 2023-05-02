#pragma once

// Client includes
#include "../Client/Customer.h"

interface class BankInterface {
	Customer^ FindCustomer(int custNumber, int pin);
};
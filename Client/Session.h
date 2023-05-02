#pragma once

#include "BankAccount.h"
#include "Customer.h"

#ifndef SESSION_H

using namespace System;
using namespace System::IO;
using namespace System::Net;
using namespace System::Net::Sockets;

/// This is a wrapper object to create and run any sort of commands from the client side of this program.
/// This handles creation of a session with the server at localhost, and will keep track of all information that's required
/// to do with with server responses. Any time a file/class would like to get information from the server, this must be
/// created first. This is an incredibly inefficient way of going about doing this, however that's the easiest way I can
/// think of doing it on short notice.
/// 
/// If there's a way of going about this that I can create a single Session that will handle everything in the program, then that may be worth doing.
/// In some of the classes, such as Customer and BankAccount, I could attmept to require a reference to a Session in the constructor, which will then get data required.
ref class Session {
private:
	int port;
	IPAddress^ ip;
	IPEndPoint^ endpoint;
	Socket^ client;
	NetworkStream^ ns;
	BinaryReader^ reader;
	BinaryWriter^ writer;

public:

	/// Creates a Session that will attempt to connect to a server at localhost:2345
	Session();

	/// Creates and returns a BankAccount object with information from the server.
	BankAccount^ CreateBankAccount(int accountNumber);

	/// Sends information to the server to be saved to the corresponding AccountRecord object.
	void StoreBalance(int accountNumber, double balance);

	/// Creates and returns a Customer object with information from the server.
	Customer^ CreateCustomer(int customerNumber);

};

#endif

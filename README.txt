This program is separated into two projects within a single solution.
To run it while inside of Visual Studio, you MUST right click on the project name in the Solution Explorer, then click Build/Rebuild from there.
This will generate an executable file inside of the project directory, then x64/Debug/
These files should be runnable without opening Visual Studio.

The other option is that they can be built like described above, then run from Right Click -> Debug -> Start with(out) debugging.
This will run it as part of the Visual Studio process. Should you need the debugger, then you must do this for both of these files.


Test Cases:

Entering valid customer information: should select customer (works)
Entering invalid customer information: should block customer selection and disconnect from server (works)

Properly selecting customer should start a connection with the server (works)

Buttons on GUI function as expected.

Error window (as an extra) works as expected.

Accessing server functions directly from the terminal works as expected. Server must be started BEFORE the client to show this.

Server does not crash upon encountering fractured data.

Server does not crash upon receiving invalid parameters for commands.

Server sends information properly across a NetworkStream.

Closing the client/server properly disconnects the Session/Service associated with the process (destructors work as planned)

GETACCOUNT allows for proper construction of a BankAccount object (client-side)
GETCUSTOMER allows for proper construction of a Customer object (client-side)
SAVEBALANCE allows for proper updates of the balance in an AccountRecord object (server-side)

Client/server check for invalid parameters in commands.
Client/server check for corrupted data, such as an incorrect passed data type.
Client/server check for fractured data, however handling this is sketchy. The program attempts to Thread::Sleep(500) and then check again if there's something in the stream.
	This presents an issue if the client sent a different type of data, and will generally create instances of phantom commands that get lost after they're read from the
	stream. As such, the server will not send a response and the client will hang.
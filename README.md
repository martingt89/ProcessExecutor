ProcessExecutor
===============

Library for running external programs

class SafeStream - threadsafe class
	- buffer to copy data over threads
		- bool operator<<(const std::string& text) nonblock write to buffer
			return true if buffer is not close
			
		- bool operator>>(std::string& text) default block read, unblock thread if write data or close buffer
			return true if buffer is not close or are data available
			
		- void enableNonBlockRead() - if is reading and data not available return empty string - non waiting
		
		- disableNonBlockRead() - return to block mode
		
		- bool isOpen() - test if buffer is still open
		
		- void close() - finally close buffer
	
class SafeInputStream - threadsafe class
	- ecapsulate SafeStream and enable only read

class SafeOutputStream - threadsafe class
	- ecapsulate SafeStream and enable only write
	
class ProcessExecutor
	- execute command with arguments and create SafeStream for stdin, stdout, stderr
		SafeInputStream& getStdOut() - return stream for reading from std out
		
		SafeInputStream& getStdErr() - return stream for reading from std err
		
		SafeOutputStream& getStdIn() - return stream for writing to std in
		
		int waitForRunChild(std::string &errorMessage) - block thread until command is execute or if error
			- return 0 if ok, else 1 and errorMessage is set
		int waitForEndChild() - block thread until command is not endit or if error
			- return child return value, or -1 if error
		void terminateChild() - send sigterm to child process
		
INSTALL
=======

		./configure
		make
		sudo make install
		sudo ldconfig

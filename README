ProcessExecutor
===============

Library for running external programs

ONLY FOR LINUX

VERSION
=======

0.2

Namespace
=========

ProcessExecutor

Using
=====

class SafeStream - threadsafe class
	- buffer to copy data over threads
		
		- bool operator<<(const std::string& text) nonblock write to buffer
			return true if buffer is not close
			
		- bool operator>>(std::string& text) block read, unblock thread if write data or close buffer
			return true if buffer is not close or are data available
		
		- int operator>>=() non block read
			return 1 if read ok, -1 if empty buffer, 0 if close stream
		
		- bool isOpen() - test if buffer is still open
		
		- void close() - finally close buffer
	
class SafeInputStream - threadsafe class
	- ecapsulate SafeStream and enable only read

class SafeOutputStream - threadsafe class
	- ecapsulate SafeStream and enable only write
	
class Process
	- execute command with arguments and create SafeStream for stdin, stdout, stderr
		
		SafeInputStream& getStdOut() - return stream for reading from std out
		
		SafeInputStream& getStdErr() - return stream for reading from std err
		
		SafeOutputStream& getStdIn() - return stream for writing to std in
		
		int waitForChildProcessBegin(std::string &errorMessage) - block thread until command is executed or if error
			- return 0 if ok, else 1
		int waitForChildProcessEnd() - block thread until command is not ended or if error
			- return child return value, or -1 if error
		void terminateChild() - send sigterm to child process

Install
=======

		./configure
		make
		sudo make install
		sudo ldconfig

Compile your project with
==========================
		-lpthread -lprocessexecutor -std=c++0x

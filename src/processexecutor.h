/*
 * processexecutor.h
 *
 *  Created on: 21.6.2012
 *      Author: martint
 */

#ifndef PROCESSEXECUTOR_H_
#define PROCESSEXECUTOR_H_

#include <iostream>
#include <sstream>
#include "safestream.h"
#include "safeoutputstream.h"
#include "safeinputstream.h"
#include <thread>
#include <list>

namespace Process {

class Executor {
public:
	Executor(const std::string& path, const std::list<std::string>& args = std::list<std::string>());
	virtual ~Executor();
	SafeInputStream& getStdOut();
	SafeInputStream& getStdErr();
	SafeOutputStream& getStdIn();
	int waitForRunChild(std::string &errorMessage);
	int waitForEndChild();
	void terminateChild();
private:
	SafeStream out;
	SafeStream err;
	SafeStream in;
	SafeInputStream errStream;
	SafeInputStream outStream;
	SafeOutputStream inStream;
	void run();
	void writeIn(int fd);
	void readOut(int fd);
	void readErr(int fd);
	void readFdWriteToStream(int fd, SafeStream &stream);
	std::thread* thread;
	std::mutex mutex;
	std::condition_variable cond;
	std::string command;
	std::list<std::string> args;

	int childPid;
	int childReturnState;
	std::string errorMessage;
	int errorState;
	bool rerunParent;
	bool endChild;
};

} /* namespace Process */
#endif /* PROCESSEXECUTOR_H_ */

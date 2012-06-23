/*
 * processexecutor.cpp
 *
 *  Created on: 21.6.2012
 *      Author: martint
 */

#include "processexecutor.h"
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>


#define PROCESS_OK			0
#define PROCESS_PIPEERR		1
#define PROCESS_VFORKERR	2
#define PROCESS_DUP0ERR		3
#define PROCESS_DUP1ERR		4
#define PROCESS_DUP2ERR		5
#define PROCESS_EXECVPERR	6

namespace Process {

std::string getErrorMessage(const std::string& text){
	return text + strerror(errno);
}

Executor::Executor(const std::string& path, const std::list<std::string>& args):
		errStream(err),
		outStream(out),
		inStream(in){
	errorState = PROCESS_OK;
	childReturnState = -1;
	childPid = -1;
	rerunParent = false;
	endChild = false;

	command = path;
	std::list<std::string>::const_iterator it;
	for(it = args.begin(); it != args.end(); it++){
		this->args.push_back(*it);
	}
	thread = new std::thread(&Executor::run, this);
}

Executor::~Executor() {
	thread->join();
	delete thread;
}
SafeInputStream& Executor::getStdOut(){
	return outStream;
}
SafeInputStream& Executor::getStdErr(){
	return errStream;
}
SafeOutputStream& Executor::getStdIn(){
	return inStream;
}
int Executor::waitForRunChild(std::string &errorMessage){
	std::unique_lock<std::mutex> m(mutex);
	while(!rerunParent){
		cond.wait(m);
	}
	if(errorState != PROCESS_OK){
		errorMessage = this->errorMessage;
		return 1;
	}
	return 0;
}
int Executor::waitForEndChild(){
	std::unique_lock<std::mutex> m(mutex);
	while(!rerunParent || !endChild){
		cond.wait(m);
	}
	return childReturnState;
}
void Executor::terminateChild(){
	std::unique_lock<std::mutex> m(mutex);
	if(childPid > 0){
		kill(childPid, SIGTERM);
	}else{
		//Child process is not running
	}
}
void Executor::writeIn(int fd){
	std::string input;
	while (in >> input){
		write (fd, input.c_str(), input.size());
	}
}

void Executor::readFdWriteToStream(int fd, SafeStream &stream) {
	char buf;
	std::stringstream ss;
	while (read(fd, &buf, 1)) {
		if (buf != '\n') {
			ss << buf;
		} else {
			stream << ss.str();
			ss.str("");
		}
	}
	if (ss.str().size() > 0)
		stream << ss.str();
}
void Executor::readOut(int fd){
	readFdWriteToStream(fd, out);
}
void Executor::readErr(int fd) {
	readFdWriteToStream(fd, err);
}

/*Fork process, start program with command and args*/
void Executor::run() {
	int toInt[2];
	int toOut[2];
	int toErr[2];
	if (pipe(toInt) != 0) {
		errorState = PROCESS_PIPEERR;
		errorMessage = getErrorMessage("Cannot create pipe: ");
		return;
	}
	if (pipe(toOut) != 0) {
		errorState = PROCESS_PIPEERR;
		errorMessage = getErrorMessage("Cannot create pipe: ");
		return;
	}
	if (pipe(toErr) != 0) {
		errorState = PROCESS_PIPEERR;
		errorMessage = getErrorMessage("Cannot create pipe: ");
		return;
	}

	std::list<std::string>::iterator it;
	char* comm[args.size() + 2];
	comm[0] = (char*) (command.c_str());
	int cc = 1;
	for (it = args.begin(); it != args.end(); it++) {
		comm[cc] = (char*) (it->c_str());
		cc++;
	}
	comm[cc] = NULL;

	static int vforkErr = 0;

	int pid = vfork();
	if (pid == -1) {
		errorState = PROCESS_VFORKERR;
		errorMessage = getErrorMessage("Cannot run vfork: ");
		return;
	}

	if(pid == 0){	//child
		close(0);
		if(dup(toInt[0]) != 0){
			errorState = PROCESS_DUP0ERR;
			errorMessage = getErrorMessage("Dup 0 error: ");
			_exit(1);
		}
		close(toInt[1]);

		close(1);
		if(dup(toOut[1]) != 1){
			errorState = PROCESS_DUP1ERR;
			errorMessage = getErrorMessage("Dup 1 error: ");
			_exit(1);
		}
		close(toOut[0]);

		close(2);
		if(dup(toErr[1]) != 2){
			errorState = PROCESS_DUP2ERR;
			errorMessage = getErrorMessage("Dup 2 error: ");
			_exit(1);
		}
		close(toErr[0]);

		execvp(command.c_str(), comm);
		{
			errorState = PROCESS_EXECVPERR;
			errorMessage = getErrorMessage("execvp error: ");
			vforkErr = 1;
		}
		_exit(1);
	}

	//parent

	close(toErr[1]);
	close(toOut[1]);
	close(toInt[0]);
	std::unique_lock<std::mutex> m(mutex);
	childPid = pid;
	rerunParent = true;
	cond.notify_all();
	m.unlock();

	if(vforkErr == 0){	//command is running
		std::thread threadIn(&Executor::writeIn, this, toInt[1]);
		std::thread threadOut(&Executor::readOut, this, toOut[0]);
		std::thread threadErr(&Executor::readErr, this, toErr[0]);

		wait(&childReturnState);
		in.close();
		err.close();
		out.close();

		threadIn.join();
		threadOut.join();
		threadErr.join();
	}
	m.lock();
	childPid = -1;
	endChild = true;
	cond.notify_all();
	m.unlock();

	in.close();
	err.close();
	out.close();
}


} /* namespace Process */


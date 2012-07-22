//compile g++ complete.cpp -lpthread -lprocessexecutor -std=c++0x -o complete

#include <iostream>
#include <processexecutor/process.h>


void run(std::string command, std::list<std::string> arg){

	std::string sa;

	ProcessExecutor::Process p(command, arg);
	if(p.waitForProcessBegin()){			//if error
		p.getLog() >>= sa;
		std::cout<<"Log: "<<sa<<std::endl;
		return;
	}

	ProcessExecutor::SafeInputStream& siso = p.getStdOut();
	ProcessExecutor::SafeInputStream& sise = p.getStdErr();

	sa = "";

	while(siso >> sa){
		std::cout<<sa<<std::endl;
	}

	std::cout<<"Return: "<<p.waitForProcessEnd()<<std::endl;

}

int main(int argc, char *argv[]){

	std::list<std::string> arg;
	arg.push_back("-a");
	
	std::cout<<"====== Running 'ls -a' ======="<<std::endl;

	run("ls", arg);	//all ok
	
	std::cout<<std::endl<<"====== Running 'lsa -a' ======="<<std::endl;
	
	run("lsa", arg); //program lsa doesn't exist


	
	return 0;
}

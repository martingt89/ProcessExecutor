//compile g++ complete.cpp -lpthread -lprocessexecutor-0.1 -std=c++0x -o complete

#include <iostream>
#include <processexecutor/processexecutor.h>


void run(std::string command, std::list<std::string> arg){

	std::string sa;

	Process::Executor p(command, arg);
	if(p.waitForRunChild()){			//if error
		p.getLog() >>= sa;
		std::cout<<"Log: "<<sa<<std::endl;
		return;
	}

	Process::SafeInputStream& siso = p.getStdOut();
	Process::SafeInputStream& sise = p.getStdErr();

	sa = "";

	while(siso >> sa){
		std::cout<<sa<<std::endl;
	}

	std::cout<<"Return: "<<p.waitForEndChild()<<std::endl;

}

int main(int argc, char *argv[]){

	std::list<std::string> arg;
	arg.push_back("-a");
	
	std::cout<<"====== running 'ls -a' ======="<<std::endl;

	run("ls", arg);	//all ok
	
	std::cout<<"====== running 'lsa -a' ======="<<std::endl;
	
	run("lsa", arg); //program lsa doesn't exist


	
	return 0;
}

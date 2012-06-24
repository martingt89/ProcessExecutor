//compile g++ arguments.cpp -lpthread -lprocessexecutor-0.1 -std=c++0x -o arguments

#include <iostream>
#include <processexecutor/processexecutor.h>



int main(){

std::list<std::string> args;
args.push_back("-l");
args.push_back("-a");

Process::Executor process("ls", args);

std::string output;

while(process.getStdOut() >> output){
	std::cout<<output<<std::endl;
}

return 0;
}

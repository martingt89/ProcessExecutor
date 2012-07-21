//compile g++ arguments.cpp -lpthread -lprocessexecutor -std=c++0x -o arguments

#include <iostream>
#include <processexecutor/process.h>

int main(){

std::cout<<"Running: "<<"ls -l -a"<<std::endl<<std::endl;

std::list<std::string> args;
args.push_back("-l");
args.push_back("-a");

ProcessExecutor::Process process("ls", args);

std::string output;

while(process.getStdOut() >> output){
	std::cout<<output<<std::endl;
}

return 0;
}

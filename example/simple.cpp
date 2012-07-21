//compile g++ simple.cpp -lpthread -lprocessexecutor -std=c++0x -o simple

#include <iostream>
#include <processexecutor/process.h>

int main(){

ProcessExecutor::Process process("uname");

std::string output;

while(process.getStdOut() >> output){
	std::cout<<output<<std::endl;
}

return 0;
}

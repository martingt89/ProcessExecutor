//compile g++ simple.cpp -lpthread -lprocessexecutor-0.1 -std=c++0x -o simple

#include <iostream>
#include <processexecutor/processexecutor.h>



int main(){

Process::Executor process("uname");

std::string output;

while(process.getStdOut() >> output){
	std::cout<<output<<std::endl;
}

return 0;
}

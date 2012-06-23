/*
 * safestream.cpp
 *
 *  Created on: 21.6.2012
 *      Author: martint
 */

#include "safestream.h"
#include <iostream>
namespace Process {

SafeStream::SafeStream() {
	open = true;
	blockRead = true;
}

SafeStream::~SafeStream() {
	// TODO Auto-generated destructor stub
}
void SafeStream::enableNonBlockRead(){
	std::unique_lock<std::mutex> m(mutex);
	blockRead = false;
	cond.notify_all();
}
void SafeStream::disableNonBlockRead(){
	std::unique_lock<std::mutex> m(mutex);
	blockRead = true;
}
bool SafeStream::operator<<(const std::string& text){
	std::unique_lock<std::mutex> m(mutex);
	if(open){
		buffer.push_back(text);
		cond.notify_all();
	}
	return open;
}
bool SafeStream::operator>>(std::string& text){
	std::unique_lock<std::mutex> m(mutex);
	while(blockRead && open && buffer.empty()){
		cond.wait(m);
	}
	if(!buffer.empty()){
		text = buffer.front();
		buffer.pop_front();
		return true;
	}
	return open;
}
bool SafeStream::isOpen(){
	std::unique_lock<std::mutex> m(mutex);
	return open;
}
void SafeStream::close(){
	std::unique_lock<std::mutex> m(mutex);
	open = false;
	cond.notify_all();
}
} /* namespace Process */

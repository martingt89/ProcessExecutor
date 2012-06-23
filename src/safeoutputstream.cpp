/*
 * safeoutputstream.cpp
 *
 *  Created on: 22.6.2012
 *      Author: martint
 */

#include "safeoutputstream.h"

namespace Process {

SafeOutputStream::SafeOutputStream(SafeStream &stream): stream(stream) {}

SafeOutputStream::~SafeOutputStream() {}

bool SafeOutputStream::isOpen(){
	return stream.isOpen();
}
void SafeOutputStream::close(){
	stream.close();
}
bool SafeOutputStream::operator<<(std::string &text){
	return stream << text;
}


} /* namespace Process */

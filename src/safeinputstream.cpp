/*
 * safeinputstream.cpp
 *
 *  Created on: 21.6.2012
 *      Author: martint
 */

#include "safeinputstream.h"

namespace Process {

SafeInputStream::SafeInputStream(SafeStream &stream): stream(stream) {
}

SafeInputStream::~SafeInputStream() {
}

bool SafeInputStream::isOpen(){
	return stream.isOpen();
}

bool SafeInputStream::operator>>(std::string &text){
	return stream >> text;
}
void SafeInputStream::enableNonBlockMode(){
	stream.enableNonBlockRead();
}
void SafeInputStream::disableNonBlockMode(){
	stream.disableNonBlockRead();
}
} /* namespace Process */

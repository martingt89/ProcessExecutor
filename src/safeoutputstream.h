/*
 * safeoutputstream.h
 *
 *  Created on: 22.6.2012
 *      Author: martint
 */

#ifndef SAFEOUTPUTSTREAM_H_
#define SAFEOUTPUTSTREAM_H_

#include "safestream.h"

namespace Process {

class SafeOutputStream {
public:
	SafeOutputStream(SafeStream &stream);
	virtual ~SafeOutputStream();
	bool isOpen();
	void close();
	bool operator<<(std::string &text);
private:
	SafeStream &stream;
	SafeOutputStream(const SafeOutputStream &stream);
	void operator=(const SafeOutputStream &stream);
};

} /* namespace Process */
#endif /* SAFEOUTPUTSTREAM_H_ */

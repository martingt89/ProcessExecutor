/*
 * safeinputstream.h
 *
 *  Created on: 21.6.2012
 *      Author: martint
 */

#ifndef SAFEINPUTSTREAM_H_
#define SAFEINPUTSTREAM_H_

#include "safestream.h"

namespace Process {

class SafeInputStream {
public:
	SafeInputStream(SafeStream &stream);
	virtual ~SafeInputStream();
	bool isOpen();
	bool operator>>(std::string &text);
	void enableNonBlockMode();
	void disableNonBlockMode();
private:
	SafeInputStream(const SafeInputStream& stream);
	void operator=(const SafeInputStream& stream);
	SafeStream &stream;
};

} /* namespace Process */
#endif /* SAFEINPUTSTREAM_H_ */

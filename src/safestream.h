/*
 * safestram.h
 *
 *  Created on: 21.6.2012
 *      Author: martint
 */

#ifndef SAFESTREAM_H_
#define SAFESTREAM_H_

#include <string>
#include <mutex>
#include <condition_variable>
#include <thread>
#include <list>
namespace Process {

class SafeStream{
public:
	SafeStream();
	virtual ~SafeStream();
	bool operator<<(const std::string& text);
	bool operator>>(std::string& text);
	bool isOpen();
	void close();
	void enableNonBlockRead();
	void disableNonBlockRead();
private:
	bool open;
	std::mutex mutex;
	std::condition_variable cond;
	std::list<std::string> buffer;
	bool blockRead;
};

} /* namespace Process */
#endif /* SAFESTREAM_H_ */



/*
* Author	FeronCompany
* Date		2019-08-18
* Function	Logger for all .cpps
*/

#pragma once

#include <string>
#include <iostream>
#include <sstream>
#include <fstream>

#include "CommSingleton.h"
#include "StrFormat.h"

class BusiLogger
{
	friend CommSingleton<BusiLogger>;
public:
	void log(const std::string& content);
	// log to designated file. to terminal if fileName is empty
	void redirect(const std::string& fileName);

private:
	BusiLogger() : mIsOnTerm(true), mLogFile("test.log") {}

private:
	bool mIsOnTerm;
	std::string mLogFile;
};

typedef CommSingleton<BusiLogger> Logger;
//typedef CommSingleton<FileLogger> Logger;

template <typename... Args>
void CommLogFunc(const Args& ... args)
{
	std::stringstream ssLog;
	std::initializer_list<int>{(ssLog << args << "|", 0)...};
	Logger::instance().log(ssLog.str());
}

#define COMM_LOG(fmt, ...) do { Logger::instance().log(ObjectTools::FormatString(fmt"<%s|%d>", ##__VA_ARGS__, __FILE__, __LINE__)); } while(0)




/*
* Author	FeronCompany
* Date		2019-08-18
* Function	Logger for all .cpps
*/

#pragma once

#include <iostream>
#include <string>
#include "CommSingleton.h"

class BaseLogger
{
public:
	virtual void log(const std::string& content) = 0;
};

class TerminalLogger : public BaseLogger
{
	friend CommSingleton<TerminalLogger>;
public:
	void log(const std::string& content) override
	{
		std::cout << content << "\n";
	}

private:
	TerminalLogger() {}
};

class FileLogger : public BaseLogger
{
	friend CommSingleton<TerminalLogger>;
public:
	void log(const std::string& content) override {}

private:
	FileLogger() {}
};

typedef CommSingleton<TerminalLogger> Logger;

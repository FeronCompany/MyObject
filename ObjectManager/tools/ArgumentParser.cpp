

#include "ArgumentParser.h"

#include <iostream>
#include <vector>
#include <cstring>
#include <exception>

void ArgumentParser::addDefaultArg(const COption& option)
{
	m_defaultArgs.insert(std::make_pair(option.strLongArgName, option));
	m_shortIndex.insert(std::make_pair(option.cShortArgName, option.strLongArgName));
}

void ArgumentParser::addDefaultArgs(COption* optionList, int size)
{
	for (int i = 0; i < size; ++i)
	{
		addDefaultArg(optionList[i]);
	}
}

void ArgumentParser::parse(int argc, char** argv)
{
	std::vector<std::string> commandStack;
	for (int i = 1; i < argc; ++i)
	{
		std::cout << i << ":" << argv[i] << "\n";
		std::string commandName;
		if (checkLongName(argv[i], commandName) || checkShortName(argv[i], commandName))
		{
			std::cout << "command name:" << commandName << "\n";
			// 确认是key时，确认其是否要跟value，如果明确不跟，直接跳过，否则放入commandStack
			std::map<std::string, COption>::iterator itor = m_defaultArgs.find(commandName);
			if (itor != m_defaultArgs.end() && itor->second.enArgType == EN_ARG_TYPE_NO_ARG)
			{
				m_argumentMap[commandName] = "";
			}
			else if (commandStack.empty())
			{
				commandStack.push_back(commandName);
			}
			else
			{
				throw std::exception("more than one command in stack");
			}
		}
		else
		{
			// 如果确认是value，匹配commandStack栈顶的command，若为空，则废弃此值；
			if (!commandStack.empty())
			{
				m_argumentMap[commandStack.back()] = argv[i];
				commandStack.pop_back();
			}
			else
			{
				std::cout << argv[i] << " is not match with any command\n";
			}
		}
	}

	if (!commandStack.empty())
	{
		std::cout << "err command: " << commandStack.front() << "\n";
	}
}

std::map<std::string, std::string>& ArgumentParser::getArgValue()
{
	return m_argumentMap;
}

bool ArgumentParser::checkShortName(const std::string& shortName, std::string& outName)
{
	if (shortName.size() == 2 && shortName.at(0) == '-')
	{
		std::map<char, std::string>::iterator itor = m_shortIndex.find(shortName.at(0));
		if (itor == m_shortIndex.end())
		{
			return false;
		}
		else
		{
			outName = itor->second;
			return true;
		}
	}
	return false;
}

bool ArgumentParser::checkLongName(const std::string& fullName, std::string& outName)
{
	if (fullName.size() > 2 && fullName.at(0) == '-' && fullName.at(1) == '-')
	{
		outName = fullName.substr(2);
		return true;
	}
	return false;
}



#include "BaseLogger.h"

void BusiLogger::log(const std::string& content)
{
	if (!mIsOnTerm)
	{
		std::ofstream ofs;
		ofs.open(mLogFile, std::ios::app);
		if (!ofs)
		{
			std::cerr << "open file failed\n";
			return;
		}
		std::streambuf* backup = std::cout.rdbuf();		// back up cin's streambuf
		std::cout.rdbuf(ofs.rdbuf());					// assign file's streambuf to cin
		std::cout << content << "\n";
		std::cout.rdbuf(backup);						// restore cin's original streambuf
		ofs.close();
	}
	else
	{
		std::cout << content << "\n";
	}
}

void BusiLogger::redirect(const std::string& fileName)
{
	mIsOnTerm = (fileName == "");
	mLogFile = fileName;
}

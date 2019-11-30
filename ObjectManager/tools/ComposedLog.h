

#pragma once

#include "MyTime.h"
#include "BaseLogger.h"

#define RECORD_LOG(fmt, ...) do { \
		Logger::instance().log(ObjectTools::FormatString("<%s> " fmt" <%s|%d>", \
		MyTime::now().tostr().c_str(), ##__VA_ARGS__, __FILE__, __LINE__)); \
	} while(0)

#define PURE_LOG(fmt, ...) do { \
		Logger::instance().log(ObjectTools::FormatString(fmt, ##__VA_ARGS__)); \
	} while(0)

#define APPEND_LOG(fmt, ...) do { \
		Logger::instance().logAppend(ObjectTools::FormatString(fmt, ##__VA_ARGS__)); \
	} while(0)

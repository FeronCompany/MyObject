

#include "StrFormat.h"

std::string ObjectTools::FormatString(const char* fmt, ...)
{
	char buf[2048] = { 0 };
	va_list ap;
	va_start(ap, fmt);
	vsnprintf(buf, sizeof(buf), fmt, ap);
	va_end(ap);
	return buf;
}

#include "Log.h"
cLog pLog;

void cLog::Log(const char* Message, ...)
{
	va_list list;
	char buffer[0xFFFF];
	va_start(list, Message);
	_vsnprintf_s(buffer, 0xFFFF, Message, list);
	va_end(list);

	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), buffer, strlen(buffer), 0, 0);
	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), "\n", strlen("\n"), 0, 0);
}

void cLog::Log(DWORD Color, const char* Message, ...)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_INTENSITY
		| Color);

	va_list list;
	char buffer[0xFFFF];
	va_start(list, Message);
	_vsnprintf_s(buffer, 0xFFFF, Message, list);
	va_end(list);

	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), buffer, strlen(buffer), 0, 0);
	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), "\n", strlen("\n"), 0, 0);
}
#pragma once

#include "Main.h"

class cLog
{
public:
	void Log(const char* Message, ...);
	void Log(DWORD Color, const char* Message, ...);

};

extern cLog pLog;
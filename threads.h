#pragma once
#include <Windows.h>
#include "auth.hpp"
#include <string>
#include "utils.hpp"
#include "skStr.h"


int is_debugger_presentt()
{
	if (IsDebuggerPresent())
		return 1;

	return 0;
}

int remote_debugger_present()
{
	BOOL is_debugger_present;

	CheckRemoteDebuggerPresent(GetCurrentProcess(), &is_debugger_present);

	return is_debugger_present;
}

__forceinline int debug_string()
{
	DWORD dwErrVal = 0x666;
	SetLastError(dwErrVal);
	OutputDebugStringA("hello dear reverse engineer");
	return GetLastError() != dwErrVal;
}

__forceinline bool find_debugger()
{
	if (IsDebuggerPresent())
	{
		return true;
	}
	else {
		return false;
	}
}

void AntiDebug()
{
	while (true)
	{
		if (find_debugger())
		{
			exit(0);
		}

		if (is_debugger_presentt() || remote_debugger_present() || debug_string()) {
			exit(0);
		}

		DebugBreak(); // redirect debugger to a return address

		Sleep(20000);

	}
}
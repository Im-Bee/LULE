/*
* Provides basic debug instrumentation:
* - Exceptions
* - Logger
* - Console output
**/

#ifndef LULE_DEBUG_H
#define LULE_DEBUG_H

#include "LULE_Multiplatform.h"

#ifdef _DEBUG
#	if _WIN32 || _WIN64
#		define L_CONSOLE_OUT_HELPER(str) (std::wstring(str) + L"\n")
#		define L_CONSOLE_OUT(str) WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), L_CONSOLE_OUT_HELPER(str).c_str(), static_cast<DWORD>(L_CONSOLE_OUT_HELPER(str).size()), NULL, NULL)
#	elif __GNUC__
#		define L_CONSOLE_OUT(str) 
#		error "L_CONSOLE_OUT not implemented on current system, L_CONSOLE_OUT macro has been left empty"
#	else
#		error "Couldn't detect the system, system specific debug not available."
#	endif
#else
#	define L_CONSOLE_OUT(str)
#endif // _DEBUG

#ifdef __cplusplus
#	include "Logger.hpp"
#else // C ---------------------------------------------------------------------
#endif // __cplusplus
#endif // !LULE_DEBUG_H

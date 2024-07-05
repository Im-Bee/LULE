/*
* Defines basic types used in the rest of the LULE.
* Defines limits.
* Defines system specfic macros:
*	- dynamic library export
* Abstracts out functionality of a window, so they are less dependent on the platform. 
**/

#ifndef LULE_MULTIPLATFORM_H
#define LULE_MULTIPLATFORM_H

#pragma region System specific macros
/*
* Dynamic library export */
#if _WIN32 || _WIN64
#	ifdef _LULE_EXPORT
#		define LULE_API __declspec(dllexport)
#	else
#		define LULE_API __declspec(dllimport)
#	endif // !_LUL_EXPORT

#	define	HInstance() GetModuleHandle(NULL)
#elif __GNUC__
#	define LULE_API 
#	error "LULE_API isn't implemented on current system"
#else
#	define LULE_API 
#	error "LULE_API isn't implemented on current system"
#endif // !_WIN32
#pragma endregion

#pragma region System includes
#if _WIN32 || _WIN64
#	ifndef WIN32_LEAN_AND_MEAN 
#		define WIN32_LEAN_AND_MEAN 
#	endif // !WIN32_LEAN_AND_MEAN 
#	include <Windows.h>
#elif __GNUC__
#else
#endif // !_WIN32

#include <string>
#pragma endregion

#include "Source/Multiplatform/Defs.h"

#ifdef __cplusplus

#	include "Source/Multiplatform/Exception.hpp"

#	include "Source/Utilities/LAllocator.hpp"
#	include "Source/Utilities/LPair.hpp"
#	include "Source/Utilities/LVector.hpp"
#	include "Source/Utilities/LTuple.hpp"

#	include "Source/Multiplatform/AppProperties.hpp"
#	include "Source/Multiplatform/Windows.hpp"
#	include "Source/Multiplatform/IApplication.hpp"
#else // C ---------------------------------------------------------------------
#endif // __cplusplus

#endif // !LULE_MULTIPLATFORM_H

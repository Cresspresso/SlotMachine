// ==========================
//    PROJECT INFO
// Title:	consolate
// Source:	consolate_pre.h
// Version:	2.0
// Date:	13/04/2018
// Author:	Elijah Shadbolt
// ==========================

#include <iostream>


// =================
//    MACRO FLAGS
// =================

/*#ifdef UNICODE

#ifndef CONSOLATE_UNICODE
#define CONSOLATE_UNICODE
#endif

#endif

#ifdef CONSOLATE_UNICODE_OFF
#undef CONSOLATE_UNICODE
#endif*/

#ifdef CONSOLATE_UNICODE
#undef CONSOLATE_UNICODE_OFF
#endif


// PREPROCESSED ONCE (as if #pragma once)
#ifndef CONSOLATE_PRE
#define CONSOLATE_PRE
namespace consolate
{
	// ====================
	//    Character Sets
	// ====================

#ifdef CONSOLATE_UNICODE

	typedef wchar_t tchar;
	//typedef std::wostream ostreamt;
	//typedef std::wistream istreamt;

//#define ccout (std::wcout)
//#define ccin (std::wcin)

#else

	typedef char tchar;
	//typedef std::ostream ostreamt;
	//typedef std::istream istreamt;

//#define ccout (std::cout)
//#define ccin (std::cin)

#endif

}
#endif

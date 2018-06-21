// ==========================
//    PROJECT INFO
// Title:	consolate
// Source:	consolate_ColorTable.h
// Version:	2.0
// Date:	13/04/2018
// Author:	Elijah Shadbolt
// ==========================

#pragma once

#include <windows.h>
#include <array>

namespace consolate
{
	typedef std::array<COLORREF, 16> ColorTable;

	// ==========================
	//    Color Scheme Library
	// ==========================

	namespace ColorSchemes
	{
		// Turns an array of 16 COLORREFs into a ColorTable.
		ColorTable CTFromArray(const COLORREF table[16]);



		// Grayscale color scheme ranging from Black (Color_0) to White (Color_15).
		extern const ColorTable Grayscale;

		// Old Windows color scheme.
		extern const ColorTable Basic;

		// A vibrant color scheme.
		extern const ColorTable Consatisfy;
	}
}

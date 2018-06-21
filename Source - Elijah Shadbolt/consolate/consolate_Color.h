// ==========================
//    PROJECT INFO
// Title:	consolate
// Source:	consolate_Color.h
// Version:	2.0
// Date:	13/04/2018
// Author:	Elijah Shadbolt
// ==========================

#pragma once

#include <windows.h>

namespace consolate
{
	// Value type representing a foreground and background color for console text.
	typedef WORD Color;

	// Some useful values for specifying console text colors.
	// Combine foreground and background like so:
	//	(Color_White | ColorBG_Blue)
	// Color_... values have a Black background by default.
	// ColorBG_... values have a Black foreground by default.
	enum ColorsEnum
	{
		Color_0 = 0x00,
		Color_1 = 0x01,
		Color_2 = 0x02,
		Color_3 = 0x03,
		Color_4 = 0x04,
		Color_5 = 0x05,
		Color_6 = 0x06,
		Color_7 = 0x07,
		Color_8 = 0x08,
		Color_9 = 0x09,
		Color_10 = 0x0A,
		Color_11 = 0x0B,
		Color_12 = 0x0C,
		Color_13 = 0x0D,
		Color_14 = 0x0E,
		Color_15 = 0x0F,

		ColorBG_0 = 0x00,
		ColorBG_1 = 0x10,
		ColorBG_2 = 0x20,
		ColorBG_3 = 0x30,
		ColorBG_4 = 0x40,
		ColorBG_5 = 0x50,
		ColorBG_6 = 0x60,
		ColorBG_7 = 0x70,
		ColorBG_8 = 0x80,
		ColorBG_9 = 0x90,
		ColorBG_10 = 0xA0,
		ColorBG_11 = 0xB0,
		ColorBG_12 = 0xC0,
		ColorBG_13 = 0xD0,
		ColorBG_14 = 0xE0,
		ColorBG_15 = 0xF0,

		// Corresponding Colors when using Default ColorTable

		Color_Black = 0x00,			// Black (Foreground)
		Color_DarkBlue = 0x01,		// Dark Blue (Foreground)
		Color_DarkGreen = 0x02,		// Dark Green (Foreground)
		Color_DarkCyan = 0x03,		// Dark Cyan (Foreground)
		Color_DarkRed = 0x04,		// Dark Red (Foreground)
		Color_DarkMagenta = 0x05,	// Dark Magenta (Foreground)
		Color_DarkYellow = 0x06,	// Dark Yellow (Foreground)
		Color_Gray = 0x07,			// Light Gray (Foreground)
		Color_DarkGray = 0x08,		// Dark Gray (Foreground)
		Color_Blue = 0x09,			// Blue (Foreground)
		Color_Green = 0x0A,			// Green (Foreground)
		Color_Cyan = 0x0B,			// Cyan (Foreground)
		Color_Red = 0x0C,			// Red (Foreground)
		Color_Magenta = 0x0D,		// Magenta (Foreground)
		Color_Yellow = 0x0E,		// Yellow (Foreground)
		Color_White = 0x0F,			// White (Foreground)

		ColorBG_Black = 0x00,		// Black (Background)
		ColorBG_DarkBlue = 0x10,	// Dark Blue (Background)
		ColorBG_DarkGreen = 0x20,	// Dark Green (Background)
		ColorBG_DarkCyan = 0x30,	// Dark Cyan (Background)
		ColorBG_DarkRed = 0x40,		// Dark Red (Background)
		ColorBG_DarkMagenta = 0x50,	// Dark Magenta (Background)
		ColorBG_DarkYellow = 0x60,	// Dark Yellow (Background)
		ColorBG_Gray = 0x70,		// Light Gray (Background)
		ColorBG_DarkGray = 0x80,	// Dark Gray (Background)
		ColorBG_Blue = 0x90,		// Blue (Background)
		ColorBG_Green = 0xA0,		// Green (Background)
		ColorBG_Cyan = 0xB0,		// Cyan (Background)
		ColorBG_Red = 0xC0,			// Red (Background)
		ColorBG_Magenta = 0xD0,		// Magenta (Background)
		ColorBG_Yellow = 0xE0,		// Yellow (Background)
		ColorBG_White = 0xF0,		// White (Background)

		Color_Default = Color_Gray	// Default Color of Windows Console
	};
}

// ==========================
//    PROJECT INFO
// Title:	consolate
// Source:	consolate_ColorTable.cpp
// Version:	2.0
// Date:	13/04/2018
// Author:	Elijah Shadbolt
// ==========================

#include "consolate_ColorTable.h"
#include <windows.h>
#include <memory>
#include <array>

namespace consolate
{
	namespace ColorSchemes
	{
		ColorTable CTFromArray(const COLORREF table[16])
		{
			ColorTable retval;
			//std::copy(std::begin(table), std::end(table), std::begin(retval));
			for (UINT i = 0; i < 16; ++i)
			{
				retval[i] = table[i];
			}
			return retval;
		}



		const ColorTable Grayscale
		{
			RGB(0x00, 0x00, 0x00),
			RGB(0x11, 0x11, 0x11),
			RGB(0x22, 0x22, 0x22),
			RGB(0x33, 0x33, 0x33),
			RGB(0x44, 0x44, 0x44),
			RGB(0x55, 0x55, 0x55),
			RGB(0x66, 0x66, 0x66),
			RGB(0x77, 0x77, 0x77),
			RGB(0x88, 0x88, 0x88),
			RGB(0x99, 0x99, 0x99),
			RGB(0xaa, 0xaa, 0xaa),
			RGB(0xbb, 0xbb, 0xbb),
			RGB(0xcc, 0xcc, 0xcc),
			RGB(0xdd, 0xdd, 0xdd),
			RGB(0xee, 0xee, 0xee),
			RGB(0xff, 0xff, 0xff),
		};

		const ColorTable Basic
		{
			RGB(0, 0, 0),
			RGB(0, 0, 128),
			RGB(0, 128, 0),
			RGB(0, 128, 128),
			RGB(128, 0, 0),
			RGB(128, 0, 128),
			RGB(128, 128, 0),
			RGB(192, 192, 192),
			RGB(128, 128, 128),
			RGB(0, 0, 255),
			RGB(0, 255, 0),
			RGB(0, 255, 255),
			RGB(255, 0, 0),
			RGB(255, 0, 255),
			RGB(255, 255, 0),
			RGB(255, 255, 255),
		};

		const ColorTable Consatisfy
		{
			RGB(0, 0, 0),
			RGB(0, 0, 230),
			RGB(0, 160, 0),
			RGB(0, 140, 140),
			RGB(200, 0, 0),
			RGB(170, 0, 170),
			RGB(150, 150, 0),
			RGB(192, 192, 192),
			RGB(128, 128, 128),
			RGB(100, 100, 255),
			RGB(0, 255, 0),
			RGB(0, 255, 255),
			RGB(255, 50, 50),
			RGB(255, 0, 255),
			RGB(255, 255, 0),
			RGB(255, 255, 255),
		};
	}
}

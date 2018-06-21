// ==========================
//    PROJECT INFO
// Title:	consolate
// Source:	consolate_PanelStyle.h
// Version:	2.0
// Date:	13/04/2018
// Author:	Elijah Shadbolt
// ==========================

#pragma once

#include "consolate_pre.h"
#include "consolate_Color.h"

namespace consolate
{
	// Character set for styling panels in consolate.
	struct PanelStyle
	{
		// ===============
		//    Variables
		// ===============

	public:

		tchar top_left;
		tchar top_right;
		tchar bottom_left;
		tchar bottom_right;

		tchar top;
		tchar bottom;
		tchar left;
		tchar right;

		tchar top_T;
		tchar bottom_T;
		tchar left_T;
		tchar right_T;
		tchar cross;

		tchar fill = ' ';

		Color outlineColor = Color_Gray;
		Color fillColor = Color_Black;


		// ==================
		//    Constructors
		// ==================

	public:

		// Default Constructor
		PanelStyle(tchar fill = ' ', Color outlineColor = Color_Gray, Color fillColor = Color_Black);

		// Partial Constructor
		PanelStyle(
			tchar top_left, tchar top_right, tchar bottom_left, tchar bottom_right,
			tchar top, tchar bottom, tchar left, tchar right,
			tchar fill = ' ', Color outlineColor = Color_Gray, Color fillColor = Color_Black
		);

		// Full Constructor
		PanelStyle(
			tchar top_left, tchar top_right, tchar bottom_left, tchar bottom_right,
			tchar top, tchar bottom, tchar left, tchar right,
			tchar top_T, tchar bottom_T, tchar left_T, tchar right_T,
			tchar cross,
			tchar fill = ' ', Color outlineColor = Color_Gray, Color fillColor = Color_Black
		);

		// Copy Constructor
		PanelStyle(const PanelStyle& other);
		// Move Constructor
		PanelStyle(PanelStyle&& rvalue);

		// Copy Assignment Operator
		PanelStyle& operator=(const PanelStyle& other);
		// Move Assignment Operator
		PanelStyle& operator=(PanelStyle&& rvalue);


		// ==========================
		//    CONST Default Values
		// ==========================

	public:

		// Panel style with single-lined border.
		static const PanelStyle Default;

		// Panel style with double-lined border.
		static const PanelStyle Double;
	};
}

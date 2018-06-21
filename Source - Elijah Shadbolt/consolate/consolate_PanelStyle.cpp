// ==========================
//    PROJECT INFO
// Title:	consolate
// Source:	consolate_PanelStyle.cpp
// Version:	2.0
// Date:	13/04/2018
// Author:	Elijah Shadbolt
// ==========================

#include "consolate_PanelStyle.h"
#include <memory>

namespace consolate
{
	// Default Constructor
	PanelStyle::PanelStyle(tchar fill, Color outlineColor, Color fillColor)
		:
		fill(fill),
		outlineColor(outlineColor),
		fillColor(fillColor)
		// TODO fill other fields with characters from PanelStyle::Default.
	{
	}

	// Partial Constructor
	PanelStyle::PanelStyle(
		tchar top_left, tchar top_right, tchar bottom_left, tchar bottom_right,
		tchar top, tchar bottom, tchar left, tchar right,
		tchar fill, Color outlineColor, Color fillColor)
		:
		top_left(top_left),
		top_right(top_right),
		bottom_left(bottom_left),
		bottom_right(bottom_right),

		top(top),
		bottom(bottom),
		left(left),
		right(right),

		fill(fill),
		outlineColor(outlineColor),
		fillColor(fillColor)
		// TODO fill other fields with characters from PanelStyle::Default.
	{
	}

	// Full Constructor
	PanelStyle::PanelStyle(
		tchar top_left, tchar top_right, tchar bottom_left, tchar bottom_right,
		tchar top, tchar bottom, tchar left, tchar right,
		tchar top_T, tchar bottom_T, tchar left_T, tchar right_T,
		tchar cross,
		tchar fill, Color outlineColor, Color fillColor)
		:
		top_left(top_left),
		top_right(top_right),
		bottom_left(bottom_left),
		bottom_right(bottom_right),

		top(top),
		bottom(bottom),
		left(left),
		right(right),

		top_T(top_T),
		bottom_T(bottom_T),
		left_T(left_T),
		right_T(right_T),

		cross(cross),

		fill(fill),
		outlineColor(outlineColor),
		fillColor(fillColor)
	{
	}


	// --------------------
	//    Copying/Moving
	// --------------------

	// Copy Constructor
	PanelStyle::PanelStyle(const PanelStyle& other)
		:
		top_left(other.top_left),
		top_right(other.top_right),
		bottom_left(other.bottom_left),
		bottom_right(other.bottom_right),

		top(other.top),
		bottom(other.bottom),
		left(other.left),
		right(other.right),

		top_T(other.top_T),
		bottom_T(other.bottom_T),
		left_T(other.left_T),
		right_T(other.right_T),

		cross(other.cross),

		fill(other.fill),
		outlineColor(other.outlineColor),
		fillColor(other.fillColor)
	{
	}

	// Move Constructor
	PanelStyle::PanelStyle(PanelStyle&& rvalue)
		:
		top_left(std::move(rvalue.top_left)),
		top_right(std::move(rvalue.top_right)),
		bottom_left(std::move(rvalue.bottom_left)),
		bottom_right(std::move(rvalue.bottom_right)),

		top(std::move(rvalue.top)),
		bottom(std::move(rvalue.bottom)),
		left(std::move(rvalue.left)),
		right(std::move(rvalue.right)),

		top_T(std::move(rvalue.top_T)),
		bottom_T(std::move(rvalue.bottom_T)),
		left_T(std::move(rvalue.left_T)),
		right_T(std::move(rvalue.right_T)),

		cross(std::move(rvalue.cross)),

		fill(std::move(rvalue.fill)),
		outlineColor(std::move(rvalue.outlineColor)),
		fillColor(std::move(rvalue.fillColor))
	{
	}

	// Copy Assignment Operator
	PanelStyle& PanelStyle::operator=(const PanelStyle& other)
	{
		top_left = other.top_left;
		top_right = other.top_right;
		bottom_left = other.bottom_left;
		bottom_right = other.bottom_right;

		top = other.top;
		bottom = other.bottom;
		left = other.left;
		right = other.right;

		top_T = other.top_T;
		bottom_T = other.bottom_T;
		left_T = other.left_T;
		right_T = other.right_T;

		cross = other.cross;

		fill = other.fill;
		outlineColor = other.outlineColor;
		fillColor = other.fillColor;

		return *this;
	}

	// Move Assignment Operator
	PanelStyle& PanelStyle::operator=(PanelStyle&& rvalue)
	{
		top_left = std::move(rvalue.top_left);
		top_right = std::move(rvalue.top_right);
		bottom_left = std::move(rvalue.bottom_left);
		bottom_right = std::move(rvalue.bottom_right);

		top = std::move(rvalue.top);
		bottom = std::move(rvalue.bottom);
		left = std::move(rvalue.left);
		right = std::move(rvalue.right);

		top_T = std::move(rvalue.top_T);
		bottom_T = std::move(rvalue.bottom_T);
		left_T = std::move(rvalue.left_T);
		right_T = std::move(rvalue.right_T);

		cross = std::move(rvalue.cross);

		fill = std::move(rvalue.fill);
		outlineColor = std::move(rvalue.outlineColor);
		fillColor = std::move(rvalue.fillColor);

		return *this;
	}


	// ==========================
	//    CONST Default Values
	// ==========================

#ifdef CONSOLATE_UNICODE
	const PanelStyle PanelStyle::Default(L'┌', L'┐', L'└', L'┘', L'─', L'─', L'│', L'│', L'┬', L'┴', L'├', L'┤', L'┼');
	const PanelStyle PanelStyle::Double	(L'╔', L'╗', L'╚', L'╝', L'═', L'═', L'║', L'║', L'╦', L'╩', L'╠', L'╣', L'╬');
#else
	const PanelStyle PanelStyle::Default(-38, -65, -64, -39, -60, -60, -77, -77, -62, -63, -61, -76, -59);
	const PanelStyle PanelStyle::Double	(-55, -69, -56, -68, -51, -51, -70, -70, -53, -54, -52, -71, -50);
#endif
}

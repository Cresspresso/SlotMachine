// ==========================
//    PROJECT INFO
// Title:	consolate
// Source:	consolate.cpp
// Version:	2.0
// Date:	13/04/2018
// Author:	Elijah Shadbolt
// ==========================

#include "consolate.h"

#include <fcntl.h>
#include <io.h>
#include <stdio.h>

namespace consolate
{
	// ==================
	//    Constructors
	// ==================

	Consolater::Consolater(
		HANDLE const hstdout,
		HANDLE const hstdin
	) :
		hstdout(hstdout),
		hstdin(hstdin),
		originalInfo{ sizeof(CONSOLE_SCREEN_BUFFER_INFOEX) }
	{
		// Cache original console settings.
		if (GetConsoleScreenBufferInfoEx(hstdout, &originalInfo))
		{
			// Initialize DrawColor
			drawColor = originalInfo.wAttributes;
		}
		else
		{
			//ccout << "Error calling GetConsoleScreenBufferInfoEx: " << GetLastError() << std::endl;
			drawColor = Color_Default;
		}

		// Enable Unicode characters.
#ifdef CONSOLATE_UNICODE
		if (hstdout == GetStdHandle(STD_OUTPUT_HANDLE))
		{
			_setmode(_fileno(stdout), _O_U16TEXT);
		}
#endif

	}


	Consolater::~Consolater()
	{
		Reset();
	}


	// =============
	//    Methods
	// =============

	CONSOLE_SCREEN_BUFFER_INFOEX Consolater::GetBufferInfo() const
	{
		CONSOLE_SCREEN_BUFFER_INFOEX bufferInfo = { sizeof(CONSOLE_SCREEN_BUFFER_INFOEX) };
		if (!GetConsoleScreenBufferInfoEx(hstdout, &bufferInfo))
		{
#ifdef CONSOLATE_UNICODE
			std::wcout << L"Error calling GetConsoleScreenBufferInfoEx: " << GetLastError() << std::endl;
#else
			std::cout << "Error calling GetConsoleScreenBufferInfoEx: " << GetLastError() << std::endl;
#endif
		}
		return bufferInfo;
	}

	void Consolater::SetBufferInfo(CONSOLE_SCREEN_BUFFER_INFOEX bufferInfo)
	{
		// counter the bug of window getting smaller
		bufferInfo.srWindow.Bottom += 1;

		if (!SetConsoleScreenBufferInfoEx(hstdout, &bufferInfo))
		{
#ifdef CONSOLATE_UNICODE
			std::wcout << L"Error calling SetConsoleScreenBufferInfoEx: " << GetLastError() << std::endl;
#else
			std::cout << "Error calling SetConsoleScreenBufferInfoEx: " << GetLastError() << std::endl;
#endif
		}
	}


	// -----------
	//    Reset
	// -----------

	void Consolater::Reset()
	{
		// Get state of the console
		auto bufferInfo = GetBufferInfo();

		// Set cursor position to bottom left of screen
		//SetCursorPosition({ 0, bufferInfo.srWindow.Bottom });


		// -- Restore original settings --

		// Restore color table

		//std::copy(std::begin(originalInfo.ColorTable), std::end(originalInfo.ColorTable), std::begin(bufferInfo.ColorTable));
		for (UINT i = 0; i < 16; ++i)
		{
			bufferInfo.ColorTable[i] = originalInfo.ColorTable[i];
		}
		SetBufferInfo(bufferInfo);

		// Restore text color
		SetConsoleTextAttribute(hstdout, originalInfo.wAttributes);
	}


	// ------------
	//    Colors
	// ------------

	void Consolater::SetColor(const Color foreground, const Color background)
	{
		SetColor((foreground & 0x0f) | ((background << 4) & 0xf0));
	}

	void Consolater::SetForegroundColor(const Color color)
	{
		SetColor((GetColor() & 0xf0) | (color & 0x0f));
	}

	void Consolater::SetBackgroundColorBG(const Color color)
	{
		SetColor((GetColor() & 0x0f) | (color & 0xf0));
	}

	void Consolater::SetBackgroundColor(const Color color)
	{
		SetColor((GetColor() & 0x0f) | ((color << 4) & 0xf0));
	}


	// -------------------
	//    Color Schemes
	// -------------------

	void Consolater::SetColorTable(const ColorTable& colorTable)
	{
		auto bufferInfo = GetBufferInfo();

		//std::copy(std::begin(colorTable), std::end(colorTable), std::begin(bufferInfo.ColorTable));
		for (UINT i = 0; i < 16; ++i)
		{
			bufferInfo.ColorTable[i] = colorTable[i];
		}

		SetBufferInfo(bufferInfo);
	}

	ColorTable Consolater::GetColorTable()
	{
		auto bufferInfo = GetBufferInfo();

		ColorTable result;
		//std::copy(std::begin(bufferInfo.ColorTable), std::end(bufferInfo.ColorTable), std::begin(result));
		for (UINT i = 0; i < 16; ++i)
		{
			result[i] = bufferInfo.ColorTable[i];
		}
		return result;
	}


	// -------------
	//    Drawing
	// -------------

	void Consolater::DrawRow(const COORD position, const DWORD length)
	{
		if (length <= 0)
			return;

		DWORD written;

#ifdef CONSOLATE_UNICODE
		FillConsoleOutputCharacterW(hstdout, drawChar, length, position, &written);
#else
		FillConsoleOutputCharacterA(hstdout, drawChar, length, position, &written);
#endif

		FillConsoleOutputAttribute(hstdout, drawColor, length, position, &written);
	}

	// --- Clearing ---

	void Consolater::ClearFill()
	{
		auto bufferInfo = GetBufferInfo();

		DrawRow({ 0, 0 }, bufferInfo.dwSize.X * bufferInfo.dwSize.Y);

		SetCursorPosition({ 0, 0 });
	}

	// --- Rectangles ---

	void Consolater::DrawRect(COORD min, const COORD max)
	{
		AssertMinMaxValid(min, max);

		DWORD length = max.X - min.X + 1;
		for (; min.Y <= max.Y; ++min.Y)
		{
			DrawRow(min, length);
		}
	}

	void Consolater::DrawRectInner(COORD min, COORD max)
	{
		min = { min.X + 1, min.Y + 1 };
		max = { max.X - 1, max.Y - 1 };
		if (min.X <= max.X && min.Y <= max.Y)
		{
			DrawRect(min, max);
		}
	}

	void Consolater::DrawRectOutline(const COORD min, const COORD max)
	{
		AssertMinMaxValid(min, max);

		DWORD length = max.X - min.X + 1;
		DrawRow(min, length);
		DrawRow({ min.X, max.Y }, length);
		for (short y = min.Y; y < max.Y; ++y)
		{
			DrawPoint({ min.X, y });
			DrawPoint({ max.X, y });
		}
	}

	void Consolater::DrawRectWithOutline(const COORD min, const COORD max,
		const Color fillColor,
		const Color outlineColor,
		const tchar fillChar,
		const tchar outlineChar)
	{
		AssertMinMaxValid(min, max);

		// Draw outline
		SetColor(outlineColor);
		SetDrawChar(outlineChar);
		DrawRectOutline(min, max);

		// Draw fill
		SetColor(fillColor);
		SetDrawChar(fillChar);
		DrawRectInner(min, max);
	}

	// --- Panels ---

	void Consolater::DrawPanelOutlineOnly(const COORD min, const COORD max, const PanelStyle& style)
	{
		AssertMinMaxValid(min, max);

		// Corners

		SetDrawChar(style.top_left);
		DrawPoint(min);

		SetDrawChar(style.bottom_left);
		DrawPoint({ min.X, max.Y });

		SetDrawChar(style.top_right);
		DrawPoint({ max.X, min.Y });

		SetDrawChar(style.bottom_right);
		DrawPoint(max);

		// Horizontal Edges

		DWORD length = max.X - min.X + 1 - 2;

		SetDrawChar(style.top);
		DrawRow({ min.X + 1, min.Y }, length);

		SetDrawChar(style.bottom);
		DrawRow({ min.X + 1, max.Y }, length);

		// Vertical Edges

		for (short y = min.Y + 1; y < max.Y; ++y)
		{
			SetDrawChar(style.left);
			DrawPoint({ min.X, y });

			SetDrawChar(style.right);
			DrawPoint({ max.X, y });
		}
	}

	void Consolater::DrawPanel(const COORD min, const COORD max,
		const PanelStyle& style)
	{
		AssertMinMaxValid(min, max);

		// Draw outline
		SetColor(style.outlineColor);
		DrawPanelOutlineOnly(min, max, style);

		// Draw fill
		SetColor(style.fillColor);
		SetDrawChar(style.fill);
		DrawRectInner(min, max);
	}


#ifndef CONSOLATE_DEFAULT_OFF
	// ===================
	//    Main Instance
	// ===================

	// The default Consolater which uses STD_OUTPUT_HANDLE and STD_INPUT_HANDLE.
	// This instance should not be overwritten.
	Consolater Consolate = Consolater();
#endif
}

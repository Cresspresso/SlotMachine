// ==========================
//    PROJECT INFO
// Title:	consolate
// Source:	consolate.h
// Version:	2.0
// Date:	13/04/2018
// Author:	Elijah Shadbolt
// ==========================

#pragma once

#define NOMINMAX
#include <windows.h>
#include <stdexcept>

#include "consolate_pre.h"
#include "consolate_Color.h"
#include "consolate_PanelStyle.h"
#include "consolate_ColorTable.h"

namespace consolate
{
	// Developer-friendly interface for the Windows Console Application.
	class Consolater
	{
		// ========================
		//    Constant Variables
		// ========================

	private:

		const HANDLE hstdin; // Standard input handle.
		const HANDLE hstdout; // Standard output handle (console).

		// Original state of the console before consolate took over.
		/*const*/ CONSOLE_SCREEN_BUFFER_INFOEX originalInfo;


		// ===============
		//    Variables
		// ===============

		// -----------------------
		//    Original Settings
		// -----------------------

	public:

		// Gets the original color of the console.
		inline Color OriginalColor() const
		{
			return originalInfo.wAttributes;
		}

		// Gets the original color scheme of the console.
		inline ColorTable OriginalColorTable() const
		{
			return ColorSchemes::CTFromArray(originalInfo.ColorTable);
		}

		// Gets the srWindow rect of the console window.
		inline SMALL_RECT GetWindowRect() const
		{
			auto bufferInfo = GetBufferInfo();
			return bufferInfo.srWindow;
		}

		// Gets the size (in character width/height) of the console window.
		inline COORD GetWindowSize() const
		{
			auto bufferInfo = GetBufferInfo();
			return {
				bufferInfo.srWindow.Right - bufferInfo.srWindow.Left,
				bufferInfo.srWindow.Bottom - bufferInfo.srWindow.Top
			};
		}

		// --------------
		//    DrawColor
		// --------------

	private:

		// Color for new characters/shapes.
		WORD drawColor;

	public:

		// The current color of the console text (foreground and background).
		inline WORD GetColor() const
		{
			return drawColor;
		}


		// --------------
		//    DrawChar
		// --------------

	private:

		// Fill character for new shapes.
		tchar drawChar = ' ';

	public:

		// Get the Fill character for new shapes.
		inline tchar GetDrawChar() const
		{
			return drawChar;
		}

		// Set the Fill character for new shapes.
		inline void SetDrawChar(const tchar fill)
		{
			drawChar = fill;
		}


		// -------------
		//    Streams
		// -------------
		/*
	private:

		// Output stream
		ostreamt* outs = &ccout;

		// Inupt stream
		istreamt* ins = &ccin;

	public:

		// Gets the output stream
		inline ostreamt& out() const
		{
			return *outs;
		}

		// Gets the input stream
		inline istreamt& in() const
		{
			return *ins;
		}

		// Sets the output stream
		inline void out(ostreamt& newValue)
		{
			outs = &newValue;
		}

		// Sets the input stream
		inline void in(istreamt& newValue)
		{
			ins = &newValue;
		}
		*/

		// ==================
		//    Constructors
		// ==================

	public:

		// Creates a new Consolater instance using the input/output handles of the default console window.
		Consolater(
			HANDLE const hstdout = GetStdHandle(STD_OUTPUT_HANDLE),
			HANDLE const hstdin = GetStdHandle(STD_INPUT_HANDLE)//,
			//ostreamt& outstream = ccout,
			//istreamt& instream = ccin
		);

		// Destructor for cleaning up and restoring original console settings.
		~Consolater();


		// =============
		//    Methods
		// =============

	private:

		// Gets the console screen buffer info-extended.
		CONSOLE_SCREEN_BUFFER_INFOEX GetBufferInfo() const;

		// Sets the console screen buffer info-extended.
		void SetBufferInfo(CONSOLE_SCREEN_BUFFER_INFOEX bufferInfo);


		// -----------
		//    Reset
		// -----------

	public:

		// Cleans itself up and restores original console settings.
		void Reset();


		// ------------
		//    Colors
		// ------------

	public:

		// Sets the color of the console text (foreground and background).
		inline void SetColor(const Color color)
		{
			drawColor = color;
			SetConsoleTextAttribute(hstdout, drawColor);
		}

		// Sets the color of the console text. Both must be Color_... values.
		void SetColor(const Color foreground, const Color background);

	public:

		// Sets the foreground color of the console text.
		void SetForegroundColor(const Color color);

		// Sets the background color of the console text, using a ColorBG_... value.
		void SetBackgroundColorBG(const Color color);

		// Sets the background color of the console text, using a Color_... value.
		void SetBackgroundColor(const Color color);

		// -----------------
		//    Color Table
		// -----------------
		
	public:

		// Sets the colour scheme of the console window.
		void SetColorTable(const ColorTable& colorTable);

		// Gets the colour scheme of the console window.
		ColorTable GetColorTable();


		// ------------
		//    Cursor
		// ------------

	public:

		// Sets the cursor position.
		inline void SetCursorPosition(const COORD position)
		{
			SetConsoleCursorPosition(hstdout, position);
		}

		inline COORD GetCursorPosition() const
		{
			auto bufferInfo = GetBufferInfo();
			return bufferInfo.dwCursorPosition;
		}


		// -------------
		//    Drawing
		// -------------

	private:

		inline static void AssertMinMaxValid(const COORD min, const COORD max)
		{
			if (min.X > max.X)
				throw std::logic_error("min.X > max.X");
			if (min.Y > max.Y)
				throw std::logic_error("min.Y > max.Y");
		}

	public:

		// Draws a horizontal row of characters, extending from position to the right.
		void DrawRow(const COORD position, const DWORD length);

		// Draws a horizontal row of characters, with color, extending from position to the right.
		inline void DrawRow(const COORD position, const DWORD length,
			const Color color,
			const char fillChar = ' ')
		{
			SetColor(color);
			SetDrawChar(fillChar);
			DrawRow(position, length);
		}

		// Draws a single character at the position.
		inline void DrawPoint(const COORD position)
		{
			DrawRow(position, 1);
		}

		// Draws a single character at the position, with color.
		inline void DrawPoint(const COORD position,
			const Color color,
			const char fillChar = ' ')
		{
			SetColor(color);
			SetDrawChar(fillChar);
			DrawPoint(position);
		}


		// --- Clearing ---
	public:

		// Clears the console screen, using Fill and Color.
		void ClearFill();

		// Clears the console screen.
		inline void Clear()
		{
			SetColor(Color_Default);
			SetDrawChar(' ');
			ClearFill();
		}


		// --- Rectangles ---

	public:

		// Draws a rectangle.
		void DrawRect(COORD min, const COORD max);

		// Draws the filled inside of an outlined rectangle.
		// If min > max, draws nothing.
		void DrawRectInner(COORD min, COORD max);

		// Draws the outline of a rectangle.
		void DrawRectOutline(const COORD min, const COORD max);

		// Draws a rectangle with an outline.
		void DrawRectWithOutline(const COORD min, const COORD max,
			const Color fillColor = Color_Default,
			const Color outlineColor = Color_Default,
			const tchar fillChar = ' ',
			const tchar outlineChar = ' ');


		// Draws a rectangle.
		inline void DrawRect(const COORD min, const COORD max,
			const Color fillColor,
			const tchar fillChar = ' ')
		{
			SetColor(fillColor);
			SetDrawChar(fillChar);
			DrawRect(min, max);
		}

		// Draws the outline of a rectangle.
		inline void DrawRectOutline(const COORD min, const COORD max,
			const Color outlineColor,
			const tchar outlineChar = ' ')
		{
			SetColor(outlineColor);
			SetDrawChar(outlineChar);
			DrawRectOutline(min, max);
		}


		// --- Panels ---
	public:

		// Draws a styled outline of a rectangle.
		void DrawPanelOutlineOnly(const COORD min, const COORD max,
			const PanelStyle& style = PanelStyle::Default);

		// Draws a styled rectangle.
		void DrawPanel(const COORD min, const COORD max,
			const PanelStyle& style = PanelStyle::Default);


		// Draws a styled outline of a rectangle, with color.
		inline void DrawPanelOutline(const COORD min, const COORD max,
			const PanelStyle& style = PanelStyle::Default)
		{
			SetColor(style.outlineColor);
			DrawPanelOutlineOnly(min, max, style);
		}

	};


#ifndef CONSOLATE_DEFAULT_OFF
	// ===================
	//    Main Instance
	// ===================

	// The default Consolater which uses STD_OUTPUT_HANDLE and STD_INPUT_HANDLE.
	// This instance should not be overwritten.
	extern Consolater Consolate;
#endif
}

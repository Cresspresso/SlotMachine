// ==========================
//    PROJECT INFO
// Title:	consolate_tests
// Source:	main.cpp
// Version:	2.0
// Date:	13/04/2018
// Author:	Elijah Shadbolt
// ==========================

#include <consolate.h>

void Wait()
{
	using namespace consolate;
	using std::cin;

	Consolate.SetColor(Color_Default);

	//cin.get();
	cin.clear();
	cin.ignore();

	Consolate.SetCursorPosition({ 0, 0 });
}

void PrintLots()
{
	using namespace consolate;
	using std::endl;
	using std::cout;

	for (int i = 0; i < 40; ++i)
	{
		cout << i << '\n';
	}
	cout << endl;
}

void TestColors()
{
	using namespace consolate;
	using std::endl;
	using std::cout;

	cout << "Default Colour" << endl;

	for (WORD i = 0; i <= 0xff; ++i)
	{
		Consolate.SetColor(i);
		cout << (i % 10);
		if (i % 0x10 == 0xf)
			cout << endl;
	}

	Consolate.SetColor(Color_White | ColorBG_Black);
	cout << "White on Black" << std::endl;

	Consolate.SetColor(Color_Black | ColorBG_White);
	cout << "Black on White" << endl;

	Consolate.SetColor(Color_White | ColorBG_Blue);
	cout << "White on Blue" << endl;

	Consolate.SetColor(Color_Green);
	cout << "Green" << endl;

	Consolate.SetColor(Color_Red);
	cout << "Red" << endl;

	Consolate.SetColor(Color_Red, Color_Blue);
	cout << "Red on Blue" << endl;

	Consolate.SetForegroundColor(Color_Cyan);
	cout << "Cyan on Blue" << endl;

	Consolate.SetBackgroundColorBG(ColorBG_DarkRed);
	cout << "Cyan on Dark Red" << endl;

	Consolate.SetBackgroundColor(Color_Magenta);
	cout << "Cyan on Magenta" << endl;
}

void TestColorTable()
{
	using namespace consolate;

	Consolate.SetColorTable(consolate::ColorSchemes::Grayscale);
	Wait();
	Consolate.SetColorTable(consolate::ColorSchemes::Basic);
	Wait();
	Consolate.SetColorTable(consolate::ColorSchemes::Consatisfy);
	Wait();
	Consolate.SetColorTable(Consolate.OriginalColorTable());
}

void DrawRects()
{
	using namespace consolate;

	// Draw Row
	Consolate.SetColor(Color_Cyan);
	Consolate.SetDrawChar('~');
	Consolate.DrawRow({ 3, 3 }, 5);

	// Fill Rect
	Consolate.SetColor(Color_Red);
	Consolate.SetDrawChar('+');
	Consolate.DrawRect({ 5, 5 }, { 20, 10 });

	// Outline Rect
	Consolate.SetColor(Color_Green);
	Consolate.SetDrawChar('-');
	Consolate.DrawRectOutline({ 15, 15 }, { 30, 20 });

	// Draw Rect
	Consolate.DrawRectWithOutline({ 24, 0 }, { 32, 5 }, Color_Yellow, Color_Blue, '~', '0');
}

void DrawPanels()
{
	using namespace consolate;

	// Custom
	PanelStyle temp = PanelStyle('a', 'b', 'c', 'd', 'e', 'f', 'g', 'h');
	Consolate.DrawPanelOutlineOnly({ 5, 1 }, { 20, 8 }, temp);

	// Single
	Consolate.DrawPanelOutlineOnly({ 5, 11 }, { 20, 18 });

	// Double
	Consolate.DrawPanelOutlineOnly({ 5, 21 }, { 20, 28 }, PanelStyle::Double);


	// Overlapping
	Consolate.SetColor(Color_Blue);
	Consolate.DrawPanelOutlineOnly({ 25, 5 }, { 35, 10 });
	Consolate.DrawPanelOutlineOnly({ 30, 7 }, { 40, 13 });

	// Custom Style based on Double
	PanelStyle style = PanelStyle::Double;
	style.fillColor = Color_Green | ColorBG_DarkGreen;
	style.outlineColor = Color_Red;
	style.fill = 'H';
	style.top_left = style.cross;
	style.top_right = style.cross;
	style.bottom_left = style.cross;
	style.bottom_right = style.cross;
	Consolate.DrawPanel({ 25, 15 }, { 35, 20 }, style);
}

int main()
{
	using namespace consolate;

	TestColors();

	Wait();

	TestColorTable();

	Wait();

	Consolate.Clear();
	DrawRects();

	Wait();

	PrintLots();

	Wait();

	Consolate.Clear();
	DrawPanels();

	Wait();

	PrintLots();

	//Wait();

	return 0;
}

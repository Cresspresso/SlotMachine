// ==========================
//    PROJECT INFO
// Title:	SlotMachine
// Source:	main.cpp
// Version:	2.0
// Date:	13/04/2018
// Author:	Elijah Shadbolt
// ==========================

#include "main.h"

namespace SlotMachine
{
	// ===============
	//    Functions
	// ===============


	// ============================================== //

	// Wraps around a value if it is smaller than 0 or larger than or equal to length.
	inline int RepeatInt(int value, int length)
	{
		return (value % length) + (value % length < 0 ? length : 0);
	}

	// Wraps around a value if it is smaller than min or larger than max.
	inline int RepeatInt(int value, int min, int max)
	{
		return RepeatInt(value - min, max + 1 - min) + min;
	}

	// ============================================== //

	// Clears the cin input stream.
	void ClearInputStream()
	{
		cin.clear();
		cin.ignore();
	}

	// ============================================== //



	// -----------------------------
	//    ReadValue	(and related)
	// -----------------------------

	// ============================================== //
#pragma region ReadCin

	// Prompts for and reads input from the cin stream.
	template<class T = string>
	void ReadCin(
		T& out,
		const COORD inputPos /**  = Consolate.GetCursorPosition()  **/,
		const string& promptMsg = ""
	)
	{
		Consolate.SetCursorPosition(inputPos);
		Consolate.SetColor(PROMPT_COLOR);
		TextAnim(promptMsg);
		Consolate.SetColor(INPUT_COLOR);
		cin >> out;
	}

	// Prompts for and reads input from the cin stream.
	// [default inputPos]
	template<class T = string>
	inline void ReadCin(
		T& out
	)
	{
		ReadCin(out, Consolate.GetCursorPosition());
	}

#pragma endregion
	// ============================================== //
#pragma region ReadValue

	// Asks the user to input a value.
	// If the input fails or the inputValidator returns false, asks again.
	template<class T>
	T ReadValue(
		const function<bool(const T& value)> inputValidator,		/**  = [](const T&){return true;}  **/
		const function<string(const T& value)> warningMsgGenerator,	/**  = [](const T&){return "That value is invalid.";}  **/
		const COORD inputPos,		/**  = Consolate.GetCursorPosition()  **/
		const COORD warningPos,		/**  = { inputPos.X, inputPos.Y + 1 }  **/
		const string& promptMsg,	/**  = ""  **/
		const string& warnFailMsg,	/**  = "Invalid input format."  **/
		const DWORD inputLen,		/**  = 256  **/
		const DWORD warningLen		/**  = static_cast<DWORD>(warnFailMsg.length())  **/
	)
	{
		T val;

		ReadCin(val, inputPos, promptMsg);

		// while input fails or condition is not satisfied
		while (cin.fail() || !inputValidator(val))
		{
			// Clear input zone
			Consolate.SetDrawChar(' ');
			Consolate.SetColor(INPUT_COLOR);
			Consolate.DrawRow(inputPos, inputLen);

			// Clear warning zone
			Consolate.SetColor(WARN_COLOR);
			Consolate.DrawRow(warningPos, warningLen);

			// Set up cursor for warning.
			Consolate.SetCursorPosition(warningPos);

			// Print warning.
			if (cin.fail())
			{
				//TextAnim(warnFailMsg);
				cout << warnFailMsg;
			}
			else // condition not satisfied
			{
				//TextAnim(warningMsgGenerator(val));
				cout << warningMsgGenerator(val);
			}

			
			ClearInputStream();

			ReadCin(val, inputPos, promptMsg);
		}

		// Clear warning zone
		Consolate.SetDrawChar(' ');
		Consolate.SetColor(WARN_COLOR);
		Consolate.DrawRow(warningPos, warningLen);

		return val;
	}

	// Asks the user to input a value.
	// If the input fails or the inputValidator returns false, asks again.
	// [default warningLen]
	template<class T>
	inline T ReadValue(
		const function<bool(const T& value)> inputValidator,
		const function<string(const T& value)> warningMsgGenerator,
		const COORD inputPos,
		const COORD warningPos,
		const string& promptMsg = "",
		const string& warnFailMsg = "Invalid input format.",
		const DWORD inputLen = 256)
	{
		return ReadValue<T>(
			inputValidator,
			warningMsgGenerator,
			inputPos,
			warningPos,
			promptMsg,
			warnFailMsg,
			inputLen,
			static_cast<DWORD>(warnFailMsg.length())
			);
	}

	// Asks the user to input a value.
	// If the input fails or the inputValidator returns false, asks again.
	// [default warningPos]
	template<class T>
	inline T ReadValue(
		const function<bool(const T& value)> inputValidator,
		const function<string(const T& value)> warningMsgGenerator,
		const COORD inputPos
	)
	{
		return ReadValue<T>(
			inputValidator,
			warningMsgGenerator,
			inputPos,
			{ inputPos.X, inputPos.Y + 1 }
			);
	}

	// Asks the user to input a value.
	// If the input fails or the inputValidator returns false, asks again.
	// [default inputPos]
	template<class T>
	inline T ReadValue(
		const function<bool(const T& value)> inputValidator,
		const function<string(const T& value)> warningMsgGenerator
	)
	{
		return ReadValue<T>(
			inputValidator,
			warningMsgGenerator,
			Consolate.GetCursorPosition()
			);
	}

	// Asks the user to input a value.
	// If the input fails or the inputValidator returns false, asks again.
	// [default warningMsgGenerator]
	template<class T>
	inline T ReadValue(
		const function<bool(const T& value)> inputValidator
	)
	{
		return ReadValue<T>(
			inputValidator,
			[](const T&) { return "That value is invalid."; }
			);
	}

	// Asks the user to input a value.
	// If the input fails, asks again.
	// [default inputValidator]
	template<class T>
	inline T ReadValue()
	{
		return ReadValue<T>(
			[](const T&) { return true; }
		);
	}

#pragma endregion
	// ============================================== //
#pragma region ReadValueFromSet

	// Asks the user to input a value.
	// If it is not one of the valid values, asks again.
	template<class T>
	T ReadValueFromSet(
		const std::set<T>& validValues,
		const COORD inputPos,			/**  = Consolate.GetCursorPosition()  **/
		const COORD warningPos,			/**  = { inputPos.X, inputPos.Y + 1 }  **/
		const string& promptMsg,		/**  = ""  **/
		const string& warnFailMsg,		/**  = "Invalid input format."  **/
		const string& warnNotInSetMsg,	/**  = "That input is not a valid value."  **/
		const DWORD inputLen,			/**  = 256  **/
		const DWORD warningLen			/**  = static_cast<DWORD>(std::max(warnFailMsg.length(), warnNotInSetMsg.length()))  **/
	)
	{
		return ReadValue<T>(
			[&validValues](const T& val) { return validValues.find(val) != validValues.end(); }, // value exists in set of validValues.
			[&warnNotInSetMsg](const T&) { return warnNotInSetMsg; },
			inputPos,
			warningPos,
			promptMsg,
			warnFailMsg,
			inputLen,
			warningLen
			);
	}

	// Asks the user to input a value.
	// If it is not one of the valid values, asks again.
	// [default warningLen]
	template<class T>
	inline T ReadValueFromSet(
		const std::set<T>& validValues,
		const COORD inputPos,
		const COORD warningPos,
		const string& promptMsg = "",
		const string& warnFailMsg = "Invalid input format.",
		const string& warnNotInSetMsg = "That input is not a valid value.",
		const DWORD inputLen = 256
	)
	{
		return ReadValueFromSet<T>(
			validValues,
			inputPos,
			warningPos,
			promptMsg,
			warnFailMsg,
			warnNotInSetMsg,
			inputLen,
			static_cast<DWORD>(std::max(warnFailMsg.length(), warnNotInSetMsg.length()))
			);
	}

	// Asks the user to input a value.
	// If it is not one of the valid values, asks again.
	// [default warningPos]
	template<class T>
	inline T ReadValueFromSet(
		const std::set<T>& validValues,
		const COORD inputPos
	)
	{
		return ReadValueFromSet<T>(
			validValues,
			inputPos,
			{ inputPos.X, inputPos.Y + 1 }
			);
	}

	// Asks the user to input a value.
	// If it is not one of the valid values, asks again.
	// [default inputPos]
	template<class T>
	inline T ReadValueFromSet(
		const std::set<T>& validValues
		)
	{
		return ReadValueFromSet<T>(
			validValues,
			Consolate.GetCursorPosition()
			);
	}
	
#pragma endregion
	// ============================================== //
#pragma region ReadValueInRange

	// Asks the user to input a value.
	// If it is not within the valid range, asks again.
	template<class T>
	T ReadValueInRange(
		const T min,
		const T max,
		const COORD inputPos,		/**  = Consolate.GetCursorPosition()  **/
		const COORD warningPos,		/**  = { inputPos.X, inputPos.Y + 1 }  **/
		const string& promptMsg,	/**  = ""  **/
		const string& warnFailMsg,	/**  = "Invalid input format."  **/
		const string& warnLessMsg,	/**  = "Input value must be at least " + to_string(min) + "."  **/
		const string& warnMoreMsg,	/**  = "Input value must be at most " + to_string(max) + "."  **/
		const DWORD inputLen,		/**  = 256  **/
		const DWORD warningLen		/**  = static_cast<DWORD>(std::max({ warnFailMsg.length(), warnLessMsg.length(), warnMoreMsg.length() }))  **/
	)
	{
		return ReadValue<T>(
			[min, max](const T& val) { return val >= min && val <= max; }, // value within range
			[min, &warnLessMsg, &warnMoreMsg](const T& val) { return val < min ? warnLessMsg : warnMoreMsg; },
			inputPos,
			warningPos,
			promptMsg,
			warnFailMsg,
			inputLen,
			warningLen
			);
	}

	// Asks the user to input a value.
	// If it is not within the valid range, asks again.
	// [default warningLen]
	template<class T>
	inline T ReadValueInRange(
		const T min,
		const T max,
		const COORD inputPos,
		const COORD warningPos,
		const string& promptMsg,
		const string& warnFailMsg,
		const string& warnLessMsg,
		const string& warnMoreMsg,
		const DWORD inputLen = 256
	)
	{
		return ReadValueInRange<T>(
			min,
			max,
			inputPos,
			warningPos,
			promptMsg,
			warnFailMsg,
			warnLessMsg,
			warnMoreMsg,
			inputLen,
			static_cast<DWORD>(std::max({ warnFailMsg.length(), warnLessMsg.length(), warnMoreMsg.length() }))
			);
	}

	// Asks the user to input a value.
	// If it is not within the valid range, asks again.
	// [default warnMoreMsg]
	template<class T>
	inline T ReadValueInRange(
		const T min,
		const T max,
		const COORD inputPos,
		const COORD warningPos,
		const string& promptMsg,
		const string& warnFailMsg,
		const string& warnLessMsg
	)
	{
		return ReadValueInRange<T>(
			min,
			max,
			inputPos,
			warningPos,
			promptMsg,
			warnFailMsg,
			warnLessMsg,
			"Input value must be at most " + to_string(max) + "."
			);
	}

	// Asks the user to input a value.
	// If it is not within the valid range, asks again.
	// [default warnLessMsg]
	template<class T>
	inline T ReadValueInRange(
		const T min,
		const T max,
		const COORD inputPos,
		const COORD warningPos,
		const string& promptMsg = "",
		const string& warnFailMsg = "Invalid input format."
	)
	{
		return ReadValueInRange<T>(
			min,
			max,
			inputPos,
			warningPos,
			promptMsg,
			warnFailMsg,
			"Input value must be at least " + to_string(min) + "."
			);
	}

	// Asks the user to input a value.
	// If it is not within the valid range, asks again.
	// [default warningPos]
	template<class T>
	inline T ReadValueInRange(
		const T min,
		const T max,
		const COORD inputPos
	)
	{
		return ReadValueInRange<T>(
			min,
			max,
			inputPos,
			{ inputPos.X, inputPos.Y + 1 }
			);
	}

	// Asks the user to input a value.
	// If it is not within the valid range, asks again.
	// [default inputPos]
	template<class T>
	inline T ReadValueInRange(
		const T min,
		const T max
		)
	{
		return ReadValueInRange<T>(
			min,
			max,
			Consolate.GetCursorPosition()
		);
	}

#pragma endregion
	// ============================================== //
#pragma region ReadValueAny

	// Asks the user to input a value.
	// If the input fails, returns the fallback value.
	template<class T = string>
	T ReadValueAny(
		const COORD inputPos, /**  = Consolate.GetCursorPosition()  **/
		const string& promptMsg	= "",
		T fallbackValue = T()//,
		//const DWORD inputLen = 256
	)
	{
		T val;

		ReadCin(val, inputPos, promptMsg);

		// If input fails, return fallbackValue.
		if (cin.fail())
		{
			ClearInputStream();
			return fallbackValue;
		}

		return val;
	}

	// Asks the user to input a value.
	// If the input fails, returns the fallback value.
	// [default inputPos]
	template<class T = string>
	inline T ReadValueAny()
	{
		return ReadValueAny<T>(
			Consolate.GetCursorPosition()
			);
	}

#pragma endregion
	// ============================================== //



	// -----------------
	//    UI Elements
	// -----------------

	// ============================================== //

	// Calls Sleep(time) only if sleeps is true.
	inline void Sleeps(DWORD time)
	{
		if (sleepsSetting && sleepsInternal)
			Sleep(time);
	}

	// ============================================== //

	// Draws a progress bar with a fill amount.
	void ProgressBar(COORD pos, const short len, const short fillLen)
	{
		Consolate.SetDrawChar(' ');
		Consolate.SetColor(ColorBG_DarkGray);
		Consolate.DrawRow(pos, len);

		Consolate.SetColor(ColorBG_Gray);
		Consolate.DrawRow(pos, fillLen);
	}

	// ============================================== //

	// Draws a progress bar and fills it over the time period.
	void ProgressBarAnimation(COORD pos, const short len, const DWORD totaltime)
	{
		Consolate.SetDrawChar(' ');
		Consolate.SetColor(ColorBG_DarkGray);
		Consolate.DrawRow(pos, len);

		Consolate.SetColor(ColorBG_Gray);
		for (short i = 0; i < len; ++i, ++pos.X)
		{
			Consolate.DrawPoint(pos);
			Sleeps(totaltime / len);
		}
	}

	// ============================================== //

	// Animates text being written to the console.
	void TextAnim(const string& x, DWORD sleepTime = 10)
	{
		const DWORD def = 10; // must be > 0

		size_t charsPerSleep = 1;
		if (sleepTime < def)
		{
			charsPerSleep = static_cast<size_t>(def / sleepTime);
			sleepTime = def;
		}

		size_t i = charsPerSleep;
		for (char c : x)
		{
			cout << c;

			if ((--i) == 0)
			{
				i = charsPerSleep;
				Sleeps(sleepTime);
			}
		}
	}

	// ============================================== //

	// Clears the screen. Animated clearing of rows from top to bottom.
	void ClearScreenAnim(const DWORD totaltime = 300)
	{
		Consolate.SetColor(CLEAR_COLOR);
		Consolate.SetDrawChar(' ');

		COORD size = Consolate.GetWindowSize();
		for (COORD pos = { 0, 0 }; pos.Y < size.Y; ++pos.Y)
		{
			Consolate.DrawRow(pos, size.X);
			Sleeps(totaltime / size.Y);
		}

		// Account for any changes to window size.
		UpdateFromWindowSize();
	}

	// ============================================== //



	// ====================
	//    Main Functions
	// ====================

	// ============================================== //

	// The main game entry point.
	void Start()
	{
		UpdateFromWindowSize();

		Consolate.Clear();

		sleepsInternal = true;
		// Initialize game state and play intro animation.
		Reset();

		// Main game loop
		while (continueGame)
		{
			if (money > 0)
			{
				Menu();
			}
			else
			{
				AskReset();
			}
		}

		// Game has ended.
		Consolate.SetCursorPosition({ 0, 0 });
	}

	// ============================================== //

	// Displays the menu and gets the user's choice.
	void Menu()
	{
		//ClearScreenAnim();

		sleepsInternal = false;
		DrawMenu();

		COORD oldPos = Consolate.GetCursorPosition();

		int choice = ReadValueInRange<int>(1, MENU_OPTIONS_COUNT, oldPos, { oldPos.X - 1, oldPos.Y + 3 }, "> ");

		Consolate.SetCursorPosition({ oldPos.X, oldPos.Y + 1 });

		Consolate.SetColor(NORMAL_COLOR);
		sleepsInternal = true;

		// Execute action.
		switch (choice)
		{
		case 1: // play
		{
			ClearScreenAnim();
			PlayRound();
		}
		break;

		case 2: // quit
		{
			ClearScreenAnim();
			Exit();
		}
		break;

		case 3: // credits
		{
			ClearScreenAnim();
			Credits();
		}
		break;

		case 4: // rules
		default:
		{
			ClearScreenAnim();
			Rules();
		}
		break;

		case 5: // toggle animations
		{
			sleepsSetting = !sleepsSetting;
			ClearScreenAnim();
		}
		break;

		case 6: // play (all or nothing)
		{
			ClearScreenAnim();
			PlayRound(true);
		}
		break;
		}
	}

	// ============================================== //

	// Sets up global variables which depend on the size of the console window.
	void UpdateFromWindowSize()
	{
		COORD windowSize = Consolate.GetWindowSize();
		TITLE_POS = { windowSize.X / 2, windowSize.Y / 5 };
		RULES_POS = { TITLE_POS.X - 28, TITLE_POS.Y };
		CREDITS_POS = RULES_POS;

		SMC_MIN = { TITLE_POS.X - SMC_WIDTH/2, TITLE_POS.Y };
		SMC_MAX = { SMC_MIN.X + SMC_WIDTH - 1, SMC_MIN.Y + SMC_HEIGHT - 1 };
	}

	// ============================================== //

	// Displays the Menu page graphics.
	void DrawMenu()
	{
		PanelStyle style = PanelStyle::Default;

		const DWORD sleepTime = 200;

#pragma region Draw Title Panel

		// Calculate Title Panel Variables

		const string titleLabel = "SLOT MACHINE";
		const short titleWidth = static_cast<short>(titleLabel.length()) + 2;
		const short titleHeight = 3;

		const COORD titleMin = { TITLE_POS.X - titleWidth/2, TITLE_POS.Y };
		const COORD titleMax = { titleMin.X + titleWidth - 1, titleMin.Y + titleHeight - 1 };

		// Draw Title Panel

		Consolate.SetCursorPosition({ titleMin.X + 1, titleMin.Y + 1 });

		style.outlineColor = TITLE_COLOR;
		Consolate.DrawPanel(titleMin, titleMax, style);

		Consolate.SetColor(TITLE_COLOR);
		cout << titleLabel; //TextAnim(titleLabel);

#pragma endregion
#pragma region Draw Money Panel with Label and Value

		// Calculate Money Panel Variables

		const string moneyValue = to_string(money);
		const short moneyWidth = static_cast<short>(MONEY_LABEL.length() + moneyValue.length()) + 2;
		const short moneyHeight = 3;

		const COORD moneyMin = { TITLE_POS.X - moneyWidth/2, titleMax.Y + 1 };
		const COORD moneyMax = { moneyMin.X + moneyWidth - 1, moneyMin.Y + moneyHeight - 1 };

		// Draw Money Panel

		Consolate.SetCursorPosition({ moneyMin.X + 1, moneyMin.Y + 1 });

		Sleeps(sleepTime);

		style.outlineColor = MONEY_LABEL_COLOR;
		Consolate.DrawPanel(moneyMin, moneyMax, style);

		Consolate.SetColor(MONEY_LABEL_COLOR);
		cout << MONEY_LABEL;

		Consolate.SetColor(MONEY_VALUE_COLOR);
		cout << moneyValue;

#pragma endregion
#pragma region Draw Menu Options Panel

		// Calculate Menu Options Variables

		const array<string, MENU_OPTIONS_COUNT> optionsLabels = {
			"1) Play",
			"2) Quit",
			"3) Credits",
			"4) Rules",
			"5) " + static_cast<string>(sleepsSetting ? "Disable" : "Enable") + " Animations",
			"6) Play (all or nothing)",
		};

		// Find the max value of item.length() for all items in optionsLabels.
		// TODO convert to GENERAL FUNCTION
		size_t tempmax = 0;
		for (string item : optionsLabels)
		{
			const size_t len = item.length();
			if (tempmax < len)
				tempmax = len;
		}
		// END GENERAL FUNCTION

		const short optionsWidth = static_cast<short>(tempmax) + 2;
		const short optionsHeight = static_cast<short>(optionsLabels.size()) + 2;

		const COORD optionsMin = { TITLE_POS.X - optionsWidth/2, moneyMax.Y + 1 };
		const COORD optionsMax = { optionsMin.X + optionsWidth - 1, optionsMin.Y + optionsHeight - 1 };


		// Draw Menu Options Panel

		COORD labelPos = { optionsMin.X + 1, optionsMin.Y + 1 };
		Consolate.SetCursorPosition(labelPos);

		Sleeps(sleepTime);

		style.outlineColor = OPTIONS_COLOR;
		Consolate.DrawPanel(optionsMin, optionsMax, style);

		// Draw Menu Options Labels

		Consolate.SetColor(OPTIONS_COLOR);
		for (string label : optionsLabels)
		{
			TextAnim(label);
			labelPos.Y++;
			Consolate.SetCursorPosition(labelPos);
		}

#pragma endregion
#pragma region Prompt for Menu Option

		const string promptLabel = "Enter a value from 1 to " + to_string(MENU_OPTIONS_COUNT);
		const short promptWidth = static_cast<short>(promptLabel.length());

		const COORD promptPos = { TITLE_POS.X - promptWidth/2, optionsMax.Y + 2 };

		Consolate.SetCursorPosition(promptPos);
		Consolate.SetColor(PROMPT_COLOR);
		TextAnim(promptLabel);

#pragma endregion

		// Set up cursor for user input.
		Consolate.SetCursorPosition({ optionsMin.X + 1, promptPos.Y + 2 });
	}

	// ============================================== //

	// Exits the game loop.
	void Exit()
	{
		continueGame = false;
	}

	// ============================================== //

	// Displays the Credits page.
	void Credits()
	{
		sleepsInternal = true;

		COORD pos = CREDITS_POS;

		// Page Title
		Consolate.SetColor(TITLE_COLOR);
		Consolate.SetCursorPosition(pos);
		cout << "CREDITS";
		Consolate.DrawPanelOutlineOnly({ pos.X - 1, pos.Y - 1 }, { pos.X + 7, pos.Y + 1 });

		pos.Y += 2;

		// Project Title
		Consolate.SetCursorPosition({ pos.X, pos.Y + 1 });
		Sleeps(50);
		Consolate.SetColor(Color_Blue);
		cout << PROJECT_TITLE;

		PanelStyle style = PanelStyle::Default;
		style.outlineColor = Color_Blue;
		Consolate.DrawPanelOutline(
			{ pos.X - 1, pos.Y },
			{ pos.X + static_cast<short>(PROJECT_TITLE.length()), pos.Y + 2 },
			style
		);

		pos.Y += 4;



		const Color labelColor = NORMAL_COLOR;
		const Color dataColor = Color_Yellow;

		// Version
		Consolate.SetCursorPosition(pos);
		Sleeps(50);
		Consolate.SetColor(labelColor);
		TextAnim("Version ");
		Consolate.SetColor(dataColor);
		TextAnim(PROJECT_VERSION);

		// Date
		pos.Y++;
		Consolate.SetCursorPosition(pos);
		Consolate.SetColor(labelColor);
		TextAnim("Date: ");
		Consolate.SetColor(dataColor);
		TextAnim(PROJECT_DATE);

		// Author
		pos.Y++;
		Consolate.SetCursorPosition(pos);
		Consolate.SetColor(labelColor);
		TextAnim("Author: ");
		Consolate.SetColor(dataColor);
		TextAnim(PROJECT_AUTHOR);

		// Other Information
		Consolate.SetColor(dataColor);
		for (string data : PROJECT_META)
		{
			pos.Y++;
			Consolate.SetCursorPosition(pos);
			TextAnim(data);
		}

		// Pause before going back to menu.
		pos.Y += 2;
		ReadValueAny<string>(pos, "Enter anything to return to menu: ");
		ClearScreenAnim();
	}

	// ============================================== //

	// Displays the Rules page.
	void Rules()
	{
		COORD pos = RULES_POS;

		// Page Title
		Consolate.SetColor(TITLE_COLOR);
		Consolate.SetCursorPosition(pos);
		cout << "RULES";
		Consolate.DrawPanelOutlineOnly({ pos.X - 1, pos.Y - 1 }, { pos.X + 5, pos.Y + 1 });

		// Print the rules

		Consolate.SetColor(NORMAL_COLOR);

		pos.Y+=2;
		Consolate.SetCursorPosition(pos);
		Sleeps(50);
		TextAnim("To play slots, you must first place a bet.");

		pos.Y++;
		Consolate.SetCursorPosition(pos);
		TextAnim("Three values in the range " + to_string(MIN_ROLL) + " to " + to_string(MAX_ROLL) + " will be randomly selected.");

		pos.Y++;
		Consolate.SetCursorPosition(pos);
		TextAnim("If two are the same, you win ");
		Consolate.SetColor(Color_Cyan);
		TextAnim(to_string(WINMULT_2SAME) + "x");
		Consolate.SetColor(NORMAL_COLOR);
		TextAnim(" the bet.");

		pos.Y++;
		Consolate.SetCursorPosition(pos);
		TextAnim("If all three are the same, you win ");
		Consolate.SetColor(Color_Magenta);
		TextAnim(to_string(WINMULT_3SAME) + "x");
		Consolate.SetColor(NORMAL_COLOR);
		TextAnim(" the bet.");

		pos.Y++;
		Consolate.SetCursorPosition(pos);
		TextAnim("If all three are " + to_string(MAX_ROLL) + ", you win ");
		Consolate.SetColor(Color_Green);
		TextAnim(to_string(WINMULT_3MAX) + "x");
		Consolate.SetColor(NORMAL_COLOR);
		TextAnim(" the bet.");

		pos.Y++;
		Consolate.SetCursorPosition(pos);
		TextAnim("If none of these events occur, you "); 
		Consolate.SetColor(Color_Red);
		TextAnim("lose");
		Consolate.SetColor(NORMAL_COLOR);
		TextAnim(" the bet.");

		// Pause before going back to menu.
		pos.Y += 2;
		ReadValueAny(pos, "Enter anything to return to menu: ");
		ClearScreenAnim();
	}

	// ============================================== //

	// Prompts the user to place a bet.
	// Returns the amount of money that was bet.
	long PlaceBet()
	{
		PanelStyle style = PanelStyle::Default;

#pragma region Draw Money Panel with Label and Value

		// Calculate Money Panel Variables

		const string moneyValue = to_string(money);
		const short moneyWidth = static_cast<short>(MONEY_LABEL.length() + moneyValue.length()) + 2;
		const short moneyHeight = 3;

		const COORD moneyMin = { TITLE_POS.X - moneyWidth / 2, TITLE_POS.Y + 1 };
		const COORD moneyMax = { moneyMin.X + moneyWidth - 1, moneyMin.Y + moneyHeight - 1 };

		// Draw Money Panel

		Consolate.SetCursorPosition({ moneyMin.X + 1, moneyMin.Y + 1 });

		style.outlineColor = MONEY_LABEL_COLOR;
		Consolate.DrawPanel(moneyMin, moneyMax, style);

		Consolate.SetColor(MONEY_LABEL_COLOR);
		cout << MONEY_LABEL;

		Consolate.SetColor(MONEY_VALUE_COLOR);
		cout << moneyValue;

#pragma endregion
#pragma region Draw Prompt and Read Input for Bet

		// Calculate Bet Prompt Variables

		const string betLabel = "Place your bet: $";
		const short betWidth = static_cast<short>(betLabel.length() + moneyValue.length());

		const COORD betPos = { TITLE_POS.X - betWidth/2, moneyMax.Y + 2 };

		// Prompt and Read Input for Bet

		long bet = ReadValueInRange<long>(1, money,
			betPos,
			{ betPos.X, betPos.Y + 2 },
			betLabel
			);

#pragma endregion

		ClearScreenAnim();

		return bet;
	}

	// ============================================== //

	// Draws a wheel of slot numbers.
	void DrawSlotNumberWheel(COORD position, const int slotResult, const UINT frame, const UINT finishedFrame)
	{
		int x = slotResult - finishedFrame - CELL_MID + std::min(frame, finishedFrame);

		for (short i = 0; i < CELL_HEIGHT; ++i, ++position.Y)
		{
			// make middle brighter
			if (i == CELL_MID)
				Consolate.SetColor(Color_White);
			else
				Consolate.SetColor(Color_DarkGray);

			// draw number
			Consolate.SetCursorPosition({ position.X + CELL_WIDTH / 2 + 1, position.Y });
			cout << RepeatInt(x + i, MIN_ROLL, MAX_ROLL);
		}
	}

	// ============================================== //

	// Plays a round of the slot machine.
	void PlayRound(bool betAll)
	{
		// Prompt for and read bet
		long bet = betAll ? money : PlaceBet();
		// Deduct bet from money balance
		money -= bet;

		Consolate.SetCursorPosition({ 0, 0 });

		// Generate final slot values randomly
		for (int& x : slotResults)
		{
			x = RandomSlot();
		}

#pragma region Slot Machine Animation

		// Calculate Animation Variables

		const COORD progressPos = { SMC_MIN.X + 1, SMC_MAX.Y + 3 };
		const short progressWidth = SMC_WIDTH - 2;

		const short minX = SMC_MIN.X + 1 - 1;
		const short minY = SMC_MIN.Y + 1;
		const short maxY = SMC_MAX.Y - 1;

		const DWORD sleepInterval = 100;

		PanelStyle style = PanelStyle::Default;

		Color smcColor = Color_DarkYellow;
		Color smcColorInner = Color_DarkGray;

		// --- Play Animation ---

		// Inline Function
		auto DrawContainerPanel = [=, &smcColor, &smcColorInner]()
		{
			PanelStyle style = PanelStyle::Double;
			style.outlineColor = smcColor;
			Consolate.DrawPanelOutline(
			{ SMC_MIN.X - 2, SMC_MIN.Y - 1 },
			{ SMC_MAX.X + 2, SMC_MAX.Y + 1 },
				style
			);

			style = PanelStyle::Default;
			style.outlineColor = smcColorInner;
			Consolate.DrawPanelOutline(
				SMC_MIN,
				SMC_MAX,
				style
			);

			Consolate.DrawPoint({ SMC_MIN.X, minY + CELL_MID }, smcColor, style.left_T);
			Consolate.DrawPoint({ SMC_MAX.X, minY + CELL_MID }, smcColor, style.right_T);

			for (UINT i = 1; i < SLOT_COUNT; ++i)
			{
				COORD min = { minX + (CELL_WIDTH + CELL_PADDING) * static_cast<short>(i), minY };
				Consolate.DrawRect(min, { min.X, maxY }, smcColorInner, style.left);
				Consolate.DrawPoint({ min.X, SMC_MIN.Y }, smcColorInner, style.top_T);
				Consolate.DrawPoint({ min.X, SMC_MAX.Y }, smcColorInner, style.bottom_T);
				Consolate.DrawPoint({ min.X, minY + CELL_MID }, smcColor, style.cross);
			}
		};

		DrawContainerPanel();

		// Animate Number Wheels

		for (UINT frame = 0; frame <= TOTAL_FRAMES; ++frame)
		{
			for (UINT i = 0; i < SLOT_COUNT; ++i)
			{
				// Draw one wheel of numbers
				DrawSlotNumberWheel(
					{ minX + (CELL_WIDTH + CELL_PADDING) * static_cast<short>(i), minY },
					slotResults[i],
					frame,
					(i + 1) * TOTAL_FRAMES / 3
				);

				// Draw the progress bar
				ProgressBar(
					progressPos,
					progressWidth,
					progressWidth * (static_cast<short>(frame * 3 + i)) / (static_cast<short>(TOTAL_FRAMES) * 3)
				);

				Consolate.SetCursorPosition({ 0, 0 });
				Sleeps(sleepInterval);
			}
		}

		// Erase Progress Bar
		Consolate.SetColor(CLEAR_COLOR);
		Consolate.SetDrawChar(' ');
		Consolate.DrawRow(progressPos, progressWidth);

#pragma endregion
#pragma region Flashing Animation

		// Inline Function
		auto FlashingAnim = [=, &smcColor, &DrawContainerPanel](const Color color1, const Color color2)
		{
			for (UINT i = 0; i < 3; ++i)
			{
				smcColor = color1;
				DrawContainerPanel();
				Sleeps(sleepInterval);

				smcColor = color2;
				DrawContainerPanel();
				Sleeps(sleepInterval);
			}
		};

#pragma endregion

		// Inline Function
		auto Reward = [](long bet, long mult)
		{
			const string msg = "You have won " + to_string(mult) + "x your bet!";
			const short width = static_cast<short>(msg.length());

			const COORD pos1 = { TITLE_POS.X - width / 2 , SMC_MAX.Y + 3 };

			Consolate.SetCursorPosition(pos1);
			TextAnim(msg);

			const string msg2 = "+ $" + to_string(bet * mult);
			const short width2 = static_cast<short>(msg2.length());

			const COORD pos2 = { TITLE_POS.X - width2 / 2, pos1.Y + 2 };

			Consolate.SetColor(MONEY_VALUE_COLOR);
			Consolate.SetCursorPosition(pos2);
			TextAnim(msg2);

			// Update money balance
			money += bet * mult;
		};

#pragma region Analyse Result Numbers

		Consolate.SetCursorPosition({ SMC_MIN.X, SMC_MAX.Y + 3 });

		// Compare equality
		bool eq1 = slotResults[0] == slotResults[1];
		bool eq2 = slotResults[0] == slotResults[2];
		bool eq3 = slotResults[1] == slotResults[2];

		// if all three are the same
		if (eq1 && eq2)
		{
			PanelStyle goldStyle = PanelStyle::Double;
			goldStyle.fill = '$';
			goldStyle.fillColor = Color_DarkYellow;
			goldStyle.outlineColor = Color_DarkYellow;

			// if all three are 7's
			if (slotResults[0] == MAX_ROLL)
			{
				Consolate.DrawPanel(
					{ SMC_MIN.X, SMC_MIN.Y - 4 },
					{ SMC_MAX.X, SMC_MIN.Y - 1 },
					goldStyle
				);
				FlashingAnim(Color_Yellow, Color_Green);
				Reward(bet, WINMULT_3MAX);
			}
			else
			{
				Consolate.DrawPanel(
					{ SMC_MIN.X, SMC_MIN.Y - 3 },
					{ SMC_MAX.X, SMC_MIN.Y - 1 },
					goldStyle
				);
				FlashingAnim(Color_DarkMagenta, Color_Magenta);
				Reward(bet, WINMULT_3SAME);
			}
		}
		// else if any two are the same
		else if (eq1 || eq2 || eq3)
		{
			FlashingAnim(Color_Blue, Color_Cyan);
			Reward(bet, WINMULT_2SAME);
		}
		// else the bet was lost.
		else
		{
			FlashingAnim(Color_DarkRed, Color_Red);

			// Tell the player they lost the bet

			const string msg = "You have lost the bet of $" + to_string(bet) + ".";
			const short width = static_cast<short>(msg.length());

			const COORD pos1 = { TITLE_POS.X - width / 2 , SMC_MAX.Y + 3 };

			Consolate.SetCursorPosition(pos1);
			TextAnim(msg);
		}

#pragma endregion

		const string promptMsg = "Enter anything to return to the menu: ";
		const short promptWidth = static_cast<short>(promptMsg.length());

		const COORD promptPos = { TITLE_POS.X - promptWidth/2, SMC_MAX.Y + 8 };

		ReadValueAny(promptPos, promptMsg);

		ClearScreenAnim();
	}

	// ============================================== //

	// Displays a page which asks the player if they want to restart.
	void AskReset()
	{
		PanelStyle style = PanelStyle::Double;

		// Calculate Title Panel Variables

		const string titleLabel = "You are out of money!";

		const short titleWidth = static_cast<short>(titleLabel.length()) + 2;
		const short titleHeight = 3;

		const COORD titleMin = { TITLE_POS.X - titleWidth / 2, TITLE_POS.Y };
		const COORD titleMax = { titleMin.X + titleWidth - 1, titleMin.Y + titleHeight - 1 };

		// Draw Title Panel

		style.outlineColor = BAD_COLOR;
		Consolate.DrawPanel(titleMin, titleMax, style);
		Consolate.SetCursorPosition({ titleMin.X + 1, titleMin.Y + 1 });
		Consolate.SetColor(BAD_COLOR);
		cout << titleLabel;

		// Draw Body Content

		const COORD bodyPos = { titleMin.X + 1, titleMax.Y + 2 };

		Consolate.SetCursorPosition(bodyPos);

		Sleeps(500);

		Consolate.SetColor(NORMAL_COLOR);
		TextAnim("Do you want to reset the game?");

		// Ask for Restart

		const COORD inputPos = { bodyPos.X, bodyPos.Y + 2 };
		const COORD warningPos = { inputPos.X, inputPos.Y + 2 };

		string inp = ReadValueFromSet<string>({ "y", "Y", "n", "N" }, inputPos, warningPos, "(Y/N): ");
		if (inp == "y" || inp == "Y")
		{
			// Reset the game.
			Reset();
		}
		else // "n" or "N"
		{
			// Print "Game Over"
			Consolate.SetCursorPosition(warningPos);
			style.outlineColor = BAD_COLOR;
			TextAnim("GAME OVER");

			Sleeps(500);

			// Exit the game.
			Exit();

			ClearScreenAnim();
		}
	}

	// ============================================== //

	// Resets the game so you can play again.
	void Reset()
	{
		money = INITIAL_MONEY;

		ClearScreenAnim();
		DrawMenu();
	}

	// ============================================== //
}

int main()
{
	SlotMachine::Start();
	return 0;
}

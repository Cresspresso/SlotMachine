// ==========================
//    PROJECT INFO
// Title:	SlotMachine
// Source:	main.h
// Version:	2.0
// Date:	13/04/2018
// Author:	Elijah Shadbolt
// ==========================

#pragma once

#include <iostream>		// cin, cout, endl
#include <string>		// string
#include <set>			// set
#include <random>
#include <functional>	// bind()
#include <algorithm>	// max()
#include <functional>	// function
#include <array>		// array
#include <consolate.h>

namespace SlotMachine
{
	using namespace consolate;

	using std::cin;
	using std::cout;
	using std::endl;
	using std::string;
	using std::to_string;
	using std::function;
	using std::array;


	// ======================
	//    PROJECT METADATA
	// ======================

	const string PROJECT_TITLE = "Slot Machine";
	const string PROJECT_VERSION = "2.0";
	const string PROJECT_DATE = "13/04/2018";
	const string PROJECT_AUTHOR = "Elijah Shadbolt";
	const array<string, 3> PROJECT_META = {
		"Media Design School 2018",
		"BSE",
		"GD1P01",
	};


	// ===============
	//    CONSTANTS
	// ===============

	// How much money the player starts with.
	const long INITIAL_MONEY = 2000L;

	// The range of values that the slot machine can randomly select.
	const int MIN_ROLL = 2;
	const int MAX_ROLL = 7;

	// When a player wins, their reward is the bet multiplied by
	// one of these values, based on the winning criteria.
	const long WINMULT_2SAME = 3L; // Two are the same.
	const long WINMULT_3SAME = 5L; // Three are the same.
	const long WINMULT_3MAX = 10L; // All three are 7's.


	// ------------
	//    Colors
	// ------------

	const Color CLEAR_COLOR = Consolate.OriginalColor();

	const Color NORMAL_COLOR = Color_Gray; // Normal color.

	const Color PROMPT_COLOR = Color_DarkGray; // ReadValue prompt color.
	const Color INPUT_COLOR = Color_White; // ReadValue input color.
	const Color WARN_COLOR = Color_Yellow; // ReadValue warning color.

	const Color TITLE_COLOR = Color_Blue; // Page title color.
	const Color MONEY_LABEL_COLOR = Color_Green; // Money label color.
	const Color MONEY_VALUE_COLOR = Color_Green; // Money value color.
	const Color OPTIONS_COLOR = Color_Gray; // Menu options color.

	const Color BAD_COLOR = Color_Red; // Critical warning color.


	// ------------
	//    Labels
	// ------------

	const string MONEY_LABEL = "Chips: $";

	// Number of menu options available.
	const size_t MENU_OPTIONS_COUNT = 6;

	// ----------------------------
	//    Slot Machine Container
	// ----------------------------

	// Number of slot wheels in the slot machine.
	const UINT SLOT_COUNT = 3;
	
	// Number of visible numbers on a slot wheel.
	const short NUMBERS_VISIBLE = static_cast<short>( std::min(  5  , MAX_ROLL + 1 - MIN_ROLL) );

	// Width of slot wheel
	const short CELL_WIDTH = 5;
	// Height of slot wheel
	const short CELL_HEIGHT = NUMBERS_VISIBLE;//(NUMBERS_VISIBLE - 1) * 2 + 1;
	// Space between slot wheel cells
	const short CELL_PADDING = 1;
	// Half the height of a slot wheel cell
	const short CELL_MID = CELL_HEIGHT / 2;

	// Width of slot machine container panel
	const short SMC_WIDTH = (CELL_WIDTH + CELL_PADDING) * SLOT_COUNT + 2 - CELL_PADDING;
	// Height of slot machine container panel
	const short SMC_HEIGHT = CELL_HEIGHT + 2;

	// Number of animation frames in the slot machine animation.
	const UINT TOTAL_FRAMES = 20;


	// =========================
	//    NAMESPACE VARIABLES
	// =========================

	// Amount of money the player has.
	long money = INITIAL_MONEY;

	// If set to false, the main game loop will exit and the program will end.
	bool continueGame = true;

	// If true, animations will happen.
	// If false, animations will be skipped. (The Sleep() routine will not be called.)
	bool sleepsInternal = true;
	// (User setting of sleeps with higher priority)
	bool sleepsSetting = true;


	// -----------
	//    Slots
	// -----------

	// RNG for the range MIN_ROLL to MAX_ROLL.
	auto RandomSlot = std::bind(
		std::uniform_int_distribution<int>(MIN_ROLL, MAX_ROLL),
		std::default_random_engine{
			std::random_device()()
			//static_cast<long unsigned int>(time(nullptr))
		}
	);

	// The result numbers of playing a round of slots.
	array<int, SLOT_COUNT> slotResults = array<int, SLOT_COUNT>();


	// --------------------------------
	//    Positioning of UI Elements
	// --------------------------------

	COORD TITLE_POS;
	COORD RULES_POS;
	COORD CREDITS_POS;

	// Slot Machine Container
	COORD SMC_MIN;
	COORD SMC_MAX;


	// =========================
	//    FUNCTION PROTOTYPES
	// =========================
	// (not all of them)

	void Start();
	void Reset();
	void Menu();
	void Exit();
	void Credits();
	void Rules();
	void AskReset();

	void DrawMenu();

	void UpdateFromWindowSize();

	void PlayRound(bool betAll = false);

}

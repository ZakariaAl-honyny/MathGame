#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsShowPlayGameScreen.h"
#include "clsInputValidate.h"
#include "clsUitil.h"
#include "clsShowPlayGameScreen.h"

class clsMainGameScreen : protected clsScreen
{
	enum enMainGameScreenChoice { ePlayGame = 1, eExit = 2 };

	static short _ReadMainGameScreenOptions()
	{
		short Choice = 0;
		cout << clsUitil::Tabs(3) << "What do you want to do? choose [1 - 2] ? ";
		Choice = clsInputValidate::ReadNumberBetween(1, 2, "\n\t\t\t\t\t What do you want to do? choose [1 - 2] ? ");

		return Choice;
	}

	static void _GoBackToMainGameScreen()
	{
		cout << "\n\n\tPress any key to go back to main game screen...";
		system("pause>0");
		ShowMainGameScreen();
	}

	static void _ShowPlayGameScreen()
	{
		//cout << "\nShow Play Game Screen Will be here soon...\n";
		clsShowPlayGameScreen::ShowPlayGameScreen();
	}

	static void _Exit()
	{

		cout << "\n!!You are outside the system :-(!!\n";
		cout << "\n\nPress any key to close this windows...";

	}

	static void _PerformMainGameScreenOptions(enMainGameScreenChoice MainGameScreenOption)
	{
		switch (MainGameScreenOption)
		{

		case enMainGameScreenChoice::ePlayGame:
		{
			clsMathGame::ResetScreen();
			_ShowPlayGameScreen();
			_GoBackToMainGameScreen();
			break;
		}

		case enMainGameScreenChoice::eExit:
		{
			clsMathGame::ResetScreen();
			_Exit();
			break;
		}

		}
	}

public:

	static void ShowMainGameScreen()
	{
		clsMathGame::ResetScreen();
		clsScreen::_DrawHeader("\t\tMath Game");

		cout << clsUitil::Tabs(3) << "\t----------------------\n";
		cout << clsUitil::Tabs(3) << "\t 1 |   Play Game Now |\n";
		cout << clsUitil::Tabs(3) << "\t----------------------\n\n";

		cout << clsUitil::Tabs(3) << "\t    --------------\n";
		cout << clsUitil::Tabs(3) << "\t     2 |  Exit  |\n";
		cout << clsUitil::Tabs(3) << "\t    --------------\n\n";

		_PerformMainGameScreenOptions((enMainGameScreenChoice)_ReadMainGameScreenOptions());
	}

};


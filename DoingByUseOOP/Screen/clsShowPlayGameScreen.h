#pragma once
#include "clsScreen.h"
#include "clsMathGame.h"
#include "clsInputValidate.h"

class clsShowPlayGameScreen : protected clsScreen
{
private:

	static short ReadHowManyQuestions()
	{
		short NumberOfQuestions = 0;

		cout << "\nHow Many Questions do you want to Answer from 1 to 10? ";
		NumberOfQuestions = clsInputValidate::ReadNumberBetween<short>(1, 10, "\nHow Many Questions do you want to Answer from 1 to 10? ");

		return NumberOfQuestions;
	}

	static clsMathGame::enQuestionsLevel ReadQuestionsLevel()
	{
		short QuestionLevel = 0;

		cout << "\nEnter Questios Level [1]:Easy, [2]:Med, [3]:Hard, [4]:Mix ? ";
		QuestionLevel = clsInputValidate::ReadNumberBetween<short>(1, 4, "\nEnter Questios Level [1]:Easy, [2]:Med, [3]:Hard, [4]:Mix ? ");

		return (clsMathGame::enQuestionsLevel)QuestionLevel;
	}

	static clsMathGame::enOperationType ReadOpType()
	{
		short OpType = 0;

		cout << "\nEnter Operation Type [1]:Add, [2]:Sub, [3]:Mul, [4]:Div, [5]:Mix  ? ";
		OpType = clsInputValidate::ReadNumberBetween<short>(1, 5, "\nEnter Operation Type [1]:Add, [2]:Sub, [3]:Mul, [4]:Div, [5]:Mix  ? ");

		return (clsMathGame::enOperationType)OpType;
	}

	static int ReadQuestionAnswer()
	{
		int Answer = 0;
		Answer = clsInputValidate::ReadNumber<int>();

		return Answer;
	}

	static void _CorrectTheQuestionAnswer(clsMathGame& Quizz, short QuestionNumber)
	{
		if (Quizz.vQuestionList[QuestionNumber].PlayerAnswer != Quizz.vQuestionList[QuestionNumber].CorrectAnswer)
		{
			Quizz.vQuestionList[QuestionNumber].AnswerResult = false;
			Quizz.NumberOfWrongAnswers++;

			cout << "Wrong Answer :-( \n";
			cout << "The right answer is: ";
			cout << Quizz.vQuestionList[QuestionNumber].CorrectAnswer;
			cout << "\n";
		}
		else
		{
			Quizz.vQuestionList[QuestionNumber].AnswerResult = true;
			Quizz.NumberOfRightAnswers++;

			cout << "\nRight Answer :-)\n";
		}
		cout << endl;

		clsMathGame::SetScreenColor(Quizz.vQuestionList[QuestionNumber].AnswerResult);
	}

	static void _PrintTheQuestion(clsMathGame Quizz, short QestionNumber)
	{

		cout << "\n";
		cout << "Question [" << QestionNumber + 1 << "/" << Quizz.NumberOfQuestions << "]\n\n";
		cout << Quizz.vQuestionList[QestionNumber].Number1 << endl;
		cout << Quizz.vQuestionList[QestionNumber].Number2 << " ";
		cout << clsMathGame::GetOpTypeSymbol(Quizz.vQuestionList[QestionNumber].OpType);
		cout << "\n_____________" << endl;
	}
	
	static void _AskAndCorrectQuestionListAnswers(clsMathGame& Quizz)
	{

		for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++)
		{
			_PrintTheQuestion(Quizz, QuestionNumber);

			Quizz.vQuestionList[QuestionNumber].PlayerAnswer = ReadQuestionAnswer();

			_CorrectTheQuestionAnswer(Quizz, QuestionNumber);
		}

		Quizz.isPass = (Quizz.NumberOfRightAnswers >= Quizz.NumberOfWrongAnswers);
	}
 
	static void _PrintQizzResults(clsMathGame Quizz)
	{
		cout << "\n";
		cout << "________________________________\n\n";

		cout << "Final results is " << Quizz.GetFinalResultsText();
		cout << "\n________________________________\n\n";

		cout << "Number of Questions: " << Quizz.NumberOfQuestions << endl;
		cout << "Question Level     : " << clsMathGame::GetQuestionLevelText(Quizz.QuestionsLevel) << endl;
		cout << "Op Type            : " << clsMathGame::GetOpTypeSymbol(Quizz.OpType) << endl;
		cout << "Number of Right Answers: " << Quizz.NumberOfRightAnswers << endl;
		cout << "Number of Wrong Answers: " << Quizz.NumberOfWrongAnswers << endl;

		cout << "________________________________\n";

		clsMathGame::SetScreenColor(Quizz.isPass);
	}
		 
	static void _PlayMathGame()
	{

		clsMathGame Quizz(ReadOpType(), ReadQuestionsLevel(), ReadHowManyQuestions());

		Quizz.GenerateQuizzQuestins();
		_AskAndCorrectQuestionListAnswers(Quizz);
		_PrintQizzResults(Quizz);

	}
		 
	static void _StartGame()
	{
		char PlayAgain = 'Y';
		do
		{

			clsMathGame::ResetScreen();
			clsScreen::_DrawHeader("\t   Play Game Screen");

			_PlayMathGame();

			cout << endl << "Do you want to play again ? Y/N ? ";
			cin >> PlayAgain;

		} while (PlayAgain == 'Y' || PlayAgain == 'y');
	}

public:

	static void ShowPlayGameScreen()
	{
		_StartGame();
	}
		 
};


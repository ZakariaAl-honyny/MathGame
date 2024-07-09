#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "clsUitil.h"
#include "clsInputValidate.h"
using namespace std;

class clsMathGame
{

private:

	enum enQuestionsLevel;
	enum enOperationType;

	short _NumberOfQuestions = 0;
	enQuestionsLevel _QuestionsLevel;
	enOperationType _OpType;
	short _NumberOfRightAnswers = 0;
	short _NumberOfWrongAnswers = 0;
	bool _isPass = false;

	struct stQuestion
	{

		int Number1 = 0;
		int Number2 = 0;
		enQuestionsLevel QuestionsLevel;
		enOperationType OpType;
		int CorrectAnswer = 0;
		int PlayerAnswer = 0;
		bool AnswerResult = false;
	
	};

public:

	enum enQuestionsLevel { EasyLevel = 1, MedLevel = 2, HardLevel = 3, Mix = 4 };
	enum enOperationType { Add = 1, Sub = 2, Mul = 3, Div = 4, MixOP = 5 };

	vector <stQuestion> vQuestionList;

	clsMathGame(enOperationType OpType, enQuestionsLevel QuestionsLevel, short NumberOfQuestions)
	{

		_NumberOfQuestions = NumberOfQuestions;
		_QuestionsLevel = QuestionsLevel;
		_OpType = OpType;
		_NumberOfRightAnswers = 0;
		_NumberOfWrongAnswers = 0;
		_isPass = false;

	}
	~clsMathGame()
	{

	}

	void SetNumberOfQuestions(short NumberOfQuestions)
	{
		_NumberOfQuestions = NumberOfQuestions;
	}

	short GetNumberOfQuestions()
	{
		return _NumberOfQuestions;
	}

	__declspec(property(get = GetNumberOfQuestions, put = SetNumberOfQuestions)) short NumberOfQuestions;

	void SetQuestionsLevel(enQuestionsLevel QuestionsLevel)
	{
		_QuestionsLevel = QuestionsLevel;
	}

	enQuestionsLevel GetQuestionsLevel()
	{
		return _QuestionsLevel;
	}

	__declspec(property(get = GetQuestionsLevel, put = SetQuestionsLevel)) enQuestionsLevel QuestionsLevel;

	void SetOpType(enOperationType OpType)
	{
		_OpType = OpType;
	}

	enOperationType GetOpType()
	{
		return _OpType;
	}

	__declspec(property(get = GetOpType, put = SetOpType)) enOperationType OpType;

	void SetNumberOfRightAnswers(short NumberOfRightAnswers)
	{
		_NumberOfRightAnswers = NumberOfRightAnswers;
	}

	short GetNumberOfRightAnswers()
	{
		return _NumberOfRightAnswers;
	}

	__declspec(property(get = GetNumberOfRightAnswers, put = SetNumberOfRightAnswers)) short NumberOfRightAnswers;

	void SetNumberOfWrongAnswers(short NumberOfWrongAnswers)
	{
		_NumberOfWrongAnswers = NumberOfWrongAnswers;
	}

	short GetNumberOfWrongAnswers()
	{
		return _NumberOfWrongAnswers;
	}

	__declspec(property(get = GetNumberOfWrongAnswers, put = SetNumberOfWrongAnswers)) short NumberOfWrongAnswers;

	void SetisPass(bool isPass)
	{
		_isPass = isPass;
	}

	bool GetisPass()
	{
		return _isPass;
	}

	__declspec(property(get = GetisPass, put = SetisPass)) bool isPass;



	static string GetOpTypeSymbol(enOperationType  OpType)
	{
		switch (OpType)
		{
		case enOperationType::Add:
			return "+";
		case enOperationType::Sub:
			return "-";
		case enOperationType::Mul:
			return "*";
		case enOperationType::Div:
			return "/";
		default:
			return "Mix";
		}
	}

	static string GetQuestionLevelText(enQuestionsLevel QuestionLevel)
	{
		string arrQuestionLevelText[4] = { "Easy", "Med", "Hard", "Mix" };
		return arrQuestionLevelText[QuestionLevel - 1];
	}

	static void SetScreenColor(bool RightAnswer)
	{
		if (RightAnswer)
			system("color 2F"); // turn screen to Green
		else
		{
			system("color 4F"); // turn screen to red
			cout << "\a";
		}
	}

	static int SimpleCalCulator(int Number1, int Number2, enOperationType OpType)
	{

		switch (OpType)
		{
		case enOperationType::Add:
			return Number1 + Number2;
		case enOperationType::Sub:
			return Number1 - Number2;
		case enOperationType::Mul:
			return Number1 * Number2;
		case enOperationType::Div:
			return Number1 / Number2;
		default:
			return Number1 + Number2;
		}

	}

	static enOperationType GetRandomOperationType()
	{

		int Op = clsUitil::RandomNumber(1, 4);
		return (enOperationType)Op;

	}

	string GetFinalResultsText()
	{
		if (isPass)
			return "Pass :-)";
		else
			return "Fail :-(";
	}

	static void ResetScreen()
	{
		system("cls"); // Clear Screen
		system("color 0F"); // turn Screen to black Screen
	}

	stQuestion GenerateQuestion()
	{

		stQuestion Question;

		if (QuestionsLevel == enQuestionsLevel::Mix)
		{
			QuestionsLevel = (enQuestionsLevel)clsUitil::RandomNumber(1, 3);
		}

		if (OpType == enOperationType::MixOP)
		{
			OpType = GetRandomOperationType();
		}

		Question.OpType = OpType;

		switch (QuestionsLevel)
		{
		case enQuestionsLevel::EasyLevel:
		{
			Question.Number1 = clsUitil::RandomNumber(1, 10);
			Question.Number2 = clsUitil::RandomNumber(1, 10);

			Question.CorrectAnswer = SimpleCalCulator(Question.Number1, Question.Number2, Question.OpType);

			Question.QuestionsLevel = QuestionsLevel;
			return Question;
		}
		case enQuestionsLevel::MedLevel:
		{
			Question.Number1 = clsUitil::RandomNumber(10, 50);
			Question.Number2 = clsUitil::RandomNumber(10, 50);

			Question.CorrectAnswer = SimpleCalCulator(Question.Number1, Question.Number2, Question.OpType);

			Question.QuestionsLevel = QuestionsLevel;
			return Question;
		}

		case enQuestionsLevel::HardLevel:
		{
			Question.Number1 = clsUitil::RandomNumber(50, 100);
			Question.Number2 = clsUitil::RandomNumber(50, 100);

			Question.CorrectAnswer = SimpleCalCulator(Question.Number1, Question.Number2, Question.OpType);

			Question.QuestionsLevel = QuestionsLevel;
			return Question;
		}

		}

		return Question;
	}

	void GenerateQuizzQuestins()
	{

		for (short Question = 0; Question < NumberOfQuestions; Question++)
		{
			vQuestionList.push_back(GenerateQuestion());
		}
	}

};


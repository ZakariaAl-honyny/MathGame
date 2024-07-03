

#include<iostream>
#include<string>
#include<iomanip>

using namespace std;

enum enQuestionsLevel { EasyLevel = 1, MedLevel = 2, HardLevel = 3, Mix = 4 };
enum enOperationType  { Add = 1, Sub = 2, Mul = 3, Div = 4, MixOP = 5 };

struct stQuestion
{
	int Number1 = 0;
	int Number2 = 0;
	enQuestionsLevel QuestionLevel;
	enOperationType OperationType;
	int CorrectAnswer = 0;
	int PlayerAnswer = 0;
	bool AnswerResult = false;
};

struct stQuizz
{
	stQuestion QuestionList[100];
	short NumberOfQuestions = 0;
	enQuestionsLevel QuestionsLevel;
	enOperationType OpType;
	short NumberOfRightAnswers = 0;
	short NumberOfWrongAnswers = 0;
	bool isPass = false;
};

string GetOpTypeSymbol(enOperationType  OpType)
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

string GetQuestionLevelText(enQuestionsLevel QuestionLevel)
{
	string arrQuestionLevelText[4] = { "Easy", "Med", "Hard", "Mix"};
	return arrQuestionLevelText[QuestionLevel - 1];
}

int RandomNumber(int From, int To)
{
	//Function to Genrate a random number
	int RandNum = rand() % (To - From + 1) + From;
	return RandNum;
}

void SetScreenColor(bool Right)
{
	if (Right)
		system("color 2F"); // turn screen to Green
	else
	{
		system("color 4F"); // turn screen to red
		cout << "\a";
	}
}

short ReadHowManyQuestions()
{
	short NumberOfQuestions = 0;
	do
	{

		cout << "How Many Questions do you want to Answer from 1 to 10? ";
		cin >> NumberOfQuestions;

	} while (NumberOfQuestions < 1 || NumberOfQuestions > 10);

	return NumberOfQuestions;
}

enQuestionsLevel ReadQuestionsLevel()
{
	short QuestionLevel = 0;
	do
	{
		cout << "Enter Questios Level [1]:Easy, [2]:Med, [3]:Hard, [4]:Mix ? ";
		cin >> QuestionLevel;

	} while (QuestionLevel < 1 || QuestionLevel > 4);

	return (enQuestionsLevel)QuestionLevel;
}

enOperationType ReadOpType()
{
	short OpType = 0;
	do
	{
		cout << "Enter Operation Type [1]:Add, [2]:Sub, [3]:Mul, [4]:Div, [5]:Mix  ? ";
		cin >> OpType;

	} while (OpType < 1 || OpType > 5);


	return (enOperationType)OpType;
}

int SimpleCalCulator(int Number1, int Number2, enOperationType OpType)
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

enOperationType GetRandomOperationType()
{
	int Op = RandomNumber(1, 4);
	return (enOperationType)Op;

}

stQuestion GenerateQuestion(enQuestionsLevel QuestionLevel, enOperationType OpType)
{

	stQuestion Question;

	if (QuestionLevel == enQuestionsLevel::Mix)
	{ 
		QuestionLevel = (enQuestionsLevel) RandomNumber(1, 3);
	}

	if (OpType == enOperationType::MixOP)
	{
		OpType = GetRandomOperationType();
	}

	Question.OperationType = OpType;

	switch (QuestionLevel)
	{
	case enQuestionsLevel::EasyLevel:
		Question.Number1 = RandomNumber(1, 10);
		Question.Number2 = RandomNumber(1, 10);

		Question.CorrectAnswer = SimpleCalCulator(Question.Number1, Question.Number2, Question.OperationType);

		Question.QuestionLevel = QuestionLevel;
		return Question;
	case enQuestionsLevel::MedLevel:
		Question.Number1 = RandomNumber(10, 50);
		Question.Number2 = RandomNumber(10, 50);

		Question.CorrectAnswer = SimpleCalCulator(Question.Number1, Question.Number2, Question.OperationType);

		Question.QuestionLevel = QuestionLevel;
		return Question;
	case enQuestionsLevel::HardLevel:
		Question.Number1 = RandomNumber(50, 100);
		Question.Number2 = RandomNumber(50, 100);

		Question.CorrectAnswer = SimpleCalCulator(Question.Number1, Question.Number2, Question.OperationType);

		Question.QuestionLevel = QuestionLevel;
		return Question;
	}
	return Question;
}

void GenerateQuizzQuestins(stQuizz& Quizz)
{

	for (short Question = 0; Question < Quizz.NumberOfQuestions; Question++)
	{
		Quizz.QuestionList[Question] = GenerateQuestion(Quizz.QuestionsLevel, Quizz.OpType);
	}
}

int ReadQuestionAnswer()
{
	int Answer = 0;
	cin >> Answer;
	return Answer;
}

void PrintTheQuestion(stQuizz& Quizz, short QestionNumber)
{
	cout << "\n";
	cout << "Question [" << QestionNumber + 1 << "/" << Quizz.NumberOfQuestions << "]\n\n";
	cout << Quizz.QuestionList[QestionNumber].Number1 << endl;
	cout << Quizz.QuestionList[QestionNumber].Number2 << " ";
    cout << GetOpTypeSymbol(Quizz.QuestionList[QestionNumber].OperationType);
	cout << "\n_____________" << endl;
}

void CorrectTheQuestionAnswer(stQuizz& Quizz, short QestionNumber)
{
	if (Quizz.QuestionList[QestionNumber].PlayerAnswer != Quizz.QuestionList[QestionNumber].CorrectAnswer)
	{
		Quizz.QuestionList[QestionNumber].AnswerResult = false;
		Quizz.NumberOfWrongAnswers++;

		cout << "Wrong Answer :-( \n";
		cout << "The right answer is: ";
		cout << Quizz.QuestionList[QestionNumber].CorrectAnswer;
		cout << "\n";
	}
	else
	{
		Quizz.QuestionList[QestionNumber].AnswerResult = true;
		Quizz.NumberOfRightAnswers++;

		cout << "\nRight Answer :-)\n";
	}
	cout << endl;

	SetScreenColor(Quizz.QuestionList[QestionNumber].AnswerResult);
}

void AskAndCorrectQuestionListAnswers(stQuizz& Quizz)
{

	for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++)
	{
		PrintTheQuestion(Quizz, QuestionNumber);

		Quizz.QuestionList[QuestionNumber].PlayerAnswer = 
		ReadQuestionAnswer();

		CorrectTheQuestionAnswer(Quizz, QuestionNumber);
	}

	Quizz.isPass = (Quizz.NumberOfRightAnswers >= Quizz.NumberOfWrongAnswers);
}

string GetFinalResultsText(bool Pass)
{
	if (Pass)
		return "Pass :-)";
	else
		return "Fail :-(";
}

void PrintQizzResults(stQuizz Quizz)
{
	cout << "\n";
	cout << "________________________________\n\n";

	cout << "Final results is " << GetFinalResultsText(Quizz.isPass);
	cout << "\n________________________________\n\n";

	cout << "Number of Questions: " << Quizz.NumberOfQuestions << endl;
	cout << "Question Level     : " << GetQuestionLevelText(Quizz.QuestionsLevel) << endl;
	cout << "Op Type            : " << GetOpTypeSymbol(Quizz.OpType) << endl;
	cout << "Number of Right Answers: " << Quizz.NumberOfRightAnswers << endl;
	cout << "Number of Wrong Answers: " << Quizz.NumberOfWrongAnswers << endl;

	cout << "________________________________\n";

	SetScreenColor(Quizz.isPass);
}

void PlayMathGame()
{

	stQuizz Quizz;

	Quizz.NumberOfQuestions = ReadHowManyQuestions();
	Quizz.QuestionsLevel = ReadQuestionsLevel();
	Quizz.OpType = ReadOpType();
	
	GenerateQuizzQuestins(Quizz);
	AskAndCorrectQuestionListAnswers(Quizz);
	PrintQizzResults(Quizz);
}

void ResetScreen()
{
	system("cls");
	system("color 0F");
}

void StartGame()
{
	char PlayAgain = 'Y';
	do
	{

		ResetScreen();
		PlayMathGame();

		cout << endl << "Do you want to play again ? Y/N ? ";
		cin >> PlayAgain;

	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
	//Seeds the random number generator in C++, called only once
	srand((unsigned)time(NULL));

	StartGame();

	system("pause");
	return 0;
}
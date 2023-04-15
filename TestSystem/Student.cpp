#include "TestSystem.h"

using namespace std;
#define lenmas 100

struct randQuestForFinalTest
{
	int randTheme;
	int randQuest;
};

int IsUniqNumbers(int* UniqNumbers, int elem, int& k)
{
	for (int i = 0; i < lenmas; ++i)
	{
		if (elem == UniqNumbers[i])
		{
			return 0;
		}

	}
	UniqNumbers[k] = elem;
	k++;
	return 1;
}

int IsUniqRandomNumbersForFinalTest(randQuestForFinalTest* fin, int randomquest, int randomtheme, int& k)
{
	for (int i = 0; i < lenmas; ++i)
	{
		if ((fin[i].randQuest == randomquest) && (fin[i].randTheme == randomtheme))
		{
			return 0;
		}
		if ((fin[i].randTheme == randomtheme) && (fin[i + 1].randTheme == randomtheme))
		{
			return 0;
		}

	}
	fin[k].randQuest == randomquest;
	fin[k].randTheme == randomtheme;
	k++;
	return 1;
}
int trainingTheme(DBQuestion& DBquestions)
{
	srand(time(NULL));
	int UniqNumbers[lenmas];
	int selecttheme = -2; int wrong[10] = { 0 }; int k = 0; int m = 0;
	int randomQuest;
	do
	{
		do {
			cout << "Выберите тему: \n1 - Циклы\n2 - Массивы(одномерные и двумерные)\n3 - Строки\n4 - Рекурсия\n5 - Структуры\n6 - Файлы\n7 - Адреса и указатели\n8 - Динамическая память\n";
			cin >> selecttheme;
		} while (!isCorrectInput());
	} while (selecttheme < 1 || selecttheme >8);
	cout << "Выбранная тема: \n" << DBquestions.themes[selecttheme].name << endl;
	
	int answer = 0; int complete = 0;
	for (int i = 0; i < 10; ++i)
	{
		do {
			randomQuest = rand() % DBquestions.themes[selecttheme].countQuestions-1;
		} while (!IsUniqNumbers(UniqNumbers, randomQuest, m) || (randomQuest == -1 ));
		//вывод вопроса
		cout << "Вопрос №" << i + 1 << " :" << endl << DBquestions.themes[selecttheme].questions[randomQuest].text<<endl;
		//вывод ответов
		for (int j = 0; j < 4; ++j) cout << j + 1 << " :" << DBquestions.themes[selecttheme].questions[randomQuest].answers[j].text << endl;
		do
		{
			do{
				do{
					cout << "Выберите правильный ответ цифрой от 1 до 4: ";
					cin >> answer;
				} while (!isCorrectInput());
			} while ((answer != 1 && answer != 2 && answer != 3 && answer != 4));
			answer -= 1;
		} while ((answer != (DBquestions.themes[selecttheme].questions[randomQuest].rightAnswer)));


	}
	cout << "Тренинг завершен. Спасибо.\n";
	return 1;
}

int TestTheme(DBUsers& users,DBQuestion& DBquestions)
{
	srand(time(NULL));
	int UniqNumbers[lenmas];
	int selecttheme = -2; int wrong[10] = { 0 }; int k = 0; int m = 0;
	int randomQuest;
	do
	{
		do{
			cout << "Выберите тему: \n1 - Циклы\n2 - Массивы(одномерные и двумерные)\n3 - Строки\n4 - Рекурсия\n5 - Структуры\n6 - Файлы\n7 - Адреса и указатели\n8 - Динамическая память\n";
			cin >> selecttheme;
		} while (!isCorrectInput());
		} while (selecttheme < 1 && selecttheme >8);
		selecttheme -= 1;
	cout << "Выбранная тема: \n" << DBquestions.themes[selecttheme].name << endl;
	int answer = 0; int complete = 0;
	for (int i = 0; i < 10; ++i)
	{
		do {
			randomQuest = rand() % DBquestions.themes[selecttheme].countQuestions - 1;
		} while (!IsUniqNumbers(UniqNumbers, randomQuest,m) || (randomQuest == -1));
		//вывод вопроса
		cout << "Вопрос №" << i + 1 << " :" << endl << DBquestions.themes[selecttheme].questions[randomQuest].text<<endl;
		//вывод ответов
		for (int j = 0; j < 4; ++j) cout << j + 1 << " :" << DBquestions.themes[selecttheme].questions[randomQuest].answers[j].text << endl;
		do
		{
			do{
			cout << "Выберите правильный ответ цифрой от 1 до 4: ";
			cin >> answer;
			} while (!isCorrectInput());
			
		} while (answer != 1 && answer != 2 && answer != 3 && answer != 4);
		answer -= 1;
		if(answer == DBquestions.themes[selecttheme].questions[randomQuest].rightAnswer)complete++;
		else
		{
			wrong[k] = randomQuest;
			k++;
		}


	}
	cout << "Количество правильных ответов: " << complete << " из 10\n\n";
	cout << "Разберем ошибки: \n";
	for (int n = 0; n < k; n++)
	{
		
		cout << "Вопрос №" << n +1<< " :" << endl << DBquestions.themes[selecttheme].questions[wrong[k]].text<<endl;
		cout << "Верный ответ: " << DBquestions.themes[selecttheme].questions[wrong[k]].rightAnswer+1<<endl;
	}
	double res = double(complete) / 10;
	int lastres;
	if (res >= 0.95)
	{
		lastres = 5;
		cout << endl << "Ваша оценка 5\n";
	}

	if (res >= 0.70)
	{
		lastres = 4;
		cout << endl << "Ваша оценка 4\n";
	}

	if (res >= 0.50)
	{
		lastres = 3;
		cout << endl << "Ваша оценка 3\n";
	}

	if (res <= 0.49)
	{
		lastres = 2;
		cout << endl << "Ваша оценка 2\n";
	}
	users.students->marks[selecttheme] = lastres;
	return 1;
}

int finalTest(DBUsers& users, DBQuestion& DBquestions)
{
	randQuestForFinalTest randomfintest[50];
	srand(time(NULL));
	int UniqNumbersQuest[lenmas];
	int UniqNumbersThemeAndQuest[lenmas];
	 int wrongQuest[45] = { 0 }; int k = 0; int m = 0;
	 int wrongTheme[45] = { 0 };
	int randomQuest = 0;
	int answer = 0; int complete = 0;
	for (int i = 0; i < 40; ++i)
	{
		do{
		randomfintest->randTheme = (rand() % 8) - 1;
		randomfintest->randQuest = (rand() % DBquestions.themes[randomfintest->randTheme].countQuestions) - 1;
		} while (!IsUniqRandomNumbersForFinalTest(randomfintest, randomfintest->randQuest, randomfintest->randTheme, m) && ((randomfintest->randQuest == -1) || (randomfintest->randTheme == -1)));
		//вывод вопроса
		cout << "Тема"<<" :" << DBquestions.themes[randomfintest->randTheme].name<<endl;
		cout << "Вопрос №" << i + 1 << " :" << endl << DBquestions.themes[randomfintest->randTheme].questions[randomfintest->randQuest].text<<endl;
		//вывод ответов
		for (int j = 0; j < 4; ++j) cout << j + 1 << " :" << DBquestions.themes[randomfintest->randTheme].questions[randomfintest->randQuest].answers[j].text << endl;
		do
		{
			cout << "Выберите правильный ответ цифрой от 1 до 4: ";
			do{
				cin >> answer;
			} while (!isCorrectInput());
		} while (answer != 1 && answer != 2 && answer != 3 && answer != 4);
		if (answer == DBquestions.themes[randomfintest->randTheme].questions[randomfintest->randQuest].rightAnswer)complete++;
		else
		{
			wrongTheme[k] = randomfintest->randTheme;
			wrongQuest[k] = randomfintest->randQuest;
			k++;
		}


	}
	cout << "Разберем ошибки: \n";
	cout << "Количество правильных ответов: " << complete << " из 40\n";
	for (int n = 0; n < k; n++)
	{
		
		cout << "Вопрос №" << n + 1 << " :" << endl << DBquestions.themes[wrongTheme[n]].questions[wrongQuest[n]].text << endl;
		cout << "Верный ответ: " << DBquestions.themes[wrongTheme[n]].questions[wrongQuest[n]].rightAnswer+1 <<endl;
	}
	double res = double(complete) / 40;
	int lastres;
	if (res >= 0.95)
	{
		lastres = 5;
		cout << endl << "Ваша оценка 5\n";
	}

	if (res >= 0.70)
	{
		lastres = 4;
		cout << endl << "Ваша оценка 4\n";
	}

	if (res >= 0.50)
	{
		lastres = 3;
		cout << endl << "Ваша оценка 3\n";
	}

	if (res <= 0.49)
	{
		lastres = 2;
		cout << endl << "Ваша оценка 2\n";
	}
	users.students->finalMark = lastres;

	return 0;
}

int StudentMenu(DBUsers& users,DBQuestion& questions)
{
	int k = 0;
	
	int choose = -2;
	do
	{
		do {
			cout << "Выберите: \n1 - Тренинг по выбранной вами теме\n2 - Тест по выбранной вами теме\n3 - Итоговый тест\n4 - Выход\n";
			cin >> choose;
		} while (!isCorrectInput());

		if (choose == 4)
			return 0;
	} while (choose != 1 && choose != 2 && choose != 3);

	switch (choose)
	{
	case 1:
	{
		trainingTheme(questions);

	}break;
	case 2:
	{
		TestTheme(users,questions);

	}break;
	case 3:
	{
		finalTest(users, questions);
	}
	default:
	{
		return 0;
	}break;
	}
}
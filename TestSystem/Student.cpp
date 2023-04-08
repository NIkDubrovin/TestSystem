#include "TestSystem.h"
#include <locale.h>
#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;
#define lenmas 50


int IsUniqNumbers(int* UniqNumbers, int elem)
{
	for (int i = 0; i < lenmas; ++i)
	{
		if (elem == UniqNumbers[i]) return 0;
	}
	return 1;
}
int trainingTheme(DBQuestion& DBquestions)
{
	srand(time(NULL));
	int UniqNumbers[lenmas];
	int selecttheme = -2; int wrong[10] = { 0 }; int k = 0;
	int randomQuest;
	do
	{
		cout << "Выберите тему: \n1 - Циклы\n2 - Массивы(одномерные и двумерные)\n3 - Строки\n4 - Рекурсия\n5 - Структуры\n6 - Файлы\n7 - Адреса и указатели\n8 - Динамическая память\n";
	} while (selecttheme < 1 && selecttheme >8);
	cout << "Выбранная тема: \n" << DBquestions.topics[selecttheme].name << endl;
	int answer = 0; int complete = 0;
	for (int i = 0; i < 10; ++i)
	{
		do {
			randomQuest = rand() % DBquestions.topics[selecttheme].countQuestions;
		} while (!IsUniqNumbers(UniqNumbers, randomQuest));
		//вывод вопроса
		cout << "Вопрос №" << i + 1 << " :" << endl << DBquestions.topics[selecttheme].questions[randomQuest].text;
		//вывод ответов
		for (int j = 0; j < 4; ++j) cout << i + 1 << " :" << DBquestions.topics[selecttheme].questions[randomQuest].answers[j].text << endl;
		do
		{
			cout << "Выберите правильный ответ цифрой от 1 до 4";
			cin >> answer;
		} while ((answer != 1 && answer != 2 && answer != 3 && answer != 4) && (answer != DBquestions.topics[selecttheme].questions[randomQuest].rightAnswer));


	}
	cout << "Количество правильных ответов: " << complete << " из 10";
	return 1;
}
void StudentMenu(DBQuestion& questions)
{

	setlocale(LC_ALL, "RUS");
	int choose = -2;
	do
	{
		cout << "Выберите: \n1 - Тренинг по выбранной вами теме\n2 - Тест по выбранной вами теме\n3 - Итоговый тест\n";
		cin >> choose;
	} while (choose != 1 && choose != 2 && choose != 3);

	switch (choose)
	{
	case 1:
	{
		trainingTheme(questions);

	}break;
	case 2:
	{
		int selecttheme = -2;
		do
		{
			cout << "Выберите тему: \n1 - Циклы\n2 - Массивы(одномерные и двумерные)\n3 - Строки\n4 - Рекурсия\n5 - Структуры\n6 - Файлы\n7 - Адреса и указатели\n8 - Динамическая память\n";
		} while (selecttheme < 1 && selecttheme >8);

	}break;
	case 3:
	{

	}
	}
}
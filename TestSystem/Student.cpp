#include "TestSystem.h"
#include <locale.h>
#include <iostream>
#include <time.h>
#include <stdlib.h>
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
		cout << "�������� ����: \n1 - �����\n2 - �������(���������� � ���������)\n3 - ������\n4 - ��������\n5 - ���������\n6 - �����\n7 - ������ � ���������\n8 - ������������ ������\n";
	} while (selecttheme < 1 && selecttheme >8);
	cout << "��������� ����: \n" << DBquestions.topics[selecttheme].name << endl;
	int answer = 0; int complete = 0;
	for (int i = 0; i < 10; ++i)
	{
		do {
			randomQuest = rand() % DBquestions.topics[selecttheme].countQuestions;
		} while (!IsUniqNumbers(UniqNumbers, randomQuest, m));
		//����� �������
		cout << "������ �" << i + 1 << " :" << endl << DBquestions.topics[selecttheme].questions[randomQuest].text;
		//����� �������
		for (int j = 0; j < 4; ++j) cout << i + 1 << " :" << DBquestions.topics[selecttheme].questions[randomQuest].answers[j].text << endl;
		do
		{
			cout << "�������� ���������� ����� ������ �� 1 �� 4";
			cin >> answer;
		} while ((answer != 1 && answer != 2 && answer != 3 && answer != 4) && (answer != DBquestions.topics[selecttheme].questions[randomQuest].rightAnswer));


	}
	cout << "������� ��������. �������.\n";
	return 1;
}

int TestTheme(DBQuestion& DBquestions)
{
	srand(time(NULL));
	int UniqNumbers[lenmas];
	int selecttheme = -2; int wrong[10] = { 0 }; int k = 0; int m = 0;
	int randomQuest;
	do
	{
		cout << "�������� ����: \n1 - �����\n2 - �������(���������� � ���������)\n3 - ������\n4 - ��������\n5 - ���������\n6 - �����\n7 - ������ � ���������\n8 - ������������ ������\n";
	} while (selecttheme < 1 && selecttheme >8);
	cout << "��������� ����: \n" << DBquestions.topics[selecttheme].name << endl;
	int answer = 0; int complete = 0;
	for (int i = 0; i < 10; ++i)
	{
		do {
			randomQuest = rand() % DBquestions.topics[selecttheme].countQuestions;
		} while (!IsUniqNumbers(UniqNumbers, randomQuest,m));
		//����� �������
		cout << "������ �" << i + 1 << " :" << endl << DBquestions.topics[selecttheme].questions[randomQuest].text;
		//����� �������
		for (int j = 0; j < 4; ++j) cout << i + 1 << " :" << DBquestions.topics[selecttheme].questions[randomQuest].answers[j].text << endl;
		do
		{
			cout << "�������� ���������� ����� ������ �� 1 �� 4";
			cin >> answer;
		} while (answer != 1 && answer != 2 && answer != 3 && answer != 4);
		if(answer == DBquestions.topics[selecttheme].questions[randomQuest].rightAnswer)complete++;
		else
		{
			wrong[k] = i;
			k++;
		}


	}
	cout << "���������� ���������� �������: " << complete << " �� 10\n";
	for (int n = 0; n < k; n++)
	{
		cout << "�������� ������: \n";
		cout << "������ �" << wrong[n] << " :" << endl << DBquestions.topics[selecttheme].questions[randomQuest].text;
		cout << "������ �����: " << DBquestions.topics[selecttheme].questions[randomQuest].rightAnswer;
	}
	return 1;
}

int TestTheme(Student* student, DBQuestion& DBquestions)
{
	srand(time(NULL));
	int UniqNumbers[lenmas];
	int selecttheme = -2; int wrong[10] = { 0 }; int k = 0; int m = 0;
	int randomQuest;
	do
	{
		cout << "�������� ����: \n1 - �����\n2 - �������(���������� � ���������)\n3 - ������\n4 - ��������\n5 - ���������\n6 - �����\n7 - ������ � ���������\n8 - ������������ ������\n";
	} while (selecttheme < 1 && selecttheme >8);
	cout << "��������� ����: \n" << DBquestions.topics[selecttheme].name << endl;
	int answer = 0; int complete = 0;
	for (int i = 0; i < 10; ++i)
	{
		do {
			randomQuest = rand() % DBquestions.topics[selecttheme].countQuestions;
		} while (!IsUniqNumbers(UniqNumbers, randomQuest,m));
		//����� �������
		cout << "������ �" << i + 1 << " :" << endl << DBquestions.topics[selecttheme].questions[randomQuest].text;
		//����� �������
		for (int j = 0; j < 4; ++j) cout << i + 1 << " :" << DBquestions.topics[selecttheme].questions[randomQuest].answers[j].text << endl;
		do
		{
			cout << "�������� ���������� ����� ������ �� 1 �� 4";
			cin >> answer;
		} while (answer != 1 && answer != 2 && answer != 3 && answer != 4);
		if (answer == DBquestions.topics[selecttheme].questions[randomQuest].rightAnswer)complete++;
		else
		{
			wrong[k] = i;
			k++;
		}


	}
	cout << "���������� ���������� �������: " << complete << " �� 10\n";
	for (int n = 0; n < k; n++)
	{
		cout << "�������� ������: \n";
		cout << "������ �" << wrong[n] << " :" << endl << DBquestions.topics[selecttheme].questions[randomQuest].text;
		cout << "������ �����: " << DBquestions.topics[selecttheme].questions[randomQuest].rightAnswer;
	}
	double res = (10 - k) / 10;
	int lastres;
	if (res >= 0.95)
	{
		lastres = 5;
		cout << endl << "���� ������ 5";
	}

	if (res >= 0.70)
	{
		lastres = 4;
		cout << endl << "���� ������ 4";
	}

	if (res >= 0.50)
	{
		lastres = 3;
		cout << endl << "���� ������ 3";
	}

	if (res <= 0.49)
	{
		lastres = 2;
		cout << endl << "���� ������ 2";
	}
	student->marks[selecttheme-1] = lastres;

	return 0;
}

int finalTest(Student* student, DBQuestion& DBquestions)
{
	randQuestForFinalTest randomfintest[50];
	srand(time(NULL));
	int UniqNumbersQuest[lenmas];
	int UniqNumbersThemeAndQuest[lenmas];
	int randomTheme;
	int selecttheme = -2; int wrong[10] = { 0 }; int k = 0; int m = 0;
	int randomQuest;
	int answer = 0; int complete = 0;
	for (int i = 0; i < 40; ++i)
	{
		do{
		randomfintest->randTheme = rand() % 8;
		randomfintest->randQuest = rand() % DBquestions.topics[randomfintest->randTheme].countQuestions;
		} while (!IsUniqRandomNumbersForFinalTest(randomfintest, randomfintest->randQuest, randomfintest->randTheme, m));
		//����� �������
		cout << "������ �" << i + 1 << " :" << endl << DBquestions.topics[randomfintest->randTheme].name;
		cout << "������ �" << i + 1 << " :" << endl << DBquestions.topics[randomfintest->randTheme].questions[randomfintest->randQuest].text;
		//����� �������
		for (int j = 0; j < 4; ++j) cout << i + 1 << " :" << DBquestions.topics[selecttheme].questions[randomQuest].answers[j].text << endl;
		do
		{
			cout << "�������� ���������� ����� ������ �� 1 �� 4";
			cin >> answer;
		} while (answer != 1 && answer != 2 && answer != 3 && answer != 4);
		if (answer == DBquestions.topics[selecttheme].questions[randomQuest].rightAnswer)complete++;
		else
		{
			wrong[k] = i;
			k++;
		}


	}
	cout << "���������� ���������� �������: " << complete << " �� 10\n";
	for (int n = 0; n < k; n++)
	{
		cout << "�������� ������: \n";
		cout << "������ �" << wrong[n] << " :" << endl << DBquestions.topics[selecttheme].questions[randomQuest].text;
		cout << "������ �����: " << DBquestions.topics[selecttheme].questions[randomQuest].rightAnswer;
	}
	double res = (10 - k) / 10;
	int lastres;
	if (res >= 0.95)
	{
		lastres = 5;
		cout << endl << "���� ������ 5";
	}

	if (res >= 0.70)
	{
		lastres = 4;
		cout << endl << "���� ������ 4";
	}

	if (res >= 0.50)
	{
		lastres = 3;
		cout << endl << "���� ������ 3";
	}

	if (res <= 0.49)
	{
		lastres = 2;
		cout << endl << "���� ������ 2";
	}
	student->finalMark = lastres;

	return 0;
}

void StudentMenu(DBQuestion& questions)
{
	int k = 0;
	setlocale(LC_ALL, "RUS");
	int choose = -2;
	do
	{
		cout << "��������: \n1 - ������� �� ��������� ���� ����\n2 - ���� �� ��������� ���� ����\n3 - �������� ����\n";
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
		TestTheme(questions);

	}break;
	case 3:
	{

	}
	}
}
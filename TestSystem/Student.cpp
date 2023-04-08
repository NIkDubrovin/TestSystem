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
		cout << "�������� ����: \n1 - �����\n2 - �������(���������� � ���������)\n3 - ������\n4 - ��������\n5 - ���������\n6 - �����\n7 - ������ � ���������\n8 - ������������ ������\n";
	} while (selecttheme < 1 && selecttheme >8);
	cout << "��������� ����: \n" << DBquestions.topics[selecttheme].name << endl;
	int answer = 0; int complete = 0;
	for (int i = 0; i < 10; ++i)
	{
		do {
			randomQuest = rand() % DBquestions.topics[selecttheme].countQuestions;
		} while (!IsUniqNumbers(UniqNumbers, randomQuest));
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
	cout << "���������� ���������� �������: " << complete << " �� 10";
	return 1;
}
void StudentMenu(DBQuestion& questions)
{

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
		int selecttheme = -2;
		do
		{
			cout << "�������� ����: \n1 - �����\n2 - �������(���������� � ���������)\n3 - ������\n4 - ��������\n5 - ���������\n6 - �����\n7 - ������ � ���������\n8 - ������������ ������\n";
		} while (selecttheme < 1 && selecttheme >8);

	}break;
	case 3:
	{

	}
	}
}
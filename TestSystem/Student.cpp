#include "TestSystem.h"
#include <locale.h>
#include <iostream>
using namespace std;

int main()
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
		int selecttheme = -2;
		do
		{
			cout << "��������: \n1 - ������� �� ��������� ���� ����\n2 - ���� �� ��������� ���� ����\n3 - �������� ����\n";
			cin >> choose;
		} while (selecttheme < 1 && selecttheme >8);
	}
	}
	return 0;
}
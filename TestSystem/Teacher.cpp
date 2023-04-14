#include "TestSystem.h"
using namespace std;
int add_student(Student& student)
{
	return 0;
}
int del_student(Student& student)
{
	return 0;
}
int changeProgress_student(DBUsers & use, DBQuestion & question)
{
	int changeMark = 0;
	int chooseStudent = 0, chooseTheme = 0;
	cout << "������ ���������" << endl;
	for (int i = 0; i < use.countStudents; i++)
	{
		cout << i + 1 << " - " << use.students[i].lastName << " " << use.students[i].firstName << endl;
	}
	cout << "�������� �������� ��� �������� ������ �������� ������: "; cin >> chooseStudent;
	while (!isCorrectInput())
	{
		cin >> chooseStudent;
	}
	while (chooseStudent > use.countStudents && chooseStudent < 1)
	{
		cout << "������ �������� ���. �������� �������� ��� �������� ������ �������� ������: "; cin >> chooseStudent;
		while (!isCorrectInput())
		{
			cin >> chooseStudent;
		}
	}
	chooseStudent--;
	for (int i = 0; i < 8; i++)
	{
		cout<< i+1 << " - " << question.themes[i].name << "\t" << use.students[chooseStudent].marks[i] << endl;
	}
	cout << "�������� ���� ��� ��������� ���������: "; cin >> chooseTheme;
	while (!isCorrectInput())
	{
		cin >> chooseTheme;
	}
	while (chooseTheme > 8 || chooseTheme < 1)
	{
		cout << "����� ���� ���. �������� ���� ��� ��������� ���������: "; cin >> chooseTheme;
		while (!isCorrectInput())
		{
			cin >> chooseTheme;
		}
	}
	chooseTheme--;
	cout << "������� ����� ������: "; cin >> changeMark;
	while (!isCorrectInput())
	{
		cin >> changeMark;
	}
	while (changeMark < 2 || changeMark > 5)
	{
		cout << "������ �������� � 5 - �� ������� �������. ������� ����� ������: "; cin >> changeMark;
		while (!isCorrectInput())
		{
			cin >> changeMark;
		}
	}
	use.students[chooseStudent].marks[chooseTheme] = changeMark;
	return 1;
}
void outputStudents(DBUsers & use, DBQuestion& question)
{
	int chooseTheme = 0, chooseTheme1 = 0;
	do{
	cout << "1 - �� ���� �����\n2 - �� ���������� ����\n3 - ������ �������� ����\n4 - ������ ������� ����\n0 - �����\n�������� ������� ������: "; cin >> chooseTheme;
	while (!isCorrectInput())
	{
		cin >> chooseTheme;
	}
		if (chooseTheme == 1)
		{
			//all them
			for (int i = 0; i < use.countStudents; i++)
			{
				cout << use.students[i].lastName << " " << use.students[i].firstName << endl;
				for (int j = 0; j < 8; j++)
				{
					cout << question.themes[j].name << " " << use.students[i].marks[j] << endl;
				}
				cout << endl << endl;
			}
		}
		else if (chooseTheme == 2)
		{
			//currThme
			for (int i = 0; i < 8; i++)
			{
				cout<< i+1 << " - " << question.themes[i].name << endl;
			}

			cout << "������� ���� ��� ������ ������ ���������:";

			cin >> chooseTheme1;
			while (!isCorrectInput())
			{
				cin >> chooseTheme1;
			}
			while (chooseTheme1 < 1 || chooseTheme1 > 8)
			{
				cout << "�������� ����� ����. ������� ����� ����: ";
				cin >> chooseTheme1;
				while (!isCorrectInput())
				{
					cin >> chooseTheme1;
				}
			}
			chooseTheme1--;
			for (int i = 0; i < use.countStudents; i++)
			{
				cout << use.students[i].lastName << " " << use.students[i].firstName << " " << use.students[i].marks[chooseTheme1] << endl;
			}
		}
		else if (chooseTheme == 3)
		{
			//finalTest
			for (int i = 0; i < use.countStudents; i++)
			{
				cout << use.students[i].lastName << " " << use.students[i].firstName << " " << use.students[i].finalMark << endl;
			}

		}
		else if (chooseTheme == 4)
		{
			//avg
			for (int i = 0; i < use.countStudents; i++)
			{
				cout << use.students[i].lastName << " " << use.students[i].firstName << " " << use.students[i].averageMark << endl;
			}
		}
		else if(chooseTheme < 0 && chooseTheme > 4)
		{
			cout << "������������ ����. ������� ������� ������:"; cin >> chooseTheme;
			while (!isCorrectInput())
			{
				cin >> chooseTheme;
			}
		}
	} while (chooseTheme != 0);
}
void Filtr(DBUsers& use, DBQuestion & question)
{
	double mark_choice = 0, num_out = 0;
	int num_theme = 0;
	int cnt = 0;
	do
	{
		cout << "1 - �� ���� �����\n2 - �� ���������� ����\n3 - ������ �������� ����\n4 - ������ ������� ����\n0 - �����\n�������� ������� ����������: "; cin >> num_out;
		while (!isCorrectInput())
		{
			cin >> num_out;
		}
		if (num_out == 1)
		{
			cout << "������� ������ ������ ��� ������: ";
			cin >> mark_choice;
			while (!isCorrectInput())
			{
				cin >> mark_choice;
			}
			while (mark_choice > 5 || mark_choice < 2)
			{
				cout << "������ ������� �����������. ������� ������ ������ ��� ������: ";
				cin >> mark_choice;
				while (!isCorrectInput())
				{
					cin >> mark_choice;
				}
			}
			mark_choice = (int)mark_choice;
			for (int i = 0; i < use.countStudents; i++)
			{
				for (int j = 0; j < 8; j++)
				{
					if (use.students[i].marks[j] == mark_choice)
					{
						cout << use.students[i].lastName << " " << use.students[i].firstName << endl;
						cout << question.themes[j].name <<endl << "������: " << use.students[i].marks[j] << endl;
						cnt++;
					}
				}
			}
			if (cnt == 0)
				cout << "�� ������� ��������� � ������� " << mark_choice << endl;
			cnt = 0;
		}
		if (num_out == 2)
		{
			cout << "������� ������ ������ ��� ������: ";
			cin >> mark_choice;
			while (!isCorrectInput())
			{
				cin >> mark_choice;
			}
			while (mark_choice > 5 || mark_choice < 2)
			{
				cout << "������ ������� �����������. ������� ������ ������ ��� ������: "; 
				cin >> mark_choice;
				while (!isCorrectInput())
				{
					cin >> mark_choice;
				}
			}
			mark_choice = (int)mark_choice;
			for (int i = 0; i < 8; i++)
			{
				cout << i + 1 << " - " << question.themes[i].name << endl;
			}
			cout << "������� ����� ����, �� ������� ����� ������������ ���������: ";
			cin >> num_theme;
			while (!isCorrectInput())
			{
				cin >> num_theme;
			}
			while (num_theme < 1 || num_theme > 8)
			{
				cout << "������, ����� ���� ���. ������� ����� ����: "; cin >> num_theme;
				while (!isCorrectInput())
				{
					cin >> num_theme;
				}
			}
			num_theme--;
			for (int i = 0; i < use.countStudents; i++)
			{
				if (use.students[i].marks[num_theme] == mark_choice)
				{
					cout << use.students[i].lastName << " " << use.students[i].firstName << endl;
					cout << "������: " << mark_choice;
					cnt++;
				}
			}
			if (cnt == 0)
				cout << "�� ������� ��������� � ������� " << mark_choice << endl;
			cnt = 0;
		}
		if (num_out == 3)
		{
			cout << "������� ������ ������ ��� ������: ";
			cin >> mark_choice;
			while (!isCorrectInput())
			{
				cin >> mark_choice;
			}
			while (mark_choice > 5 || mark_choice < 2)
			{
				cout << "������ ������� �����������. ������� ������ ������ ��� ������: ";
				cin >> mark_choice;
				while (!isCorrectInput())
				{
					cin >> mark_choice;
				}
			}
			mark_choice = (int)mark_choice;
			for (int i = 0; i < use.countStudents; i++)
			{
				if (use.students[i].finalMark == mark_choice)
				{
					cout << use.students[i].lastName << " " << use.students[i].firstName << endl << "������: " << use.students[i].finalMark << endl;
					cnt++;
				}
			}
			if (cnt == 0)
				cout << "�� ������� ��������� � ������� " << mark_choice << endl;
			cnt = 0;
		}
		if (num_out == 4)
		{
			cout << "������� ������ ������ ��� ������: ";
			cin >> mark_choice;
			while (!isCorrectInput())
			{
				cin >> mark_choice;
			}
			while (mark_choice > 5 || mark_choice < 2)
			{
				cout << "������ ������� �����������. ������� ������ ������ ��� ������: ";
				cin >> mark_choice;
				while (!isCorrectInput())
				{
					cin >> mark_choice;
				}
			}
			for (int i = 0; i < use.countStudents; i++)
			{
				cout << use.students[i].lastName << " " << use.students[i].firstName;
				if (use.students[i].averageMark == mark_choice)
				{
					cout << use.students[i].lastName << " " << use.students[i].firstName << endl;
					cout << "������: " << use.students[i].averageMark << endl;
					cnt++;
				}
			}
			if (cnt == 0)
				cout << "�� ������� ��������� � ������� " << mark_choice << endl;
			cnt = 0;
		}
		if (num_out < 0 && num_out > 4)
		{
			cout << "�� ���������� ����. �������� ������� ����������: "; cin >> num_out;
			while (!isCorrectInput())
			{
				cin >> num_out;
			}
		}
	} while (num_out != 0);
}
void Sorted(Student& student, Theme& theme)
{
	cout << " ";
}
void TeacherMain(DBUsers& Dbusers, DBQuestion& question)
{

	int choice = 0, choice1 = 0, choice2 = 0;
	do {
		std::cout << "����� �������������.\n1 - �������������� ��������\n2 - ������ �� ������� ���������\n0 - �����\n������� ����� ��������� ��������: ";
		std::cin >> choice;
		while (!isCorrectInput())
		{
			cin >> choice;
		}
		switch (choice)
		{
		case 1:
		{
			//Question
			do {
				std::cout << "�������������� ��������.\n1 - �������� ��������\n2 - ���������� ��������\n3 - ��������� ��������\n0 - �����\n������� ����� ��������� ��������: ";
				std::cin >> choice1;
				while (!isCorrectInput())
				{
					cin >> choice1;
				}
				switch (choice1)
				{
				case 1:
				{
					//delete
					cout << " ";
				}
				break;
				case 2:
				{
					//add
					cout << " ";
				}
				break;
				case 3:
				{
					//change
					cout << " ";
				}
				break;
				case 0:
				{
					break;
				}
				default:
				{
					cout << "������������ ����. ������� ����� ��������� ��������:"; cin >> choice1;
					while (!isCorrectInput())
					{
						cin >> choice1;
					}
				}
				}
			} while (choice1 != 0);
		}
		break;
		case 2:
		{
			do {
				//DB_Students
				std::cout << "������ �� ������� ���������.\n1 - �������� � ����������� ���������\n2 - ��������� ��������� ���������\n3 - ����� ������ ��������� � ��������\n4 - ���������� �� �������\n5 - ���������� �� �������\n0 - �����\n������� ����� ��������� ��������: ";
				std::cin >> choice2;
				while (!isCorrectInput())
				{
					cin >> choice2;
				}
				switch (choice2)
				{
				case 1:
				{
					cout << " ";
				}
				break;
				case 2:
				{
					//changeProgress
					changeProgress_student(Dbusers, question);
				}
				break;
				case 3:
				{
					//output spisok students
					outputStudents(Dbusers, question);
				}
				break;
				case 4:
				{	//����������
					Filtr(Dbusers, question);
				}
				break;
				case 5:
				{
					cout << " ";
				}
				break;
				case 0:
					break;
				default:
				{
					cout << "������������ ����. ������� ����� ��������� ��������:"; cin >> choice2;
					while (!isCorrectInput())
					{
						cin >> choice2;
					}
				}
				}
			} while (choice2 != 0);
		}
		break;
		case 0:
		{
			break;
		}
		default:
		{
			cout << "������������ ����. ������� ����� ��������� ��������:"; cin >> choice;
			while (!isCorrectInput())
			{
				cin >> choice;
			}
		}
		}
	}while (choice != 0);
}
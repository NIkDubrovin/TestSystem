#include "TestSystem.h"

using namespace std;

int add_student(DBUsers& dbuser)
{
	int various = 1;
	clearScreen();
	
	do
	{
		cout << "1 - ���������� ������ ��������\n0 - �����\n������� ����� �������� ��������: ";
		do
		{
			cin >> various;
		} while (!isCorrectInput());

		if (various == 1)
		{
			dbuser.countStudents += 1;
			dbuser.students = (Student*)realloc(dbuser.students, sizeof(Student) * dbuser.countStudents);
			//add
			cout << "������� �����: ";
			dbuser.students[dbuser.countStudents - 1].user.login = getConsoleString();
			cout << "������� ������: ";
			dbuser.students[dbuser.countStudents - 1].user.password = getConsoleString();
			cout << "������� �������: ";
			dbuser.students[dbuser.countStudents - 1].lastName = getConsoleString();
			cout << "������� ���: "; 
			dbuser.students[dbuser.countStudents - 1].firstName = getConsoleString();
			for (int i = 0; i < 8; i++)
			{
				dbuser.students[dbuser.countStudents - 1].marks[i] = 0;
			}
			
			dbuser.students[dbuser.countStudents - 1].averageMark = 0.f;
			dbuser.students[dbuser.countStudents - 1].finalMark = 0;
		}

	} while (various != 0);

	return 1;
}
int del_student(DBUsers& dbuser)
{
	clearScreen();
	int various = 1;
	cout << "1 -  �������� ��������\n0 - �����\n������� ����� �������� ��������: ";
	do
	{
		cin >> various;
	} while (!isCorrectInput());

	if (various == 0)
		return 0;

	cout << endl;
	do
	{
		int del = 0;
		for (int i = 0; i < dbuser.countStudents; i++)
		{
			cout << i << " " << dbuser.students[i].lastName << " " << dbuser.students[i].firstName << endl;

		}
		cout << "������� ����� ��������, �������� ������� �������: "; 

		do
		{
			cin >> del;
		} while (!isCorrectInput() || del < 0 || del >= dbuser.countStudents);

		freeStudent(dbuser.students[del]); // free del student

		for (int i = del; i < dbuser.countStudents - 1; i++)
		{
			Student& curSt = dbuser.students[i];
			Student& nextSt = dbuser.students[i + 1];

			curSt.firstName = nextSt.firstName;
			curSt.lastName = nextSt.lastName;
			curSt.user.login = nextSt.user.login;
			curSt.user.password = nextSt.user.password;

			curSt.averageMark = nextSt.averageMark;
			curSt.finalMark = nextSt.finalMark;

			for (int j = 0; j < 8; j++)
				curSt.marks[j] = dbuser.students[i+1].marks[j];
		}
		
		dbuser.countStudents--;

		Student* newArr = (Student*)malloc(sizeof(Student) * dbuser.countStudents);
		memcpy_s(newArr, sizeof(Student) * (dbuser.countStudents),
			dbuser.students, sizeof(Student) * dbuser.countStudents);
		
		free(dbuser.students);
		dbuser.students = newArr;

		cout << "���������� ������ ���������: \n";
		for (int i = 0; i < dbuser.countStudents; i++)
		{
			cout << i << " " << dbuser.students[i].lastName << " " << dbuser.students[i].firstName << endl;

		}
		cout << "1 -  �������� ��������\n0 - �����\n������� ����� �������� ��������: ";

		do
		{
			cin >> various;
		} while (!isCorrectInput());
	} while (various != 0);
	return 1;
}


int changeProgress_student(DBUsers& use, DBQuestion& question)
{
	clearScreen();
	int changeMark = 0;
	int chooseStudent = 0, chooseTheme = 0;
	cout << "������ ���������" << endl;
	for (int i = 0; i < use.countStudents; i++)
	{
		cout << i + 1 << " - " << use.students[i].lastName << " " << use.students[i].firstName << endl;
	}
	cout << "�������� �������� ��� �������� ������ �������� ������: "; 

	do
	{
		cin >> chooseStudent;
	} while (!isCorrectInput());

	while (chooseStudent > use.countStudents && chooseStudent < 1)
	{
		cout << "������ �������� ���. �������� �������� ��� �������� ������ �������� ������: "; 
		do
		{
			cin >> chooseStudent;
		} while (!isCorrectInput());
	}
	chooseStudent--;
	for (int i = 0; i < 8; i++)
	{
		cout << i + 1 << " - " << question.themes[i].name << "\t" << use.students[chooseStudent].marks[i] << endl;
	}
	cout << "�������� ���� ��� ��������� ���������: "; 
	do
	{
		cin >> chooseStudent;
	} while (!isCorrectInput());
	while (chooseTheme > 8 || chooseTheme < 1)
	{
		cout << "����� ���� ���. �������� ���� ��� ��������� ���������: "; 
		do
		{
			cin >> chooseStudent;
		} while (!isCorrectInput());
	}
	chooseTheme--;
	cout << "������� ����� ������: "; cin >> changeMark;
	while (!isCorrectInput())
	{
		cin >> changeMark;
	}
	while (changeMark < 2 || changeMark > 5)
	{
		cout << "������ �������� � 5 - �� ������� �������. ������� ����� ������: "; 
		do
		{
			cin >> chooseStudent;
		} while (!isCorrectInput());
	}
	use.students[chooseStudent].marks[chooseTheme] = changeMark;
	return 1;
}
void outputStudents(DBUsers& use, DBQuestion& question)
{
	clearScreen();
	int chooseTheme = 0, chooseTheme1 = 0;
	do {
		cout << "1 - �� ���� �����\n2 - �� ���������� ����\n3 - ������ �������� ����\n4 - ������ ������� ����\n0 - �����\n�������� ������� ������: ";
		do
		{
			cin >> chooseTheme;
		} while (!isCorrectInput());

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
				cout << i + 1 << " - " << question.themes[i].name << endl;
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
		else if (chooseTheme < 0 && chooseTheme > 4)
		{
			cout << "������������ ����. ������� ������� ������:"; cin >> chooseTheme;
			while (!isCorrectInput())
			{
				cin >> chooseTheme;
			}
		}
	} while (chooseTheme != 0);
}
void Filtr(DBUsers& use, DBQuestion& question)
{
	clearScreen();
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
						cout << question.themes[j].name << endl << "������: " << use.students[i].marks[j] << endl;
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
void sortMarks(DBUsers& use, DBQuestion& dbq)
{
	clearScreen();
	int sortChoice;
	cout << "�������� �������� ����������:\n";
	cout << "1. �� ���������� ����\n";
	cout << "2. �� ��������� �����\n";
	cout << "3. �� �������� �����\n";
	cin >> sortChoice;
	switch (sortChoice)
	{
	case 1:
		int themeChoice;
		cout << "�������� ���� ��� ����������:\n";
		for (int i = 0; i < dbq.countThemes; i++)
		{
			cout << i + 1 << ". " << dbq.themes[i].name << endl;
		}
		cin >> themeChoice;


		// ���������� �� ��������� ����
		for (int i = 0; i < use.countStudents; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				if (j == themeChoice - 1)
				{
					for (int k = j + 1; k < 8; k++)
					{
						if (use.students[i].marks[j] < use.students[i].marks[k])
						{
							swap(use.students[i].marks[j], use.students[i].marks[k]);
						}
					}
				}
			}
		}

		// ����� ��������������� ������ �� ����
		for (int i = 0; i < use.countStudents; i++)
		{
			Student& st = use.students[i];
			cout << st.lastName << " " << st.firstName << ": " << st.marks[themeChoice - 1] << endl;
		}
		break;

	case 2:
		// ���������� �� ��������� �����
		for (int i = 0; i < use.countStudents; i++)
		{
			for (int j = i + 1; j < use.countStudents; j++)
			{
				if (use.students[i].finalMark < use.students[j].finalMark)
				{
					swap(use.students[i], use.students[j]);
				}
			}
		}

		// ����� ��������������� ������ �� ��������� �����
		for (int i = 0; i < use.countStudents; i++)
		{
			Student& st = use.students[i];
			cout << st.lastName << " " << st.firstName << ": " << st.finalMark << endl;
		}
		break;

	case 3:
		// ���������� �� �������� �����
		for (int i = 0; i < use.countStudents; i++)
		{
			for (int j = i + 1; j < use.countStudents; j++)
			{
				if (use.students[i].averageMark < use.students[j].averageMark) {
					swap(use.students[i], use.students[j]);
				}
			}
		}

		// ����� ��������������� ������
		for (int i = 0; i < use.countStudents; i++)
		{
			Student& st = use.students[i];
			cout << st.lastName << " " << st.firstName << ": " << st.averageMark << endl;
		}
		break;

	default:
		cout << "������������ ����� �������� ����������\n";
		break;
	}
}
int add_qoestion(DBQuestion& quse)
{
	clearScreen();
	int num_theme, quit = 1, true_answer;
	do {
		for (int i = 0; i < 8; i++)
		{
			cout << i + 1 << " - " << quse.themes[i].name << endl;
		}
		cout << "������� ����� �������� ���� ��� ���������� �������: "; cin >> num_theme;
		while (!isCorrectInput())
		{
			cin >> num_theme;
		}
		while (num_theme > 8 || num_theme < 1)
		{
			cout << "����� ���� ���. ������� ����� �������� ����: "; cin >> num_theme;
			while (!isCorrectInput())
			{
				cin >> num_theme;
			}
		}
		num_theme--;
		quse.themes[num_theme].countQuestions++;
		quse.themes[num_theme].questions = (Question*)realloc(quse.themes[num_theme].questions, sizeof(Question) * quse.themes[num_theme].countQuestions);
		cout << "������� ����� ������ �������: ";  quse.themes[num_theme].questions[quse.themes[num_theme].countQuestions - 1].text = getConsoleString();
		for (int j = 0; j < 4; j++)
		{
			cout << "������� " << j + 1 << " ������� ������:"; quse.themes[num_theme].questions[quse.themes[num_theme].countQuestions - 1].answers[j].text = getConsoleString(); cout << endl;
		}
		cout << "������� ����� ����������� ������: "; cin >> true_answer;
		while (!isCorrectInput())
		{
			cin >> true_answer;
		}
		while (true_answer < 1 || true_answer > 4)
		{
			cout << "������ �������� ������ ���. ������� ����� ����������� ������: "; cin >> true_answer;
			while (!isCorrectInput())
			{
				cin >> true_answer;
			}
		}
		true_answer--;
		quse.themes[num_theme].questions[quse.themes[num_theme].countQuestions - 1].rightAnswer = true_answer;
		cout << "1 - �������� ������\n0 - �����\n������� ����� ��������� ��������: "; cin >> quit;
		while (!isCorrectInput())
		{
			cin >> quit;
		}
		while (quit != 1 && quit != 0)
		{
			cout << "������. ������� ����� ��������� ��������: "; cin >> quit;
			while (!isCorrectInput())
			{
				cin >> quit;
			}
		}
	} while (quit != 0);
	return 1;
}

int del_question(DBQuestion& quse)
{
	clearScreen();
	int theme_num = 0, que_num = 0, quit = 1;
	do
	{
		cout << "������ �������� �� �����:\n";
		for (int i = 0; i < 8; i++)
		{
			cout << i + 1 << quse.themes[i].name << endl;
			for (int j = 0; j < quse.themes[i].countQuestions; j++)
			{
				cout << "\t\t" << j + 1 << ". " << quse.themes[i].questions[j].text << endl;
			}
			cout << endl;

		}
		cout << "������� ����� �������� ���� ��� �������� �������: "; cin >> theme_num;
		while (!isCorrectInput())
		{
			cin >> theme_num;
		}
		while (theme_num > 8 || theme_num < 1)
		{
			cout << "����� ���� ���. ������� ����� �������� ����: "; cin >> theme_num;
			while (!isCorrectInput())
			{
				cin >> theme_num;
			}
		}
		cout << "������� ����� ������� ������� ������ �������: ";
		cin >> que_num;
		while (!isCorrectInput())
		{
			cin >> que_num;
		}
		/*while (que_num > quse.themes[quse.countThemes].countQuestions || que_num < 0)
		{
			cout << "������ �� ������������ ����� �������\n������� ���������� ����� �������: "; cin >> que_num;*/
			while (!isCorrectInput())
			{
				cin >> que_num;
			}
		//}

		theme_num--; que_num--;

		for (int i = 0; i < quse.themes[theme_num].countQuestions; i++)
		{
			quse.themes[theme_num].questions[i].text = quse.themes[theme_num].questions[i + 1].text;
			for (int j = 0; j < 4; j++)
			{
				quse.themes[theme_num].questions[i].answers[j] = quse.themes[theme_num].questions[i + 1].answers[j];
			}
			quse.themes[theme_num].questions[i].rightAnswer = quse.themes[theme_num].questions[i + 1].rightAnswer;
		}

		quse.themes[theme_num].countQuestions--;
		/*quse.themes[theme_num].questions[quse.themes[theme_num].countQuestions] = 
			(DBQuestion*)realloc(quse.themes[theme_num].questions[quse.themes[theme_num].countQuestions], sizeof(DBQuestion) * (quse.themes[theme_num].countQuestions-1));*/
		cout << "1 - ������� ������\n0 - �����\n������� ����� ��������� ��������: "; cin >> quit;
		while (!isCorrectInput())
		{
			cin >> quit;
		}
		while (quit != 1 && quit != 0)
		{
			cout << "������. ������� ����� ��������� ��������: "; cin >> quit;
			while (!isCorrectInput())
			{
				cin >> quit;
			}
		}
	} while (quit != 0);
	return 1;
}

int change_qustion(DBQuestion& quse)
{
	clearScreen();
	int theme_num = 0, que_num = 0, quit = 1, true_answer = 0;
	do
	{
		cout << "������ �������� �� �����:\n";
		for (int i = 0; i < 8; i++)
		{
			cout << i + 1 << quse.themes[i].name << endl;
			for (int j = 0; j < quse.themes[i].countQuestions; j++)
			{
				cout << "\t\t" << j + 1 << ". " << quse.themes[i].questions[j].text << endl;
			}
			cout << endl;

		}
		cout << "������� ����� ����, ������ ������� ������ ��������: ";
		cin >> theme_num;
		while (!isCorrectInput())
		{
			cin >> theme_num;
		}
		if (theme_num > 8 || theme_num < 0)
		{
			cout << "������ �� ������������ ����� ����\n������� ���������� ����� ����: "; cin >> theme_num;
			while (!isCorrectInput())
			{
				cin >> theme_num;
			}
		}
		cout << "������� ����� ������� ������� ������ ��������: ";
		cin >> que_num;
		while (!isCorrectInput())
		{
			cin >> que_num;
		}
//		while (que_num > quse.themes[quse.countThemes].countQuestions || que_num < 0)
//		{
			//cout << "������ �� ������������ ����� �������\n������� ���������� ����� �������: "; cin >> que_num;
			while (!isCorrectInput())
			{
				cin >> que_num;
			}
//		}

		theme_num--; que_num--;
		char quest;
		cout << quse.themes[theme_num].name << "\n\n" << quse.themes[theme_num].questions[que_num].text;

	
		cout << "������� ����� ������ �������: ";  //quest = getConsoleString();
		cin >> quse.themes[theme_num].questions[que_num].text;
		for (int j = 0; j < 4; j++)
		{
			cout << "������� " << j + 1 << " ������� ������:"; quse.themes[theme_num].questions[que_num].answers[j].text = getConsoleString(); cout << endl;
		}
		cout << "������� ����� ����������� ������: "; cin >> true_answer;
		while (!isCorrectInput())
		{
			cin >> true_answer;
		}
		while (true_answer < 1 || true_answer > 4)
		{
			cout << "������ �������� ������ ���. ������� ����� ����������� ������: "; cin >> true_answer;
			while (!isCorrectInput())
			{
				cin >> true_answer;
			}
		}
		true_answer--;
		quse.themes[theme_num].questions[que_num].rightAnswer = true_answer;
		
		cout << "1 - �������� ������\n0 - �����\n������� ����� ��������� ��������: "; cin >> quit;
		while (!isCorrectInput())
		{
			cin >> quit;
		}
		while (quit != 1 && quit != 0)
		{
			cout << "������. ������� ����� ��������� ��������: "; cin >> quit;
			while (!isCorrectInput())
			{
				cin >> quit;
			}
		}
	} while (quit != 0);
	return 1;
}

void TeacherMain(DBUsers& Dbusers, DBQuestion& question)
{
	clearScreen();
	int choice = 0, choice1 = 0, choice2 = 0, stud_add = 0;
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
					del_question(question);
				}
				break;
				case 2:
				{
					//add
					add_qoestion(question);
				}
				break;
				case 3:
				{
					//change
					change_qustion(question);
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
					do {
						cout << "1 - ���������� ��������\n2 - �������� ��������\n0 - �����\n������� ����� ��������� ��������"; cin >> stud_add;
						while (!isCorrectInput())
						{
							cin >> stud_add;
						}
						if (stud_add == 1)
						{
							add_student(Dbusers);
						}
						else if (stud_add == 2)
						{
							del_student(Dbusers);
						}
						else if (stud_add < 0 || stud_add > 2)
						{
							cout << "������. ��� ������ �������� ������. ������� ����� ��������� ��������: "; cin >> stud_add;
							while (!isCorrectInput())
							{
								cin >> stud_add;
							}
						}
					} while (stud_add != 0);
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
					sortMarks(Dbusers, question);
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
	} while (choice != 0);
}
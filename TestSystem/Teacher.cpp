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
		cin >> chooseTheme;
	} while (!isCorrectInput());
	while (chooseTheme > 8 || chooseTheme < 1)
	{
		cout << "����� ���� ���. �������� ���� ��� ��������� ���������: "; 
		do
		{
			cin >> chooseTheme;
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
			cin >> changeMark;
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
			mark_choice = (double)mark_choice;
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
		for (int i = 0; i < use.countStudents; i++)
		{
			Student& st = use.students[i];
			cout << st.lastName << " " << st.firstName << ": " << st.marks[themeChoice - 1] << endl;
		}
		break;

	case 2:
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
		for (int i = 0; i < use.countStudents; i++)
		{
			Student& st = use.students[i];
			cout << st.lastName << " " << st.firstName << ": " << st.finalMark << endl;
		}
		break;

	case 3:
		for (int i = 0; i < use.countStudents; i++)
		{
			for (int j = i + 1; j < use.countStudents; j++)
			{
				if (use.students[i].averageMark < use.students[j].averageMark) {
					swap(use.students[i], use.students[j]);
				}
			}
		}
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
			cout << i << " - " << quse.themes[i].name << endl;
		}

		cout << "������� ����� �������� ���� ��� ���������� �������: "; 

		do 
		{
			cin >> num_theme;
			if (num_theme > 7 || num_theme < 0) {
				cout << "����� ���� ���. ������� ����� �������� ����: ";
			}
		} while (!isCorrectInput() || num_theme > 7 || num_theme < 0);

		Theme& theme = quse.themes[num_theme];
		theme.countQuestions++;
		theme.questions = (Question*)realloc(theme.questions, sizeof(Question) * theme.countQuestions);

		cout << "������� ����� ������ �������: "; 
		theme.questions[theme.countQuestions - 1].text = getConsoleString();

		for (int j = 0; j < 4; j++)
		{
			cout << "������� " << j + 1<< " ������� ������:"; 
			theme.questions[theme.countQuestions - 1].answers[j].text = getConsoleString(); 
		}

		cout << "������� ����� ����������� ������ (1 - 4): "; 

		do 
		{
			cin >> true_answer;
			if(true_answer < 1 || true_answer > 4)
				cout << "������ �������� ������ ���. ������� ����� ����������� ������: ";

		} while (!isCorrectInput() || true_answer < 1 || true_answer > 4);

		true_answer--;
		theme.questions[theme.countQuestions - 1].rightAnswer = true_answer;

		cout << "1 - �������� ������\n0 - �����\n������� ����� ��������� ��������: "; 
		
		cin >> quit;
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
			cout << i << " : " << quse.themes[i].name << endl;
		}

		cout << "������� ����� �������� ���� ��� �������� �������: "; 
		do 
		{
			cin >> theme_num;
			if(theme_num > 7 || theme_num < 0)
				cout << "����� ���� ���. ������� ����� �������� ����: ";
		} while (!isCorrectInput() || theme_num > 7 || theme_num < 0);

		Theme& theme = quse.themes[theme_num];

		cout << "������� ��������� ����: " << endl;

		for (int j = 0; j < theme.countQuestions; j++)
		{
			cout << "\t" << j << ". " << theme.questions[j].text << endl;
		}
		cout << endl;
		
		cout << "������� ����� ������� ������� ������ �������: ";
		do 
		{
			cin >> que_num;
			if(que_num > theme.countQuestions - 1 || que_num < 0)
				cout << "������ �� ������������ ����� �������\n������� ���������� ����� �������: ";

		} while (!isCorrectInput() || que_num > theme.countQuestions - 1 || que_num < 0);

		for (int i = que_num; i < theme.countQuestions - 1; i++)
		{
			Question& curQuest = theme.questions[i];
			Question& nextQuest = theme.questions[i + 1];

			freeQuestion(curQuest);

			curQuest.text = nextQuest.text;

			for (int j = 0; j < 4; j++)
			{
				curQuest.answers[j] = nextQuest.answers[j];
			}

			curQuest.rightAnswer = nextQuest.rightAnswer;
		}

		theme.countQuestions--;

		Question* newArr = (Question*)malloc(sizeof(Question) * theme.countQuestions);
		memcpy_s(newArr, sizeof(Question) * (theme.countQuestions),
			theme.questions, sizeof(Question) * theme.countQuestions);

		free(theme.questions);
		theme.questions = newArr;
		
		cout << "������ ������.\n1 - ������� ������\n0 - �����\n������� ����� ��������� ��������: "; 
		do
		{
			cin >> quit;
			if(quit != 1 && quit != 0)
				cout << "������. ������� ����� ��������� ��������: ";

		} while (!isCorrectInput() || quit != 1 && quit != 0);
		
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
			cout << i << " : " << quse.themes[i].name << endl;
		}

		cout << "������� ����� �������� ���� ��� �������� �������: ";
		do
		{
			cin >> theme_num;
			if (theme_num > 7 || theme_num < 0)
				cout << "����� ���� ���. ������� ����� �������� ����: ";
		} while (!isCorrectInput() || theme_num > 7 || theme_num < 0);

		Theme& theme = quse.themes[theme_num];

		cout << "������� ��������� ����: " << endl;

		for (int j = 0; j < theme.countQuestions; j++)
		{
			cout << "\t" << j << ". " << theme.questions[j].text << endl;
		}
		cout << endl;

		cout << "������� ����� ������� ������� ������ �������: ";
		do
		{
			cin >> que_num;
			if (que_num > theme.countQuestions - 1 || que_num < 0)
				cout << "������ �� ������������ ����� �������\n������� ���������� ����� �������: ";

		} while (!isCorrectInput() || que_num > theme.countQuestions - 1 || que_num < 0);

		Question& quest = theme.questions[que_num];
		cout << "��������� ������: " << endl;
		cout << quest.text << endl;
		for (int j = 0; j < 4; j++)
		{
			cout << j + 1 << " : " << quest.answers[j].text << endl;
		}
	
		cout << "\n������� ����� ������ �������: ";  

		free(quest.text);
		quest.text = getConsoleString();
		
		for (int j = 0; j < 4; j++)
		{
			cout << "������� " << j + 1 << " ������� ������:"; 
			quest.answers[j].text = getConsoleString(); 
		}

		cout << "������� ����� ����������� ������ (1 - 4): "; 
		do 
		{
			cin >> true_answer;
			if(true_answer < 1 || true_answer > 4)
				cout << "������ �������� ������ ���. ������� ����� ����������� ������: ";

		} while (!isCorrectInput() || true_answer < 1 || true_answer > 4);
	
		true_answer--;
		quest.rightAnswer = true_answer;
		
		cout << "1 - �������� ������\n0 - �����\n������� ����� ��������� ��������: "; 
		do
		{
			cin >> quit;
			if (quit != 1 && quit != 0)
				cout << "������. ������� ����� ��������� ��������: ";

		} while (!isCorrectInput() || quit != 1 && quit != 0);

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
			clearScreen();
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
					clearScreen();
					del_question(question);
				}
				break;
				case 2:
				{
					//add
					clearScreen();
					add_qoestion(question);
				}
				break;
				case 3:
				{
					//change
					clearScreen();
					change_qustion(question);
				}
				break;
				case 0:
				{
					clearScreen();
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
				if(choice1 == 0)
					clearScreen();
			} while (choice1 != 0);
		}
		break;
		case 2:
		{
			clearScreen();
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
					clearScreen();
					do {
						cout << "1 - ���������� ��������\n2 - �������� ��������\n0 - �����\n������� ����� ��������� ��������"; cin >> stud_add;
						while (!isCorrectInput())
						{
							cin >> stud_add;
						}
						if (stud_add == 1)
						{
							clearScreen();
							add_student(Dbusers);
						}
						else if (stud_add == 2)
						{
							clearScreen();
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
						if (stud_add == 0)
							clearScreen();
					} while (stud_add != 0);
				}
				break;
				case 2:
				{
					clearScreen();
					//changeProgress
					changeProgress_student(Dbusers, question);
				}
				break;
				case 3:
				{
					clearScreen();
					//output spisok students
					outputStudents(Dbusers, question);
				}
				break;
				case 4:
				{	//����������
					clearScreen();
					Filtr(Dbusers, question);
				}
				break;
				case 5:
				{
					clearScreen();
					sortMarks(Dbusers, question);
				}
				break;
				case 0:
				{clearScreen();
				break; }
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
			clearScreen();
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
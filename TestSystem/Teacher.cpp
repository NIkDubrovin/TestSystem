#include "TestSystem.h"

using namespace std;

int add_student(DBUsers& dbuser)
{
	int various = 1;
	clearScreen();
	
	do
	{
		cout << "1 - Добавление нового студента\n0 - Выход\nВведите номер желаемой операции: ";
		do
		{
			cin >> various;
		} while (!isCorrectInput());

		if (various == 1)
		{
			dbuser.countStudents += 1;
			dbuser.students = (Student*)realloc(dbuser.students, sizeof(Student) * dbuser.countStudents);
			//add
			cout << "Введите логин: ";
			dbuser.students[dbuser.countStudents - 1].user.login = getConsoleString();
			cout << "Введите пароль: ";
			dbuser.students[dbuser.countStudents - 1].user.password = getConsoleString();
			cout << "Введите Фамилию: ";
			dbuser.students[dbuser.countStudents - 1].lastName = getConsoleString();
			cout << "Введите Имя: "; 
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
	cout << "1 -  Удаление студента\n0 - Выход\nВведите номер желаемой операции: ";
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
		cout << "Введите номер студента, которого желаете удалить: "; 

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

		cout << "Измененный список студентов: \n";
		for (int i = 0; i < dbuser.countStudents; i++)
		{
			cout << i << " " << dbuser.students[i].lastName << " " << dbuser.students[i].firstName << endl;

		}
		cout << "1 -  Удаление студента\n0 - Выход\nВведите номер желаемой операции: ";

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
	cout << "Список студентов" << endl;
	for (int i = 0; i < use.countStudents; i++)
	{
		cout << i + 1 << " - " << use.students[i].lastName << " " << use.students[i].firstName << endl;
	}
	cout << "Выберете студента для которого хотите изменить оценку: "; 

	do
	{
		cin >> chooseStudent;
	} while (!isCorrectInput());

	while (chooseStudent > use.countStudents && chooseStudent < 1)
	{
		cout << "Такого студента нет. Выберите студента для которого хотите изменить оценку: "; 
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
	cout << "Выберите тему для изменения прогресса: "; 
	do
	{
		cin >> chooseTheme;
	} while (!isCorrectInput());
	while (chooseTheme > 8 || chooseTheme < 1)
	{
		cout << "Такой темы нет. Выберите тему для изменения прогресса: "; 
		do
		{
			cin >> chooseTheme;
		} while (!isCorrectInput());
	}
	chooseTheme--;
	cout << "Введите новую оценку: "; cin >> changeMark;
	while (!isCorrectInput())
	{
		cin >> changeMark;
	}
	while (changeMark < 2 || changeMark > 5)
	{
		cout << "Оценки ставятся в 5 - ти бальной системе. Введите новую оценку: "; 
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
		cout << "1 - По всем темам\n2 - По конкретной теме\n3 - Только итоговый тест\n4 - Только средний балл\n0 - Выход\nВыберете вариант вывода: ";
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

			cout << "Введите тему для вывода оценки студентов:";

			cin >> chooseTheme1;
			while (!isCorrectInput())
			{
				cin >> chooseTheme1;
			}
			while (chooseTheme1 < 1 || chooseTheme1 > 8)
			{
				cout << "Неверный номер темы. Введите номер темы: ";
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
			cout << "Некорректный ввод. Введите вариант вывода:"; cin >> chooseTheme;
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
		cout << "1 - По всем темам\n2 - По конкретной теме\n3 - Только итоговый тест\n4 - Только средний балл\n0 - Выход\nВыберете вариант фильтрации: "; cin >> num_out;
		while (!isCorrectInput())
		{
			cin >> num_out;
		}
		if (num_out == 1)
		{
			cout << "Введите нужную оценку для поиска: ";
			cin >> mark_choice;
			while (!isCorrectInput())
			{
				cin >> mark_choice;
			}
			while (mark_choice > 5 || mark_choice < 2)
			{
				cout << "Оценка введена некорректно. Введите нужную оценку для поиска: ";
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
						cout << question.themes[j].name << endl << "Оценка: " << use.students[i].marks[j] << endl;
						cnt++;
					}
				}
			}
			if (cnt == 0)
				cout << "Не найдено студентов с оценкой " << mark_choice << endl;
			cnt = 0;
		}
		if (num_out == 2)
		{
			cout << "Введите нужную оценку для поиска: ";
			cin >> mark_choice;
			while (!isCorrectInput())
			{
				cin >> mark_choice;
			}
			while (mark_choice > 5 || mark_choice < 2)
			{
				cout << "Оценка введена некорректно. Введите нужную оценку для поиска: ";
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
			cout << "Введите номер темы, по которой нужно предоставить студентов: ";
			cin >> num_theme;
			while (!isCorrectInput())
			{
				cin >> num_theme;
			}
			while (num_theme < 1 || num_theme > 8)
			{
				cout << "Ошибка, такой темы нет. Введите номер темы: "; cin >> num_theme;
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
					cout << "Оценка: " << mark_choice;
					cnt++;
				}
			}
			if (cnt == 0)
				cout << "Не найдено студентов с оценкой " << mark_choice << endl;
			cnt = 0;
		}
		if (num_out == 3)
		{
			cout << "Введите нужную оценку для поиска: ";
			cin >> mark_choice;
			while (!isCorrectInput())
			{
				cin >> mark_choice;
			}
			while (mark_choice > 5 || mark_choice < 2)
			{
				cout << "Оценка введена некорректно. Введите нужную оценку для поиска: ";
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
					cout << use.students[i].lastName << " " << use.students[i].firstName << endl << "Оценка: " << use.students[i].finalMark << endl;
					cnt++;
				}
			}
			if (cnt == 0)
				cout << "Не найдено студентов с оценкой " << mark_choice << endl;
			cnt = 0;
		}
		if (num_out == 4)
		{
			mark_choice = (double)mark_choice;
			cout << "Введите нужную оценку для поиска: ";
			cin >> mark_choice;
			while (!isCorrectInput())
			{
				cin >> mark_choice;
			}
			while (mark_choice > 5 || mark_choice < 2)
			{
				cout << "Оценка введена некорректно. Введите нужную оценку для поиска: ";
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
					cout << "Оценка: " << use.students[i].averageMark << endl;
					cnt++;
				}
			}
			if (cnt == 0)
				cout << "Не найдено студентов с оценкой " << mark_choice << endl;
			cnt = 0;
		}
		if (num_out < 0 && num_out > 4)
		{
			cout << "Не корректный ввод. Выберите вариант фильтрации: "; cin >> num_out;
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
	cout << "Выберите критерий сортировки:\n";
	cout << "1. По конкретной теме\n";
	cout << "2. По итоговому тесту\n";
	cout << "3. По среднему баллу\n";
	cin >> sortChoice;
	switch (sortChoice)
	{
	case 1:
		int themeChoice;
		cout << "Выберите тему для сортировки:\n";
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
		cout << "Неправильный выбор критерия сортировки\n";
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

		cout << "Введите номер желаемой темы для добавления вопроса: "; 

		do 
		{
			cin >> num_theme;
			if (num_theme > 7 || num_theme < 0) {
				cout << "Такой темы нет. Введите номер желаемой темы: ";
			}
		} while (!isCorrectInput() || num_theme > 7 || num_theme < 0);

		Theme& theme = quse.themes[num_theme];
		theme.countQuestions++;
		theme.questions = (Question*)realloc(theme.questions, sizeof(Question) * theme.countQuestions);

		cout << "Введите текст нового вопроса: "; 
		theme.questions[theme.countQuestions - 1].text = getConsoleString();

		for (int j = 0; j < 4; j++)
		{
			cout << "Введите " << j + 1<< " вариант ответа:"; 
			theme.questions[theme.countQuestions - 1].answers[j].text = getConsoleString(); 
		}

		cout << "Введите номер правильного ответа (1 - 4): "; 

		do 
		{
			cin >> true_answer;
			if(true_answer < 1 || true_answer > 4)
				cout << "Такого варианта ответа нет. Введите номер правильного ответа: ";

		} while (!isCorrectInput() || true_answer < 1 || true_answer > 4);

		true_answer--;
		theme.questions[theme.countQuestions - 1].rightAnswer = true_answer;

		cout << "1 - Добавить вопрос\n0 - Выход\nВведите номер желаемого действия: "; 
		
		cin >> quit;
		while (!isCorrectInput())
		{
			cin >> quit;
		}

		while (quit != 1 && quit != 0)
		{
			cout << "Ошибка. Введите номер желаемого действия: "; cin >> quit;
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
		cout << "Список вопросов по темам:\n";
		for (int i = 0; i < 8; i++)
		{
			cout << i << " : " << quse.themes[i].name << endl;
		}

		cout << "Введите номер желаемой темы для удаления вопроса: "; 
		do 
		{
			cin >> theme_num;
			if(theme_num > 7 || theme_num < 0)
				cout << "Такой темы нет. Введите номер желаемой темы: ";
		} while (!isCorrectInput() || theme_num > 7 || theme_num < 0);

		Theme& theme = quse.themes[theme_num];

		cout << "Вопросы выбранной темы: " << endl;

		for (int j = 0; j < theme.countQuestions; j++)
		{
			cout << "\t" << j << ". " << theme.questions[j].text << endl;
		}
		cout << endl;
		
		cout << "Введите номер вопроса который хотите удалить: ";
		do 
		{
			cin >> que_num;
			if(que_num > theme.countQuestions - 1 || que_num < 0)
				cout << "Введен не существующий номер вопроса\nВведите корректный номер вопроса: ";

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
		
		cout << "Вопрос удален.\n1 - Удалить вопрос\n0 - Выход\nВведите номер желаемого действия: "; 
		do
		{
			cin >> quit;
			if(quit != 1 && quit != 0)
				cout << "Ошибка. Введите номер желаемого действия: ";

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
		cout << "Список вопросов по темам:\n";
		for (int i = 0; i < 8; i++)
		{
			cout << i << " : " << quse.themes[i].name << endl;
		}

		cout << "Введите номер желаемой темы для удаления вопроса: ";
		do
		{
			cin >> theme_num;
			if (theme_num > 7 || theme_num < 0)
				cout << "Такой темы нет. Введите номер желаемой темы: ";
		} while (!isCorrectInput() || theme_num > 7 || theme_num < 0);

		Theme& theme = quse.themes[theme_num];

		cout << "Вопросы выбранной темы: " << endl;

		for (int j = 0; j < theme.countQuestions; j++)
		{
			cout << "\t" << j << ". " << theme.questions[j].text << endl;
		}
		cout << endl;

		cout << "Введите номер вопроса который хотите удалить: ";
		do
		{
			cin >> que_num;
			if (que_num > theme.countQuestions - 1 || que_num < 0)
				cout << "Введен не существующий номер вопроса\nВведите корректный номер вопроса: ";

		} while (!isCorrectInput() || que_num > theme.countQuestions - 1 || que_num < 0);

		Question& quest = theme.questions[que_num];
		cout << "Выбранный вопрос: " << endl;
		cout << quest.text << endl;
		for (int j = 0; j < 4; j++)
		{
			cout << j + 1 << " : " << quest.answers[j].text << endl;
		}
	
		cout << "\nВведите текст нового вопроса: ";  

		free(quest.text);
		quest.text = getConsoleString();
		
		for (int j = 0; j < 4; j++)
		{
			cout << "Введите " << j + 1 << " вариант ответа:"; 
			quest.answers[j].text = getConsoleString(); 
		}

		cout << "Введите номер правильного ответа (1 - 4): "; 
		do 
		{
			cin >> true_answer;
			if(true_answer < 1 || true_answer > 4)
				cout << "Такого варианта ответа нет. Введите номер правильного ответа: ";

		} while (!isCorrectInput() || true_answer < 1 || true_answer > 4);
	
		true_answer--;
		quest.rightAnswer = true_answer;
		
		cout << "1 - Изменить вопрос\n0 - Выход\nВведите номер желаемого действия: "; 
		do
		{
			cin >> quit;
			if (quit != 1 && quit != 0)
				cout << "Ошибка. Введите номер желаемого действия: ";

		} while (!isCorrectInput() || quit != 1 && quit != 0);

	} while (quit != 0);

	return 1;
}

void TeacherMain(DBUsers& Dbusers, DBQuestion& question)
{
	clearScreen();
	int choice = 0, choice1 = 0, choice2 = 0, stud_add = 0;
	do {
		std::cout << "Режим преподавателя.\n1 - Редактирование вопросов\n2 - Работа со списком студентов\n0 - Выход\nВведите номер желаемого действия: ";
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
				std::cout << "Редактирование вопросов.\n1 - Удаление вопросов\n2 - Добавление вопросов\n3 - Изменение вопросов\n0 - Выход\nВведите номер желаемого действия: ";
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
					cout << "Некорректный ввод. Введите номер желаемого действия:"; cin >> choice1;
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
				std::cout << "Работа со списком студентов.\n1 - Удаление и регистрация студентов\n2 - Изменение прогресса студентов\n3 - Вывод списка студентов с оценками\n4 - Фильтрация по оценкам\n5 - Сортировка по оценкам\n0 - Выход\nВведите номер желаемого действия: ";
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
						cout << "1 - Добавление студента\n2 - Удаление студента\n0 - Выход\nВведите номер желаемого действия"; cin >> stud_add;
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
							cout << "Ошибка. Нет такого варианта выбора. Введите номер желаемого действия: "; cin >> stud_add;
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
				{	//Фильтрация
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
					cout << "Некорректный ввод. Введите номер желаемого действия:"; cin >> choice2;
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
			cout << "Некорректный ввод. Введите номер желаемого действия:"; cin >> choice;
			while (!isCorrectInput())
			{
				cin >> choice;
			}
		}
		}
	} while (choice != 0);
}
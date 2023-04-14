#include "TestSystem.h"
using namespace std;

void TeacherMain()
{
	system("chcp1251");


	int choice = 0, choice1 = 0, choice2 = 0;
	std::cout << "Редактирование вопросов.\n1 - Удаление вопросов\n2 - Добавление вопросов\n3 - Изменение вопросов\nВведите номер желаемого действия: "; std::cin >> choice1;

	switch (choice)
	{
	case 1:
	{
		//Question
		std::cout << "Редактирование вопросов.\n1 - Удаление вопросов\n2 - Добавление вопросов\n3 - Изменение вопросов\nВведите номер желаемого действия: "; std::cin >> choice1;
		switch (choice1)
		{
		case 1:
		{
			//delete
		}
		break;
		case 2:
		{
			//add
		}
		break;
		case 3:
		{
			//change
		}
		break;
		default:
			break;
		}
	}
	break;
	case 2:
	{
		//DB_Students
		switch (choice2)
		{
		case 1:
		{
			//Add/delete stdudent
			Student student;
			DBUsers Dbusers;
			int various = 3;
			DBUsers use;
			do
			{
				cout << "1 - Добавление нового студента\n2 - Удаление студента\n0 - Выход\nВведите номер желаемой операции: ";
				cin >> various;
				if (various == 1)
				{
					//add
					student.user.login = (char*)malloc(sizeof(char) * /*Dbusers.maxSymbols*/20);
					cout << "Введите логин: "; cin >> student.user.login;
					student.user.password = (char*)malloc(sizeof(char) * /*Dbusers.maxSymbols*/20);
					cout << "Введите пароль: "; cin >> student.user.password;
					cout << "Введите Фамилию: "; cin >> student.firstName;
					cout << "Введите Имя: "; cin >> student.lastName;
				}
				if (various == 2)
				{
					//delete
					int del = 0;
					for (int i = 0; i < use.countStudents; i++)
					{
						Student& st = use.students[i]; cout << i + 1 << " " << st.lastName << " " << st.firstName << endl;

					}
					cout << "Введите номер студента, которого желаете удалить: "; cin >> del;
					for (int i = del; i < use.countStudents - 1; i++)
					{
						Student& one = use.students[i];
						Student& two = use.students[i + 1];

						one.firstName = two.firstName;
						one.lastName = two.lastName;
						one.user.login = two.user.password;
						one.user.password = two.user.password;
						one.averageMark = two.averageMark;
						one.finalMark = two.finalMark;
						for (int j = 0; j < 8; j++)
							one.marks[j] = two.marks[j];
					}
					//добавить очистку последнего типочка и проверки
					cout << "Измененный список студентов: ";
					for (int i = 0; i < use.countStudents; i++)
					{
						Student& st = use.students[i]; cout << i + 1 << " " << st.lastName << " " << st.firstName << endl;

					}

				}
			} while (various != 0);

		}
		break;
		case 2:
		{
			//change progress
			DBUsers use;
			Student student;
			int changeMark = 0;
			int chooseStudent = 0, chooseTheme = 0;
			cout << "Список студентов" << endl;
			for (int i = 0; i < use.countStudents; i++)
			{
				Student& st = use.students[i]; cout << i << " " << st.lastName << " " << st.firstName << endl;

			}
			cout << "Выберете стуента для которого хотите изменить оценку: "; cin >> chooseStudent;
			Theme theme;
			for (int i = 0; i < 8; i++)
			{
				cout << theme.name[i] << "\t" << use.students[chooseStudent].marks[i] << endl;
			}
			cout << "Выберете тему для изменения прогресса: "; cin >> chooseTheme;
			cout << "Введите измененную оценку: "; cin >> changeMark;
			use.students[chooseStudent].marks[chooseTheme] = changeMark;
			//добавить проверки
		}
		break;
		case 3:
		{
			//input spisok students
			DBUsers use;
			Student student; Theme theme;
			int chooseTheme = 0, chooseTheme1 = 0;
			cout << "1 - По всем темам\n2 - По конкретной теме\n3 - Только итоговый тест\n4 -Только средний балл\n0 - Выход\nВыберете вариант вывода: "; cin >> chooseTheme;
			do {
				if (chooseTheme == 1)
				{
					//all them
					for (int i = 0; i < use.countStudents; i++)
					{
						Student& st = use.students[i]; cout << i << " " << st.lastName << " " << st.firstName;
						for (int i = 0; i < 8; i++)
						{
							cout << theme.name[i] << " " << student.marks[i];
						}
						cout << endl;
					}
				}
				else if (chooseTheme == 2)
				{
					//currThme
					for (int i = 0; i < 8; i++)
					{
						cout << theme.name[i] << endl;
					}

					cout << "Введите тему для вывода оценки студентов:\n";

					cin >> chooseTheme1;
					for (int i = 0; i < use.countStudents; i++)
					{
						Student& st = use.students[i]; cout << i << " " << st.lastName << " " << st.firstName << " " << student.marks[chooseTheme1] << endl;
					}
				}
				else if (chooseTheme == 3)
				{
					//finalTest
					for (int i = 0; i < use.countStudents; i++)
					{
						Student& st = use.students[i]; cout << i << " " << st.lastName << " " << st.firstName << " " << student.finalMark << endl;
					}

				}
				else if (chooseTheme == 4)
				{
					//avg
					for (int i = 0; i < use.countStudents; i++)
					{
						Student& st = use.students[i]; cout << i << " " << st.lastName << " " << st.firstName << " " << student.averageMark << endl;
					}
				}
			} while (chooseTheme != 0);
		}
		break;
		case 4:
		{
			DBUsers use;
			Student student; Theme theme;
			double mark_choice = 0, num_out = 0;
			int num_theme = 0;
			cout << "Введите нужную оценку для поиска: ";
			cin >> mark_choice;
			cout << "1 - По всем темам\n2 - По конкретной теме\n3 - Только итоговый тест\n4 -Только средний балл\n0 - Выход\nВыберете вариант вывода: "; cin >> num_out;
			do
			{
				if (num_out == 1)
				{
					mark_choice = (int)mark_choice;
					for (int i = 0; i < use.countStudents; i++)
					{
						Student& st = use.students[i]; cout << st.lastName << " " << st.firstName;
						for (int j = 0; j < 8; j++)
						{
							if (use.students[i].marks[j] == mark_choice)
							{
								cout << theme.name[i] << " " << use.students[i].marks[j] << endl;
							}
						}
						cout << endl;
					}
				}
				if (num_out == 2)
				{
					mark_choice = (int)mark_choice;
					for (int i = 0; i < 8; i++)
					{
						cout << i << " - " << theme.name[i];
					}
					cout << "Введите номер темы, по которой нужно предоставить студентов: ";
					cin >> num_theme;
					while (num_theme < 0 && num_theme > 7)
					{
						cout << "Ошибка, такой темы нет. Введите номер темы: "; cin >> num_theme;
					}
					for (int i = 0; i < use.countStudents; i++)
					{
						Student& st = use.students[i];
						if (st.marks[num_theme] == mark_choice)
						{
							cout << st.lastName << " " << st.firstName << " " << mark_choice;
						}
						cout << endl;
					}
				}
				if (num_out == 3)
				{
					mark_choice = (int)mark_choice;
					for (int i = 0; i < use.countStudents; i++)
					{
						Student& st = use.students[i];
						if (st.finalMark == mark_choice)
						{
							cout << st.lastName << " " << st.firstName << " " << st.finalMark;
						}
						cout << endl;
					}
				}
				if (num_out == 4)
				{
					for (int i = 0; i < use.countStudents; i++)
					{
						Student& st = use.students[i];
						if (st.averageMark == mark_choice)
						{
							cout << st.lastName << " " << st.firstName << " " << st.averageMark;
						}
						cout << endl;
					}
				}
				if (num_out < 0 && num_out > 4)
				{
					cout << "Не корректный ввод. Выберите вариант вывода: "; cin >> num_out;
				}
			} while (num_out != 0);

		}
		break;
		case 5:
		{

		}
		break;

		default:
			break;
		}
	}
	break;
	default:
		break;
	}
}
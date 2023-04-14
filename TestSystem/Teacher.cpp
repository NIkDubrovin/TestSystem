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
	cout << "Список студентов" << endl;
	for (int i = 0; i < use.countStudents; i++)
	{
		cout << i + 1 << " - " << use.students[i].lastName << " " << use.students[i].firstName << endl;
	}
	cout << "Выберете студента для которого хотите изменить оценку: "; cin >> chooseStudent;
	while (!isCorrectInput())
	{
		cin >> chooseStudent;
	}
	while (chooseStudent > use.countStudents && chooseStudent < 1)
	{
		cout << "Такого студента нет. Выберите студента для которого хотите изменить оценку: "; cin >> chooseStudent;
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
	cout << "Выберите тему для изменения прогресса: "; cin >> chooseTheme;
	while (!isCorrectInput())
	{
		cin >> chooseTheme;
	}
	while (chooseTheme > 8 || chooseTheme < 1)
	{
		cout << "Такой темы нет. Выберите тему для изменения прогресса: "; cin >> chooseTheme;
		while (!isCorrectInput())
		{
			cin >> chooseTheme;
		}
	}
	chooseTheme--;
	cout << "Введите новую оценку: "; cin >> changeMark;
	while (!isCorrectInput())
	{
		cin >> changeMark;
	}
	while (changeMark < 2 || changeMark > 5)
	{
		cout << "Оценки ставятся в 5 - ти бальной системе. Введите новую оценку: "; cin >> changeMark;
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
	cout << "1 - По всем темам\n2 - По конкретной теме\n3 - Только итоговый тест\n4 - Только средний балл\n0 - Выход\nВыберете вариант вывода: "; cin >> chooseTheme;
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
		else if(chooseTheme < 0 && chooseTheme > 4)
		{
			cout << "Некорректный ввод. Введите вариант вывода:"; cin >> chooseTheme;
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
						cout << question.themes[j].name <<endl << "Оценка: " << use.students[i].marks[j] << endl;
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
				cout << use.students[i].lastName << " " << use.students[i].firstName;
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
void Sorted(Student& student, Theme& theme)
{
	cout << " ";
}
void TeacherMain(DBUsers& Dbusers, DBQuestion& question)
{

	int choice = 0, choice1 = 0, choice2 = 0;
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
					cout << "Некорректный ввод. Введите номер желаемого действия:"; cin >> choice1;
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
				{	//Фильтрация
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
	}while (choice != 0);
}
#include "TestSystem.h"

int main()
{
	DBQuestion questions = { 0 };
	DBUsers users{ 0 };
	const char* nameDbUsers = "dbU.db",
		* nameDbQuestions = "dbQ.db";
	STATE state = MENU;
	int id = 0;

	// LOCALE
	setlocale(LC_ALL, "RUS");
	system("chcp 1251");
	clearScreen();

	if (!toDecodeFile(nameDbQuestions, nameDbUsers, questions, users))
	{
		debug("Ошибка при загрузке БД!");
		return 0;
	}

	while (state != EXIT)
	{
		switch (state)
		{
		case MENU:
			if (!inLogin(state, users, id)) 
			{
				debug("malloc strings\n");
				return 0;
			}
			break;
		case TEACHER:
			TeacherMain(users, questions);
			break;
		case STUDENT:
			StudentMenu(users, questions);
			break;
		case EXIT:
			break;
		default:
			break;
		}
	}

	if (!toEncodeFile(nameDbQuestions, nameDbUsers, questions, users))
	{
		debug("Ошибка при сохранении БД!");
		return 0;
	}

	freeDBs(users, questions);

	return 0;
}

int inLogin(STATE& state, DBUsers& users, int& id) {
	User user = { 0 };
	int exit = 0;
	
	while (!exit)
	{
		printf_s("Введите логин: ");
		user.login = getConsoleString();

		printf_s("Введите пароль: ");
		user.password = getConsoleString();

		int res = checkUser(user, users, id);
		switch (res)
		{
		case 0:
		{
			state = TEACHER;
			exit = 1;
			printf_s("Преподаватель.\n");
		} break;
		case 1:
		{
			printf_s("Студент.\n");
			state = STUDENT;
			exit = 1;
		} break;
		default:
		{
			printf_s("Пользователь не найден.\n");
		} break;
		}

		if (!exit)
		{
			char c = 0;
			printf_s("Ввести заново (y/n) : ");
			if ((c = getchar()) != 'y') {
				exit = 1;
				state = EXIT;
			}
			else
			{
				free(user.login);
				free(user.password);
				clearScreen();
			}
		}
	}

	free(user.login);
	free(user.password);

	return 1;
}

char* getConsoleString() {
	int MAX_SYMBOLS = 256;
	char* buf = nullptr;

	if ((buf = (char*)malloc(MAX_SYMBOLS * sizeof(char))) == nullptr)
		return nullptr;

	scanf_s("%255[^\n]%*c", buf, MAX_SYMBOLS);

	std::cin.seekg(0, std::ios::end);
	std::cin.clear();
}

int checkUser(User& user, DBUsers& users, int& id) {
	for (int i = 0; i < users.countAdmins; i++)
	{
		User& check = users.admins[i];
		if (!strcmp(user.login, check.login) && !strcmp(user.password, check.password))
		{
			id = i;
			return 0;
		}
	}

	for (int i = 0; i < users.countStudents; i++)
	{
		User& check = users.students[i].user;
		if (!strcmp(user.login, check.login) && !strcmp(user.password, check.password))
		{
			id = i;
			return 1;
		}
	}

	id = -1;
	return -1;
}

unsigned char isCorrectInput() 
{
	if (std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore(1000, '\n');
		std::cout << "\nERROR! Некорректный ввод.\n\n";
		return 0;
	}

	std::cin.ignore(1000, '\n');
	if (std::cin.gcount() > 1) {
		std::cout << "\nERROR! Некорректный ввод.\n\n";
		return 0;
	}

	return 1;
}

void clearScreen()
{
	system("cls");

	// to skip other symbols
	std::cin.seekg(0, std::ios::end);
	std::cin.clear();
}

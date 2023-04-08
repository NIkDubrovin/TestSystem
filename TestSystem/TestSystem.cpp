#include <iostream>
#include "TestSystem.h"

typedef enum State
{
	MENU,
	TEACHER,
	STUDENT,
	EXIT
} State;

int main()
{
	DBQuestion questions = { 0 };
	DBUsers users{ 0 };
	const char* nameDbUsers = "dbUsers.bin",
		* nameDbQuestions   = "dbQuestions.bin";
	State state = MENU;

	// LOCALE
	setlocale(LC_ALL, "RUS");
	system("chcp 1251");
	

	/*if (!toDecodeFile(nameDbQuestions, nameDbUsers, questions, users))
		return 0;*/

	createDbFiles("dbQ.bin", "dbU.bin", &questions, &users);

	switch (state)
	{
	case MENU:
		inLogin();
		break;
	case TEACHER:
		break;
	case STUDENT:
		break;
	case EXIT:
		break;
	default:
		break;
	}


	if (!toEncodeFile(nameDbQuestions, nameDbUsers, questions, users))
		return 0;


	return 0;
}

int inLogin() {
	return 0;
}



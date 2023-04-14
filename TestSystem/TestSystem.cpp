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
	const char* nameDbUsers = "dbU.db",
		* nameDbQuestions   = "dbQ.db";
	State state = MENU;

	// LOCALE
	setlocale(LC_ALL, "RUS");
	system("chcp 1251");
	
	/*createDbFiles(nameDbQuestions, nameDbUsers);
	readDBsFromFiles(nameDbUsers, nameDbQuestions, questions, users);*/

	if (!toDecodeFile(nameDbQuestions, nameDbUsers, questions, users))
		return 0;

	printDBs(users, questions);

	switch (state)
	{
	case MENU:
		inLogin();
		break;
	case TEACHER:
		break;
	case STUDENT:
		StudentMenu(users,questions);
	case EXIT:
		break;
	default:
		break;
	}
	StudentMenu(users, questions);
	

	if (!toEncodeFile(nameDbQuestions, nameDbUsers, questions, users))
		return 0;

	freeDBs(users, questions);

	return 0;
}

int inLogin() {
	return 0;
}



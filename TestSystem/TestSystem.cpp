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

	if (!toEncodeFile(nameDbQuestions, nameDbUsers, &questions, &users))
		return 0;

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


	if (!toDecodeFile(nameDbQuestions, nameDbUsers, &questions, &users))
		return 0;


	return 0;
}

int inLogin() {
	return 0;
}



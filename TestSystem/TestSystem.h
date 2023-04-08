#include <stdio.h> 
#include <stdlib.h>
#include <math.h>

const int code = 0x2;

typedef struct Question
{
	int maxSymbols = 300;
	char *text;
	int Answer[4];
	int rightAnswer;
} Question;

typedef struct Answer
{
	char* text;
} Answer;

typedef struct Theme
{
	char name[15];
	int countQuestions;
	Question* questions;
} Theme;

typedef struct DBQuestion
{
	const int countTopics = 8;
	Theme* topics;
} Question;

typedef struct DBUsers
{
	int maxSymbols = 20;
	int countAdmins;
	User* admins;
	int countStudents;
	Student* students;
} DBUsers;

typedef struct Student
{
	User user;
	char* lastName;
	char* firstName;

	int marks[8] = {0};
	int finalMark = 0;
	float averageMark = 0;
} Student;

typedef struct User
{
	char* login;
	char* password;
} User;

// DB FUNCTIONS
int toEncodeFile(char* fQuests, char* fUsers, DBQuestion* questions, DBUsers* users);
int toDecodeFile(char* fQuests, char* fUsers, DBQuestion* questions, DBUsers* users);
int fileOpen(char* nameFile);
int createDbFiles(char* fQuests, char* fUsers, DBQuestion* questions, DBUsers* users);

// TEACHERS FUNCTIONS
 
// return 0 - isnt founded
// return 1 - teacher
// return 2  - student
int checkUser(User* user, DBUsers* users);
int editQuestions(DBQuestion* qs);
int workDBStudents(DBUsers* dbUsers);

int trainingTheme(DBQuestion* questions);
int testTheme(Student* student, DBQuestion* questions);
int finalTest(Student* student, DBQuestion* questions);


#pragma once
#include <stdio.h> 
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <locale.h>
#include <time.h>


const int code = 0x10;

typedef struct Answer
{
	char* text;
} Answer;

typedef struct Question
{
	char* text;
	Answer answers[4];
	int rightAnswer;
} Question;

typedef struct Theme
{
	char* name;
	int countQuestions;
	Question* questions;
} Theme;

typedef struct User
{
	char* login;
	char* password;
} User;

typedef struct Student
{
	User user;
	char* lastName;
	char* firstName;

	int marks[8];
	int finalMark = 0;
	float averageMark = 0;
} Student;

typedef struct DBQuestion
{
	int countThemes = 8;
	Theme* themes;
} DBQuestion;

typedef struct DBUsers
{
	int countAdmins;
	int countStudents;
	User* admins;
	Student* students;
} DBUsers;

typedef enum STATE
{
	MENU,
	TEACHER,
	STUDENT,
	EXIT
} STATE;

// DB FUNCTIONS
int toEncodeFile(const char* fileNameQues, const char* fileNameUsers, const DBQuestion& questions, const DBUsers& users);
int toDecodeFile(const char* fileNameQues, const char* fileNameUsers, DBQuestion& questions, DBUsers& users);
int createDbFiles(const char* fileNameQues, const char* fileNameUsers);
int createUser(User&, int);
void randStr(char* buf, int count, int startC, int endC);
char* readStringFromFileToBuffer(FILE* file, char* buf);
char* readStringFromBuffer(char** buf);
void freeDBs(const DBUsers& users, const DBQuestion& questions);
void printDBs(const DBUsers& users, const DBQuestion& questions);
int readDBsFromFiles(const char* fileNameUsers, const char* fileNameQuests, DBQuestion& questions, DBUsers& users);
int readDBsFromBuffers(const char* bufUsers, int sizeBufUsers, DBUsers& users, const char* bufQuests, int sizeBufQuests, DBQuestion& questions);
int DBsToBuffers(char** bufQuests, int* sizeQuests, char** bufUsers, int* sizeUsers, const DBQuestion& questions, const DBUsers& users);
int writeDBsFromBuffers(const char* fileNameUsers, char* bufUsers, int sizeBufUsers, const DBUsers& users, const char* fileNameQuests, char* bufQuests, int sizeBufQuests, const DBQuestion& questions);
void printBuffer(const char* buf, int size, const char* type);
int sizesDBs(int* sizeDBUsers, int* sizeDBQues, DBQuestion& questions, DBUsers& users);
void freeStudent(const Student&);
void freeQuestion(const Question&);

// MENU  FUNCTIONS

// return -1 - isnt founded
// return 0 - teacher
// return 1  - student
int checkUser(User& user, DBUsers& users, int&);

int inLogin(STATE& state, DBUsers& users, int& id);
int editQuestions(DBQuestion* qs);
int workDBStudents(DBUsers* dbUsers);

int StudentMenu(DBUsers& users, DBQuestion& questions);
int trainingTheme(DBQuestion* questions);
int testTheme(Student* student, DBQuestion* questions);
int finalTest(Student* student, DBQuestion* questions);

char* getConsoleString();
void clearScreen();
unsigned char isCorrectInput();
void debug(const char*);

void TeacherMain(DBUsers& Dbusers, DBQuestion& question);
int add_student(DBUsers& dbuser);
int  del_student(DBUsers& dbuser);
int changeProgress_student(DBUsers& use, DBQuestion& question);
void outputStudents(DBUsers& use, DBQuestion& question);
void Filtr(DBUsers& use, DBQuestion& question);
void sortMarks(DBUsers& use, DBQuestion& dbq);

int add_qoestion(DBQuestion& quse);
int del_question(DBQuestion& quse);
int change_qustion(DBQuestion& quse);
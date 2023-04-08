#include "TestSystem.h"

int toEncodeFile(const char* fQuests, const char* fUsers, DBQuestion& questions, DBUsers& users)
{

    return 0;
}

//typedef struct DBUsers
//{
//	const int maxSymbols = 20;
//	int countAdmins;
//	User* admins;
//	int countStudents;
//	Student* students;
//} DBUsers;
int toDecodeFile(const char* fileNameQuests,const char* fileNameUsers, DBQuestion& questions, DBUsers& users)
{
	FILE* dbFileQ = nullptr, *dbFileUsers = nullptr;

	if (fopen_s(&dbFileQ, fileNameQuests, "rb") != 0) {
		printf("The file %s was not opened\n", fileNameQuests);
		return 0;
	}

	if (fopen_s(&dbFileUsers, fileNameUsers, "rb") != 0) {
		printf("The file %s was not opened\n", fileNameUsers);
		return 0;
	}

	// users
	fscanf_s(dbFileUsers, "%d %d %d", users.maxSymbols, users.countAdmins,
													 users.countStudents);

	users.admins = (User*)malloc(sizeof(User) * users.countAdmins);
	users.students = (Student*)malloc(sizeof(Student) * users.countStudents);

	if (users.admins == nullptr || users.students == nullptr) {
		printf("error - malloc admins || students");
		return 0;
	}

	for (int i = 0; i < users.countAdmins; i++)
	{
		users.admins[i].login = (char *)malloc(sizeof(char) * users.maxSymbols); 
		users.admins[i].password = (char*)malloc(sizeof(char) * users.maxSymbols);
		fread_s()
	}

	
	

	
	fclose(dbFileQ);
	fclose(dbFileUsers);

	return 1;
}

int fileOpen(char* nameFile)
{
	return 0;
}

int createDbFiles(char* fQuests, char* fUsers, DBQuestion* questions, DBUsers* users) 
{
	/*FILE* out = nullptr;

	if (fopen_s(&out, fileOut, "r") != 0)
		printf("The file %s was not opened\n", fileOut);
	else {
		darr.m = 0, darr.n = 0;

		while (fscanf_s(out, "%lf", &darr.arr[darr.n][darr.m]) != EOF) {
			darr.m++;
			if (fgetc(out) == '\n') {
				darr.n++;
				darr.m = 0;
			}
		}

		darr.n++;

		fclose(out);
	}*/

	return 0;
}
#include "TestSystem.h"

int toEncodeFile(const char* fQuests, const char* fUsers, DBQuestion& questions, DBUsers& users)
{

    return 0;
}

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
	fscanf_s(dbFileUsers, "%d %d %d", &users.maxSymbols, &users.countAdmins,
													 &users.countStudents);

	users.admins = (User*)malloc(sizeof(User) * users.countAdmins);
	users.students = (Student*)malloc(sizeof(Student) * users.countStudents);

	if (users.admins == nullptr || users.students == nullptr) {
		printf("error - malloc admins || students");
		return 0;
	}

	// READ ADMINS
	for (int i = 0; i < users.countAdmins; i++)
	{
		User& user = users.admins[i];
		if (!createUser(users.admins[i], users.maxSymbols)) {
			// todo check malloc
		}

		fread_s(user.login, sizeof(char) * users.maxSymbols, sizeof(char), users.maxSymbols, dbFileUsers);
		fread_s(user.password, sizeof(char) * users.maxSymbols, sizeof(char), users.maxSymbols, dbFileUsers);
	}

	// todo check fread

	// READ STUDENTS
	for (int i = 0; i < users.countStudents; i++)
	{
		Student& st = users.students[i];

		if (createUser(st.user, users.maxSymbols)) {
			fread_s(st.user.login, sizeof(char) * users.maxSymbols, sizeof(char), users.maxSymbols, dbFileUsers);
			fread_s(st.user.password, sizeof(char) * users.maxSymbols, sizeof(char), users.maxSymbols, dbFileUsers);
		}
		else {
			// todo check malloc
		}

		st.firstName = (char*)malloc(sizeof(char) * users.maxSymbols);
		st.lastName = (char*)malloc(sizeof(char) * users.maxSymbols);
		if (st.firstName != nullptr && st.lastName != nullptr) {
			memset(st.firstName, 0, users.maxSymbols);
			memset(st.lastName, 0, users.maxSymbols);
		} // todo check

		fread_s(st.firstName, sizeof(char) * users.maxSymbols, sizeof(char), users.maxSymbols, dbFileUsers);
		fread_s(st.lastName, sizeof(char) * users.maxSymbols, sizeof(char), users.maxSymbols, dbFileUsers);

		// todo number of themes
		int countThemes = 8;
		memset(st.marks, 0, countThemes);
		fread_s(st.marks, sizeof(int) * countThemes, sizeof(int), countThemes, dbFileUsers);

		fscanf_s(dbFileUsers, "%d%d", &st.finalMark, &st.averageMark);
		// todo check malloc
	}


	// READ QUESTIONS
	fscanf_s(dbFileQ, "%d", &questions.countThemes);
	questions.themes = (Theme*)malloc(sizeof(Theme) * questions.countThemes);

	for (int i = 0; i < questions.countThemes; i++)
	{
		Theme& th = questions.themes[i];
		// todo count bytes name
		int countBytes = 15;
		fread_s(th.name, countBytes * sizeof(char), sizeof(char), countBytes, dbFileQ);
		fscanf_s(dbFileQ, "%d", &th.countQuestions);

		th.questions = (Question*)malloc(sizeof(Question) * th.countQuestions);
		// todo check

		// QUESTION
		for (int j = 0; j < th.countQuestions; j++)
		{
			Question& q = th.questions[j];
			fscanf_s(dbFileQ, "%d", &q.maxSymbols);

			q.text = (char*)malloc(q.maxSymbols * sizeof(char));
			fread_s(q.text, q.maxSymbols * sizeof(char), sizeof(char), q.maxSymbols, dbFileQ);

			int countAnswers = 4;
			for (int k = 0; k < countAnswers; k++)
			{
				Answer& a = q.answers[k];
				a.text = (char*)malloc(q.maxSymbols * sizeof(char));
				fread_s(a.text, q.maxSymbols * sizeof(char), sizeof(char), q.maxSymbols, dbFileQ);
			}

			fscanf_s(dbFileQ, "%d", &q.rightAnswer);
		}
	}

	
	fclose(dbFileQ);
	fclose(dbFileUsers);

	return 1;
}

int createUser(User& user, int maxSymbols) {
	user.login = (char*)malloc(sizeof(char) * maxSymbols);
	user.password = (char*)malloc(sizeof(char) * maxSymbols);
	
	if (user.login != nullptr && user.password != nullptr) {
		memset(user.login, 0, maxSymbols);
		memset(user.password, 0, maxSymbols);
		return 1;
	}
	else
		return 0;
}

int fileOpen(char* nameFile)
{
	return 0;
}

//#define con 0;

int createDbFiles(const char* fileNameQuests,const char* fileNameUsers, DBQuestion* questions, DBUsers* users)
{
	FILE* dbFileQ = nullptr, * dbFileUsers = nullptr;
	FILE* files[8];
	const char* names[8] = {
		"адреса и указатели.txt",
		"динамическая память.txt",
		"массивы.txt",
		"рекурсия.txt",
		"строки.txt",
		"структуры.txt",
		"файлы.txt",
		"циклы.txt"
	};

	if (fopen_s(&dbFileQ, fileNameQuests, "w+b") != 0) {
		printf("The file %s was not opened\n", fileNameQuests);
		return 0;
	}

	if (fopen_s(&dbFileUsers, fileNameUsers, "w+b") != 0) {
		printf("The file %s was not opened\n", fileNameUsers);
		return 0;
	}

	fprintf_s(dbFileQ, "%d", 8);

	for (int i = 0; i < 8; i++)
	{
		if (fopen_s(&files[i], names[i], "rt") != 0)
			std::cout << "errror" << names[i] << std::endl;

		fprintf(dbFileQ, "%s", names[i]);
		fprintf(dbFileQ, "%d", 30);

#ifdef con
		printf_s( "%s", names[i]);
		printf_s( "%d", 30); 
#endif // con

		// questions
		for (int j = 0; j < 30; j++)
		{
			char buf[300] = { 0 };
			fprintf(dbFileQ, "%d", 300);

#ifdef con
			printf_s("\n%d: \n%d",j, 300);
#endif // con

			if (i == 2 || i == 3 || i == 7) //arrays// foreaches
				fseek(files[i], 2, SEEK_CUR);
			else if(i == 4 && j > 0)
				fseek(files[i], 5, SEEK_CUR);
			else if(i == 4) // strings
				fseek(files[i], 3, SEEK_CUR);

			if (i == 4) { // strings
				int k = 0;
				while (k < 300) {
					buf[k] = fgetc(files[i]);
					if (buf[k] == '?')
						break;
					k++;
				} 
			}
			else {
				fgets(buf, 300, files[i]);
				if (buf[0] == '.')
					buf[0] = ' ';

				int pos = strlen(buf);
				buf[pos - 1] = 0;
			}

			fwrite(buf, sizeof(char), 300, dbFileQ);
#ifdef  con
			printf_s("%s", buf);
#endif //  con

			for (int k = 0; k < 4; k++)
			{
				int pos = ftell(files[i]);
				memset(buf, 0, 300);

				if (i == 4) {
					if(k == 0)
						fseek(files[i], 4, SEEK_CUR);
					else 
						fseek(files[i], 3, SEEK_CUR);

					int k = 0;
					char c = 0;
					while (k < 300) {
						c = fgetc(files[i]);
						if (c == ' ' || c == '\n')
							break;
						buf[k] = c;
						k++;
					}
				}
				else {
					fseek(files[i], 2, SEEK_CUR);
					fgets(buf, 300, files[i]);

					pos = strlen(buf);
					buf[pos - 1] = 0;
				}

				fwrite(buf, sizeof(char), 300, dbFileQ);
#ifdef  con
				printf_s("%s", buf);
#endif
			}

			int rightQ = 0;

			if (i == 2 || i == 7)
				fseek(files[i], 1, SEEK_CUR);
			else if(i == 3)
				fseek(files[i], 8, SEEK_CUR);
			else if(i == 4)
				fseek(files[i], 10, SEEK_CUR);
			else if(i == 5 || i == 6)
				fseek(files[i], 2, SEEK_CUR);
			else 
				fseek(files[i], 7, SEEK_CUR);

			if (i == 5 || i == 6)
			{
				int ansPos = 0;
				if (i == 5)
					ansPos = 5572;
				else
					ansPos = 3360;

				int lastPos = ftell(files[i]);

				fseek(files[i], ansPos + j * 3, SEEK_SET);
				rightQ = fgetc(files[i]);
				
				fseek(files[i], lastPos, SEEK_SET);
			} else 
			{
				fscanf_s(files[i], "%c", &rightQ);
			}

			rightQ -= int('a');

			fprintf(dbFileQ, "%d", rightQ);
#ifdef con
			printf_s("%d", rightQ);
#endif	

			if (i != 4 && i != 5 && i != 6)
				fseek(files[i], 4, SEEK_CUR);
#ifdef con
			std::cout << std::endl;
#endif
		}
	}

	
	for (int i = 0; i < 8; i++)
	{
		fclose(files[i]);
	}
	

	//// READ QUESTIONS
	//fscanf_s(dbFileQ, "%d", questions.countThemes);
	//questions.themes = (Theme*)malloc(sizeof(Theme) * questions.countThemes);

	//for (int i = 0; i < questions.countThemes; i++)
	//{
	//	Theme& th = questions.themes[i];
	//	// todo count bytes name
	//	int countBytes = 15;
	//	fread_s(th.name, countBytes * sizeof(char), sizeof(char), countBytes, dbFileQ);
	//	fscanf_s(dbFileQ, "%d", th.countQuestions);

	//	th.questions = (Question*)malloc(sizeof(Question) * th.countQuestions);
	//	// todo check

	//	// QUESTION
	//	for (int j = 0; j < th.countQuestions; j++)
	//	{
	//		Question& q = th.questions[j];
	//		fscanf_s(dbFileQ, "%d", q.maxSymbols);

	//		q.text = (char*)malloc(q.maxSymbols * sizeof(char));
	//		fread_s(q.text, q.maxSymbols * sizeof(char), sizeof(char), q.maxSymbols, dbFileQ);

	//		int countAnswers = 4;
	//		for (int k = 0; k < countAnswers; k++)
	//		{
	//			Answer& a = q.answers[k];
	//			a.text = (char*)malloc(q.maxSymbols * sizeof(char));
	//			fread_s(a.text, q.maxSymbols * sizeof(char), sizeof(char), q.maxSymbols, dbFileQ);
	//		}

	//		fscanf_s(dbFileQ, "%d", q.rightAnswer);
	//	}
	//}


	fclose(dbFileQ);
	fclose(dbFileUsers);

	return 1;

	return 0;
}
#include "TestSystem.h"

int toEncodeFile(const char* fileNameQues, const char* fileNameUsers, const DBQuestion& questions, const DBUsers& users)
{
	char* bufUsers = nullptr, * bufQues = nullptr;
	int sizeBufUsers = 0, sizeBufQues = 0;

	if (!DBsToBuffers(&bufQues, &sizeBufQues, &bufUsers, &sizeBufUsers, questions, users))
		return 0;

	for (int i = 0; i < sizeBufUsers; i++)
	{
		bufUsers[i] += code;
	}

	for (int i = 0; i < sizeBufQues; i++)
	{
		bufQues[i] += code;
	}

	if (!writeDBsFromBuffers(fileNameUsers, bufUsers, sizeBufUsers, users, fileNameQues, bufQues, sizeBufQues, questions))
		return 0;

	free(bufUsers);
	free(bufQues);

    return 1;
}

int sizesDBs(int* sizeDBUsers, int* sizeDBQues,const DBQuestion& questions,const DBUsers& users) 
{
	int size = 0;
	
	// USERS
	size += sizeof(int) * 2;

	for (int i = 0; i < users.countAdmins; i++)
	{
		User& user = users.admins[i];
		if (user.login == nullptr || user.password == nullptr)
			return 0;

		size += (strlen(user.login) + strlen(user.password) + 2); // two \0
	}

	for (int i = 0; i < users.countStudents; i++)
	{
		Student& st = users.students[i];

		if (st.user.login == nullptr || st.user.password == nullptr || st.lastName == nullptr || st.firstName == nullptr)
			return 0;

		size += (strlen(st.user.login) + strlen(st.user.password) +
			strlen(st.lastName) + strlen(st.firstName) + 4 +
			sizeof(int) * 9 + sizeof(float));
	}

	*sizeDBUsers = size;
	size = 0;

	// QUESTIONS
	size += sizeof(int);

	for (int i = 0; i < questions.countThemes; i++)
	{
		Theme& th = questions.themes[i];
		size += (strlen(th.name) + 1 + sizeof(int));

		// QUESTION
		for (int j = 0; j < th.countQuestions; j++)
		{
			Question& q = th.questions[j];
			if (q.text == nullptr)
				return 0;

			size += (strlen(q.text) + 1);

			int countAnswers = 4;
			for (int k = 0; k < countAnswers; k++)
			{
				Answer& a = q.answers[k];
				if (a.text == nullptr)
					return 0;

				size += (strlen(a.text) + 1);
			}

			size += sizeof(int);
		}
	}

	*sizeDBQues = size;
	return 1;
}

int DBsToBuffers(char** bufQuests, int* sizeQuests, char** bufUsers, int *sizeUsers, const DBQuestion& questions, const DBUsers& users) 
{
	char* buf = nullptr;
	int size = 0, pos = 0;

	if (!sizesDBs(sizeUsers, sizeQuests, questions, users))
		return 0;

	*bufQuests = (char*)malloc(*sizeQuests * sizeof(char));
	*bufUsers = (char*)malloc(*sizeUsers * sizeof(char));
	if (*bufQuests == nullptr || *bufUsers == nullptr)
	{
		debug("malloc buf ques and buf users");
		return 0;
	}

	memset(*bufUsers, 0, *sizeUsers);
	memset(*bufQuests, 0, *sizeQuests);

	// USERS
	buf = *bufUsers, size = *sizeUsers;
	*(int*)buf = users.countAdmins;
	pos += sizeof(int);
	*(int*) (buf + pos) = users.countStudents;
	pos += sizeof(int);

	// ADMINS
	for (int i = 0; i < users.countAdmins; i++)
	{
		
		User& user = users.admins[i];
		sprintf_s((buf + pos), size - pos, "%s%c%s", user.login, 0, user.password);
		pos += ((strlen(user.login) + strlen(user.password) + 2));
	}

	// STUDENTS
	for (int i = 0; i < users.countStudents; i++)
	{
		Student& st = users.students[i];
		sprintf_s((buf + pos), size - pos, "%s%c%s%c%s%c%s", st.user.login, 0, st.user.password,0, st.lastName, 0, st.firstName);


		pos += (strlen(st.user.login) + strlen(st.user.password)
			+ strlen(st.lastName) + strlen(st.firstName) + 4);

		// todo number of themes
		for (int j = 0; j < 8; j++)
		{
			((int*)(buf + pos))[j] = st.marks[j];
		}
	
		pos += sizeof(int) * 8;

		*((int*)(buf + pos)) = st.finalMark;
		pos += sizeof(int);

		*((float*)(buf + pos)) = st.averageMark;
		pos += sizeof(float);
	}

	// QUESTIONS
	buf = *bufQuests;
	pos = 0, size = *sizeQuests;

	*((int*)(buf + pos)) = questions.countThemes;
	pos += sizeof(int);

	for (int i = 0; i < questions.countThemes; i++)
	{
		//printBuffer(buf, pos, "%c");
		Theme& th = questions.themes[i];
		pos += sprintf_s((buf + pos), size - pos, "%s", th.name);
		pos += 1; // \0

		*((int*)(buf + pos)) = th.countQuestions;
		pos += sizeof(int);

		// QUESTION
		for (int j = 0; j < th.countQuestions; j++)
		{
			Question& q = th.questions[j];

			pos += sprintf_s((buf + pos), size - pos, "%s", q.text);
			pos += 1; // \0

			int countAnswers = 4;
			for (int k = 0; k < countAnswers; k++)
			{
				Answer& a = q.answers[k];
				pos += sprintf_s((buf + pos), size - pos, "%s", a.text);
				pos += 1; // \0
			}

			*((int*)(buf + pos)) = q.rightAnswer;
			pos += sizeof(int);
		}
	}

	return 1;
}

int writeDBsFromBuffers(const char* fileNameUsers, char* bufUsers, int sizeBufUsers, const DBUsers& users, const char* fileNameQuests, char* bufQuests, int sizeBufQuests,const DBQuestion& questions) {
	FILE* dbFileQ = nullptr, * dbFileUsers = nullptr;
	
	if (bufUsers == nullptr || bufQuests == nullptr)
		return 0;

	if (fopen_s(&dbFileQ, fileNameQuests, "wb") != 0) {
		printf("The file %s was not opened\n", fileNameQuests);
		return 0;
	}

	if (fopen_s(&dbFileUsers, fileNameUsers, "wb") != 0) {
		printf("The file %s was not opened\n", fileNameUsers);
		return 0;
	}

	fwrite(bufUsers, sizeof(char), sizeBufUsers, dbFileUsers);
	fwrite(bufQuests, sizeof(char), sizeBufQuests, dbFileQ);

	fclose(dbFileQ);
	fclose(dbFileUsers);

	return 1;
}

int readDBsFromBuffers(const char* bufUsers, int sizeBufUsers,DBUsers& users, const char* bufQuests, int sizeBufQuests, DBQuestion& questions)
{
	char* buf = (char*)bufUsers;
	// users
	users.countAdmins = *((int*)buf);
	buf += sizeof(int);
	users.countStudents = *((int*)buf);
	buf += sizeof(int);

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

		user.login = readStringFromBuffer(&buf);
		user.password = readStringFromBuffer(&buf);
	}

	// READ STUDENTS
	for (int i = 0; i < users.countStudents; i++)
	{
		Student& st = users.students[i];

		// USER
		st.user.login = readStringFromBuffer(&buf);
		st.user.password = readStringFromBuffer(&buf);

		// Names
		st.lastName = readStringFromBuffer(&buf);
		st.firstName = readStringFromBuffer(&buf);

		// todo number of themes
		int countThemes = 8;
		memset(st.marks, 0, countThemes * sizeof(int));
		for (int j = 0; j < 8; j++)
		{
			st.marks[j] = *((int*)buf);
			buf += sizeof(int);
		}

		st.finalMark = *((int*)buf);
		buf += sizeof(int); 

		st.averageMark = *((float*)buf);
		buf += sizeof(float);
	}

	// READ QUESTIONS
	buf = (char*)bufQuests;

	questions.countThemes = *((int*)buf);
	buf += sizeof(int);

	if ((questions.themes = (Theme*)malloc(sizeof(Theme) * questions.countThemes)) == nullptr) {
		debug("malloc themes");
		return 0;
	}

	for (int i = 0; i < questions.countThemes; i++)
	{
		Theme& th = questions.themes[i];

		th.name = readStringFromBuffer(&buf);

		th.countQuestions = *((int*)buf);
		buf += sizeof(int);

		if((th.questions = (Question*)malloc(sizeof(Question) * th.countQuestions)) == nullptr)
			return 0;

		// QUESTION
		for (int j = 0; j < th.countQuestions; j++)
		{
			Question& q = th.questions[j];

			q.text = readStringFromBuffer(&buf);

			int countAnswers = 4;
			for (int k = 0; k < countAnswers; k++)
			{
				Answer& a = q.answers[k];
				a.text = readStringFromBuffer(&buf);
			}

			q.rightAnswer = *((int*)buf);
			buf += sizeof(int);
		}
	}

	return 1;
}

int readDBsFromFiles(const char* fileNameUsers,const char* fileNameQuests, DBQuestion& questions, DBUsers& users)
{
	FILE* dbFileQ = nullptr, * dbFileUsers = nullptr;
	char* buf = nullptr;
	int sizeBuf = 300;

	buf = (char*)malloc(sizeBuf * sizeof(char));
	if (buf == nullptr)
		return 0;

	memset(buf, 0, sizeBuf);

	if (fopen_s(&dbFileQ, fileNameQuests, "rb") != 0) {
		printf("The file %s was not opened\n", fileNameQuests);
		return 0;
	}

	if (fopen_s(&dbFileUsers, fileNameUsers, "rb") != 0) {
		printf("The file %s was not opened\n", fileNameUsers);
		return 0;
	}

	// users
	fread_s(&users.countAdmins, 1 * sizeof(int), sizeof(int), 1, dbFileUsers);
	fread_s(&users.countStudents, 1 * sizeof(int), sizeof(int), 1, dbFileUsers);

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

		user.login = readStringFromFileToBuffer(dbFileUsers, buf);
		user.password = readStringFromFileToBuffer(dbFileUsers, buf);
	}

	// todo check fread

	// READ STUDENTS
	for (int i = 0; i < users.countStudents; i++)
	{
		Student& st = users.students[i];

		// USER

		st.user.login = readStringFromFileToBuffer(dbFileUsers, buf);
		st.user.password = readStringFromFileToBuffer(dbFileUsers, buf);

		// Names

		st.lastName = readStringFromFileToBuffer(dbFileUsers, buf);
		st.firstName = readStringFromFileToBuffer(dbFileUsers, buf);

		// todo number of themes
		int countThemes = 8;
		memset(st.marks, 0, countThemes * sizeof(int));
		fread_s(st.marks, sizeof(int) * countThemes, sizeof(int), countThemes, dbFileUsers);

		fread_s(&st.finalMark, 1 * sizeof(int), sizeof(int), 1, dbFileUsers);
		fread_s(&st.averageMark, 1 * sizeof(float), sizeof(float), 1, dbFileUsers);
		// todo check malloc
	}

	// READ QUESTIONS
	fread_s(&questions.countThemes, 1 * sizeof(int), sizeof(int), 1, dbFileQ);
	questions.themes = (Theme*)malloc(sizeof(Theme) * questions.countThemes);

	for (int i = 0; i < questions.countThemes; i++)
	{
		Theme& th = questions.themes[i];

		th.name = readStringFromFileToBuffer(dbFileQ, buf);
		fread_s(&th.countQuestions, 1 * sizeof(int), sizeof(int), 1, dbFileQ);

		th.questions = (Question*)malloc(sizeof(Question) * th.countQuestions);
		// todo check

		// QUESTION
		for (int j = 0; j < th.countQuestions; j++)
		{
			Question& q = th.questions[j];

			q.text = readStringFromFileToBuffer(dbFileQ, buf);

			int countAnswers = 4;
			for (int k = 0; k < countAnswers; k++)
			{
				Answer& a = q.answers[k];
				a.text = readStringFromFileToBuffer(dbFileQ, buf);
			}

			fread_s(&q.rightAnswer, 1 * sizeof(int), sizeof(int), 1, dbFileQ);
		}
	}


	fclose(dbFileQ);
	fclose(dbFileUsers);
	free(buf);
	return 1;
}

int toDecodeFile(const char* fileNameQuests, const char* fileNameUsers, DBQuestion& questions, DBUsers& users)
{
	FILE* dbFileQ = nullptr, *dbFileUsers = nullptr;
	char* bufDBUsers = nullptr, * bufDBQuestions = nullptr;
	int sizeBufUsers = 0, sizeBufQues = 0;

	if (fopen_s(&dbFileQ, fileNameQuests, "rb") != 0) {
		printf("The file %s was not opened\n", fileNameQuests);
		return 0;
	}

	if (fopen_s(&dbFileUsers, fileNameUsers, "rb") != 0) {
		printf("The file %s was not opened\n", fileNameUsers);
		return 0;
	}

	// DB QUESTIONS
	fseek(dbFileQ, 0, SEEK_END);
	sizeBufQues = ftell(dbFileQ);
	bufDBQuestions = (char*)malloc(sizeBufQues * sizeof(char));
	if (bufDBQuestions == nullptr) {
		debug("malloc buf ques");
		return 0;
	}

	fseek(dbFileQ, 0, SEEK_SET);
	fread_s(bufDBQuestions, sizeBufQues * sizeof(char), sizeof(char), sizeBufQues, dbFileQ);

   	for (int i = 0; i < sizeBufQues; i++)
	{
		bufDBQuestions[i] -= code;
	}

	fseek(dbFileUsers, 0, SEEK_END);
	sizeBufUsers = ftell(dbFileUsers);
	bufDBUsers = (char*)malloc(sizeBufUsers * sizeof(char));
	if (bufDBUsers == nullptr)
	{
		debug("malloc buf users");
		return 0;
	}

	fseek(dbFileUsers, 0, SEEK_SET);
	fread_s(bufDBUsers, sizeBufUsers * sizeof(char), sizeof(char), sizeBufUsers, dbFileUsers);

	for (int i = 0; i < sizeBufUsers; i++)
	{
		bufDBUsers[i] -= code;
	}

	readDBsFromBuffers(bufDBUsers, sizeBufUsers, users, bufDBQuestions, sizeBufQues, questions);

	free(bufDBUsers);
	free(bufDBQuestions);

	fclose(dbFileQ);
	fclose(dbFileUsers);

	return 1;
}

void freeDBs(const DBUsers& users, const DBQuestion& questions) {
	if (users.admins != nullptr)
	{
		for (int i = 0; i < users.countAdmins; i++)
		{
			free(users.admins[i].login);
			free(users.admins[i].password);
		}

		free(users.admins);
	}

	if (users.students != nullptr) 
	{
		for (int i = 0; i < users.countStudents; i++)
		{
			Student& st = users.students[i];
			free(st.user.login);
			free(st.user.password);
			free(st.firstName);
			free(st.lastName);
		}

		free(users.students);
	}

	if (questions.themes != nullptr) 
	{
		for (int i = 0; i < questions.countThemes; i++)
		{
			free(questions.themes[i].name);
			for (int j = 0; j < questions.themes[i].countQuestions; j++)
			{
				Question& q = questions.themes[i].questions[j];

				free(q.text);
				for (int k = 0; k < 4; k++)
				{
					free(q.answers[k].text);
				}
			}
		}

		free(questions.themes);
	}
}

char* readStringFromBuffer(char** buf)
{
	int length = 0;
	char* string = nullptr;

	if (buf == nullptr)
		return nullptr;

	length = strlen(*buf) + 1; // \0

	if ((string = (char*)malloc(sizeof(char) * length)) == nullptr) {
		debug("malloc string");
		return nullptr;
	}
	
	for (int i = 0; i < length; i++)
	{
		string[i] = (*buf)[i];
	}

	*buf += length;

	return string;
}

char* readStringFromFileToBuffer(FILE* file, char* buf) {
	char c = 0;
	int length = 0;
	char* string = nullptr;

	if (buf == nullptr)
		return nullptr;

	do {
		fread(&c, sizeof(char), 1, file);
		buf[length++] = c;
	} while (c != 0);

	if ((string = (char*)malloc(sizeof(char) * length)) == nullptr)
	{
		printf_s("%s\n", "Error - malloc string");
		return nullptr;
	}

	memset(string, 0, length);

	for (int i = 0; i < length; i++)
	{
		string[i] = buf[i];
	}

	memset(buf, 0, length);

	return string;
}

void printDBs(const DBUsers& users, const DBQuestion& questions) {
	printf_s("USERS :\n");
	for (int i = 0; i < users.countAdmins; i++)
	{
		printf_s("Admin : %d : log: %s, pass : %s\n", i, users.admins[i].login, users.admins[i].password);
	}

	for (int i = 0; i < users.countStudents; i++)
	{
		Student& st = users.students[i];
		printf_s("Student: %d : log: %s, pass : %s, name : %s, lastname : %s, averM : %f\n",
			i, st.user.login, st.user.password, st.firstName, st.lastName, st.averageMark);
	}

	printf_s("\n\nQUESTIONS :\n");
	if (questions.themes != nullptr) 
	{
		for (int i = 0; i < questions.countThemes; i++)
		{
			Theme& th = questions.themes[i];
			if(th.name == nullptr)
				debug("theme name == nullptr");
			else
				printf_s("%d : %s\n", i, questions.themes[i].name);

			for (int j = 0; j < questions.themes[i].countQuestions; j++)
			{
				if (questions.themes[i].questions != nullptr) 
				{
					Question& q = questions.themes[i].questions[j];

					if(q.text == nullptr)
						debug("quest text == nullptr");
					else
						printf_s("%d : %s\n", j, q.text);

					for (int k = 0; k < 4; k++)
					{
						if(q.answers[k].text == nullptr)
							debug("answer text == nullptr");
						else
						printf_s("%d : %s\n", k, q.answers[k].text);
					}

					printf_s("rightAnswer : %d\n", q.rightAnswer);
				} else 
					debug("themes questions == nullptr");
			}
		}
	}
	else {
		debug("themes == nullptr");
	}
}

void randStr(char* buf, int count, int startC, int endC) {
	for (int i = 0; i < count; i++)
	{
		buf[i] = char(startC + rand() % (endC - startC) + 1);
	}
}

int createDbFiles(const char* fileNameQuests,const char* fileNameUsers)
{
	FILE* dbFileQ = nullptr, * dbFileUsers = nullptr;
	FILE* files[8] = {0};
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

	// DBQUESTIONS
	char buf[300] = { 0 };
	int countThemes = 8;
	fwrite(&countThemes, sizeof(int), 1, dbFileQ);

	for (int i = 0; i < 8; i++) // THEMES
	{
		if (fopen_s(&files[i], names[i], "rt") != 0) {
			std::cout << "error : " << names[i] << std::endl;
			return 0;
		}

		int countBytesName = 0, countQ = 30;

		// theme name
		memset(buf, 0, 300);
		while (names[i][countBytesName] != '.') {
			buf[countBytesName] = names[i][countBytesName];
			countBytesName++;
		}
		buf[countBytesName] = 0;
		fwrite(buf, sizeof(char), countBytesName + 1, dbFileQ);

		// count questions
		fwrite(&countQ, sizeof(int), 1, dbFileQ);

		for (int j = 0; j < 30; j++) // QUESTIONS
		{
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
			fwrite(buf, sizeof(char), strlen(buf) + 1, dbFileQ);


			for (int k = 0; k < 4; k++) // ANSWERS
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

				fwrite(buf, sizeof(char), strlen(buf) + 1, dbFileQ);
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

			fwrite(&rightQ, sizeof(int), 1, dbFileQ);

			if (i != 4 && i != 5 && i != 6)
				fseek(files[i], 4, SEEK_CUR);
		}
	}

	for (int i = 0; i < 8; i++)
	{
		if(files[i] != nullptr)
			fclose(files[i]);
	}
	
	//	DB USERS
	int countUsersArr[] = {
		1, // countAdmins
		3 //countStudents
	};
	int maxSymbols = 50;

	fwrite(countUsersArr, sizeof(int), 2, dbFileUsers);

	// USERS
	sprintf_s(buf, maxSymbols, "%s", "admin");
	fwrite(buf, sizeof(char), strlen(buf) + 1, dbFileUsers);
	memset(buf, 0, maxSymbols);

	sprintf_s(buf, maxSymbols, "%s", "12345");
	fwrite(buf, sizeof(char), strlen(buf) + 1, dbFileUsers);
	memset(buf, 0, maxSymbols);

	// STUDENTS
	for (int i = 0; i < countUsersArr[1]; i++)
	{
		// names
		for (int j = 0; j < 2; j++)
		{
			randStr(buf, 4, 'a', 'z');
			fwrite(buf, sizeof(char), strlen(buf) + 1, dbFileUsers);
			memset(buf, 0, maxSymbols);
		}
		
		// login and password
		sprintf_s(buf, maxSymbols, "%s%d", "Алексеев", i);
		fwrite(buf, sizeof(char), strlen(buf) + 1, dbFileUsers);
		memset(buf, 0, maxSymbols);

		sprintf_s(buf, maxSymbols, "%s%d", "Кирил", i);
		fwrite(buf, sizeof(char), strlen(buf) + 1, dbFileUsers);
		memset(buf, 0, maxSymbols);

		int marks[8] = { 0 };
		int finalMark = 3;
		float averageMark = (rand() % 50 + 10) / 10.f;
		fwrite(marks, sizeof(int), 8, dbFileUsers);
		fwrite(&finalMark, sizeof(int), 1, dbFileUsers);
		fwrite(&averageMark, sizeof(float), 1, dbFileUsers);

	}

	fclose(dbFileQ);
	fclose(dbFileUsers);

	return 1;
}

void printBuffer(const char* buf, int size, const char* type) {
	for (int i = 0; i < size; i++)
	{
		printf_s(type, buf[i]);
	}

	printf_s("\n");
}

void debug(const char* s) {
	printf_s("\n\nERROR: %s\n", s);
}
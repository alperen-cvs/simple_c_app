
#ifdef WIN32
	#define CLEAR_COMMAND "cls"
#endif

#ifdef __linux__
	#define CLEAR_COMMAND "clear"
#endif   
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <locale.h>

const char* quit_char = "q";
const char* main_prompt = "Welcome: ";
const char* student_registration_prompt = "Enter student information: ";
const int REGISTER_AGE = 0XFF;

typedef struct {
	char student_name[30];
	char student_surname[30];

	short int age;

	char student_father_name[30];
	char student_mother_name[30];
} StudentInfo;

void clear_terminal() {
	system(CLEAR_COMMAND);
}
/*

YAPILAN HATALAR  - STRUCT'ların uzunluğuna dikkat et
strtol ile bir endptr belirt ve \0 değil mi diye kontrol et
Kullanıcıya daha iyi okunabilir mesajlar ver 

memset ile sürekli yapma
memset(struct_->name,0,sizeof(struct_->name);
memset(struct_->name,0,sizeof(struct_->name);
memset(struct_->name,0,sizeof(struct_->name);

eğer ki direkt bir struct sıfırlanacaksa

memset(struct_,0,sizeof(struct_)); yap

mutlaka ve mutlaka uzunlukları kontrol et

null terminator ile sonlandırılacaksa

char array[8];
strncpy(array,"Alperen",7); ile bir uzunluk belirt

array[7] = '\0';

mutlaka ve mutlaka bir null terminator ile sonlandır 
eskisi gibi
len = len - 1; python kodlar gibi yapma
--len; yap 

değişkenlerin ne işe yaradığını belirt


*/
bool fill_buffer(const char* instring, char* buffer, size_t len) {
	if (strlen(instring) >= len) {
		printf("[ ERROR ] Buffer fill error because instring long then buffer\n ");
		return false;
	}
	if (len < 2) {
		printf("[ ERROR ] Buffer size error we cant include null terminator to buffer :/\n");
		return false;
	}
	--len; // for null terminator
	strncpy(buffer, instring, len);
	buffer[len] = '\0';
	return true;
}

void clear_stdin_buffer() {
	int ch; // safer then char and more compability
	while ((ch = getchar()) != EOF && ch != '\n');
}

void input(const char* prompt, char* buffer, size_t bufflen) {
	printf("%s", prompt);
	fgets(buffer, bufflen, stdin);
	if (!strchr(buffer, '\n')) {
		clear_stdin_buffer(); // overflow
	}
	else {
		buffer[strcspn(buffer, "\n")] = '\0';
	}
}
bool string_compare(const char* str1, const char* string2) {
	return strcmp(str1, string2) == 0;
}


void add_new_student(StudentInfo* student_struct) {
	clear_terminal();
	printf("Student registration prompt started now you can student information\n1.Student Name\n2.Student Surname\n3.Student Mother Name\n4.Student Father Name\n");
	char buffer[30];
	int opt = 0;
	long result = 0;
	printf("Enter student name !!!\n");
	do {
		input(student_registration_prompt, buffer, sizeof(buffer));
		if (string_compare(buffer, quit_char)) {
			return;
		}
		if (opt == REGISTER_AGE) {
			result = strtol(buffer, NULL, 10);
			if (result < 5 || result > 20) {
				printf("Registration failed\n");
			}
			else {
				printf("Age set as: %s\n", buffer);
				student_struct->age = (int)result;
				return;
			}
		}
		if (strlen(buffer) > 2 && opt != REGISTER_AGE) {
			++opt;
			switch (opt) {
			case 1:
				fill_buffer(buffer, student_struct->student_name, sizeof(student_struct->student_name));
				printf("Name set as: %s\n", student_struct->student_name);
				break;
			case 2:
				fill_buffer(buffer, student_struct->student_surname, sizeof(student_struct->student_surname));
				printf("Surname set as: %s\n", student_struct->student_surname);
				break;
			case 3:
				fill_buffer(buffer, student_struct->student_mother_name, sizeof(student_struct->student_mother_name));
				printf("Mother name set as: %s\n", student_struct->student_mother_name);
				break;
			case 4:
				fill_buffer(buffer, student_struct->student_father_name, sizeof(student_struct->student_father_name));
				printf("Father name set as: %s\n", student_struct->student_father_name);
				opt = REGISTER_AGE;
				break;
			}
		}
	} while (true);
}
void remove_student(StudentInfo* student_info,int* count) {
	*count = *count - 1;
	memset(student_info, 0, sizeof(StudentInfo)); 
	printf("All done student removed !!\n");
}

bool find_student(const StudentInfo* student_info,const char* student_name, const char* student_mother_name, const char* father_name) {
	return (
		string_compare(student_info->student_name, student_name)
		&& string_compare(student_info->student_mother_name, student_mother_name)
		&& string_compare(student_info->student_father_name, father_name));
}
int main() {
	char student_creds[3][30];
	char buffer[3]; // Not: Belleği aşma
	long result = 0;
	int count = 0; // registered student count 
	StudentInfo student_info[60] = { 0 };
	
	printf("Welcome to student registration system !\n");
	printf("1 - For student registration! 1\n");
	printf("2 - List all students !\n");
	printf("3 - Delete exists student \n");
	printf("4 - for exit  4\n\n\n\n");
	do {
		input(main_prompt, buffer, sizeof(buffer));
		if (string_compare(buffer, quit_char)) {
			printf("Quitting !! \n");
			return -1;
		}
		result = strtol(buffer, NULL, 10);
		switch (result) {
		case 1:
			add_new_student(&student_info[count]);
			count++;
			break;
		case 2:
			//printf("Şu kadar kişi var:%d\n", (sizeof(student_info) / sizeof(student_info[0])));
			for (int i = 0; i < count; ++i) {
				if (strlen(student_info[i].student_name) > 2) {
					printf("Student name: %s\n", student_info[i].student_name);
					printf("Student surname: %s\n", student_info[i].student_surname);
					printf("Student's mother name: %s\n", student_info[i].student_mother_name);
					printf("Student's father name: %s\n", student_info[i].student_father_name);
					printf("Student's age: %d\n", student_info[i].age);
				}
			}
			break;
		case 3:
			printf("1.Student name\n2.Student Mother Name\n3.Student Father Name\n");
			int start = 0;
			while (start < 3 && count != 0) {
				input("Enter student info for searching: ", student_creds[start], sizeof(student_creds[start]));
				if (strlen(student_creds[start]) > 2) {
					++start;
				}
			} 
			printf("Searching now\n");
			for (start = 0; start < count ; ++start) {
				if (find_student(&student_info[start], student_creds[0], student_creds[1], student_creds[2])) {
					remove_student(&student_info[start], &count);
				}
			}
			break;
		case 4:
			printf("Quitting have a good day\n");
			return 0;
		}
	} while (count < 60);
	return 1;
}
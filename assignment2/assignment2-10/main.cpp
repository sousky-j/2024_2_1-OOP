#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
using namespace std;

int my_strlen(const char* arr);
void my_strcpy(char* arr1, const char* arr2, int arr2_len);
bool my_strcmp(const char* arr1, const  char* arr2);
double my_atoi(char* arr);
class Student
{
private:
	char* name;
	char* studentID;
	double Score;
public:
	Student()
	{
		this->name = NULL;
		this->studentID = NULL;
		this->Score = 0;
	}
	~Student()
	{
		delete[] this->name;
		delete[] this->studentID;
	}
	void new_stu(char* name, char* studentID, double Score)
	{
		int len = my_strlen(name);
		this->name = new char[len + 1];
		my_strcpy(this->name, name, len);
		len = my_strlen(studentID);
		this->studentID = new char[len + 1];
		my_strcpy(this->studentID, studentID, len);
		this->Score = Score;
	}
	double return_Score() { return this->Score; }
	char* return_name() { return this->name; }
	char* return_studentID() { return this->studentID; }
	void print()
	{
		cout << "Name : " << this->name << "\n";
		cout << "Student ID : " << this->studentID << "\n";
		cout << "Score : " << this->Score << "\n";
		cout << "---------------\n";
	}
	void cpy(Student* a)
	{
		if (this->name != NULL)
			delete[] this->name;
		int len = my_strlen(a->return_name());
		this->name = new char[len + 1];
		my_strcpy(this->name, a->return_name(), len);
		if (this->studentID != NULL)
			delete[] this->studentID;
		len = my_strlen(a->return_studentID());
		this->studentID = new char[len + 1];
		my_strcpy(this->studentID, a->return_studentID(), len);
		this->Score = a->return_Score();
	}
};
class school
{
private:
	class Student* student_list;
	int size = 0;
public:
	school()
	{
		this->student_list = NULL;
	}
	~school()
	{
		delete[] this->student_list;
	}
	void new_stu(char* name, char* studentID, double Score)
	{
		if (this->student_list == NULL)
		{
			this->student_list = new Student[100];
		}
		else if (size % 100 == 0 && size != 0)
		{
			Student tmp[100];
			member_cpy(this->student_list, tmp);
			delete[] this->student_list;
			this->student_list = new Student[size + 100];
			member_cpy(tmp, this->student_list + (size - 100));
			size++;
		}
		this->student_list[this->size].new_stu(name, studentID, Score);
		size++;
	}
	void member_cpy(Student* ori, Student* tmp)
	{
		for (int i = 0; i < 100; i++)
			ori[i].cpy(tmp + i);
	}
	void sort_by_score()
	{
		int k = 0;
		for (int i = 0; i < size - 1; i++)
		{
			k = i;
			for (int j = i + 1; j < size; j++)
			{
				if (this->student_list[k].return_Score() < this->student_list[j].return_Score())
					k = j;
			}
			if (k != i)
				this->swap(&this->student_list[k], &this->student_list[i]);
		}
	}
	void print()
	{
		cout << "=====print=====\n";
		for (int i = 0; i < size; i++)
			this->student_list[i].print();
	}
	void print_A_grade()
	{
		Student* test = new Student[size];
		for (int i = 0; i < size; i++)
			test[i].cpy(&this->student_list[i]);
		for (int i = 0; i < size - 1; i++)
		{
			int k = i;
			for (int j = i + 1; j < size; j++)
			{
				if (test[k].return_Score() < test[j].return_Score())
					k = j;
			}
			if (k != i)
				this->swap(&test[k], &test[i]);
		}
		int A_grade = size * (0.3);
		cout << "=====A grade=====\n";
		for (int i = 0; i < A_grade; i++)
			test[i].print();
	}
	void print_B_grade()
	{
		Student* test = new Student[size];
		for (int i = 0; i < size; i++)
			test[i].cpy(&this->student_list[i]);
		for (int i = 0; i < size - 1; i++)
		{
			int k = i;
			for (int j = i + 1; j < size; j++)
			{
				if (test[k].return_Score() < test[j].return_Score())
					k = j;
			}
			if (k != i)
				this->swap(&test[k], &test[i]);
		}
		int A_grade = (size * (0.3));
		int B_grade = (size / 2);
		cout << "=====B grade=====\n";
		for (int i = A_grade; i < B_grade; i++)
			test[i].print();
	}
	void swap(Student* s1, Student* s2)

	{
		Student* tmp = new Student;
		tmp->cpy(s1);
		s1->cpy(s2);
		s2->cpy(tmp);
	}
};
void delete_space(char* arr);
void Tokenizer(school& a, char* line);
int main(void)
{
	char command[6][20] = { "load_student","sort_by_score","print_all","print_A_grade","print_B_grade", "exit" };
	char input_command[20];
	school a;
	ifstream read_file;
	while (1)
	{
		cin >> input_command;
		if (my_strcmp(input_command, command[0]))//load_student part code
		{
			char inputline[100];
			read_file.open("./student.txt");
			while (!read_file.eof())
			{
				read_file.getline(inputline, 100);
				delete_space(inputline);
				Tokenizer(a, inputline);
			}
			read_file.close();
		}
		else if (my_strcmp(input_command, command[1]))//sort part code
		{
			a.sort_by_score();
		}
		else if (my_strcmp(input_command, command[2]))//print_all part code
		{
			a.print();
		}
		else if (my_strcmp(input_command, command[3]))//print_A_grade part code
		{
			a.print_A_grade();
		}
		else if (my_strcmp(input_command, command[4]))//print_B_grade part code
		{
			a.print_B_grade();
		}
		else if (my_strcmp(input_command, command[5]))//exit aprt code
		{
			break;
		}
		else
			cout << "error command\n";
	}
	cout << "Exit the program";
	return 0;
}

void Tokenizer(school& a, char* line)
{
	int line_len = my_strlen(line);
	char name[101]{};
	char stu_id[101]{};
	double score = 0;
	int tag = 0;
	int flag = 0;

	for (int i = 0; i <= line_len; i++)
	{
		if (line[i] == '\0' || line[i] == ',')
		{
			switch (tag)
			{
			case 0:
				my_strcpy(name, line, i);
				flag = i + 1;
				tag++;
				break;
			case 1:
				my_strcpy(stu_id, line + flag, i - flag);
				flag = i + 1;
				tag++;
				break;
			case 2:
				char ch_score[4];
				my_strcpy(ch_score, (line + flag), i - flag);
				score = my_atoi(ch_score);
				break;
			}
		}
	}
	a.new_stu(name, stu_id, score);
}
void delete_space(char* arr)
{
	int len = my_strlen(arr);
	int ll = len;
	for (int i = 0; i < len; i++)
	{
		int ll = len;
		while (arr[i] != ' ')
		{
			for (int j = i; j < len - 1; j++)
				arr[j] = arr[j + 1];
			ll--;
			arr[ll] = '\0';

		}
	}
}
double my_atoi(char* arr)
{
	double re_value = 0;
	int len = my_strlen(arr);
	int mtp = 1;
	while (len)
	{
		re_value += (arr[len - 1] - '0') * mtp;
		mtp = mtp * 10;
		len--;
	}
	return re_value;
}
int my_strlen(const char* arr)
{

	int len = 0;
	for (int i = 0; i < 1000; i++)
	{
		if (arr[i] == '\0')
			return len;
		len++;
	}
	return len;
}
void my_strcpy(char* arr1, const char* arr2, int arr2_len)
{
	for (int i = 0; i < arr2_len; i++)
		arr1[i] = arr2[i];
	*(arr1 + arr2_len) = '\0';
}
bool my_strcmp(const char* arr1, const  char* arr2)
{
	int arr1_len = my_strlen(arr1);
	int arr2_len = my_strlen(arr2);
	if (arr1_len != arr2_len)
		return false;
	for (int i = 0; i < arr1_len; i++)
	{
		char input_token = arr1[i];
		char saved_token = arr2[i];
		if (input_token != saved_token)
			return false;
	}
	return true;
}
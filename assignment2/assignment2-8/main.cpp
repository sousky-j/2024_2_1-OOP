#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

bool my_strcmp(const char* input, const  char* command);
int my_strlen(const char* arr);
void my_strcpy(char* arr1, const char* arr2, int arr2_len);

class Student
{
private:
	char* name;//이름
	char* studentID;//학번
	double assignmentScore=0;//과제 점수
	double examScore=0;//시험점수
	double attendance=0;//출석점수
	double finalScore=0;//최종점수

public:
	Student(char* name, char* id, double aScore, double eScore, double att)
	{
		int len = my_strlen(name);
		this->name = new char[len + 1];
		my_strcpy(this->name, name, len);
		len = my_strlen(id);
		this->studentID = new char[len + 1];
		my_strcpy(this->studentID, id, len);
		this->assignmentScore = aScore;
		this->examScore = eScore;
		this->attendance = att;
		this->finalScore = 0;
		this->finalScore += this->attendance / 10;
		this->finalScore += this->assignmentScore * (0.4);
		this->finalScore += this->examScore / 2;
	}
	~Student()
	{
		delete[] this->name;
		delete[] this->studentID;
	}
	bool Isnamecorrect(char* name)
	{
		if (my_strcmp(this->name, name))
			return true;
		else false;
	}
	void changeScores(double aScore, double eScore, double att)
	{

	}
	void print()
	{

	}
};

class school
{
private:
	class Student* stu_list[10]{};
	int size = 0;

public:
	~school()
	{
		for (int i = 0; i < size; i++)
			delete stu_list[i];
	}
	void new_stu(char* name, char* id, double aScore, double eScore, double att)
	{
		this->stu_list[this->size] = new class Student(name, id, aScore, eScore, att);
		size++;
	}
	void print_all()
	{
		cout << "=====print_all=====\n";
		for (int i = 0; i < size; i++)
			stu_list[i]->print();
	}
};

int main(void)
{
	return 0;
}

bool my_strcmp(const char* input_name, const  char* saved_name)
{
	int input_name_len = my_strlen(input_name);
	int saved_name_len = my_strlen(saved_name);
	if (saved_name_len != input_name_len)
		return false;
	char input_token = input_name[0];
	char saved_token = saved_name[0];
	for (int i = 0; saved_name[i] != '\0'; i++)
	{
		input_token = input_name[i];
		saved_token = saved_name[i];
		if (input_token >= 65 && input_token <= 90)
			input_token += 32;
		if (saved_token >= 65 && saved_token <= 90)
			saved_token += 32;
		if (input_name[i] > saved_name[i])
			return false;
		else if (input_name[i] < saved_name[i])
			return false;
	}
	return true;
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
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

class Student
{
private:
	char* name;
	char* studentID;
	double assignmentScore;
	double examScore;
	double attendance;
	double finalScore;

public:
	Student(char* name, char* id, double aScore, double eScore, double att);
	~Student();
};
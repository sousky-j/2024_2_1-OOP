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
    double assignmentScore = 0;//과제 점수
    double examScore = 0;//시험점수
    double attendance = 0;//출석점수
    double finalScore = 0;//최종점수

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
        return my_strcmp(this->name, name);
    }
    void changeScores(double aScore, double eScore, double att)
    {
        this->assignmentScore = aScore;
        this->examScore = eScore;
        this->attendance = att;
        this->finalScore = this->attendance / 10;
        this->finalScore += this->assignmentScore * (0.4);
        this->finalScore += this->examScore / 2;
    }
    void print()
    {
        cout << "Name : " << this->name << "\n";
        cout << "Student ID : " << this->studentID << "\n";
        cout << "Final Score : " << this->finalScore << "\n";
        cout << "----------------\n";
    }
};

class school
{
private:
    class Student* stu_list[10]{};
    int size;

public:
    school()
    {
        size = 0;
    }
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
        cout << "=====print=====\n";
        for (int i = 0; i < size; i++)
            stu_list[i]->print();
    }
    void print_find(char* name)
    {
        int flag = 0;
        cout << "=====find=====\n";
        for (int i = 0; i < size; i++)
        {
            if (stu_list[i]->Isnamecorrect(name))
            {
                stu_list[i]->print();
                flag = 1;
            }
        }
        if (flag == 0)
        {
            cout << "Not found\n";
            cout << "---------------\n";
        }
    }
    void change(char* name, double aScore, double eScore, double att)
    {
        for (int i = 0; i < size; i++)
        {
            if (stu_list[i]->Isnamecorrect(name))
            {
                stu_list[i]->changeScores(aScore, eScore, att);
                break;
            }
        }
    }
};

int main(void)
{
    school a;
    char command[5][10] = { "insert","find","change","print","exit" };
    char input_command[20];
    char input_name[101];
    char input_id[101];
    double input_aScore, input_eScore, input_att;

    while (1)
    {
        cin >> input_command;
        if (my_strcmp(input_command, command[0]))//insert part code
        {
            cin >> input_name >> input_id >> input_aScore >> input_eScore >> input_att;
            a.new_stu(input_name, input_id, input_aScore, input_eScore, input_att);
        }
        else if (my_strcmp(input_command, command[1]))//find part code
        {
            cin >> input_name;
            a.print_find(input_name);
        }
        else if (my_strcmp(input_command, command[2]))//change part code
        {
            cin >> input_name >> input_aScore >> input_eScore >> input_att;
            a.change(input_name, input_aScore, input_eScore,input_att);
        }
        else if (my_strcmp(input_command, command[3]))//print part code
        {
            a.print_all();
        }
        else if (my_strcmp(input_command, command[4]))//exit part code
        {
            break;
        }
        else
        {
            cout << "Wrong command\n";
        }
    }
    cout << "Exit the program\n";;
    return 0;
}


bool my_strcmp(const char* input_name, const  char* saved_name)
{
    int input_name_len = my_strlen(input_name);
    int saved_name_len = my_strlen(saved_name);
    if (saved_name_len != input_name_len)
        return false;
    for (int i = 0; i < saved_name_len; i++)
    {
        char input_token = input_name[i];
        char saved_token = saved_name[i];
        if (input_token >= 65 && input_token <= 90)
            input_token += 32;
        if (saved_token >= 65 && saved_token <= 90)
            saved_token += 32;
        if (input_token != saved_token)
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
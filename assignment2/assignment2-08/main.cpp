#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

bool my_strcmp(const char* input, const char* command); // 문자열 비교 함수
int my_strlen(const char* arr); // 문자열 길이 계산 함수
void my_strcpy(char* arr1, const char* arr2, int arr2_len); // 문자열 복사 함수

class Student//Student 클래스 정의
{
private:
    char* name; // 학생 이름
    char* studentID; // 학생 학번
    double assignmentScore = 0; // 과제 점수
    double examScore = 0; // 시험 점수
    double attendance = 0; // 출석 점수
    double finalScore = 0; // 최종 점수

public:
    // 생성자: 학생 객체 초기화
    Student(char* name, char* id, double aScore, double eScore, double att)
    {
        // 이름과 학번 복사
        int len = my_strlen(name);
        this->name = new char[len + 1];
        my_strcpy(this->name, name, len);
        len = my_strlen(id);
        this->studentID = new char[len + 1];
        my_strcpy(this->studentID, id, len);

        // 점수 초기화 및 최종 점수 계산
        this->assignmentScore = aScore;
        this->examScore = eScore;
        this->attendance = att;
        this->finalScore = 0;
        this->finalScore += this->attendance / 10;
        this->finalScore += this->assignmentScore * (0.4);
        this->finalScore += this->examScore / 2;
    }

    // 소멸자: 동적 할당된 메모리 해제
    ~Student()
    {
        delete[] this->name;
        delete[] this->studentID;
    }

    // 이름이 맞는지 확인하는 함수
    bool Isnamecorrect(char* name)
    {
        return my_strcmp(this->name, name);
    }

    // 점수 변경 함수
    void changeScores(double aScore, double eScore, double att)
    {
        this->assignmentScore = aScore;
        this->examScore = eScore;
        this->attendance = att;
        this->finalScore = this->attendance / 10;
        this->finalScore += this->assignmentScore * (0.4);
        this->finalScore += this->examScore / 2;
    }

    // 정보 출력 함수
    void print()
    {
        cout << "Name : " << this->name << "\n";
        cout << "Student ID : " << this->studentID << "\n";
        cout << "Final Score : " << this->finalScore << "\n";
        cout << "----------------\n";
    }
};

// 학교(School) 클래스 정의
class school
{
private:
    class Student* stu_list[10]{}; // 학생 객체 배열
    int size; // 학생 수

public:
    // 생성자: 학생 수 초기화
    school()
    {
        size = 0;
    }

    // 소멸자: 동적 할당된 메모리 해제
    ~school()
    {
        for (int i = 0; i < size; i++)
            delete stu_list[i];
    }

    // 새로운 학생 추가 함수
    void new_stu(char* name, char* id, double aScore, double eScore, double att)
    {
        this->stu_list[this->size] = new class Student(name, id, aScore, eScore, att);
        size++;
    }

    // 모든 학생 정보 출력 함수
    void print_all()
    {
        cout << "=====print=====\n";
        for (int i = 0; i < size; i++)
            stu_list[i]->print();
    }

    // 이름으로 학생 정보 찾아 출력하는 함수
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
            cout << "not found.\n";
            cout << "---------------\n";
        }
    }

    // 학생 정보 수정 함수
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

// 메인 함수
int main(void)
{
    school a; // 학교 객체 생성
    // 명령어 배열 정의
    char command[5][10] = { "insert","find","change","print","exit" };
    // 입력 변수 정의
    char input_command[20];
    char input_name[101];
    char input_id[101];
    double input_aScore, input_eScore, input_att;

    // 명령어 입력 반복
    while (1)
    {
        cin >> input_command;
        // 입력한 명령어가 "insert"인 경우
        if (my_strcmp(input_command, command[0]))
        {
            cin >> input_name >> input_id >> input_aScore >> input_eScore >> input_att;
            a.new_stu(input_name, input_id, input_aScore, input_eScore, input_att);
        }
        // 입력한 명령어가 "find"인 경우
        else if (my_strcmp(input_command, command[1]))
        {
            cin >> input_name;
            a.print_find(input_name);
        }
        // 입력한 명령어가 "change"인 경우
        else if (my_strcmp(input_command, command[2]))
        {
            cin >> input_name >> input_aScore >> input_eScore >> input_att;
            a.change(input_name, input_aScore, input_eScore, input_att);
        }
        // 입력한 명령어가 "print"인 경우
        else if (my_strcmp(input_command, command[3]))
        {
            a.print_all();
        }
        // 입력한 명령어가 "exit"인 경우
        else if (my_strcmp(input_command, command[4]))
        {
            break;
        }
        // 그 외의 경우
        else
        {
            cout << "error command\n";
        }
    }
    cout << "Exit the program\n";
    return 0;
}

// 문자열 비교 함수
bool my_strcmp(const char* input_name, const char* saved_name)
{
    int input_name_len = my_strlen(input_name);
    int saved_name_len = my_strlen(saved_name);
    if (saved_name_len != input_name_len)
        return false;
    for (int i = 0; i < saved_name_len; i++)
    {
        char input_token = input_name[i];//배열에서 한글자 가져옴
        char saved_token = saved_name[i];//배열에서 한글자 가져옴
        if (input_token >= 65 && input_token <= 90)//소문자로 변환
            input_token += 32;
        if (saved_token >= 65 && saved_token <= 90)//소문자로 변환
            saved_token += 32;
        if (input_token != saved_token)
            return false;
    }
    return true;
}

// 문자열 길이 계산 함수
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

// 문자열 복사 함수
void my_strcpy(char* arr1, const char* arr2, int arr2_len)
{
    for (int i = 0; i < arr2_len; i++)
        arr1[i] = arr2[i];
    *(arr1 + arr2_len) = '\0';
}

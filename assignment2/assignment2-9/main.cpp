#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

// 문자열 길이를 반환하는 함수 선언
int my_strlen(const char* arr);
// 문자열을 복사하는 함수 선언
void my_strcpy(char* arr1, const char* arr2, int arr2_len);
// 문자열을 비교하는 함수 선언
bool my_strcmp(const char* arr1, const char* arr2);

// 학생 클래스 정의
class Student
{
private:
    char* name;     // 이름
    char* studentID; // 학번
    double Score;   // 점수

public:
    // 생성자
    Student()
    {
        this->name = NULL;
        this->studentID = NULL;
        this->Score = 0;
    }
    // 소멸자
    ~Student()
    {
        delete[] this->name;
        delete[] this->studentID;
    }
    // 새로운 학생 정보를 입력받아 저장하는 함수
    void new_stu(char* name, char* studentID, double Score)
    {
        // 이름 복사
        int len = my_strlen(name);
        this->name = new char[len + 1];
        my_strcpy(this->name, name, len);
        // 학번 복사
        len = my_strlen(studentID);
        this->studentID = new char[len + 1];
        my_strcpy(this->studentID, studentID, len);
        // 점수 저장
        this->Score = Score;
    }
    // 점수 반환 함수
    double return_Score() { return this->Score; }
    // 이름 반환 함수
    char* return_name() { return this->name; }
    // 학번 반환 함수
    char* return_studentID() { return this->studentID; }
    // 학생 정보 출력 함수
    void print()
    {
        cout << "Name : " << this->name << "\n";
        cout << "Student ID : " << this->studentID << "\n";
        cout << "Score : " << this->Score << "\n";
        cout << "---------------\n";
    }
    // 다른 학생 객체의 정보를 복사하는 함수
    void cpy(Student* a)
    {
        // 기존 동적 할당된 메모리 해제
        if (this->name != NULL)
            delete[] this->name;
        // 이름 복사
        int len = my_strlen(a->return_name());
        this->name = new char[len + 1];
        my_strcpy(this->name, a->return_name(), len);
        // 기존 동적 할당된 메모리 해제
        if (this->studentID != NULL)
            delete[] this->studentID;
        // 학번 복사
        len = my_strlen(a->return_studentID());
        this->studentID = new char[len + 1];
        my_strcpy(this->studentID, a->return_studentID(), len);
        // 점수 복사
        this->Score = a->return_Score();
    }
};

// 학교 클래스 정의
class school
{
private:
    Student* student_list; // 학생 목록
    int size = 0;          // 학생 수

public:
    // 생성자
    school()
    {
        this->student_list = NULL;
    }
    // 소멸자
    ~school()
    {
        delete[] this->student_list;
    }
    // 새로운 학생 정보를 입력받아 목록에 추가하는 함수
    void new_stu(char* name, char* studentID, double Score)
    {
        // 초기 할당 또는 추가할 공간이 필요한 경우
        if (this->student_list == NULL)
        {
            this->student_list = new Student[100]; // 초기 공간 할당
        }
        else if (size % 100 == 0 && size != 0)
        {
            Student tmp[100]; // 임시 배열 생성
            member_cpy(this->student_list, tmp); // 현재 목록을 임시 배열로 복사
            delete[] this->student_list; // 이전 메모리 해제
            this->student_list = new Student[size + 100]; // 새로운 메모리 할당
            member_cpy(tmp, this->student_list + (size - 100)); // 임시 배열에서 현재 위치로 복사
            size++; // 학생 수 증가
        }
        // 새로운 학생 정보를 추가
        this->student_list[this->size].new_stu(name, studentID, Score);
        size++;
    }
    // 학생 정보를 복사하는 함수
    void member_cpy(Student* ori, Student* tmp)
    {
        for (int i = 0; i < 100; i++)
            ori[i].cpy(tmp + i);
    }
    // 점수를 기준으로 학생 정보를 정렬하는 함수
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
            // 정렬
            if (k != i)
                this->swap(&this->student_list[k], &this->student_list[i]);
        }
    }
    // 전체 학생 정보를 출력하는 함수
    void print()
    {
        cout << "=====print=====\n";
        for (int i = 0; i < size; i++)
            this->student_list[i].print();
    }
    // A 학점을 받은 학생 정보를 출력하는 함수
    void print_A_grade()
    {
        Student* test = new Student[size];
        for (int i = 0; i < size; i++)
            test[i].cpy(&this->student_list[i]);
        // 점수를 기준으로 정렬
        for (int i = 0; i < size - 1; i++)
        {
            int k = i;
            for (int j = i + 1; j < size; j++)
            {
                if (test[k].return_Score() < test[j].return_Score())
                    k = j;
            }
            // 정렬
            if (k != i)
                this->swap(&test[k], &test[i]);
        }
        // 상위 30%의 학생 정보 출력
        int A_grade = size * (0.3);
        cout << "=====A grade=====\n";
        for (int i = 0; i < A_grade; i++)
            test[i].print();
    }
    // B 학점을 받은 학생 정보를 출력하는 함수
    void print_B_grade()
    {
        Student* test = new Student[size];
        for (int i = 0; i < size; i++)
            test[i].cpy(&this->student_list[i]);
        // 점수를 기준으로 정렬
        for (int i = 0; i < size - 1; i++)
        {
            int k = i;
            for (int j = i + 1; j < size; j++)
            {
                if (test[k].return_Score() < test[j].return_Score())
                    k = j;
            }
            // 정렬
            if (k != i)
                this->swap(&test[k], &test[i]);
        }
        // 상위 30%에서 중간까지의 학생 정보 출력
        int A_grade = (size * (0.3));
        int B_grade = (size / 2);
        cout << "=====B grade=====\n";
        for (int i = A_grade; i < B_grade; i++)
            test[i].print();
    }
    // 학생 정보를 교환하는 함수
    void swap(Student* s1, Student* s2)
    {
        Student* tmp = new Student;
        tmp->cpy(s1);
        s1->cpy(s2);
        s2->cpy(tmp);
    }
};

// 메인 함수
int main(void)
{
    // 명령어 배열 선언
    char command[6][20] = { "new_student","sort_by_score","print_all","print_A_grade","print_B_grade", "exit" };
    char input_command[20]; // 입력 명령어
    char input_name[101]; // 입력 이름
    char input_id[101]; // 입력 학번
    double input_score; // 입력 점수
    school a; // 학교 객체 생성

    // 사용자 입력 반복
    while (1)
    {
        cin >> input_command;
        // 새로운 학생 정보 입력
        if (my_strcmp(input_command, command[0]))
        {
            cin >> input_name >> input_id >> input_score;
            a.new_stu(input_name, input_id, input_score);
        }
        // 점수로 학생 정보 정렬
        else if (my_strcmp(input_command, command[1]))
        {
            a.sort_by_score();
        }
        // 전체 학생 정보 출력
        else if (my_strcmp(input_command, command[2]))
        {
            a.print();
        }
        // A 학점 학생 정보 출력
        else if (my_strcmp(input_command, command[3]))
        {
            a.print_A_grade();
        }
        // B 학점 학생 정보 출력
        else if (my_strcmp(input_command, command[4]))
        {
            a.print_B_grade();
        }
        // 프로그램 종료
        else if (my_strcmp(input_command, command[5]))
        {
            break;
        }
        else
            cout << "error command\n"; // 잘못된 명령어 처리
    }
    cout << "Exit the program"; // 프로그램 종료 메시지 출력
    return 0;
}

// 문자열 길이를 반환하는 함수 정의
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

// 문자열을 복사하는 함수 정의
void my_strcpy(char* arr1, const char* arr2, int arr2_len)
{
    for (int i = 0; i < arr2_len; i++)
        arr1[i] = arr2[i];
    *(arr1 + arr2_len) = '\0';
}

// 문자열을 비교하는 함수 정의
bool my_strcmp(const char* arr1, const char* arr2)
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

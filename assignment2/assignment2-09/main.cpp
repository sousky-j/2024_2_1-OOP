#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

// ���ڿ� ���̸� ��ȯ�ϴ� �Լ� ����
int my_strlen(const char* arr);
// ���ڿ��� �����ϴ� �Լ� ����
void my_strcpy(char* arr1, const char* arr2, int arr2_len);
// ���ڿ��� ���ϴ� �Լ� ����
bool my_strcmp(const char* arr1, const char* arr2);

// �л� Ŭ���� ����
class Student
{
private:
    char* name;     // �̸�
    char* studentID; // �й�
    double Score;   // ����

public:
    // ������
    Student()
    {
        this->name = NULL;
        this->studentID = NULL;
        this->Score = 0;
    }
    // �Ҹ���
    ~Student()
    {
        delete[] this->name;
        delete[] this->studentID;
    }
    // ���ο� �л� ������ �Է¹޾� �����ϴ� �Լ�
    void new_stu(char* name, char* studentID, double Score)
    {
        // �̸� ����
        int len = my_strlen(name);
        this->name = new char[len + 1];
        my_strcpy(this->name, name, len);
        // �й� ����
        len = my_strlen(studentID);
        this->studentID = new char[len + 1];
        my_strcpy(this->studentID, studentID, len);
        // ���� ����
        this->Score = Score;
    }
    // ���� ��ȯ �Լ�
    double return_Score() { return this->Score; }
    // �̸� ��ȯ �Լ�
    char* return_name() { return this->name; }
    // �й� ��ȯ �Լ�
    char* return_studentID() { return this->studentID; }
    // �л� ���� ��� �Լ�
    void print()
    {
        cout << "Name : " << this->name << "\n";
        cout << "Student ID : " << this->studentID << "\n";
        cout << "Score : " << this->Score << "\n";
        cout << "---------------\n";
    }
    // �ٸ� �л� ��ü�� ������ �����ϴ� �Լ�
    void cpy(Student* a)
    {
        // ���� ���� �Ҵ�� �޸� ����
        if (this->name != NULL)
            delete[] this->name;
        // �̸� ����
        int len = my_strlen(a->return_name());
        this->name = new char[len + 1];
        my_strcpy(this->name, a->return_name(), len);
        // ���� ���� �Ҵ�� �޸� ����
        if (this->studentID != NULL)
            delete[] this->studentID;
        // �й� ����
        len = my_strlen(a->return_studentID());
        this->studentID = new char[len + 1];
        my_strcpy(this->studentID, a->return_studentID(), len);
        // ���� ����
        this->Score = a->return_Score();
    }
};

// �б� Ŭ���� ����
class school
{
private:
    Student* student_list; // �л� ���
    int size = 0;          // �л� ��

public:
    // ������
    school()
    {
        this->student_list = NULL;
    }
    // �Ҹ���
    ~school()
    {
        delete[] this->student_list;
    }
    // ���ο� �л� ������ �Է¹޾� ��Ͽ� �߰��ϴ� �Լ�
    void new_stu(char* name, char* studentID, double Score)
    {
        // �ʱ� �Ҵ� �Ǵ� �߰��� ������ �ʿ��� ���
        if (this->student_list == NULL)
        {
            this->student_list = new Student[100]; // �ʱ� ���� �Ҵ�
        }
        else if (size % 100 == 0 && size != 0)
        {
            Student tmp[100]; // �ӽ� �迭 ����
            member_cpy(this->student_list, tmp); // ���� ����� �ӽ� �迭�� ����
            delete[] this->student_list; // ���� �޸� ����
            this->student_list = new Student[size + 100]; // ���ο� �޸� �Ҵ�
            member_cpy(tmp, this->student_list + (size - 100)); // �ӽ� �迭���� ���� ��ġ�� ����
            size++; // �л� �� ����
        }
        // ���ο� �л� ������ �߰�
        this->student_list[this->size].new_stu(name, studentID, Score);
        size++;
    }
    // �л� ������ �����ϴ� �Լ�
    void member_cpy(Student* ori, Student* tmp)
    {
        for (int i = 0; i < 100; i++)
            ori[i].cpy(tmp + i);
    }
    // ������ �������� �л� ������ �����ϴ� �Լ�
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
            // ����
            if (k != i)
                this->swap(&this->student_list[k], &this->student_list[i]);
        }
    }
    // ��ü �л� ������ ����ϴ� �Լ�
    void print()
    {
        cout << "=====print=====\n";
        for (int i = 0; i < size; i++)
            this->student_list[i].print();
    }
    // A ������ ���� �л� ������ ����ϴ� �Լ�
    void print_A_grade()
    {
        Student* test = new Student[size];
        for (int i = 0; i < size; i++)
            test[i].cpy(&this->student_list[i]);
        // ������ �������� ����
        for (int i = 0; i < size - 1; i++)
        {
            int k = i;
            for (int j = i + 1; j < size; j++)
            {
                if (test[k].return_Score() < test[j].return_Score())
                    k = j;
            }
            // ����
            if (k != i)
                this->swap(&test[k], &test[i]);
        }
        // ���� 30%�� �л� ���� ���
        int A_grade = size * (0.3);
        cout << "=====A grade=====\n";
        for (int i = 0; i < A_grade; i++)
            test[i].print();
    }
    // B ������ ���� �л� ������ ����ϴ� �Լ�
    void print_B_grade()
    {
        Student* test = new Student[size];
        for (int i = 0; i < size; i++)
            test[i].cpy(&this->student_list[i]);
        // ������ �������� ����
        for (int i = 0; i < size - 1; i++)
        {
            int k = i;
            for (int j = i + 1; j < size; j++)
            {
                if (test[k].return_Score() < test[j].return_Score())
                    k = j;
            }
            // ����
            if (k != i)
                this->swap(&test[k], &test[i]);
        }
        // ���� 30%���� �߰������� �л� ���� ���
        int A_grade = (size * (0.3));
        int B_grade = (size / 2);
        cout << "=====B grade=====\n";
        for (int i = A_grade; i < B_grade; i++)
            test[i].print();
    }
    // �л� ������ ��ȯ�ϴ� �Լ�
    void swap(Student* s1, Student* s2)
    {
        Student* tmp = new Student;
        tmp->cpy(s1);
        s1->cpy(s2);
        s2->cpy(tmp);
    }
};

// ���� �Լ�
int main(void)
{
    // ��ɾ� �迭 ����
    char command[6][20] = { "new_student","sort_by_score","print_all","print_A_grade","print_B_grade", "exit" };
    char input_command[20]; // �Է� ��ɾ�
    char input_name[101]; // �Է� �̸�
    char input_id[101]; // �Է� �й�
    double input_score; // �Է� ����
    school a; // �б� ��ü ����

    // ����� �Է� �ݺ�
    while (1)
    {
        cin >> input_command;
        // ���ο� �л� ���� �Է�
        if (my_strcmp(input_command, command[0]))
        {
            cin >> input_name >> input_id >> input_score;
            a.new_stu(input_name, input_id, input_score);
        }
        // ������ �л� ���� ����
        else if (my_strcmp(input_command, command[1]))
        {
            a.sort_by_score();
        }
        // ��ü �л� ���� ���
        else if (my_strcmp(input_command, command[2]))
        {
            a.print();
        }
        // A ���� �л� ���� ���
        else if (my_strcmp(input_command, command[3]))
        {
            a.print_A_grade();
        }
        // B ���� �л� ���� ���
        else if (my_strcmp(input_command, command[4]))
        {
            a.print_B_grade();
        }
        // ���α׷� ����
        else if (my_strcmp(input_command, command[5]))
        {
            break;
        }
        else
            cout << "error command\n"; // �߸��� ��ɾ� ó��
    }
    cout << "Exit the program"; // ���α׷� ���� �޽��� ���
    return 0;
}

// ���ڿ� ���̸� ��ȯ�ϴ� �Լ� ����
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

// ���ڿ��� �����ϴ� �Լ� ����
void my_strcpy(char* arr1, const char* arr2, int arr2_len)
{
    for (int i = 0; i < arr2_len; i++)
        arr1[i] = arr2[i];
    *(arr1 + arr2_len) = '\0';
}

// ���ڿ��� ���ϴ� �Լ� ����
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

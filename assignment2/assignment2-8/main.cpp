#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

bool my_strcmp(const char* input, const char* command); // ���ڿ� �� �Լ�
int my_strlen(const char* arr); // ���ڿ� ���� ��� �Լ�
void my_strcpy(char* arr1, const char* arr2, int arr2_len); // ���ڿ� ���� �Լ�

class Student//Student Ŭ���� ����
{
private:
    char* name; // �л� �̸�
    char* studentID; // �л� �й�
    double assignmentScore = 0; // ���� ����
    double examScore = 0; // ���� ����
    double attendance = 0; // �⼮ ����
    double finalScore = 0; // ���� ����

public:
    // ������: �л� ��ü �ʱ�ȭ
    Student(char* name, char* id, double aScore, double eScore, double att)
    {
        // �̸��� �й� ����
        int len = my_strlen(name);
        this->name = new char[len + 1];
        my_strcpy(this->name, name, len);
        len = my_strlen(id);
        this->studentID = new char[len + 1];
        my_strcpy(this->studentID, id, len);

        // ���� �ʱ�ȭ �� ���� ���� ���
        this->assignmentScore = aScore;
        this->examScore = eScore;
        this->attendance = att;
        this->finalScore = 0;
        this->finalScore += this->attendance / 10;
        this->finalScore += this->assignmentScore * (0.4);
        this->finalScore += this->examScore / 2;
    }

    // �Ҹ���: ���� �Ҵ�� �޸� ����
    ~Student()
    {
        delete[] this->name;
        delete[] this->studentID;
    }

    // �̸��� �´��� Ȯ���ϴ� �Լ�
    bool Isnamecorrect(char* name)
    {
        return my_strcmp(this->name, name);
    }

    // ���� ���� �Լ�
    void changeScores(double aScore, double eScore, double att)
    {
        this->assignmentScore = aScore;
        this->examScore = eScore;
        this->attendance = att;
        this->finalScore = this->attendance / 10;
        this->finalScore += this->assignmentScore * (0.4);
        this->finalScore += this->examScore / 2;
    }

    // ���� ��� �Լ�
    void print()
    {
        cout << "Name : " << this->name << "\n";
        cout << "Student ID : " << this->studentID << "\n";
        cout << "Final Score : " << this->finalScore << "\n";
        cout << "----------------\n";
    }
};

// �б�(School) Ŭ���� ����
class school
{
private:
    class Student* stu_list[10]{}; // �л� ��ü �迭
    int size; // �л� ��

public:
    // ������: �л� �� �ʱ�ȭ
    school()
    {
        size = 0;
    }

    // �Ҹ���: ���� �Ҵ�� �޸� ����
    ~school()
    {
        for (int i = 0; i < size; i++)
            delete stu_list[i];
    }

    // ���ο� �л� �߰� �Լ�
    void new_stu(char* name, char* id, double aScore, double eScore, double att)
    {
        this->stu_list[this->size] = new class Student(name, id, aScore, eScore, att);
        size++;
    }

    // ��� �л� ���� ��� �Լ�
    void print_all()
    {
        cout << "=====print=====\n";
        for (int i = 0; i < size; i++)
            stu_list[i]->print();
    }

    // �̸����� �л� ���� ã�� ����ϴ� �Լ�
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

    // �л� ���� ���� �Լ�
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

// ���� �Լ�
int main(void)
{
    school a; // �б� ��ü ����
    // ��ɾ� �迭 ����
    char command[5][10] = { "insert","find","change","print","exit" };
    // �Է� ���� ����
    char input_command[20];
    char input_name[101];
    char input_id[101];
    double input_aScore, input_eScore, input_att;

    // ��ɾ� �Է� �ݺ�
    while (1)
    {
        cin >> input_command;
        // �Է��� ��ɾ "insert"�� ���
        if (my_strcmp(input_command, command[0]))
        {
            cin >> input_name >> input_id >> input_aScore >> input_eScore >> input_att;
            a.new_stu(input_name, input_id, input_aScore, input_eScore, input_att);
        }
        // �Է��� ��ɾ "find"�� ���
        else if (my_strcmp(input_command, command[1]))
        {
            cin >> input_name;
            a.print_find(input_name);
        }
        // �Է��� ��ɾ "change"�� ���
        else if (my_strcmp(input_command, command[2]))
        {
            cin >> input_name >> input_aScore >> input_eScore >> input_att;
            a.change(input_name, input_aScore, input_eScore, input_att);
        }
        // �Է��� ��ɾ "print"�� ���
        else if (my_strcmp(input_command, command[3]))
        {
            a.print_all();
        }
        // �Է��� ��ɾ "exit"�� ���
        else if (my_strcmp(input_command, command[4]))
        {
            break;
        }
        // �� ���� ���
        else
        {
            cout << "error command\n";
        }
    }
    cout << "Exit the program\n";
    return 0;
}

// ���ڿ� �� �Լ�
bool my_strcmp(const char* input_name, const char* saved_name)
{
    int input_name_len = my_strlen(input_name);
    int saved_name_len = my_strlen(saved_name);
    if (saved_name_len != input_name_len)
        return false;
    for (int i = 0; i < saved_name_len; i++)
    {
        char input_token = input_name[i];//�迭���� �ѱ��� ������
        char saved_token = saved_name[i];//�迭���� �ѱ��� ������
        if (input_token >= 65 && input_token <= 90)//�ҹ��ڷ� ��ȯ
            input_token += 32;
        if (saved_token >= 65 && saved_token <= 90)//�ҹ��ڷ� ��ȯ
            saved_token += 32;
        if (input_token != saved_token)
            return false;
    }
    return true;
}

// ���ڿ� ���� ��� �Լ�
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

// ���ڿ� ���� �Լ�
void my_strcpy(char* arr1, const char* arr2, int arr2_len)
{
    for (int i = 0; i < arr2_len; i++)
        arr1[i] = arr2[i];
    *(arr1 + arr2_len) = '\0';
}

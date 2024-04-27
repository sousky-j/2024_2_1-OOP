// �ʿ��� ��� ������ �����մϴ�.
#define _CRT_SECURE_NO_WARNINGS // Visual Studio���� ��� ����� ��Ƽ��
#include <iostream> // ǥ�� ����� ��Ʈ�� ���̺귯��

using namespace std; // ǥ�� ���ӽ����̽��� ����մϴ�.

// ���� ���� ����
char input_string[101]; // �Է� ���ڿ��� ������ �迭
char delimiter[11]; // �����ڸ� ������ �迭
bool check[100]; // �������� ��ġ�� üũ�� �迭

// �Լ� ������Ÿ�� ����
int my_strlen(char* arr); // ���ڿ��� ���̸� ��ȯ�ϴ� �Լ�
bool Iscorrect(int i, int delimiter_len); // i ��ġ���� delimiter_len ���̸�ŭ�� ���ڿ��� �����ڿ� ��ġ�ϴ��� Ȯ���ϴ� �Լ�

// main �Լ�
int main(void)
{
    // ����ڷκ��� ���ڿ��� �����ڸ� �Է� �޽��ϴ�.
    cout << "Enter the string : ";
    cin.getline(input_string, 100); // ���ڿ� �Է�
    cout << "Enter the delimiter : ";
    cin.getline(delimiter, 10); // ������ �Է�
    cout << "\n";

    // ���ڿ��� ���̿� �������� ���̸� ����մϴ�.
    int string_len = my_strlen(input_string);
    int delimiter_len = my_strlen(delimiter);
    int search_len = string_len - delimiter_len;

    // �����ڰ� �߰ߵǴ� ��ġ�� üũ�մϴ�.
    for (int i = 0; i < search_len; i++)
    {
        if (Iscorrect(i, delimiter_len))
        {
            for (int k = 0; k < delimiter_len; k++)
                check[i + k] = true; // �������� ��ġ�� üũ�մϴ�.
        }
    }

    bool sequence_flag = true;

    // �����ڸ� �������� ���ڿ��� �и��Ͽ� ����մϴ�.
    cout << "Separated tokens :\n";
    for (int i = 0; i < string_len; i++)
    {
        if (!check[i]) // �����ڰ� �ƴ� ���
        {
            if (!sequence_flag) // ������ �����ڰ� �־��ٸ�
            {
                cout << "\n" << input_string[i]; // ���ο� �ٿ� ���ڿ� ���
                sequence_flag = true; // ���ӵ� ���ڿ� �÷��׸� true�� ����
            }
            else
                cout << input_string[i]; // �����ڰ� ���ӵ��� ���� ��� ���ڿ� ���
        }
        else
            sequence_flag = false; // �������� ��� ���ӵ� ���ڿ� �÷��׸� false�� ����
    }
    return 0;
}

// ���ڿ��� ���̸� ��ȯ�ϴ� �Լ�
int my_strlen(char* arr)
{
    int len = 0;
    for (int i = 0; i < 100; i++)
    {
        if (arr[i] == '\0') // �� ���ڸ� ������ �ݺ� ����
            return len;
        len++; // ���̸� ����
    }
    return len; // ���� ��ȯ
}

// i ��ġ���� delimiter_len ���̸�ŭ�� ���ڿ��� �����ڿ� ��ġ�ϴ��� Ȯ���ϴ� �Լ�
bool Iscorrect(int i, int delimiter_len)
{
    for (int k = 0; k < delimiter_len; k++)
    {
        if (input_string[i + k] != delimiter[k]) // �����ڿ� ��ġ���� �ʴ� ���
            return false; // false ��ȯ
    }
    return true; // ��ġ�ϴ� ��� true ��ȯ
}

#include <iostream>
using namespace std;

int main()
{
    char input[101]; //���ڿ��� ������ �迭 ����
    cout << "Enter the string: "; //����ڷκ��� ���ڿ� �Է� ��û
    cin.getline(input, 100); //���ڿ� �Է� �ޱ�

    for (int i = 0; input[i] != '\0'; i++) //�� ����(���ڿ� ��)�� ���� ������ �ݺ�
    {
        if (input[i] >= 65 && input[i] <= 90) //�빮���� ���
            input[i] += 32; //�ҹ��ڷ� ��ȯ
        else if (input[i] >= 97 && input[i] <= 122) //�ҹ����� ���
            input[i] -= 32; //�빮�ڷ� ��ȯ
    }
    cout << "Result: " << input; //��ȯ�� ���ڿ� ���
    return 0;
}
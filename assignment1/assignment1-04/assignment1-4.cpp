#include <iostream>
using namespace std;

int main(void)
{
    int input, len = 0, tmp, div = 1, flag = 0, reverse[10] = {}; // ���� ���� �� �ʱ�ȭ
    cout << "Enter the number: "; // ����ڷκ��� ���� �Է� ��û
    cin >> input; // ���� �Է� �ޱ�
    tmp = input; // �Էµ� ���ڸ� �ӽ� ������ ����
    while (tmp != 0) // �Էµ� ������ �ڸ��� ���
    {
        tmp /= 10;
        len++;
    }
    for (int i = 0; i < len; i++) // �Էµ� ���ڸ� ����� �迭�� ����
    {
        reverse[i] = (input / div) % 10;
        div *= 10;
    }
    cout << "Reversed number: "; // ������ ���� ��� ��Ʈ
    for (int i = 0; i < len; i++) // ������ ���� ���
    {
        if (flag == 0 && reverse[i] == 0) // �տ� ���� 0�� ������� ����
            continue;
        else
        {
            cout << reverse[i]; // ���� ���
            flag++;//ù ���� ��½� flag ����
        }
    }
    return 0;
}
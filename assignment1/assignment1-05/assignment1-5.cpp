#include <iostream>
using namespace std;

int main(void)
{
    int input, div = 1, arr[5] = {}; // ���� ���� �� �ʱ�ȭ
    cout << "Enter the number: "; // ����ڷκ��� ���� �Է� ��û
    cin >> input; // ���� �Է� �ޱ�
    for (int i = 0; i < 5; i++)
    {
        arr[4 - i] = (input / div) % 10;  // �Էµ� ���ڸ� �� �ڸ������� �迭�� ����
        div *= 10;
    }
    for (int i = 0; i < 5; i++)
    {
        // ���� �ڸ������� ������ �ڸ������� ����ϴ� ����
        for (int j = i; j < 5; j++)
        {
            cout << arr[j]; // �� �ڸ��� ���
            if (j < 4) // ������ �ڸ��� �� ���
                cout << "  "; // ���� ���
        }
        cout << "\n";
    }
    return 0;
}

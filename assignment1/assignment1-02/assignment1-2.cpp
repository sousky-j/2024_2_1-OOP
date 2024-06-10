#include <iostream>
#include <ctime>
using namespace std;

int main(void)
{
    int arr[5][10] = {}; // 5x10 ũ���� �迭 ���� �� �ʱ�ȭ
    int tmp;//���� ���� ������ ���� �ӽ� ����
    int init = static_cast<unsigned int>(time(NULL)); //���� �ð��� �õ尪���� �ʱ�ȭ ����
    cout.precision(0); // �Ҽ��� ���� �ڸ��� 0���� ����
    cout << fixed; // ������ �Ҽ��� ���
    srand(init); // �õ尪 ����

    // 5x10 �迭�� ���� ä���
    for (int i = 0; i < 5; i++) // �� �࿡ ���� ����
    {
        int sum = 0; // �� ���� �� �ʱ�ȭ
        for (int j = 0; j < 10; j++) // �� ���� ���� ����
        {
            tmp = (rand() % 99) + 1; // 1���� 99������ ���� ����
            while (tmp >= 100 || tmp <= 0) // 1���� 99 ������ ������ �����ϱ� ���� �ݺ���
                tmp = (rand() % 99) + 1;
            arr[i][j] = tmp; // �迭�� ���� ����
            cout.width(2); // ��� �� ����
            cout << arr[i][j]; // �迭 ��� ���
            if (j < 9) // �� ���̿� ���� ���
                cout << "  ";
            sum += arr[i][j]; // �� ���� �� ����
        }
        cout << " | "; // ��� ��, ����� �����ϴ� ������ ���
        cout.width(3); // ��� �� ����
        cout << sum << " | "; // �� ���� �� ���
        cout.width(2); // ��� �� ����
        float avg = sum; // ��� ����� ���� ���� ����
        cout << avg / 10 << "\n"; // ��� ���
    }
    return 0;
}

#include <iostream>
using namespace std;

int main(void)
{
    int min, max, arr[5] = {}; // ���� �ʱ�ȭ
    double avg = 0;
    cout << "Enter the five numbers: ";
    for (int i = 0; i < 5; i++)
    {
        cin >> arr[i];// ����ڷκ��� 5���� ���� �Է� �ޱ�
        avg += (double)arr[i] / 5;// ��� ����� ���� �Էµ� ���� ����
        if (i == 0)// ù ��° �Էµ� ���ڸ� min�� max�� �ʱ�ȭ
        {
            min = arr[i];
            max = arr[i];
        }
        if (min > arr[i])// ���� ���ڰ� min���� ������ min ������Ʈ
            min = arr[i];
        if (max < arr[i])// ���� ���ڰ� max���� ũ�� max ������Ʈ
            max = arr[i];
    }
    // �ּڰ�, �ִ� ���
    cout << "MIN: " << min << "\n";
    cout << "MAX: " << max << "\n";
    cout << "AVG: ";
    // ��հ��� ������ ����ϱ� ���� �Ҽ��� ���� �ڸ� �ݿø� �� ��� ���
    cout << fixed;
    cout.precision(0);
    cout << avg;

    return 0;
}
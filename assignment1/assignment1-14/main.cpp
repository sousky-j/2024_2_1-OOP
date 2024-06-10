#include <iostream>
using namespace std;

bool perfect(int n); //������ ��ȯ

int main()
{
    cout << "Perfect numbers between 1 and 1000:\n"; //������ ��� ��Ʈ
    for (int i = 1; i <= 1000; i++) //1���� 1000���� �ݺ�
    {
        if (perfect(i)) //�Լ� ȣ���Ͽ� ���������� Ȯ��
        {
            cout << i << " = "; //������ ��� �غ�
            int sum = 0; //�������� ��� �� �ʱ�ȭ
            for (int j = 1; j < i; j++) //�������� ��� �� ���ϱ�
            {
                if (i % j == 0) //j�� i�� ����� ���
                {
                    cout << j; //��� ���
                    sum += j; //����� �տ� ����
                    if (sum != i) //������ ����� �ƴ� ���
                        cout << " + "; //"+" ���
                }
            }
            cout << "\n";
        }
    }
    return 0;
}

bool perfect(int n) //������ ��ȯ
{
    int sum = 0; // ����� ���� ������ ���� ���� �� �ʱ�ȭ
    for (int i = 1; i < n; i++) // 1���� n-1���� �ݺ�
    {
        if (n % i == 0) // i�� n�� ����� ���
            sum += i; // ����� �տ� ����
    }
    return sum == n; // ����� ���� n�� ������ true ��ȯ, �׷��� ������ false ��ȯ
}

#include <iostream>
using namespace std;

int Fibonacci_rec(int x);//��� �Ǻ���ġ �Լ� ����
int Fibonacci_iter(int x);//�ݺ��� �Ǻ���ġ �Լ� ����

int a[50];//�ݺ��� �Ǻ���ġ �迭 ����

int main()
{
	a[1] = 1;//2��° ��(1��° �ε���) �ʱ�ȭ
	int input;//�Է� ���� ����
	cout << "Enter the number: "; //�Է� �䫊
	cin >> input;
	cout << "Fibonacci_iter(" << input << "): " << Fibonacci_iter(input) << "\n";//�ݺ��� �Ǻ���ġ �Լ��� ���
	cout << "Fibonacci_rec(" << input << "): " << Fibonacci_rec(input - 1);//��� �Ǻ���ġ �Լ��� ���
	return 0;
}

int Fibonacci_rec(int n)//��� �Ǻ���ġ �Լ� ����
{
	if (n == 0)// �Ķ���� ���� 0�϶�
		return 0; //0 ��ȯ
	else if (n == 1) //�Ķ���� ���� 1�϶�
		return 1; //1 ��ȯ
	else
		return Fibonacci_rec(n - 1) + Fibonacci_rec(n - 2); //������ �� ���� ���� �� ��ȯ
}

int Fibonacci_iter(int n)//�ݺ��� �Ǻ���ġ �Լ� ����
{
	for (int i = 2; i < n; i++)//2�� �ε������� n-1���� �ݺ�
		a[i] = a[i - 1] + a[i - 2];//���� �� ���� ���� ���� �ش� �׿� ����
	return a[n-1];//n-1��° �� ��ȯ
}
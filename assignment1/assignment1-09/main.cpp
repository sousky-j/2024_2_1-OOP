#include <iostream>
using namespace std;

int gcd(int a, int b); //�ִ����� ���ϴ� ����Լ� ����
int lcm(int a, int b); //�ִ������� �̿��� �ּҰ���� �Լ� ������
int main()
{
	int input1, input2;
	cout << "Enter the 1st number: ";
	cin >> input1;
	cout << "Enter the 2nd number: ";
	cin >> input2;
	cout << "lcm(" << input1 << "," << input2 << "): ";
	cout << lcm(input1, input2);
	return 0;
}

int gcd(int a, int b) //�ִ����� ���ϴ� ����Լ� ����
{
	if (b == 0) //y�� 0�̸�
		return a; //x��ȯ
	else
		gcd(b, a % b); //��� ȣ���� ���� �ִ����� ���
}

int lcm(int a, int b) //�ִ������� �̿��� �ּҰ���� �Լ� ����
{
	return (int)((float)a * b) / gcd(a, b); //�Է°� 2���� �ִ������� ���� �� ��ȯ
}
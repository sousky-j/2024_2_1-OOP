#include <iostream>
using namespace std;

int gcd(int a, int b);//�ִ� ����� �Լ� ����
int main()
{
	int input1, input2;
	cout << "Enter the 1st number: ";//�Է� ��û
	cin >> input1;
	cout << "Enter the 2nd number: "; //�Է� ��û
	cin >> input2;
	cout << "gcd(" << input1 << "," << input2 << "): "; //�ִ����� ��� ����
	cout << gcd(input1, input2);//�ִ����� �� ���
	return 0;
}

int gcd(int a, int b) //�ִ� ����� �Լ� ����
{
	if (b == 0) //y�� 0�� ���
		return a; //x�� ��ȯ
	else 
		gcd(b, a % b); // gcd �Լ��� ��� ȣ��� �ִ����� ���
}
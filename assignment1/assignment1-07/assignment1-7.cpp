#include <iostream>
using namespace std;

int power(int base, int exponent);//power �Լ� ����

int main(void)
{
	int base, exponent; //�ذ� ���� ���� ����
	cout << "Enter the base: "; //�� �Է� ��û
	cin >> base;
	cout << "Enter the exponent: "; //���� �Է� ��û
	cin >> exponent;
	cout << "power(" << base << "," << exponent << "): " << power(base, exponent); //��갪 ���
	return 0;
}

int power(int base, int exponent)//power �Լ� ����
{
	if (!exponent)//���� ������ 0�϶�
		return 1;//1 ��ȯ
	else
		return base * power(base, exponent - 1); //��ͷ� �ŵ����� �� ��ȯ
}
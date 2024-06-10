#include <iostream>
using namespace std;

float my_ceil(float x); //��°�ڸ������� õ�� �Լ� ����
float my_floor(float x); //��°�ڸ������� �ٴ� �Լ� ����
float my_round(float x); //��°�ڸ������� �ݿø� �Լ� ����
int main(void)
{
	float input; //�Է°� ���� ����
	cout << "Enter the floating-point number: "; //float �� �Է� ��û
	cin >> input; //�Է°� �ޱ�
	cout << fixed; // �Ҽ��� ���� �ڸ��� ��� ���� ����
	cout.precision(2); // �Ҽ��� ���� ��° �ڸ����� ���
	cout << "Ceiling: " << my_ceil(input) << "\n"; //�Է°��� ��°�ڸ������� õ�� �Լ��� ���
	cout << "Floor: " << my_floor(input) << "\n"; //�Է°��� ��°�ڸ������� �ٴ� �Լ��� ���
	cout << "Rounding: " << my_round(input); //�Է°��� ��°�ڸ������� �ݿø� �Լ��� ���
	return 0;
}

float my_ceil(float x)//õ���Լ� ����
{
	if (x > 0) //����� ��
	{
		float ori = (x * 100); //�Է°� �Ҽ��� ��°�ڸ����� ����ȭ
		int tmp = ori; //�Ͻ��� �� ��ȯ���� �Ҽ��� ��°�ڸ������� �ӽ� ������ ����
		if ((ori - tmp)) //0�� �ƴҶ�
			ori++; //�Ҽ��� ��°�ڸ��� 1 ����
		return (float) ori / 100; //�Է°��� �Ҽ��� ��ġ�� ���� �� ��ȯ
	}
	else //������ ��
		return (-1) * my_floor(x * (-1)); //�Է°��� ������ �ٴ��Լ����� ���� ��ȯ
}
float my_floor(float x)//�ٴ��Լ� ����
{
	if (x > 0)//����� ��
	{
		float k = (int)(x * 100); //����� �� ��ȯ�� ���� �Ҽ��� ��°�ڸ����� ����ȭ
		return (k / 100); //�Է°��� �Ҽ��� ��ġ�� ���� �� ��ȯ
	}
	else //������ ��
		return (-1) * my_ceil(x * (-1));//�Է°��� ������ õ���Լ��� ���� ��ȯ
}
float my_round(float x) //�ݿø� �Լ� ����
{
	if (x > 0) //����� ��
		return my_floor(x + 0.005); //�ٴ��Լ��� ��Ī�̵��� ��� ��ȯ
	else //������ ��
		return (-1) * my_floor(x * (-1) + 0.005);//�Է°��� ������ ��Ī�̵� �� �ٴ��Լ����� ���� ��ȯ
}
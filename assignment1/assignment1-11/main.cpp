#include <iostream>
using namespace std;

bool multiple(int st, int nd);//��� �Ǻ� �Լ� ����

int main()
{
	int st, nd;//�� ���� �Է� ���� ����
	cout << "Enter the 1st number: ";//ù��° ���� �Է� ��û
	cin >> st;
	cout << "Enter the 2nd number: ";//�ι��� ���� �Է� ��û
	cin >> nd;
	bool check = multiple(st, nd);//üũ�� ������ �Լ� ��ȯ�� ����
	cout << "multiple(" << st << "," << nd << "): "; //��� ����
	if (check)//bool ������ �̿��� ���
		cout << "true";//���� �� true ���
	else
		cout << "false"; // ���� ������ false ���
	return 0;
}

bool multiple(int st, int nd)//��� �Ǻ� �Լ� ����
{
	if (!(nd % st))	return true; //������ ������ ���� �Ǻ� ��� ��ȯ
	else return false; //���� ���� �� false ��ȯ
}
#include <iostream>
using namespace std;

int main()
{
	int input; //�Է� ���� ����
	char matrix[19][19]; //���� �� 2���� �迭 ���� ����
	cout << "Enter the number of rows: "; //�Է� ��û
	cin >> input;
	if (input == 1) //�Է��� 1�� ���
	{
		cout << "*"; //�� �ϳ� ��� �� ����
		return 1;
	}
	for (int i = 0; i < 19; i++) //2���� �迭 matrix �������� �ʱ�ȭ
	{
		for (int j = 0; j < 19; j++)
			matrix[i][j] = ' ';
	}

	int m = (input - 1) / 2; //�Է°��� �߾��� �ʱ�ȭ

	for (int i = 0; i < m; i++)
	{
		matrix[9 - i][9 + m - i] = '*'; //+���� X��� 1��и� �����
		matrix[9 - m + i][9 - i] = '*'; //+���� Y��� 2��и� �����
		matrix[9 + i][9 - m + i] = '*'; //-���� X��� 3��и� �����
		matrix[9 + m - i][9 + i] = '*'; //-���� Y��� 4��и� �����
	}

	////2���� matrix ���////
	for (int i = 9 - m; i < 10 + m; i++)
	{
		for (int j = 9 - m; j < 10 + m; j++)
			cout << matrix[i][j];
		cout << "\n";
	}
	////////////////////////
	return 0;
}
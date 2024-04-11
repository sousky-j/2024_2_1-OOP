#include <iostream>
using namespace std;

int main()
{
	int input; //입력 변수 선언
	char matrix[19][19]; //별이 들어갈 2차원 배열 변수 생성
	cout << "Enter the number of rows: "; //입력 요청
	cin >> input;
	if (input == 1) //입력이 1인 경우
	{
		cout << "*"; //별 하나 출력 후 종료
		return 1;
	}
	for (int i = 0; i < 19; i++) //2차원 배열 matrix 공백으로 초기화
	{
		for (int j = 0; j < 19; j++)
			matrix[i][j] = ' ';
	}

	int m = (input - 1) / 2; //입력값의 중앙점 초기화

	for (int i = 0; i < m; i++)
	{
		matrix[9 - i][9 + m - i] = '*'; //+방향 X축과 1사분면 별찍기
		matrix[9 - m + i][9 - i] = '*'; //+방향 Y축과 2사분면 별찍기
		matrix[9 + i][9 - m + i] = '*'; //-방향 X축과 3사분면 별찍기
		matrix[9 + m - i][9 + i] = '*'; //-방향 Y축과 4사분면 별찍기
	}

	////2차원 matrix 출력////
	for (int i = 9 - m; i < 10 + m; i++)
	{
		for (int j = 9 - m; j < 10 + m; j++)
			cout << matrix[i][j];
		cout << "\n";
	}
	////////////////////////
	return 0;
}
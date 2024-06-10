#include <iostream>
using namespace std;

bool multiple(int st, int nd);//배수 판별 함수 선언

int main()
{
	int st, nd;//두 개의 입력 변수 선언
	cout << "Enter the 1st number: ";//첫번째 숫자 입력 요청
	cin >> st;
	cout << "Enter the 2nd number: ";//두번쨰 숫자 입력 요청
	cin >> nd;
	bool check = multiple(st, nd);//체크할 변수에 함수 반환값 대입
	cout << "multiple(" << st << "," << nd << "): "; //출력 포맷
	if (check)//bool 변수를 이용한 제어문
		cout << "true";//옳을 때 true 출력
	else
		cout << "false"; // 옳지 않을때 false 출력
	return 0;
}

bool multiple(int st, int nd)//배수 판별 함수 정의
{
	if (!(nd % st))	return true; //나머지 연산을 통한 판별 결과 반환
	else return false; //옳지 않을 때 false 반환
}
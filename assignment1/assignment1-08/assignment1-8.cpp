#include <iostream>
using namespace std;

int gcd(int a, int b);//최대 공약수 함수 선언
int main()
{
	int input1, input2;
	cout << "Enter the 1st number: ";//입력 요청
	cin >> input1;
	cout << "Enter the 2nd number: "; //입력 요청
	cin >> input2;
	cout << "gcd(" << input1 << "," << input2 << "): "; //최대공약수 출력 포맷
	cout << gcd(input1, input2);//최대공약수 값 출력
	return 0;
}

int gcd(int a, int b) //최대 공약수 함수 선언
{
	if (b == 0) //y가 0인 경우
		return a; //x를 반환
	else 
		gcd(b, a % b); // gcd 함수의 재귀 호출로 최대공약수 계산
}
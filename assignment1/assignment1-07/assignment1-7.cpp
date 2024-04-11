#include <iostream>
using namespace std;

int power(int base, int exponent);//power 함수 선언

int main(void)
{
	int base, exponent; //밑과 지수 변수 선언
	cout << "Enter the base: "; //밑 입력 요청
	cin >> base;
	cout << "Enter the exponent: "; //지수 입력 요청
	cin >> exponent;
	cout << "power(" << base << "," << exponent << "): " << power(base, exponent); //계산값 출력
	return 0;
}

int power(int base, int exponent)//power 함수 정의
{
	if (!exponent)//지수 변수가 0일때
		return 1;//1 반환
	else
		return base * power(base, exponent - 1); //재귀로 거듭제곱 값 반환
}
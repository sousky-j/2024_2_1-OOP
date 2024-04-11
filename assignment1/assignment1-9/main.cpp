#include <iostream>
using namespace std;

int gcd(int a, int b); //최대공약수 구하는 재귀함수 선언
int lcm(int a, int b); //최대공약수를 이용한 최소공배수 함수 선ㅇ언
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

int gcd(int a, int b) //최대공약수 구하는 재귀함수 정의
{
	if (b == 0) //y가 0이면
		return a; //x반환
	else
		gcd(b, a % b); //재귀 호출을 통한 최대공약수 계산
}

int lcm(int a, int b) //최대공약수를 이용한 최소공배수 함수 선언
{
	return (int)((float)a * b) / gcd(a, b); //입력값 2개를 최대공약수로 나눈 값 반환
}
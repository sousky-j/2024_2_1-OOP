#include <iostream>
using namespace std;

int Fibonacci_rec(int x);//재귀 피보나치 함수 선언
int Fibonacci_iter(int x);//반복문 피보나치 함수 선언

int a[50];//반복문 피보나치 배열 선언

int main()
{
	a[1] = 1;//2번째 값(1번째 인덱스) 초기화
	int input;//입력 변수 선언
	cout << "Enter the number: "; //입력 요쳥
	cin >> input;
	cout << "Fibonacci_iter(" << input << "): " << Fibonacci_iter(input) << "\n";//반복문 피보나치 함숫값 출력
	cout << "Fibonacci_rec(" << input << "): " << Fibonacci_rec(input - 1);//재귀 피보나치 함숫값 출력
	return 0;
}

int Fibonacci_rec(int n)//재귀 피보나치 함수 정의
{
	if (n == 0)// 파라미터 값이 0일때
		return 0; //0 반환
	else if (n == 1) //파라미터 값이 1일때
		return 1; //1 반환
	else
		return Fibonacci_rec(n - 1) + Fibonacci_rec(n - 2); //이전의 두 수를 더한 값 반환
}

int Fibonacci_iter(int n)//반복문 피보나치 함수 정의
{
	for (int i = 2; i < n; i++)//2번 인덱스부터 n-1까지 반복
		a[i] = a[i - 1] + a[i - 2];//이전 두 항을 더한 값을 해당 항에 더함
	return a[n-1];//n-1번째 항 반환
}
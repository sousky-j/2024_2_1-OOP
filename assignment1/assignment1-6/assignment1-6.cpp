#include <iostream>
using namespace std;

float my_ceil(float x); //셋째자리에서의 천장 함수 선언
float my_floor(float x); //셋째자리에서의 바닥 함수 선언
float my_round(float x); //셋째자리에서의 반올림 함수 선언
int main(void)
{
	float input; //입력값 변수 선언
	cout << "Enter the floating-point number: "; //float 형 입력 요청
	cin >> input; //입력값 받기
	cout << fixed; // 소수점 이하 자리수 출력 포맷 설정
	cout.precision(2); // 소수점 이하 둘째 자리까지 출력
	cout << "Ceiling: " << my_ceil(input) << "\n"; //입력값의 셋째자리에서의 천장 함수값 출력
	cout << "Floor: " << my_floor(input) << "\n"; //입력값의 셋째자리에서의 바닥 함수값 출력
	cout << "Rounding: " << my_round(input); //입력값의 셋째자리에서의 반올림 함수값 출력
	return 0;
}

float my_ceil(float x)//천장함수 정의
{
	if (x > 0) //양수일 때
	{
		float ori = (x * 100); //입력값 소수점 둘째자리까지 정수화
		int tmp = ori; //암시적 형 변환으로 소수점 둘째자리까지만 임시 변수에 저장
		if ((ori - tmp)) //0이 아닐때
			ori++; //소수점 둘째자리에 1 더함
		return (float) ori / 100; //입력값의 소수점 위치로 복구 후 반환
	}
	else //음수일 때
		return (-1) * my_floor(x * (-1)); //입력값의 음수의 바닥함숫값의 음수 반환
}
float my_floor(float x)//바닥함수 정의
{
	if (x > 0)//양수일 때
	{
		float k = (int)(x * 100); //명시적 형 변환을 통한 소수점 둘째자리까지 정수화
		return (k / 100); //입력값의 소수점 위치로 복구 후 반환
	}
	else //음수일 때
		return (-1) * my_ceil(x * (-1));//입력값의 음수의 천장함수의 음수 반환
}
float my_round(float x) //반올림 함수 정의
{
	if (x > 0) //양수일 때
		return my_floor(x + 0.005); //바닥함수를 대칭이동한 결과 반환
	else //음수일 때
		return (-1) * my_floor(x * (-1) + 0.005);//입력값의 음수에 대칭이동 후 바닥함숫값의 음수 반환
}
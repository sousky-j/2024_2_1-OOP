#include <iostream>
using namespace std;

int main(void)
{
    int input, len = 0, tmp, div = 1, flag = 0, reverse[10] = {}; // 변수 선언 및 초기화
    cout << "Enter the number: "; // 사용자로부터 숫자 입력 요청
    cin >> input; // 숫자 입력 받기
    tmp = input; // 입력된 숫자를 임시 변수에 저장
    while (tmp != 0) // 입력된 숫자의 자릿수 계산
    {
        tmp /= 10;
        len++;
    }
    for (int i = 0; i < len; i++) // 입력된 숫자를 뒤집어서 배열에 저장
    {
        reverse[i] = (input / div) % 10;
        div *= 10;
    }
    cout << "Reversed number: "; // 뒤집힌 숫자 출력 멘트
    for (int i = 0; i < len; i++) // 뒤집힌 숫자 출력
    {
        if (flag == 0 && reverse[i] == 0) // 앞에 오는 0은 출력하지 않음
            continue;
        else
        {
            cout << reverse[i]; // 숫자 출력
            flag++;//첫 숫자 출력시 flag 증가
        }
    }
    return 0;
}
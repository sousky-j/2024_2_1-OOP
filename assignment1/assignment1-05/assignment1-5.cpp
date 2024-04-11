#include <iostream>
using namespace std;

int main(void)
{
    int input, div = 1, arr[5] = {}; // 변수 선언 및 초기화
    cout << "Enter the number: "; // 사용자로부터 숫자 입력 요청
    cin >> input; // 숫자 입력 받기
    for (int i = 0; i < 5; i++)
    {
        arr[4 - i] = (input / div) % 10;  // 입력된 숫자를 각 자릿수마다 배열에 저장
        div *= 10;
    }
    for (int i = 0; i < 5; i++)
    {
        // 현재 자릿수부터 마지막 자릿수까지 출력하는 루프
        for (int j = i; j < 5; j++)
        {
            cout << arr[j]; // 각 자릿수 출력
            if (j < 4) // 마지막 자릿수 뺀 제어문
                cout << "  "; // 공백 출력
        }
        cout << "\n";
    }
    return 0;
}

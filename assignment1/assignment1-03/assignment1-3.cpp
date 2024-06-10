#include <iostream>
using namespace std;

int main() {
    char arr[10]{}; // 크기가 10인 문자 배열 선언 및 초기화
    cout << "Enter ten characters: "; // 사용자로부터 10개의 문자 입력 요청
    for (int i = 0; i < 10; i++) // 10번 반복하여 문자 입력 받기
        cin >> arr[i];
    cout << "Input characters are:\n"; // 입력된 문자 출력 멘트
    for (int i = 0; i < 5; i++) // 배열의 1-10 문자부터 5-6 문자까지 반복
        cout << arr[i] << " " << arr[9 - i] << "\n"; // 배열의 대칭 쌍 문자 출력
    return 0;
}
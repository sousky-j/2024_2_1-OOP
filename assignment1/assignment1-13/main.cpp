#include <iostream>
using namespace std;

int main()
{
    char input[101]; //문자열을 저장할 배열 선언
    cout << "Enter the string: "; //사용자로부터 문자열 입력 요청
    cin.getline(input, 100); //문자열 입력 받기

    for (int i = 0; input[i] != '\0'; i++) //널 문자(문자열 끝)를 만날 때까지 반복
    {
        if (input[i] >= 65 && input[i] <= 90) //대문자인 경우
            input[i] += 32; //소문자로 변환
        else if (input[i] >= 97 && input[i] <= 122) //소문자인 경우
            input[i] -= 32; //대문자로 변환
    }
    cout << "Result: " << input; //변환된 문자열 출력
    return 0;
}
// 필요한 헤더 파일을 포함합니다.
#define _CRT_SECURE_NO_WARNINGS // Visual Studio에서 경고를 숨기는 디렉티브
#include <iostream> // 표준 입출력 스트림 라이브러리

using namespace std; // 표준 네임스페이스를 사용합니다.

// 전역 변수 선언
char input_string[101]; // 입력 문자열을 저장할 배열
char delimiter[11]; // 구분자를 저장할 배열
bool check[100]; // 구분자의 위치를 체크할 배열

// 함수 프로토타입 선언
int my_strlen(char* arr); // 문자열의 길이를 반환하는 함수
bool Iscorrect(int i, int delimiter_len); // i 위치부터 delimiter_len 길이만큼의 문자열이 구분자와 일치하는지 확인하는 함수

// main 함수
int main(void)
{
    // 사용자로부터 문자열과 구분자를 입력 받습니다.
    cout << "Enter the string : ";
    cin.getline(input_string, 100); // 문자열 입력
    cout << "Enter the delimiter : ";
    cin.getline(delimiter, 10); // 구분자 입력
    cout << "\n";

    // 문자열의 길이와 구분자의 길이를 계산합니다.
    int string_len = my_strlen(input_string);
    int delimiter_len = my_strlen(delimiter);
    int search_len = string_len - delimiter_len;

    // 구분자가 발견되는 위치를 체크합니다.
    for (int i = 0; i < search_len; i++)
    {
        if (Iscorrect(i, delimiter_len))
        {
            for (int k = 0; k < delimiter_len; k++)
                check[i + k] = true; // 구분자의 위치를 체크합니다.
        }
    }

    bool sequence_flag = true;

    // 구분자를 기준으로 문자열을 분리하여 출력합니다.
    cout << "Separated tokens :\n";
    for (int i = 0; i < string_len; i++)
    {
        if (!check[i]) // 구분자가 아닌 경우
        {
            if (!sequence_flag) // 이전에 구분자가 있었다면
            {
                cout << "\n" << input_string[i]; // 새로운 줄에 문자열 출력
                sequence_flag = true; // 연속된 문자열 플래그를 true로 설정
            }
            else
                cout << input_string[i]; // 구분자가 연속되지 않은 경우 문자열 출력
        }
        else
            sequence_flag = false; // 구분자인 경우 연속된 문자열 플래그를 false로 설정
    }
    return 0;
}

// 문자열의 길이를 반환하는 함수
int my_strlen(char* arr)
{
    int len = 0;
    for (int i = 0; i < 100; i++)
    {
        if (arr[i] == '\0') // 널 문자를 만나면 반복 종료
            return len;
        len++; // 길이를 증가
    }
    return len; // 길이 반환
}

// i 위치부터 delimiter_len 길이만큼의 문자열이 구분자와 일치하는지 확인하는 함수
bool Iscorrect(int i, int delimiter_len)
{
    for (int k = 0; k < delimiter_len; k++)
    {
        if (input_string[i + k] != delimiter[k]) // 구분자와 일치하지 않는 경우
            return false; // false 반환
    }
    return true; // 일치하는 경우 true 반환
}

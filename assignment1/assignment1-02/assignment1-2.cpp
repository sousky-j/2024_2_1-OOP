#include <iostream>
#include <ctime>
using namespace std;

int main(void)
{
    int arr[5][10] = {}; // 5x10 크기의 배열 선언 및 초기화
    int tmp;//난수 범위 설정을 위한 임시 변수
    int init = static_cast<unsigned int>(time(NULL)); //현재 시간을 시드값으로 초기화 설정
    cout.precision(0); // 소수점 이하 자리를 0으로 설정
    cout << fixed; // 고정된 소수점 출력
    srand(init); // 시드값 설정

    // 5x10 배열에 난수 채우기
    for (int i = 0; i < 5; i++) // 각 행에 대한 루프
    {
        int sum = 0; // 각 행의 합 초기화
        for (int j = 0; j < 10; j++) // 각 열에 대한 루프
        {
            tmp = (rand() % 99) + 1; // 1부터 99까지의 난수 생성
            while (tmp >= 100 || tmp <= 0) // 1부터 99 사이의 난수를 생성하기 위한 반복문
                tmp = (rand() % 99) + 1;
            arr[i][j] = tmp; // 배열에 난수 저장
            cout.width(2); // 출력 폭 설정
            cout << arr[i][j]; // 배열 요소 출력
            if (j < 9) // 열 사이에 공백 출력
                cout << "  ";
            sum += arr[i][j]; // 각 행의 합 누적
        }
        cout << " | "; // 행과 합, 평균을 구분하는 구분자 출력
        cout.width(3); // 출력 폭 설정
        cout << sum << " | "; // 각 행의 합 출력
        cout.width(2); // 출력 폭 설정
        float avg = sum; // 평균 계산을 위한 변수 설정
        cout << avg / 10 << "\n"; // 평균 출력
    }
    return 0;
}

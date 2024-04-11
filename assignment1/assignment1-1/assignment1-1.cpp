#include <iostream>
using namespace std;

int main(void)
{
    int min, max, arr[5] = {}; // 변수 초기화
    double avg = 0;
    cout << "Enter the five numbers: ";
    for (int i = 0; i < 5; i++)
    {
        cin >> arr[i];// 사용자로부터 5개의 정수 입력 받기
        avg += (double)arr[i] / 5;// 평균 계산을 위해 입력된 숫자 누적
        if (i == 0)// 첫 번째 입력된 숫자를 min과 max로 초기화
        {
            min = arr[i];
            max = arr[i];
        }
        if (min > arr[i])// 현재 숫자가 min보다 작으면 min 업데이트
            min = arr[i];
        if (max < arr[i])// 현재 숫자가 max보다 크면 max 업데이트
            max = arr[i];
    }
    // 최솟값, 최댓값 출력
    cout << "MIN: " << min << "\n";
    cout << "MAX: " << max << "\n";
    cout << "AVG: ";
    // 평균값을 정수로 출력하기 위해 소수점 이하 자리 반올림 후 평균 출력
    cout << fixed;
    cout.precision(0);
    cout << avg;

    return 0;
}
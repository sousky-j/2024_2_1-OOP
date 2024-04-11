#include <iostream>
using namespace std;

bool perfect(int n); //완전수 반환

int main()
{
    cout << "Perfect numbers between 1 and 1000:\n"; //완전수 출력 멘트
    for (int i = 1; i <= 1000; i++) //1부터 1000까지 반복
    {
        if (perfect(i)) //함수 호출하여 완전수인지 확인
        {
            cout << i << " = "; //완전수 출력 준비
            int sum = 0; //완전수의 약수 합 초기화
            for (int j = 1; j < i; j++) //완전수의 약수 합 구하기
            {
                if (i % j == 0) //j가 i의 약수인 경우
                {
                    cout << j; //약수 출력
                    sum += j; //약수를 합에 더함
                    if (sum != i) //마지막 약수가 아닌 경우
                        cout << " + "; //"+" 출력
                }
            }
            cout << "\n";
        }
    }
    return 0;
}

bool perfect(int n) //완전수 반환
{
    int sum = 0; // 약수의 합을 저장할 변수 선언 및 초기화
    for (int i = 1; i < n; i++) // 1부터 n-1까지 반복
    {
        if (n % i == 0) // i가 n의 약수인 경우
            sum += i; // 약수를 합에 더함
    }
    return sum == n; // 약수의 합이 n과 같으면 true 반환, 그렇지 않으면 false 반환
}

#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

void hadamard_mat(int rows, int cols, int power_n, bool invert_minus); // 하다마드 행렬을 생성하는 함수 선언

int** mat; // 2차원 배열을 가리키는 이중 포인터를 선언

int main(void)
{
    int n, power_n = 1; // 변수 n과 power_n을 선언하고, power_n을 1로 초기화

    cout << "Enter the value of Hadamard matrix (2^n x 2^n): "; // 사용자에게 메시지를 출력
    cin >> n; // 사용자로부터 n 값을 입력받습니다.

    for (int i = 0; i < n; i++) // n번 반복
        power_n *= 2; // power_n을 2배씩 곱해줍니다.

    mat = new int* [power_n]; // mat에 power_n만큼의 포인터를 동적으로 할당

    for (int i = 0; i < power_n; i++) // power_n번 반복
        *(mat + i) = new int[power_n]; // mat의 각 요소에 power_n만큼의 배열을 동적으로 할당

    hadamard_mat(0, 0, power_n, 0); // 하다마드 행렬을 생성하는 함수를 호출

    cout << "Hadamard Matrix of size " << power_n << "x" << power_n << ":\n"; // 하다마드 행렬의 크기를 출력
    for (int i = 0; i < power_n; i++) // power_n번 반복
    {
        for (int j = 0; j < power_n; j++) // power_n번 반복
            cout << *(*(mat + i) + j) << "\t"; // mat의 각 요소를 탭으로 구분하여 출력

        cout << "\n"; // 다음 줄로 이동
    }

    for (int i = 0; i < power_n; i++) // power_n번 반복
        delete[] mat[i]; // mat의 각 행을 해제

    delete[] mat; // mat을 해제

    return 0; // 프로그램 종료를 나타냅니다.
}

void hadamard_mat(int rows, int cols, int power_n, bool invert_minus)
{
    if (power_n == 1) // power_n이 1인 경우:
    {
        if (!invert_minus) // invert_minus가 false인 경우:
            mat[rows][cols] = 1; // 해당 위치에 1을 설정
        else // invert_minus가 true인 경우:
            mat[rows][cols] = -1; // 해당 위치에 -1을 설정
    }
    else // power_n이 1이 아닌 경우:
    {
        power_n /= 2; // power_n을 절반으로 줄입니다.

        if (invert_minus) // invert_minus가 true인 경우: 1을 곱함
        {
            hadamard_mat(rows, cols, power_n, 1); // 왼쪽 위 사분면에 대해 재귀 호출
            hadamard_mat(rows, cols + power_n, power_n, 1); // 오른쪽 위 사분면에 대해 재귀 호출
            hadamard_mat(rows + power_n, cols, power_n, 1); // 왼쪽 아래 사분면에 대해 재귀 호출
            hadamard_mat(rows + power_n, cols + power_n, power_n, 0); // 오른쪽 아래 사분면에 대해 재귀 호출
        }
        else // invert_minus가 false인 경우:-1을 곱함
        {
            hadamard_mat(rows, cols, power_n, 0); // 왼쪽 위 사분면에 대해 재귀 호출
            hadamard_mat(rows, cols + power_n, power_n, 0); // 오른쪽 위 사분면에 대해 재귀 호출
            hadamard_mat(rows + power_n, cols, power_n, 0); // 왼쪽 아래 사분면에 대해 재귀 호출
            hadamard_mat(rows + power_n, cols + power_n, power_n, 1); // 오른쪽 아래 사분면에 대해 재귀 호출
        }
    }
}

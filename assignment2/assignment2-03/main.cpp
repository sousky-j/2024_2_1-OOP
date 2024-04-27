#define _CRT_SECURE_NO_WARNINGS
#include <iostream> 
#include <ctime> 
#define SWP(x,y,tmp) ( (tmp)=(x), (x)=(y), (y)=(tmp) ) // 두 변수의 값을 교환하는 매크로

using namespace std;

// 함수 프로토타입 선언
void print_matrix(int** mat); // 매트릭스 출력 함수
void print_marix(int** mat, int* sum); // 매트릭스 및 각 행의 합 출력 함수
void rows_Descending_sort(int** mat); // 행 기준 내림차순 정렬 함수
void sum_ascending_sort(int** mat, int* sum); // 합 기준 오름차순 정렬 함수

// main 함수
int main(void)
{
    // 현재 시간을 시드값으로 설정
    int init = static_cast<unsigned int>(time(NULL));
    srand(init); // 랜덤 시드 설정

    // 10x10 크기의 2차원 배열 동적 할당
    int** mat = new int* [10];
    for (int i = 0; i < 10; i++)
        *(mat + i) = new int[10];

    // 각 행의 합을 저장할 배열 동적 할당
    int* sum = new int[10];

    // 매트릭스 및 각 행의 합 초기화
    for (int i = 0; i < 10; i++)
    {
        *(sum + i) = 0;
        for (int j = 0; j < 10; j++)
        {
            *(*(mat + i) + j) = rand() % 101; // 0에서 100 사이의 랜덤한 값으로 초기화
            *(sum + i) += *(*(mat + i) + j); // 각 행의 합 계산
        }
    }

    // 원본 매트릭스 출력
    cout << "Original Matrix:\n";
    print_matrix(mat);

    // 행 기준 내림차순 정렬
    rows_Descending_sort(mat);
    cout << "Sort of Row (Descending Order):\n";
    print_marix(mat, sum);

    // 합 기준 오름차순 정렬
    sum_ascending_sort(mat, sum);
    cout << "Sort of Sum (Ascending Order):\n";
    print_marix(mat, sum);

    // 동적 할당된 메모리 해제
    for (int i = 0; i < 10; i++)
        delete[] * (mat + i);
    delete[] mat;
    delete[] sum;
    return 0;
}

// 매트릭스 출력 함수
void print_matrix(int** mat)
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
            cout << *(*(mat + i) + j) << "\t"; // 각 원소 출력
        cout << "\n";
    }
    cout << "\n";
}

// 매트릭스 및 각 행의 합 출력 함수
void print_marix(int** mat, int* sum)
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
            cout << *(*(mat + i) + j) << "\t"; // 각 원소 출력
        cout << "| Sum: " << *(sum + i); // 행의 합 출력
        cout << "\n";
    }
    cout << "\n";
}

// 행 기준 내림차순 정렬 함수
void rows_Descending_sort(int** mat)
{
    int tmp;
    for (int rows = 0; rows < 10; rows++)
    {
        for (int i = 0; i < 9; i++)
        {
            int k = i;//인덱스 저장
            for (int j = i + 1; j < 10; j++)//비교 loop
            {
                if (*(*(mat + rows) + k) < *(*(mat + rows) + j))//값 비교
                    k = j;
            }
            if (k != i)//인덱스 바뀌면
                SWP(*(*(mat + rows) + i), *(*(mat + rows) + k), tmp); // 교환 매크로 호출
        }
    }
}

// 합 기준 오름차순 정렬 함수
void sum_ascending_sort(int** mat, int* sum)
{
    for (int i = 0; i < 9; i++)
    {
        int k = i;//인덱스 저장
        for (int j = i + 1; j < 10; j++)
        {
            if (*(sum + k) > *(sum + j))//값 비교
                k = j;//인덱스 변화
        }
        if (k != i)//인덱스 바뀌면
        {
            int tmp;
            for (int j = 0; j < 10; j++)//각 열 스왑
                SWP(*(*(mat + i) + j), *(*(mat + k) + j), tmp); // 교환 매크로 호출
            SWP(*(sum + i), *(sum + k), tmp); // 행의 합도 교환
        }
    }
}

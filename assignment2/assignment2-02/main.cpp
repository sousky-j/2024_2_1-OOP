#include <iostream>
#include <ctime>
using namespace std;

// 함수 선언
void quick_sort(int* arr, int st, int en); // 퀵 정렬 함수 선언
void merge_sort(int* arr, int st, int en); // 병합 정렬 함수 선언
void merge(int* arr, int st, int en);
void my_insertion(int* arr, int en, int input);

int tmp[10]; // 임시 배열 선언

int main(void)
{
    // 시드 값 초기화
    int init = static_cast<unsigned int>(time(NULL)); // 현재 시간을 시드 값으로 초기화 설정
    srand(init); // 시드 값 설정

    // 배열 및 변수 초기화
    int* arr = new int[11]; // 배열 동적 할당
    int input, st = 0, en = 9; // 입력 변수 및 배열 범위 변수 선언 및 초기화

    // 무작위 값 생성
    cout << "Random values : ";
    for (int i = 0; i < 10; i++)
    {
        arr[i] = rand() % 101; // 0부터 100까지의 무작위 값 할당
        cout << " " << arr[i]; // 생성된 값 출력
    }
    cout << "\n";

    // 정렬 방법 선택
    cout << "Select sorting method (1: Quick Sort, 2: Merge Sort) : ";
    cin >> input; // 사용자 입력 받기

    // 선택된 정렬 방법에 따라 정렬 수행
    if (input == 1)
    {
        quick_sort(arr, 0, 10);//퀵 실행
        cout << "Sorted numbers (Quick Sort): ";
    }
    else if (input == 2)
    {
        merge_sort(arr, 0, 10);//머지 실행
        cout << "Sorted numbers (Merge Sort): ";
    }

    // 정렬된 배열 출력
    for (int i = 0; i < 10; i++)
        cout << " " << arr[i];
    cout << "\nEnter a value to search : ";
    cin >> input;

    // 이진 탐색 수행
    int mid = (st + en) / 2;
    while (1)
    {
        if (st > en)
        {
            my_insertion(arr, en, input); // 삽입 정렬 호출
            cout << "Updated numbers:";
            for (int i = 0; i < 11; i++)
                cout << " " << *(arr + i); // 업데이트된 배열 출력
            break;
        }
        else if (input == *(arr + mid))//입력값을 찾았을 때
        {
            cout << "Searched number index : " << mid;
            break;
        }
        else if (input > *(arr + mid))//입력값이 중간보다 클때
        {
            st = mid + 1;//시작점 변화
            mid = (st + en) / 2;//중간 변화
        }
        else if (input < *(arr + mid))//입력값이 중간보다 작을때
        {
            en = mid - 1;//끝점 변화
            mid = (st + en) / 2;//중간 변화
        }
    }
    return 0;
}


void merge_sort(int* arr, int st, int en)// 병합 정렬 함수 정의
{
    if (en == (st + 1))
        return;              // 기저 조건
    int mid = (st + en) / 2; // 중간 값 계산
    merge_sort(arr, st, mid);     // 재귀 호출
    merge_sort(arr, mid, en);     // 재귀 호출
    merge(arr, st, en);           // 병합 함수 호출
}

// 병합 함수 정의
void merge(int* arr, int st, int en)
{
    int mid = (st + en) / 2; // 중간 값 계산
    int idx1 = st;           // 시작 지점 초기화
    int idx2 = mid;          // 끝 지점 초기화
    for (int i = st; i < en; i++)
    {
        if (idx2 == en)
            tmp[i] = arr[idx1++]; // 두 번째 배열이 끝난 경우
        else if (idx1 == mid)
            tmp[i] = arr[idx2++]; // 첫 번째 배열이 끝난 경우
        else if (arr[idx1] <= arr[idx2])
            tmp[i] = arr[idx1++]; // 값 비교 후 삽입
        else
            tmp[i] = arr[idx2++]; // 값 비교 후 삽입
    }
    for (int i = st; i < en; i++) // 임시 배열에서 원래 배열로 이동
        arr[i] = tmp[i];
}

// 퀵 정렬 함수 정의
void quick_sort(int* arr, int st, int en)
{
    if (en <= st + 1) // 기저 조건
        return;
    int pivot = arr[st]; // 피벗 값 설정
    int id1 = st + 1;  // 인덱스 초기화
    int id2 = en - 1;  // 인덱스 초기화

    while (1)
    {
        while (id1 <= id2 && arr[id1] <= pivot)
            id1++; // 인덱스 이동
        while (id1 <= id2 && arr[id2] > pivot)
            id2--; // 인덱스 이동
        if (id1 > id2)
            break;// 반복 종료 조건
        // 값 비교 후 교환
        int temp = arr[id1];
        arr[id1] = arr[id2];
        arr[id2] = temp;
    }
    // 피벗과 피벗보다 작은 값의 교환
    int temp = arr[st];
    arr[st] = arr[id2];
    arr[id2] = temp;
    quick_sort(arr, st, id2);	 // 재귀 호출
    quick_sort(arr, id2 + 1, en); // 재귀 호출
}

// 삽입 정렬 함수 정의
void my_insertion(int* arr, int en, int input)
{
    for (int i = 10; i > en + 1; i--)
        *(arr + i) = *(arr + i - 1); // 원소 이동
    *(arr + en + 1) = input; // 값 삽입
}

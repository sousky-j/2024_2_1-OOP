#include <iostream>
#include <ctime>
using namespace std;

int main(void)
{
	int init = static_cast<unsigned int>(time(NULL)); //현재 시간을 시드값으로 초기화 설정
	srand(init);// 시드값 설정
	int input, min = 101, max = -1;//입력값, 최댓값, 최솟값 변수 선언
	int min_index = 0;//최솟값 인덱스 변수 선언
	int max_index = 0;//최댓값 인덱스 변수 선언
	cout << "Size of the array : ";//입력 요청 출력
	cin >> input;//사용자 입력
	int* arr = new int[input];//입력에 따른 배열 동적 할당
	cout << "Random numbers :";//출력 멘트 출력
	for (int i = 0; i < input; i++)//배열 순회 반복문
	{
		arr[i] = rand() % 101;//배열에 난수 입력
		cout << " " << arr[i];//입력된 난수 출력
	}
	for (int i = 0; i < input; i++)//배열 선형 탐색
	{
		if (min > arr[i])//최솟값 제어 조건
		{
			min = arr[i];//최솟값 변환
			min_index = i;//인덱스 변환
		}
		if (max < arr[i])//최댓값 제어 조건
		{
			max = arr[i];//최댓값 변환
			max_index = i;//인덱스 변환
		}
	}
	cout << "\n"<<"Maximum value : " << min << "\t, Address: " << arr + min_index << "\n";//최솟값과 인덱스 주소 출력
	cout << "Maximum value: " << max << "\t, Address: " << arr + max_index << "\n";//최댓값과 인덱스 주소 출력

	delete[] arr;//할당된 메모리 해제
	return 0;
}
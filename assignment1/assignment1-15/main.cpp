#include <iostream>
#include <ctime> //시드로 현재 시간 사용
using namespace std;

int main()
{
    int init = static_cast<unsigned int>(time(NULL)); //현재 시간을 시드값으로 초기화 설정
    srand(init); //랜덤 시드 설정

    int random[4] = { 10,10,10,10 }; //무작위 숫자를 저장할 배열, 초기화된 값은 범위를 벗어나는 임의의 값
    int save_index[4] = { 0 }; //입력된 추측 숫자와 비교할 때 이미 검사한 인덱스를 저장하는 배열
    char input[5]; //사용자가 입력할 숫자 배열 (+1은 null 문자를 저장할 공간)

    int tmp = 0, hit, blow; //임시 변수 및 hit, blow 개수를 저장할 변수 초기화
    //random 배열에 중복되지 않는 0부터 9까지의 무작위한 4자리 숫자 생성
    for (int i = 0; i < 4; i++)
    {
        tmp = rand() % 10; //0부터 9까지의 무작위 숫자 생성
        while (1)//중복되지 않는 값인지 확인
        {
            if (random[0] != tmp && random[1] != tmp && random[2] != tmp && random[3] != tmp)
            {
                random[i] = tmp; //중복되지 않는 경우 현재 인덱스에 값을 저장하고 반복문 종료
                break;
            }
            else
                tmp = rand() % 10; //중복된 경우 새로운 무작위 숫자 생성
        }
    }
    //사용자가 5번의 시도 동안 추측한 숫자와 비교하여 Hit과 Blow를 계산
    for (int i = 0; i < 5; i++)
    {
        cout << "Guess: ";
        cin >> input;
        cout << "\n\n";
        hit = 0, blow = 0; //Hit과 Blow 개수 초기화
        for (int j = 0; j < 4; j++) //hit 개수 체크 반복문
        {
            save_index[j] = 0; //인덱스 플래그 초기화
            if ((input[j] - '0') == random[j]) //같은 자리 값이 같은지 확인
            {
                hit++; //hit 개수 증가
                save_index[j]++; //현재 인덱스가 검사되었음을 표시
            }
        }
        for (int j = 0; j < 4; j++) //Blow 개수 체크 반복문
        {
            for (int k = 0; k < 4; k++)
            {
                if (((input[j] - '0') == random[k]) && (save_index[j] != 1))
                    blow++; //인덱스가 이미 검사되지 않았고, 값은 같은 경우 Blow 증가
            }
        }
        //결과 출력
        cout << "Hit: " << hit << ", Blow: " << blow << "\n\n";
        cout << "------------------\n\n";
        if (hit == 4) //모든 숫자를 맞춘 경우 승리 출력 후 반복문 종료
        {
            cout << "Win";
            break;
        }
    }
    if (hit != 4) //모든 시도에서 숫자를 맞추지 못한 경우 패배 출력과 정답 출력
    {
        cout << "Lose\n\n";
        cout << "the correct answer: ";
        for (int i = 0; i < 4; i++)
            cout << random[i];
    }
}

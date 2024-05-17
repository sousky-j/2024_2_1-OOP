#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

bool flag = false;//패배했는지 확인, true면 패배, false면 패배하지 않음, 게임을 졌는지 확인

class TaggerState//술래 상태
{
public:
    virtual void toward() = 0;//앞으로 가는 함수
};
class Back : public TaggerState//뒤를 보고 있을 때
{
public:
    void toward() override { flag = false; }//뒤를 보고 있을 때
};
class Front : public TaggerState//앞을 보고 있을 때
{
    void toward() override { flag = true; }//앞을 보고 있을 때
};

class Player
{
private:
    TaggerState* state;
    int progess;
public:
    Player() : state(NULL), progess(0)//생성자
    {//초기화
        this->state = NULL;
        progess = 0;
    }
    ~Player()//소멸자
    {//메모리 해제
        if (state != NULL)
            delete state;
    }
    void SetState()
    {
        static bool tmp_state = false;//임시 상태 변수
        static bool cur_state = false;//현재 상태 변수
        time_t current = time(NULL);//현재 시간 저장
        char* time_element = ctime(&current);//시간 요소 저장
        string time_str(time_element);//시간 문자열로 변환
        string sec = time_str.substr(17, 2);
        static int tmp = -1;//static 변수 선언 및 초기화, 초 측정, 1초가 지났는지 확인
        static int randn = -1;//랜덤 변수 선언 및 초기화, 랜덤 변수, 1초에 출력하는 횟수
        static int idx = 0;//인덱스 변수 선언 및 초기화, 문자열 인덱스, 출력할 문자열의 인덱스
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 }); //커서 위치 설정
        if (tmp_state)//알맞는 스테이트 찾아가기
        {
            cout << "Red Light!                                     \n"; //빨간불
            cout << "                                      \n";
            if (!cur_state) //지금 스테이트와 이전이 겹치지 않는다면
            {
                this->~Player(); //이전->제거, 새롭게 할당
                Front* front_state = new Front;//앞을 보고 있을 때
                state = front_state;//상태 저장
                cur_state = true; //지금 스테이트 저장
            }
            if (randn == -1) { //랜덤 난수 생성
                while (randn <= 1)
                    randn = rand() % 11;
            }
            if (tmp != stoi(sec)) //1초가 지날 때마다 실행
            {
                if (randn == 0) //시간이 전부 지나면
                {
                    randn = -1;
                    tmp_state = false; //스테이트 변경
                    cur_state = false;
                    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 }); //커서 이동
                    cout << "                                      \n";
                }
                else
                    randn--; //랜덤 난수만큼 반복
            }
        }
        else
        {
            if (!cur_state) //지금 스테이트와 이전이 겹치지 않는다면
            {
                this->~Player();//이전->제거, 새롭게 할당
                Back* back_state = new Back;
                state = back_state;
                cur_state = true; //지금 스테이트 저장
            }
            char green_time[20] = { "Green Light!" };
            randn = rand() % 6; //랜덤 난수 생성
            while (randn <= 1)
                randn = rand() % 6;
            if (tmp != stoi(sec)) //1초가 지난다면
            {
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { (short)idx, 0 }); //커서 이동
                cout << "                                      \n";
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { (short)idx, 0 }); //커서 이동
                for (int i = 0; i < randn; i++) //문자열의 끝에 도달할 때까지 차례대로 출력, 1초에 출력하는 횟수는 랜덤
                {
                    if (idx < strlen(green_time))
                    {
                        cout << green_time[idx];
                        idx++;
                    }
                }
                if (idx == strlen(green_time)) //전부 출력했다면
                {
                    randn = -1; //상태 변경
                    idx = 0;
                    cur_state = false;
                    tmp_state = true;
                }
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,1 }); //커서 이동
            }
        }
        tmp = stoi(sec); //초 측정
    }
   
    void toward()
    {
        state->toward();//앞으로 가는 함수
        this->progess++;
    }
    int GetProgress() { return progess; };
    TaggerState* GetState() { return state; }
};

int main() {

    Player player;
    cout << "==============================\n";
    cout << "    Red Light! Green Light!\n\n";
    cout << "        (Press any key)\n";
    cout << "==============================\n";
    while (!_kbhit());
   
    char tmp = _getch();
    short cursor = 0;

    while (1)
    {
        if (player.GetProgress() == 20)//게임 승리
        {
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 7 }); //커서 이동
            cout << "Win!!\n\n";
            cout << "exit the program";
            break;
        }
        if (flag == true)//게임 패배
        {
            cout<< "\n\n\n\n\n\n\n\n";
            cout << "lose..\n\n";
            cout<< "exit the program";
            break;
        }
        player.SetState();//스테이트 설정
        if (_kbhit())
        {
            tmp = _getch();//키보드 입력 빼기
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 1 }); //커서 이동
            cout << "\n\n";
            cout << "Forward.\n\n";
            player.toward();
        }
        //커서 이동
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 1 });//커서 이동
        cout << "                                      \n                                      \n";
        cout << "                                      \n                                      \n";
        cout << "start | ";
        for (int i = 0; i < player.GetProgress(); i++)//현재 상태 출력
            cout << "@@";
        for (int i = 0; i < 20 - player.GetProgress(); i++)//현재 상태 출력
            cout << "--";
        cout << " | end ";
        cout << " ( " << player.GetProgress() << "/20 )\n";//현재 상태 출력
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 1 });//커서 이동
    }
    return 0;
}
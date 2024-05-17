#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

bool flag = false;//�й��ߴ��� Ȯ��, true�� �й�, false�� �й����� ����, ������ ������ Ȯ��

class TaggerState//���� ����
{
public:
    virtual void toward() = 0;//������ ���� �Լ�
};
class Back : public TaggerState//�ڸ� ���� ���� ��
{
public:
    void toward() override { flag = false; }//�ڸ� ���� ���� ��
};
class Front : public TaggerState//���� ���� ���� ��
{
    void toward() override { flag = true; }//���� ���� ���� ��
};

class Player
{
private:
    TaggerState* state;
    int progess;
public:
    Player() : state(NULL), progess(0)//������
    {//�ʱ�ȭ
        this->state = NULL;
        progess = 0;
    }
    ~Player()//�Ҹ���
    {//�޸� ����
        if (state != NULL)
            delete state;
    }
    void SetState()
    {
        static bool tmp_state = false;//�ӽ� ���� ����
        static bool cur_state = false;//���� ���� ����
        time_t current = time(NULL);//���� �ð� ����
        char* time_element = ctime(&current);//�ð� ��� ����
        string time_str(time_element);//�ð� ���ڿ��� ��ȯ
        string sec = time_str.substr(17, 2);
        static int tmp = -1;//static ���� ���� �� �ʱ�ȭ, �� ����, 1�ʰ� �������� Ȯ��
        static int randn = -1;//���� ���� ���� �� �ʱ�ȭ, ���� ����, 1�ʿ� ����ϴ� Ƚ��
        static int idx = 0;//�ε��� ���� ���� �� �ʱ�ȭ, ���ڿ� �ε���, ����� ���ڿ��� �ε���
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 }); //Ŀ�� ��ġ ����
        if (tmp_state)//�˸´� ������Ʈ ã�ư���
        {
            cout << "Red Light!                                     \n"; //������
            cout << "                                      \n";
            if (!cur_state) //���� ������Ʈ�� ������ ��ġ�� �ʴ´ٸ�
            {
                this->~Player(); //����->����, ���Ӱ� �Ҵ�
                Front* front_state = new Front;//���� ���� ���� ��
                state = front_state;//���� ����
                cur_state = true; //���� ������Ʈ ����
            }
            if (randn == -1) { //���� ���� ����
                while (randn <= 1)
                    randn = rand() % 11;
            }
            if (tmp != stoi(sec)) //1�ʰ� ���� ������ ����
            {
                if (randn == 0) //�ð��� ���� ������
                {
                    randn = -1;
                    tmp_state = false; //������Ʈ ����
                    cur_state = false;
                    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,0 }); //Ŀ�� �̵�
                    cout << "                                      \n";
                }
                else
                    randn--; //���� ������ŭ �ݺ�
            }
        }
        else
        {
            if (!cur_state) //���� ������Ʈ�� ������ ��ġ�� �ʴ´ٸ�
            {
                this->~Player();//����->����, ���Ӱ� �Ҵ�
                Back* back_state = new Back;
                state = back_state;
                cur_state = true; //���� ������Ʈ ����
            }
            char green_time[20] = { "Green Light!" };
            randn = rand() % 6; //���� ���� ����
            while (randn <= 1)
                randn = rand() % 6;
            if (tmp != stoi(sec)) //1�ʰ� �����ٸ�
            {
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { (short)idx, 0 }); //Ŀ�� �̵�
                cout << "                                      \n";
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { (short)idx, 0 }); //Ŀ�� �̵�
                for (int i = 0; i < randn; i++) //���ڿ��� ���� ������ ������ ���ʴ�� ���, 1�ʿ� ����ϴ� Ƚ���� ����
                {
                    if (idx < strlen(green_time))
                    {
                        cout << green_time[idx];
                        idx++;
                    }
                }
                if (idx == strlen(green_time)) //���� ����ߴٸ�
                {
                    randn = -1; //���� ����
                    idx = 0;
                    cur_state = false;
                    tmp_state = true;
                }
                SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,1 }); //Ŀ�� �̵�
            }
        }
        tmp = stoi(sec); //�� ����
    }
   
    void toward()
    {
        state->toward();//������ ���� �Լ�
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
        if (player.GetProgress() == 20)//���� �¸�
        {
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 7 }); //Ŀ�� �̵�
            cout << "Win!!\n\n";
            cout << "exit the program";
            break;
        }
        if (flag == true)//���� �й�
        {
            cout<< "\n\n\n\n\n\n\n\n";
            cout << "lose..\n\n";
            cout<< "exit the program";
            break;
        }
        player.SetState();//������Ʈ ����
        if (_kbhit())
        {
            tmp = _getch();//Ű���� �Է� ����
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 1 }); //Ŀ�� �̵�
            cout << "\n\n";
            cout << "Forward.\n\n";
            player.toward();
        }
        //Ŀ�� �̵�
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 1 });//Ŀ�� �̵�
        cout << "                                      \n                                      \n";
        cout << "                                      \n                                      \n";
        cout << "start | ";
        for (int i = 0; i < player.GetProgress(); i++)//���� ���� ���
            cout << "@@";
        for (int i = 0; i < 20 - player.GetProgress(); i++)//���� ���� ���
            cout << "--";
        cout << " | end ";
        cout << " ( " << player.GetProgress() << "/20 )\n";//���� ���� ���
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0, 1 });//Ŀ�� �̵�
    }
    return 0;
}
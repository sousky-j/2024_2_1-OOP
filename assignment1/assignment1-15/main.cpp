#include <iostream>
#include <ctime> //�õ�� ���� �ð� ���
using namespace std;

int main()
{
    int init = static_cast<unsigned int>(time(NULL)); //���� �ð��� �õ尪���� �ʱ�ȭ ����
    srand(init); //���� �õ� ����

    int random[4] = { 10,10,10,10 }; //������ ���ڸ� ������ �迭, �ʱ�ȭ�� ���� ������ ����� ������ ��
    int save_index[4] = { 0 }; //�Էµ� ���� ���ڿ� ���� �� �̹� �˻��� �ε����� �����ϴ� �迭
    char input[5]; //����ڰ� �Է��� ���� �迭 (+1�� null ���ڸ� ������ ����)

    int tmp = 0, hit, blow; //�ӽ� ���� �� hit, blow ������ ������ ���� �ʱ�ȭ
    //random �迭�� �ߺ����� �ʴ� 0���� 9������ �������� 4�ڸ� ���� ����
    for (int i = 0; i < 4; i++)
    {
        tmp = rand() % 10; //0���� 9������ ������ ���� ����
        while (1)//�ߺ����� �ʴ� ������ Ȯ��
        {
            if (random[0] != tmp && random[1] != tmp && random[2] != tmp && random[3] != tmp)
            {
                random[i] = tmp; //�ߺ����� �ʴ� ��� ���� �ε����� ���� �����ϰ� �ݺ��� ����
                break;
            }
            else
                tmp = rand() % 10; //�ߺ��� ��� ���ο� ������ ���� ����
        }
    }
    //����ڰ� 5���� �õ� ���� ������ ���ڿ� ���Ͽ� Hit�� Blow�� ���
    for (int i = 0; i < 5; i++)
    {
        cout << "Guess: ";
        cin >> input;
        cout << "\n\n";
        hit = 0, blow = 0; //Hit�� Blow ���� �ʱ�ȭ
        for (int j = 0; j < 4; j++) //hit ���� üũ �ݺ���
        {
            save_index[j] = 0; //�ε��� �÷��� �ʱ�ȭ
            if ((input[j] - '0') == random[j]) //���� �ڸ� ���� ������ Ȯ��
            {
                hit++; //hit ���� ����
                save_index[j]++; //���� �ε����� �˻�Ǿ����� ǥ��
            }
        }
        for (int j = 0; j < 4; j++) //Blow ���� üũ �ݺ���
        {
            for (int k = 0; k < 4; k++)
            {
                if (((input[j] - '0') == random[k]) && (save_index[j] != 1))
                    blow++; //�ε����� �̹� �˻���� �ʾҰ�, ���� ���� ��� Blow ����
            }
        }
        //��� ���
        cout << "Hit: " << hit << ", Blow: " << blow << "\n\n";
        cout << "------------------\n\n";
        if (hit == 4) //��� ���ڸ� ���� ��� �¸� ��� �� �ݺ��� ����
        {
            cout << "Win";
            break;
        }
    }
    if (hit != 4) //��� �õ����� ���ڸ� ������ ���� ��� �й� ��°� ���� ���
    {
        cout << "Lose\n\n";
        cout << "the correct answer: ";
        for (int i = 0; i < 4; i++)
            cout << random[i];
    }
}

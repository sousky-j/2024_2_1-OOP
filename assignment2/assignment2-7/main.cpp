#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

int my_atoi(const char* arr);

// ��� Ŭ���� ����
class node
{
public:
    double val; // ��� ��
    char oper;  // ��� ������
    node* next; // ���� ��� ������
    node* prev; // ���� ��� ������

    // ��� ������
    node()
    {
        val = 0;
        oper = 0;
        next = NULL;
        prev = NULL;
    }

    // ��� �Ҹ���
    ~node()
    {
        next = NULL;
        prev = NULL;
    }
};

// ���� Ŭ���� ����
class stack
{
private:
    node* head; // ������ ù ��° ���
    node* tail; // ������ ������ ���
    int num = 0; // ������ ũ��
public:
    // ���� ������
    stack() {
        head = NULL;
        tail = NULL;
    }

    // ���� �Ҹ���
    ~stack() {
        while (head != NULL)
        {
            tail = head;
            head = head->next;
            delete tail;
        }
    }

    // ���ڸ� ���ÿ� �߰��ϴ� �Լ�
    void push(double a)
    {
        node* new_node = new node;
        new_node->val = a;
        new_node->next = NULL;
        new_node->prev = NULL;
        if (head == NULL)
        {
            head = new_node;
            tail = head;
            tail->prev = NULL;
        }
        else
        {
            new_node->prev = tail;
            tail = new_node;
            new_node->next = NULL;
        }
        this->num++;
    }

    // �����ڸ� ���ÿ� �߰��ϴ� �Լ�
    void push(char a)
    {
        node* new_node = new node;
        new_node->oper = a;
        new_node->next = NULL;
        new_node->prev = NULL;

        if (head == NULL)
        {
            head = new_node;
            tail = head;
            tail->prev = NULL;
        }
        else
        {
            new_node->prev = tail;
            tail = new_node;
            new_node->next = NULL;
        }
        this->num++;
    }

    // ���ÿ��� ��Ҹ� �����ϴ� �Լ�
    void pop()
    {
        if (head == NULL)
        {
            cout << "-1\n"; // ������ ����ִ� ��� ���� �޽��� ���
        }
        else if (tail != head)
        {
            tail = tail->prev;
            delete tail->next;
            tail->next = NULL;
            this->num--;
        }
        else if (head == tail)
        {
            delete tail;
            head = NULL;
            tail = NULL;
            this->num--;
        }
    }

    // ������ ũ�⸦ ��ȯ�ϴ� �Լ�
    int size()
    {
        return this->num;
    }

    // ������ ����ִ��� Ȯ���ϴ� �Լ�
    bool empty()
    {
        if (num == 0)
            return 1;
        else
            return 0;
    }

    // ������ �� �� ����� �����ڸ� ��ȯ�ϴ� �Լ�
    char gettop()
    {
        return this->tail->oper;
    }

    // ������ �� �� ����� ���� ��ȯ�ϴ� �Լ�
    double getval()
    {
        return this->tail->val;
    }
};

int main(void)
{
    stack a; // ���� ǥ����� ���� ǥ������� ��ȯ�� �� ����� ������ ���� ����
    char input[101]; // �Է� �迭, ���� ǥ��� -> ���� ǥ���
    stack b; // ���� ǥ����� ������ �� ����� ���� ����
    char reward[50][4]{}; // ���� ǥ����� ������ �� ���� �迭
    char oper[6] = { '+', '-', '*', '/', '(', ')' }; // ���Ǵ� ������ �� ��ȣ
    char num[4] = {};
    int reward_size = 0; // ���� ǥ��� �迭�� ũ��
    cin.getline(input, 100); // ����ڷκ��� �Է� ����
    int i = 0;
    // �Է� �迭�� ��ȸ�ϸ� ó��
    while (input[i] != '\0')
    {
        if (input[i] == ' ')
        {
            i++;
            continue;
        }
        // ������ ���
        if (input[i] >= 48 && input[i] <= 57)
        {
            reward[reward_size][0] = input[i];
            reward[reward_size][1] = '\0';
            if (input[i + 1] != NULL)//���� ���� ĭ Ȯ��
            {
                if (input[i + 1] >= 48 && input[i + 1] <= 57)//��������
                {
                    reward[reward_size][1] = input[i + 1];//���ڸ� ����
                    reward[reward_size][2] = '\0';
                    i++;
                }
            }
            if (input[i + 1] != NULL)//���� ���� ���� ĭ Ȯ��
            {
                if (input[i + 1] >= 48 && input[i + 1] <= 57)//��������
                {
                    reward[reward_size][2] = input[i + 1];
                    reward[reward_size][3] = '\0';
                    i++;
                }
            }
            reward_size++;
        }
        else
        {
            // �����ڳ� ��ȣ�� ���
            if (a.empty()) // ������ ����ִ� ���
                a.push(input[i]);
            else if (input[i] == oper[4]) // ���� ��ȣ�� ���
                a.push(input[i]);
            else if (a.gettop() == oper[4] && input[i] != oper[5]) // ������ top�� ���� ��ȣ�̰� ���� �ݴ� ��ȣ�� �ƴ� ���
                a.push(input[i]);
            else if (input[i] == oper[5]) // �ݴ� ��ȣ�� ���
            {
                while (a.gettop() != oper[4]) // ���� ��ȣ�� ���� ������
                {
                    reward[reward_size][0] = a.gettop(); // ���ÿ� �ִ� �����ڸ� ���� ǥ�� �迭�� �߰�
                    reward[reward_size][1] = '\0';
                    reward_size++; // ���� ǥ�� �迭 ũ�� ����
                    a.pop(); // ���ÿ��� pop
                }
                a.pop(); // ���� ��ȣ '(' �� pop
            }
            else if ((input[i] == oper[2] || input[i] == oper[3])) // ���ϱ� �Ǵ� �������� ���
            {
                if ((a.gettop() == oper[0] || a.gettop() == oper[1])) // ���ϱ⳪ ������ ���
                    a.push(input[i]);
                else // ���ϱ⳪ �������� ���
                {
                    while (!a.empty()) // ������ ������� ���� ����
                    {
                        if (a.gettop() == oper[2] || a.gettop() == oper[3]) // top�� ���ϱ⳪ �����Ⱑ �ƴ� ���
                            break;
                        reward[reward_size][0] = a.gettop(); // ���ÿ� �ִ� ���� �迭�� �߰�
                        reward[reward_size][1] = '\0';
                        reward_size++; // �迭 ũ�� ����
                        a.pop(); // pop
                    }
                    reward[reward_size][0] = a.gettop(); // ���ÿ� �ִ� ���� �迭�� �߰�
                    reward[reward_size][1] = '\0';
                    reward_size++; // �迭 ũ�� ����
                    a.pop(); // pop
                    a.push(input[i]); // �����ڸ� ���ÿ� push
                }
            }
            else if ((input[i] == oper[0] || input[i] == oper[1])) // ���ϱ� �Ǵ� ������ ���
            {
                while (!a.empty()) // ������ ������� ���� ����
                {
                    if (a.gettop() == oper[4]) // top�� ���� ��ȣ�� ���
                        break;
                    reward[reward_size][0] = a.gettop(); // ���ÿ� �ִ� ���� �迭�� �߰�
                    reward[reward_size][1] = '\0';
                    reward_size++; // �迭 ũ�� ����
                    a.pop(); // pop
                }
                a.push(input[i]); // �����ڸ� ���ÿ� push
            }
        }
        i++;
    }

    // ���ÿ� ���� �����ڵ��� ���� ǥ��� �迭�� �߰�
    while (!a.empty())
    {
        reward[reward_size][0] = a.gettop();
        reward[reward_size][1] = '\0';
        reward_size++;
        a.pop();
    }

    i = 0;
    // ���� ǥ��� �迭�� ��ȸ�ϸ� ���
    while (reward[i][0] != NULL)
    {
        if (reward[i][0] >= 48 && reward[i][0] <= 57) // ������ ���
        {
            double tmp = my_atoi(reward[i]); // ���ڷ� ��ȯ
            b.push(tmp); // ���ÿ� push
        }
        else // �������� ���
        {
            double back = b.getval(); // ������ �� �� ����
            b.pop();
            double front = b.getval(); // ������ �� ���� ����
            b.pop();
            if (reward[i][0] == oper[0]) // ���ϱ�
            {
                double tmp = front + back;
                b.push(tmp);
            }
            else if (reward[i][0] == oper[1]) // ����
            {
                double tmp = front - back;
                b.push(tmp);
            }
            else if (reward[i][0] == oper[2]) // ���ϱ�
            {
                double tmp = front * back;
                b.push(tmp);
            }
            else if (reward[i][0] == oper[3]) // ������
            {
                double tmp = front / back;
                b.push(tmp);
            }
        }
        i++;
    }
    int print_num = b.getval();
    if (b.getval() > 0)//����� 0���� ũ�� 0.5 ���� �ݿø�
        print_num = b.getval() + 0.5;
    else if (b.getval() < 0)//����� 0���� ������ 0.5�� �� �ݿø�
        print_num = b.getval() - 0.5;
    cout << "Result : " << print_num; // �����
    return 0;
}

// ���ڿ��� ������ ��ȯ�ϴ� �Լ�
int my_atoi(const char* arr)
{
    int sum = 0, i = 0;
    while (arr[i] != '\0')
    {
        sum *= 10;//���� ����� 10����
        sum += arr[i] - '0';
        i++;
    }
    return sum;
}

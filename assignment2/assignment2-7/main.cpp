#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

int my_atoi(const char* arr);

// 노드 클래스 정의
class node
{
public:
    double val; // 노드 값
    char oper;  // 노드 연산자
    node* next; // 다음 노드 포인터
    node* prev; // 이전 노드 포인터

    // 노드 생성자
    node()
    {
        val = 0;
        oper = 0;
        next = NULL;
        prev = NULL;
    }

    // 노드 소멸자
    ~node()
    {
        next = NULL;
        prev = NULL;
    }
};

// 스택 클래스 정의
class stack
{
private:
    node* head; // 스택의 첫 번째 노드
    node* tail; // 스택의 마지막 노드
    int num = 0; // 스택의 크기
public:
    // 스택 생성자
    stack() {
        head = NULL;
        tail = NULL;
    }

    // 스택 소멸자
    ~stack() {
        while (head != NULL)
        {
            tail = head;
            head = head->next;
            delete tail;
        }
    }

    // 숫자를 스택에 추가하는 함수
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

    // 연산자를 스택에 추가하는 함수
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

    // 스택에서 요소를 제거하는 함수
    void pop()
    {
        if (head == NULL)
        {
            cout << "-1\n"; // 스택이 비어있는 경우 에러 메시지 출력
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

    // 스택의 크기를 반환하는 함수
    int size()
    {
        return this->num;
    }

    // 스택이 비어있는지 확인하는 함수
    bool empty()
    {
        if (num == 0)
            return 1;
        else
            return 0;
    }

    // 스택의 맨 위 요소의 연산자를 반환하는 함수
    char gettop()
    {
        return this->tail->oper;
    }

    // 스택의 맨 위 요소의 값을 반환하는 함수
    double getval()
    {
        return this->tail->val;
    }
};

int main(void)
{
    stack a; // 중위 표기식을 후위 표기식으로 변환할 때 사용할 연산자 저장 스택
    char input[101]; // 입력 배열, 중위 표기식 -> 후위 표기식
    stack b; // 후위 표기식을 연산할 때 사용할 숫자 스택
    char reward[50][4]{}; // 후위 표기식을 연산할 때 과정 배열
    char oper[6] = { '+', '-', '*', '/', '(', ')' }; // 허용되는 연산자 및 괄호
    char num[4] = {};
    int reward_size = 0; // 후위 표기식 배열의 크기
    cin.getline(input, 100); // 사용자로부터 입력 받음
    int i = 0;
    // 입력 배열을 순회하며 처리
    while (input[i] != '\0')
    {
        if (input[i] == ' ')
        {
            i++;
            continue;
        }
        // 숫자인 경우
        if (input[i] >= 48 && input[i] <= 57)
        {
            reward[reward_size][0] = input[i];
            reward[reward_size][1] = '\0';
            if (input[i + 1] != NULL)//숫자 다음 칸 확인
            {
                if (input[i + 1] >= 48 && input[i + 1] <= 57)//숫자인지
                {
                    reward[reward_size][1] = input[i + 1];//숫자면 대입
                    reward[reward_size][2] = '\0';
                    i++;
                }
            }
            if (input[i + 1] != NULL)//숫자 다음 다음 칸 확인
            {
                if (input[i + 1] >= 48 && input[i + 1] <= 57)//숫자인지
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
            // 연산자나 괄호인 경우
            if (a.empty()) // 스택이 비어있는 경우
                a.push(input[i]);
            else if (input[i] == oper[4]) // 여는 괄호인 경우
                a.push(input[i]);
            else if (a.gettop() == oper[4] && input[i] != oper[5]) // 스택의 top이 여는 괄호이고 들어갈게 닫는 괄호가 아닌 경우
                a.push(input[i]);
            else if (input[i] == oper[5]) // 닫는 괄호인 경우
            {
                while (a.gettop() != oper[4]) // 여는 괄호가 나올 때까지
                {
                    reward[reward_size][0] = a.gettop(); // 스택에 있는 연산자를 후위 표기 배열에 추가
                    reward[reward_size][1] = '\0';
                    reward_size++; // 후위 표기 배열 크기 증가
                    a.pop(); // 스택에서 pop
                }
                a.pop(); // 여는 괄호 '(' 를 pop
            }
            else if ((input[i] == oper[2] || input[i] == oper[3])) // 곱하기 또는 나누기인 경우
            {
                if ((a.gettop() == oper[0] || a.gettop() == oper[1])) // 더하기나 빼기인 경우
                    a.push(input[i]);
                else // 곱하기나 나누기인 경우
                {
                    while (!a.empty()) // 스택이 비어있지 않은 동안
                    {
                        if (a.gettop() == oper[2] || a.gettop() == oper[3]) // top이 곱하기나 나누기가 아닌 경우
                            break;
                        reward[reward_size][0] = a.gettop(); // 스택에 있는 것을 배열에 추가
                        reward[reward_size][1] = '\0';
                        reward_size++; // 배열 크기 증가
                        a.pop(); // pop
                    }
                    reward[reward_size][0] = a.gettop(); // 스택에 있는 것을 배열에 추가
                    reward[reward_size][1] = '\0';
                    reward_size++; // 배열 크기 증가
                    a.pop(); // pop
                    a.push(input[i]); // 연산자를 스택에 push
                }
            }
            else if ((input[i] == oper[0] || input[i] == oper[1])) // 더하기 또는 빼기인 경우
            {
                while (!a.empty()) // 스택이 비어있지 않은 동안
                {
                    if (a.gettop() == oper[4]) // top이 여는 괄호인 경우
                        break;
                    reward[reward_size][0] = a.gettop(); // 스택에 있는 것을 배열에 추가
                    reward[reward_size][1] = '\0';
                    reward_size++; // 배열 크기 증가
                    a.pop(); // pop
                }
                a.push(input[i]); // 연산자를 스택에 push
            }
        }
        i++;
    }

    // 스택에 남은 연산자들을 후위 표기식 배열에 추가
    while (!a.empty())
    {
        reward[reward_size][0] = a.gettop();
        reward[reward_size][1] = '\0';
        reward_size++;
        a.pop();
    }

    i = 0;
    // 후위 표기식 배열을 순회하며 계산
    while (reward[i][0] != NULL)
    {
        if (reward[i][0] >= 48 && reward[i][0] <= 57) // 숫자인 경우
        {
            double tmp = my_atoi(reward[i]); // 숫자로 변환
            b.push(tmp); // 스택에 push
        }
        else // 연산자인 경우
        {
            double back = b.getval(); // 스택의 맨 위 숫자
            b.pop();
            double front = b.getval(); // 스택의 그 다음 숫자
            b.pop();
            if (reward[i][0] == oper[0]) // 더하기
            {
                double tmp = front + back;
                b.push(tmp);
            }
            else if (reward[i][0] == oper[1]) // 빼기
            {
                double tmp = front - back;
                b.push(tmp);
            }
            else if (reward[i][0] == oper[2]) // 곱하기
            {
                double tmp = front * back;
                b.push(tmp);
            }
            else if (reward[i][0] == oper[3]) // 나누기
            {
                double tmp = front / back;
                b.push(tmp);
            }
        }
        i++;
    }
    int print_num = b.getval();
    if (b.getval() > 0)//결과가 0보다 크면 0.5 더해 반올림
        print_num = b.getval() + 0.5;
    else if (b.getval() < 0)//결과가 0보다 작으면 0.5를 빼 반올림
        print_num = b.getval() - 0.5;
    cout << "Result : " << print_num; // 결과값
    return 0;
}

// 문자열을 정수로 변환하는 함수
int my_atoi(const char* arr)
{
    int sum = 0, i = 0;
    while (arr[i] != '\0')
    {
        sum *= 10;//기존 결과에 10곱함
        sum += arr[i] - '0';
        i++;
    }
    return sum;
}

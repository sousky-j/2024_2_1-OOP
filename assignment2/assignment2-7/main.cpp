#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

typedef struct _node
{
    int val;
    _node* next;
    _node* prev;
}node;

class stack
{
private:
    node* head;
    node* tail;
    int siz = 0;
public:
    stack() {
        head = NULL;
        tail = NULL;
    }
    ~stack() {
        while (head != NULL)
        {
            tail = head;
            head = head->next;
            delete tail;
        }
    }
    void push(int a);
    void pop();
    void size();
    void empty();
    void top();
};

int main(void)
{
    return 0;
}

void stack::push(int a)
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
        tail->next = new_node;
        tail->next->prev = tail;
        tail = tail->next;
    }
    siz++;
}

void stack::pop()
{
    if (head == NULL)
    {
        cout << "-1\n";
    }
    else if (tail != head)
    {
        cout << tail->val << "\n";

        tail = tail->prev;
        delete tail->next;
        tail->next = NULL;
        siz--;
    }
    else if (head == tail)
    {
        cout << tail->val << "\n";
        delete tail;
        head = NULL;
        tail = NULL;
        siz--;
    }
}

void stack::size()
{
    cout << siz << "\n";
}

void stack::empty()
{
    if (siz == 0)
        cout << "1" << "\n";
    else
        cout << "0" << "\n";
}

void stack::top()
{
    if (tail != NULL)
        cout << tail->val << "\n";
    else
        cout << "-1\n";
}
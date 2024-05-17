#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <ctime>
#include <string>

using namespace std;
class node
{
private:
	int data;
	int index;
	node* next;
public:
	node(int data, int index)
	{
		this->data = data;
		this->index = index;
		this->next = NULL;
	}
	~node()
	{
		this->data = 0;
		this->index = 0;
		this->next = NULL;
	}
	void setnext(node* next) { this->next = next; }
	void setdata(int trans) { this->data = trans; }
	int getdata() const { return this->data; }
	int getindex() const { return this->index; }
	node* getnext() { return this->next; }
};

class list
{
private:
	node* head;
	node* tail;//끊길 때 메모리 해제를 위한 포인터
	node* tmp;
	node* pre;
public:
	list()
	{
		head = nullptr;
		tail = nullptr;
		tmp = nullptr;
		pre = nullptr;
	}
	~list()
	{
		if (tail == NULL)
		{
			tmp = head;
			for (int i = 0; i < 9; i++)
			{
				pre = tmp;
				tmp = tmp->getnext();
				delete pre;
			}
			delete tmp;
		}
		else
		{
			tmp = tail;
			for (int i = 0; i < 9; i++)
			{
				pre = tmp;
				tmp = tmp->getnext();
				delete pre;
			}
			delete tmp;
		}
	}
	void initialize(int* val)
	{
		for (int i = 0; i < 10; i++)
		{
			node* new_node = new node(val[i], i);
			if (head == NULL)
				head = new_node;
			else
			{
				tmp = head;
				for (int j = 0; j < i-1; j++)
					tmp = tmp->getnext();
				tmp->setnext(new_node);
				new_node->setnext(NULL);
			}
		}
		tmp = head;
		while (tmp->getnext() != NULL)
			tmp = tmp->getnext();
		tmp->setnext(head);
	}
	bool transfer(int id1, int id2)
	{
		int val;
		tmp = head;
		while (tmp->getindex() != id1)
		{
			if (probabilitic_disconnected_func())
			{
				tail = tmp->getnext();
				cout << "Output 	: Detected a disconnection between " << tmp->getindex() << " and " << tmp->getnext()->getindex() << "\n";
				tmp->setnext(NULL);
				return 1;
			}
			tmp = tmp->getnext();
		}
		val = tmp->getdata();
		while (tmp->getindex() != id2)
			tmp = tmp->getnext();
		tmp->setdata(val);
		return 0;
	}
	void print()
	{
		tmp = head;
		cout << "Output 	:";
		while (1)
		{
			cout << " " << tmp->getdata();
			tmp = tmp->getnext();
			if (tmp->getindex() == 0)
				break;
		}
		cout << "\n";
	}
	bool probabilitic_disconnected_func()
	{
		int out = rand() % 10;
		if (!out)	return true;
		else	return false;
	}
};

int main()
{
	list a;
	string input;
	string command[4] = { "initialize","transfer","print","exit" };
	int val[10]{};
	int id1, id2;
	string sub_input;
	while (1)
	{
		cout << "Command : ";
		cin >> input;
		if (!input.compare(command[0]))
		{
			for (int i = 0; i < 10; i++)
				cin >> val[i];
			a.initialize(val);
		}
		else if (!input.compare(command[1]))
		{
			cin >> id1 >> sub_input >> id2;
			if (sub_input.compare("to"))
				continue;
			if (a.transfer(id1, id2))
				return 0;
		}
		else if (!input.compare(command[2])) a.print();
		else if (!input.compare(command[3])) break;
	}
	return 0;
}
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;

class node
{
private:
	int num;
	node* next;
public:
	node(int num)
	{
		this->next = NULL;
		this->setnum(num);
	}
	~node()
	{
		this->next = NULL;
	}

	int getnum() { return this->num; }
	node* getnext() { return this->next; }

	void setnum(int num) { this->num = num; }
	void setnext(node* next) { this->next = next; }
};

class list
{
private:
	node* head;
	node* tail;
public:
	list()
	{
		this->head = NULL;
		this->tail = NULL;
	}
	~list()
	{
		node* prev;
		while (head->getnext() != NULL)
		{
			prev = head;
			head = head->getnext();
			delete prev;
		}
		delete head;
	}
	void setnode(int num)
	{
		node* new_node = new node(num);
		if (head == NULL)
		{
			head = new_node;
			tail = head;
		}
		else
		{
			new_node->setnext(head);
			head = new_node;
		}
	}
	void print()
	{
		node* tmp = head;
		cout << "Linked list : ";
		if (tmp->getnext() != NULL)
		{
			cout << tmp->getnum();
			tmp = tmp->getnext();
		}
		else
		{
			cout << tmp->getnum() << "\n";
			return;
		}
		while (tmp != NULL)
		{
			cout << " -> " << tmp->getnum();
			tmp = tmp->getnext();
		}
		cout << "\n";
	}
	void del(int num)
	{
		node* tmp = NULL;
		if (head->getnum()==num)
		{
			tmp = head;
			head = head->getnext();
			delete tmp;
		}
		else
		{
			node* pre = head;
			tmp = pre->getnext();
			while (tmp != NULL)
			{
				if (tmp->getnum() == num)
				{
					if (pre->getnext() != NULL)
						pre->setnext(tmp->getnext());
					delete tmp;
					break;
				}
				pre = pre->getnext();
				tmp = pre->getnext();
			}
		}
	}
};

int my_strcmp(const char* input, const  char* command);

int main()
{
	int num = 0;
	char command[20] = {};
	list a;

	while (1)
	{
		cin >> command;
		if (my_strcmp(command, "insert"))
		{
			cin >> num;
			a.setnode(num);
			a.print();
		}
		else if (my_strcmp(command, "delete"))
		{
			cin >> num;
			a.del(num);
			a.print();
		}
		else if (my_strcmp(command, "exit"))
		{
			break;
		}
		else
		{
			cout << "error command\n";
		}
	}
	return 0;
}

int my_strcmp(const char* input, const  char* command)
{
	for (int i = 0; input[i] != '\0'; i++)
	{
		if (input[i] != command[i])
			return 0;
	}
	return 1;
}
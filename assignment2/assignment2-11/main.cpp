#define _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

class node  // ���� ����Ʈ�� ���� ��Ҹ� ��Ÿ���� 'node' Ŭ������ ����
{
private:  // ����� ��� ������ ������ �� �ִ� ���� ������
	int num;  // ����� ���� �����ϴ� ���� ����
	node* next;  // ���� ����Ʈ���� ���� ��带 ����Ű�� ������
public:  // ���� ��� �Լ��� ������ �� �ִ� ���� ������
	node(int num)  // �־��� ���ڷ� ��带 �ʱ�ȭ�ϴ� ������
	{
		this->next = NULL;  // 'next' �����͸� NULL�� �ʱ�ȭ
		this->setnum(num);  // ���� �����ϴ� ��� �Լ��� ȣ��
	}
	~node()  // ��尡 ������ �޸𸮸� �����ϴ� �Ҹ���
	{
		this->next = NULL;  // �Ŵ޸� �����͸� NULL�� �����Ͽ� ��۸� �����͸� ����
	}

	int getnum() { return this->num; }  // 'num' ���� ��ȯ�ϴ� ��� �Լ�
	node* getnext() { return this->next; }  // ���� ��带 ����Ű�� �����͸� ��ȯ�ϴ� ��� �Լ�

	void setnum(int num) { this->num = num; }  // 'num' ���� �����ϴ� ��� �Լ�
	void setnext(node* next) { this->next = next; }  // ���� ��带 �����ϴ� ��� �Լ�
};

class list  // ���� ����Ʈ�� �����ϴ� 'list' Ŭ������ ����
{
private:  // ����� ��� ������ ������ �� �ִ� ���� ������
	node* head;  // ���� ����Ʈ�� ù ��° ��带 ����Ű�� ������
	node* tail;  // ���� ����Ʈ�� ������ ��带 ����Ű�� ������
public:  // ���� ��� �Լ��� ������ �� �ִ� ���� ������
	list()  // �� ����Ʈ�� �ʱ�ȭ�ϴ� ������
	{
		this->head = NULL;  // 'head' �����͸� NULL�� �ʱ�ȭ
		this->tail = NULL;  // 'tail' �����͸� NULL�� �ʱ�ȭ
	}
	~list()  // ����Ʈ�� �ִ� ��� ��尡 ������ �޸𸮸� �����ϴ� �Ҹ�����
	{
		node* prev;  // ��ȸ �� ���� ��带 �����ϴ� ������
		if (head == NULL)  // ����Ʈ�� �̹� ��� �ִ��� Ȯ��
			return;  // �׷��ٸ� �߰� �۾� ���� ��ȯ
		while (head->getnext() != NULL)  // �� ��° ������ ������ ����Ʈ�� ��ȸ
		{
			prev = head;  // ���� ��带 ���� ���� �����մϴ�.
			head = head->getnext();  // ���� ���� �̵��մϴ�.
			delete prev;  // ���� ��带 �����մϴ�.
		}
		delete head;  // ���� ������ ��带 �����մϴ�.
	}
	void setnode(int num)  // �־��� ���ڷ� �� ��带 ����Ʈ�� ���ۿ� �����ϴ� ��� �Լ�
	{
		node* new_node = new node(num);  // �־��� ���ڷ� �� ��带 ����
		if (head == NULL)  // ����Ʈ�� ��� �ִ��� Ȯ��
		{
			head = new_node;  // �� ��带 head�� �����մϴ�.
			tail = head;  // tail�� head�� �����մϴ�.
		}
		else  // �׷��� �ʴٸ� ����Ʈ�� �̹� �����մϴ�.
		{
			new_node->setnext(head);  // �� ����� ���� ��带 ���� head�� �����մϴ�.
			head = new_node;  // �� ��带 ���ο� head�� �����մϴ�.
		}
	}
	void print()  // ����Ʈ�� ����ϴ� ��� �Լ��Դϴ�.
	{
		node* tmp = head;  // ���� ��带 �����ϱ� ���� �ӽ� �������Դϴ�.
		cout << "Linked list : ";  // ���� ����Ʈ�� ��Ÿ���� ���ڿ��� ����մϴ�.
		if (head == NULL)  // ����Ʈ�� ��� �ִ��� Ȯ���մϴ�.
		{
			cout << "\n";  // ��� �ִٸ� �����մϴ�.
			return;  // �߰� �۾� ���� ��ȯ�մϴ�.
		}
		if (tmp->getnext() != NULL)  // ���� ��尡 ������ ��尡 �ƴ��� Ȯ��
		{
			cout << tmp->getnum();  // ���� ����� ���� ���
			tmp = tmp->getnext();  // ���� ���� �̵�
		}
		else  // ���� ��尡 ������ �����
		{
			cout << tmp->getnum() << "\n";  // ���� ����� ���� ����ϰ� �����մϴ�.
			return;  // �߰� �۾� ���� ��ȯ�մϴ�.
		}
		while (tmp != NULL)  // ����Ʈ�� ��� ��带 ����մϴ�.
		{
			cout << " -> " << tmp->getnum();  // ���� ����� ���� ����մϴ�.
			tmp = tmp->getnext();  // ���� ���� �̵��մϴ�.
		}
		cout << "\n";  // ����� �������ϱ� ���� �����մϴ�.
	}
	void del(int num)  // �־��� ���ڿ� ��ġ�ϴ� ��带 �����ϴ� ��� �Լ��Դϴ�.
	{
		node* tmp = NULL;  // ������ ��带 �����ϱ� ���� �ӽ� �������Դϴ�.
		if (head->getnum() == num)  // ������ ��尡 ù ��° ������� Ȯ���մϴ�.
		{
			tmp = head;  // ������ ��带 �����մϴ�.
			head = head->getnext();  // head�� ���� ���� �̵��մϴ�.
			delete tmp;  // ������ ��带 �����մϴ�.
		}
		else  // ������ ��尡 ù ��° ��尡 �ƴ� ���
		{
			node* pre = head;  // ���� ��带 �����ϱ� ���� �������Դϴ�.
			tmp = pre->getnext();  // ������ ��带 ����Ű�� �����͸� �����մϴ�.
			while (tmp != NULL)  // ����Ʈ�� ��ȸ�մϴ�.
			{
				if (tmp->getnum() == num)  // ������ ��带 ã�Ҵ��� Ȯ���մϴ�.
				{
					if (pre->getnext() != NULL)  // ������ ��尡 ������ ��尡 �ƴ��� Ȯ���մϴ�.
						pre->setnext(tmp->getnext());  // ���� ����� �����͸� �����մϴ�.
					delete tmp;  // ������ ��带 �����մϴ�.
					break;  // �ݺ����� �����մϴ�.
				}
				pre = tmp;  // ���� ��带 ���� ���� �����մϴ�.
				tmp = pre->getnext();  // ���� ��带 ���� ���� �����մϴ�.
			}
		}
	}
};

int my_strcmp(const char* input, const char* command);  // ���ڿ��� ���ϴ� ����� ���� �Լ��� ������Ÿ�� �����Դϴ�.

int main()  // ���α׷��� �������Դϴ�.
{
	int num = 0;  // �Է� ���� ���ڸ� �����ϴ� �����Դϴ�.
	char command[20] = {};  // �Է� ���� ���ɾ �����ϴ� �迭�Դϴ�.
	list a;  // ����Ʈ ��ü�� �����մϴ�.

	while (1)  // ���� ������ �����մϴ�.
	{
		cin >> command;  // ����ڷκ��� ���ɾ �Է� �޽��ϴ�.
		if (my_strcmp(command, "insert"))  // �Էµ� ���ɾ "insert"���� Ȯ���մϴ�.
		{
			cin >> num;  // ���ڸ� �Է� �޽��ϴ�.
			a.setnode(num);  // ����Ʈ�� ���ڸ� �����մϴ�.
			a.print();  // ����Ʈ�� ����մϴ�.
		}
		else if (my_strcmp(command, "delete"))  // �Էµ� ���ɾ "delete"���� Ȯ���մϴ�.
		{
			cin >> num;  // ���ڸ� �Է� �޽��ϴ�.
			a.del(num);  // ����Ʈ���� ���ڿ� ��ġ�ϴ� ��带 �����մϴ�.
			a.print();  // ����Ʈ�� ����մϴ�.
		}
		else if (my_strcmp(command, "exit"))  // �Էµ� ���ɾ "exit"���� Ȯ���մϴ�.
		{
			break;  // ���� ������ �����մϴ�.
		}
		else  // �� ���� ���
		{
			cout << "error command\n";  // �߸��� ���ɾ����� �˸��� �޽����� ����մϴ�.
		}
	}
	return 0;  // ���α׷��� �����մϴ�.
}

int my_strcmp(const char* input, const char* command)  // ���ڿ��� ���ϴ� ����� ���� �Լ��Դϴ�.
{
	for (int i = 0; input[i] != '\0'; i++)  // �Էµ� �� ���ڿ��� ���մϴ�.
	{
		if (input[i] != command[i])  // ���ڰ� ��ġ���� �ʴ� ���
			return 0;  // 0�� ��ȯ�ϰ� �񱳸� �����մϴ�.
	}
	return 1;  // ���ڿ��� ��ġ�ϴ� ��� 1�� ��ȯ�մϴ�.
}
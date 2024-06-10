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
		this->data = data;//������ �ʱ�ȭ
		this->index = index;//�ε��� �ʱ�ȭ
		this->next = NULL;//���� ��带 ����Ű�� ������ �ʱ�ȭ
	}
	~node()
	{
		this->data = 0;//������ �ʱ�ȭ
		this->index = 0;//�ε��� �ʱ�ȭ
		this->next = NULL;//���� ��带 ����Ű�� ������ �ʱ�ȭ
	}
	//setter, getter
	void setnext(node* next) { this->next = next; }
	void setdata(int trans) { this->data = trans; }
	int getdata() const { return this->data; }
	int getindex() const { return this->index; }
	node* getnext() { return this->next; }
};

class list
{
private:
	node* head;//ù��° ��带 ����Ű�� ������
	node* tail;//���� �� �޸� ������ ���� ������
	node* tmp;//��带 �̵��ϱ� ���� ������
	node* pre;//tmp ���� ������
public:
	list()//������
	{//private ���� �ʱ�ȭ
		head = nullptr;
		tail = nullptr;
		tmp = nullptr;
		pre = nullptr;
	}
	~list()
	{
		if (tail == NULL)//tail�� NULL�̸� head�� �޸� ����
			tmp = head;
		else
			tmp= tail;//tail�� NULL�� �ƴϸ� tail���� head���� �޸� ����
		while (tmp != NULL)//tmp�� NULL�� �ƴ� ������ �ݺ�
		{
			pre = tmp;//pre�� tmp�� ����
			tmp = tmp->getnext();//tmp�� ���� ���� �̵�
			delete pre;//pre�� �޸� ����
		}
	}
	void initialize(int* val)
	{
		for (int i = 0; i < 10; i++)//10���� ��� ����
		{
			node* new_node = new node(val[i], i);//��� ����
			if (head == NULL)//head�� NULL�̸� head�� ��带 ����
				head = new_node;
			else
			{
				tmp = head;//tmp�� head�� ����
				for (int j = 0; j < i-1; j++)//tmp�� ������ ���� �̵�
					tmp = tmp->getnext();
				tmp->setnext(new_node);//tmp�� ���� ��忡 ���ο� ��带 ����
				new_node->setnext(NULL);//���ο� ����� ���� ��带 NULL�� �ʱ�ȭ
			}
		}
		tmp = head;//tmp�� head�� ����
		while (tmp->getnext() != NULL)//tmp�� ������ ��尡 �� ������ �̵�
			tmp = tmp->getnext();
		tmp->setnext(head);//������ ����� ���� ��带 head�� ����
	}
	bool transfer(int id1, int id2)
	{
		int val = 0;//�����͸� �ӽ÷� ������ ����
		tmp = head;//tmp�� head�� ����
		while (tmp->getindex() != id1)//tmp�� �ε����� id1�� �� ������ �̵�
			tmp = tmp->getnext();
		val = tmp->getdata();//tmp�� �����͸� val�� ����
		while (tmp->getindex() != id2)//tmp�� �ε����� id2�� �� ������ �̵�
		{
			if (probabilitic_disconnected_func())//Ȯ�������� ���� ��
			{
				tail = tmp->getnext();//tail�� tmp�� ���� ��带 ����
				cout << "Output 	: Detected a disconnection between " << tmp->getindex() << " and " << tmp->getnext()->getindex() << "\n";
				tmp->setnext(nullptr);//tmp�� ���� ��带 NULL�� �ʱ�ȭ
				return 1;
			}
			tmp = tmp->getnext();//tmp�� ���� ���� �̵�
		}
		tmp->setdata(val);//tmp�� �����͸� val�� �ʱ�ȭ
		return 0;
	}
	void print()
	{
		tmp = head;//tmp�� head�� ����
		cout << "Output 	:";
		while (1)//���� ����
		{
			cout << " " << tmp->getdata();//tmp�� ������ ���
			tmp = tmp->getnext();//tmp�� ���� ���� �̵�
			if (tmp->getindex() == 0)//tmp�� �ε����� 0�̸� ���� Ż��
				break;
		}
		cout << "\n";
	}
	bool probabilitic_disconnected_func()//Ȯ�������� ���� ��
	{
		int out = rand() % 10;//0~9������ ������ ���� out�� ����
		if (!out)	return true;//out�� 0�̸� true ��ȯ
		else	return false;//out�� 0�� �ƴϸ� false ��ȯ
	}
};

int main()
{
	list a;//list ��ü ����
	string input;//�Է¹��� ���ڿ�
	string command[4] = { "initialize","transfer","print","exit" };//��ɾ� �迭
	int val[10]{};//10���� �����͸� ������ �迭
	int id1, id2;//�����͸� ������ ����� �ε���
	string sub_input;//transfer ��ɾ��� to�� ������ ���ڿ�
	while (1)
	{
		cout << "Command : ";
		cin >> input;
		if (!input.compare(command[0]))
		{
			for (int i = 0; i < 10; i++)//10���� ������ �Է�
				cin >> val[i];
			a.initialize(val);//���� ��ü�� Ŀ�ǵ� ����
		}
		else if (!input.compare(command[1]))//transfer ��ɾ�
		{
			cin >> id1 >> sub_input >> id2;//�����͸� ������ ����� �ε����� to, �����͸� ���� ����� �ε��� �Է�
			if (sub_input.compare("to"))//to�� �ƴϸ� continue
				continue;
			if (a.transfer(id1, id2))//transfer �Լ� ����
				return 0;
		}
		else if (!input.compare(command[2])) a.print();//print ��� ����
		else if (!input.compare(command[3])) break;//exit ��� ����
	}
	return 0;
}
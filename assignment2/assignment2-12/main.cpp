#define _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include <fstream>

using namespace std;

int my_strcmp(const char* input, const char* command);
void my_strcpy(char* arr1, char* arr2, int arr2_len);
int my_strlen(const char* arr);

class node
{
private:
	char* name; // ����� �̸� ����
	node* next; // ���� ��� ����Ŵ
	node* down; // ���� �̴ϼ� ���� ��� ����Ŵ
public:
	node(char* name)
	{
		this->name = NULL; // �̸� �ʱ�ȭ
		this->next = NULL; // ���� ��� �ʱ�ȭ
		this->down = NULL; // ���� �̴ϼ� ��� �ʱ�ȭ
		int len = my_strlen(name); // �̸� ���� ����
		this->name = new char[len + 1]; // �̸� �޸� �Ҵ�
		my_strcpy(this->name, name, len); // �̸� ����
	}
	~node()
	{
		delete[] name; // �޸� ����
		this->next = NULL; // ���� ��� NULL�� ����
		this->down = NULL; // ���� �̴ϼ� ��� NULL�� ����
	}
	char getinitial()
	{
		char c = this->name[0]; // ù ���� ������
		if (c >= 97 && c <= 122) // �ҹ����� ��� �빮�� ��ȯ
			c -= 32;
		return c; // �̴ϼ� ��ȯ
	}
	void setnext(node* next) { this->next = next; } // ���� ��� ����
	void setdown(node* down) { this->down = down; } // ���� �̴ϼ� ��� ����
	char* getname() { return this->name; } // �̸� ��ȯ
	node* getnext() { return this->next; } // ���� ��� ��ȯ
	node* getdown() { return this->down; } // ���� �̴ϼ� ��� ��ȯ
};

class list
{
private:
	node* head; // ����Ʈ ù ��° ��� ����Ŵ
	node* tmp; // ���� ��� ����Ŵ
	node* pre; // ���� ��� ����Ŵ
	node* cur; // ���� �̴ϼ� ��� ����Ŵ
public:
	list()
	{
		this->head = NULL; // ��� NULL�� �ʱ�ȭ
		this->cur = NULL; // ���� �̴ϼ� ��� NULL�� �ʱ�ȭ
		this->pre = NULL; // ���� ��� NULL�� �ʱ�ȭ
		this->tmp = NULL; // ���� ��� NULL�� �ʱ�ȭ
	}
	~list()
	{
		node* prev;
		while (head->getnext() != NULL) // ����Ʈ ��ȸ�ϸ� �޸� ����
		{
			prev = head;
			head = head->getnext();
			delete prev;
		}
		delete head; // ���� ������ ��� ����
	}
	node* gethead() { return head; } // ����Ʈ ��� ��ȯ
	void setnode(char* name)
	{
		node* new_node = new node(name); // �� ��� ����
		if (head == NULL) // ����Ʈ ��� �ִ� ���
			head = new_node; // ��忡 �� ��� ����
		else
		{
			tmp = head;
			pre = NULL;
			while (1)
			{
				int a = new_node->getinitial() - tmp->getinitial(); // �̴ϼ� ��
				if (a < 0) // �� ��� �̴ϼ� �� ���� ���
				{
					new_node->setdown(tmp); // �� ��� ���� �̴ϼ� ��� ����
					if (tmp == head) // ��� �̴ϼȰ� ���� ���
						head = new_node; // �� ��� ���� ����
					else
						pre->setdown(new_node); // ���� ���� �� ��� ����
					break;
				}
				else if (a > 0) // �� ��� �̴ϼ� �� ū ���
				{
					if (tmp->getdown() == NULL) // ���� �̴ϼ� ��� ���� ���
					{
						tmp->setdown(new_node); // �� ��� ���� �̴ϼ� ��� ����
						break;
					}
					else
					{
						pre = tmp; // ���� ��� ���� ���� ����
						tmp = tmp->getdown(); // ���� �̴ϼ� ���� �̵�
					}
				}
				else if (a == 0) // �̴ϼ� ���� ���
				{
					while (1)
					{
						int b = my_strcmp(new_node->getname(), tmp->getname()); // �̸� ��
						if (b < 0) // �� ��� �̸� �� ���� ���
						{
							if (pre == NULL) // ��� ����� ���
							{
								new_node->setnext(tmp); // �� ��� ���� ��� ����
								head = new_node; // �� ��� ���� ����
							}
							else if (pre->getinitial() != tmp->getinitial()) // �ٸ� �̴ϼ� ����� ���
							{
								new_node->setnext(tmp); // �� ��� ���� ��� ����
								if (tmp->getdown() != NULL)
									new_node->setdown(tmp->getdown()); // ���� �̴ϼ� ���� ����
								pre->setdown(new_node); // ���� ���� �� ��� ����
							}
							else // ���� �̴ϼ� ����� ���
							{
								new_node->setnext(tmp); // �� ��� ���� ��� ����
								pre->setnext(new_node); // ���� ���� �� ��� ����
							}
							break;
						}
						else if (b > 0) // �� ��� �̸� �� ū ���
						{
							if (tmp->getnext() == NULL) // ���� ��� ���� ���
							{
								tmp->setnext(new_node); // �� ��� ���� ��� ����
								break;
							}
							else
							{
								pre = tmp; // ���� ��� ���� ���� ����
								tmp = tmp->getnext(); // ���� ���� �̵�
							}
						}
					}
					break;
				}
			}
		}
	}
	void print()
	{
		tmp = head;
		cur = head;
		while (cur != NULL)
		{
			cout << tmp->getinitial() << " : "; // �̴ϼ� ���
			while (tmp != NULL)
			{
				cout << tmp->getname(); // �̸� ���
				if (tmp->getnext() != NULL)
					cout << " -> "; // ���� ��� �ִ� ��� ȭ��ǥ ���
				tmp = tmp->getnext(); // ���� ���� �̵�
			}
			cout << "\n"; // �� �ٲ� ����
			cur = cur->getdown(); // ���� �̴ϼ� ���� �̵�
			tmp = cur; // ���� ��� ����
		}
	}
};

int main(void)
{
	list a;
	ifstream read_file;
	read_file.open("./Input.dat");
	if (read_file.fail())
		cout << "���� ȣ�� ����"; // ���� ȣ�� ���� �޽��� ���
	char input[51];
	while (!read_file.eof()) // ���� ������ �ݺ�
	{
		read_file.getline(input, 50); // �� �پ� �Է� ����
		a.setnode(input); // �Էµ� ���ڿ� ����Ʈ�� �߰�
	}
	a.print(); // ����Ʈ ���
	read_file.close(); // ���� ����
	return 0; // ���α׷� ����
}

int my_strcmp(const char* input1, const char* input2)
{
	int input1_len = my_strlen(input1); // ù ���ڿ� ���� ����
	int input2_len = my_strlen(input2); // �� ��° ���ڿ� ���� ����
	int chai = input1_len - input2_len; // ���� ���� ���
	int short_len = input1_len; // ª�� ���ڿ� ���� ����
	if (chai > 0)
		short_len = input2_len;
	for (int i = 0; i < short_len; i++) // ª�� ���ڿ� ���̸�ŭ �ݺ�
	{
		char input1_token = input1[i]; // ù ���ڿ� ���� ������
		char input2_token = input2[i]; // �� ��° ���ڿ� ���� ������
		if (input1_token >= 65 && input1_token <= 90) // �빮���� ��� �ҹ��� ��ȯ
			input1_token += 32;
		if (input2_token >= 65 && input2_token <= 90) // �빮���� ��� �ҹ��� ��ȯ
			input2_token += 32;
		if (input1_token > input2_token) // ù ���ڿ� ���� �� ū ���
			return 1; // ��� ��ȯ
		else if (input1_token < input2_token) // �� ��° ���ڿ� ���� �� ū ���
			return -1; // ���� ��ȯ
	}
	if (chai > 0) // ù ���ڿ� ���� �� �� ���
		return 1; // ��� ��ȯ
	else if (chai < 0) // �� ��° ���ڿ� ���� �� �� ���
		return -1; // ���� ��ȯ
	return 0; // �� ���ڿ� ���� ��� 0 ��ȯ
}

int my_strlen(const char* arr)
{
	int len = 0; // ���ڿ� ���� ���� ���� �ʱ�ȭ
	for (int i = 0; i < 1000; i++) // �ִ� ���̱��� �ݺ�
	{
		if (arr[i] == '\0') // ���ڿ� ���� ������
			return len; // ���� ��ȯ
		len++; // ���� ����
	}
	return len; // ���� ��ȯ
}

void my_strcpy(char* arr1, char* arr2, int arr2_len)
{
	for (int i = 0; i < arr2_len; i++) // �� ��° ���ڿ� ���̸�ŭ �ݺ�
		arr1[i] = arr2[i]; // �� ��° ���ڿ��� ù ��° ���ڿ��� ����
	*(arr1 + arr2_len) = '\0'; // ���ڿ� ���� NULL ���� �߰�
}

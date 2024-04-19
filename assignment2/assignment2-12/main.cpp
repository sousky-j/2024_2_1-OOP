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
	char* name;
	node* next;
	node* down;
public:
	node(char* name)
	{
		this->name = NULL;
		this->next = NULL;
		this->down = NULL;
		int len = my_strlen(name);
		this->name = new char[len + 1];
		my_strcpy(this->name, name, len);
	}
	~node()
	{
		delete[] name;
		this->next = NULL;
		this->down = NULL;
	}
	char getinitial()
	{
		char c = this->name[0];
		if (c >= 65 && c <= 90)
			c += 32;
		return c;
	}
	void setnext(node* next) { this->next = next; }
	void setdown(node* down) { this->down = down; }
	char* getname() { return this->name; }
	node* getnext() { return this->next; }
	node* getdown() { return this->down; }
	
};

class list
{
private:
	node* head;
	node* tmp;
	node* pre;
	node* cur;
public:
	list()
	{
		this->head = NULL;
		this->cur = NULL;
		this->pre = NULL;
		this->tmp = NULL;
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
	node* gethead() { return head; }
	void setnode(char* name)
	{
		node* new_node = new node(name);
		if (head == NULL)
			head = new_node;
		else
		{
			tmp = head;
			while (1)
			{
				if (tmp == NULL)
				{
					tmp = head;
					break;
				}
				else if (new_node->getinitial() < tmp->getinitial())
				{
					new_node->setdown(tmp);
					if (tmp == head)
						head = new_node;
					else
						pre->setdown(new_node);
					break;
				}
				else if (new_node->getinitial() > tmp->getinitial())
				{
					cout << "2";
					if(tmp->getdown() == NULL)
					{
						tmp->setdown(new_node);
						break;
					}
					else
					{
						if (pre != NULL)
							pre = tmp;
						else if (pre == NULL)
							pre = head;
						tmp = tmp->getdown();
					}
				}
				else if (new_node->getinitial() == tmp->getinitial())
				{
					while (1)
					{
						cout << "1";
						if (tmp == NULL)
						{
							tmp->setnext(new_node);
							break;
						}
						if (my_strcmp(new_node->getname(), tmp->getname()) < 0)
						{
							if (pre->getinitial() != tmp->getinitial())
							{
								new_node->setnext(tmp);
								if(tmp->getnext() !=NULL)
									new_node->setdown(tmp->getnext());
								pre->setdown(new_node);
							}
							else
							{
								new_node->setnext(tmp);
								pre->setnext(new_node);
							}
							break;
						}
						else if (my_strcmp(new_node->getname(), tmp->getname()) > 0)
						{
							if (tmp->getnext() == NULL)
							{
								tmp->setnext(new_node);
								break;
							}
							else
							{
								if (pre != NULL)
									pre = tmp;
								else if (pre == NULL)
									pre = head;
								tmp = tmp->getnext();
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
		node* tmp = head;
		while (tmp != NULL)
		{
			if (tmp->getnext() != NULL)
				cout << " -> ";
			cout << tmp->getname();
			tmp = tmp->getnext();
		}
	}
};

int main(void)
{
	list a;
	ifstream read_file;
	read_file.open("./Input.dat");
	if (read_file.fail())
		cout << "파일 호출 실패";
	char input[51];
	while (!read_file.eof())
	{
		read_file.getline(input, 50);
		a.setnode(input);
		cout << "0";
	}

	read_file.close();
	return 0;
}

int my_strcmp(const char* input1, const  char* input2)
{
	int input1_len = my_strlen(input1);
	int input2_len = my_strlen(input2);

	int chai = input1_len - input2_len;
	if (chai > 0)
		return 1;
	else if (chai < 0)
		return -1;
	for (int i = 0; i < input1_len; i++)
	{
		char input1_token = input1[i];
		char input2_token = input2[i];
		if (input1_token >= 65 && input1_token <= 90)
			input1_token += 32;
		if (input2_token >= 65 && input2_token <= 90)
			input2_token += 32;
		if (input1_token > input2_token)
			return 1;
		else if (input1_token < input2_token)
			return -1;
	}
	return 0;
}
int my_strlen(const char* arr)
{
	int len = 0;
	for (int i = 0; i < 1000; i++)
	{
		if (arr[i] == '\0')
			return len;
		len++;
	}
	return len;
}
void my_strcpy(char* arr1, char* arr2, int arr2_len)
{
	for (int i = 0; i < arr2_len; i++)
		arr1[i] = arr2[i];
	*(arr1 + arr2_len) = '\0';
}
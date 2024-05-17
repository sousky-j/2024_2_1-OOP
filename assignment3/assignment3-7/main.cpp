#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

template <typename T>
class Node {
private:
	Node<T>* m_Next;
	T m_Data;
public:
	Node(T data) {//������
	this->m_Data = data;//������ �ʱ�ȭ
	this->m_Next = nullptr;//���� ��� �ʱ�ȭ
	}
	~Node()
	{
		this->m_Data = 0;//������ �ʱ�ȭ
		this->m_Next = nullptr;//���� ��� �ʱ�ȭ
	}
	//getter, setter
	T getData() { return m_Data; }
	Node<T>* getnext() { return m_Next; }
	void setData(T data) { this->m_Data = data; }
	void setNext(Node<T>* next) { this->m_Next = next; }
};

template <typename T>
class Stack
{
private:
	Node<T>* m_Top;
public:
	Stack() {
		m_Top = nullptr;
	}
	~Stack() {
		while (m_Top != nullptr) {//������ ������� �ʴٸ�
			Node<T>* temp = m_Top;//�ӽ� ��忡 ���� ž ��� ����
			m_Top = m_Top->getnext();//ž ��带 ���� ���� �̵�
			delete temp;//�ӽ� ��� ����
		}
	}
	void push(T data) {
		Node<T>* newNode = new Node<T>(data);//���ο� ��� ����
		newNode->setNext(m_Top);//���ο� ����� ���� ��带 ���� ž ���� ����
		m_Top = newNode;//���ο� ��带 ž ���� ����
	}
	T pop()
	{
		if (this->m_Top == nullptr) {//������ ����ִٸ�
			cout << "Stack is empty" << "\n";//������ ����ִٰ� ���
			return -1;
		}
		Node<T>* temp = m_Top;//�ӽ� ��忡 ���� ž ��� ����
		T data = m_Top->getData();//������ ����
		m_Top = m_Top->getnext();//ž ��带 ���� ���� �̵�
		delete temp;//�ӽ� ��� ����
		return data;
	}
	bool isEmpty() { return m_Top == nullptr; }//������ ����ִ��� Ȯ��
	T top()//ž ����� ������ ��ȯ
	{
		if (this->m_Top == nullptr) {//������ ����ִٸ�
			cout << "Stack is empty" << "\n";
			return -1;
		}
		return m_Top->getData();//ž ����� ������ ��ȯ
	}
	void print()
	{
		Node<T>* temp = m_Top;//�ӽ� ��忡 ���� ž ��� ����
		while (temp != nullptr) {//������ ������� �ʴٸ�
			cout << temp->getData() << " ";
			temp = temp->getnext();//���� ���� �̵�
		}
		cout << "\n";
	}
};

int main()
{
	/////////����////////////
	Stack<char> stack;
	stack.push('a');
	stack.push('b');
	stack.push('c');
	cout<<stack.isEmpty() << "\n";
	cout << "stack print:";
	stack.print();
	cout << stack.pop() << "\n";
	cout << "stack print:";
	stack.print();
	cout << stack.top() << "\n";
	cout << "stack print:";
	stack.print();
	cout << stack.pop() << "\n";
	cout << "stack print:";
	stack.print();
	cout << stack.pop() << "\n";
	cout << "stack print:";
	stack.print();		
	cout << stack.isEmpty() << "\n";
	////////////////////////
	return 0;
}
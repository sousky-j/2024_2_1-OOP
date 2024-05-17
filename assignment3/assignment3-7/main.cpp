#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

template <typename T>
class Node {
private:
	Node<T>* m_Next;
	T m_Data;
public:
	Node(T data) {
	this->m_Data = data;
	this->m_Next = nullptr;
	}
	~Node()
	{
		this->m_Data = 0;
		this->m_Next = nullptr;
	}
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
		while (m_Top != nullptr) {
			Node<T>* temp = m_Top;
			m_Top = m_Top->getnext();
			delete temp;
		}
	}
	void push(T data) {
		Node<T>* newNode = new Node<T>(data);
		newNode->setNext(m_Top);
		m_Top = newNode;
	}
	T pop()
	{
		if (this->m_Top == nullptr) {
			cout << "Stack is empty" << "\n";
			return -1;
		}
		Node<T>* temp = m_Top;
		T data = m_Top->getData();
		m_Top = m_Top->getnext();
		delete temp;
		return data;
	}
	bool isEmpty() { return m_Top == nullptr; }
	T top()
	{
		if (this->m_Top == nullptr) {
			cout << "Stack is empty" << "\n";
			return -1;
		}
		return m_Top->getData();
	}
	void print()
	{
		Node<T>* temp = m_Top;
		while (temp != nullptr) {
			cout << temp->getData() << " ";
			temp = temp->getnext();
		}
		cout << "\n";
	}
};

int main()
{
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
	return 0;
}
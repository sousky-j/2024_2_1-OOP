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
class Queue
{
private:
	Node<T>* m_Front;
	Node<T>* m_Back;
public:
	Queue() {
		m_Front = nullptr;
		m_Back = nullptr;
	}
	~Queue() {
		while (m_Front != nullptr) {
			Node<T>* temp = m_Front;
			m_Front = m_Front->getnext();
			delete temp;
		}
	}
	void enqueue(T data) {
		Node<T>* newNode = new Node<T>(data);
		if (m_Front == nullptr) {
			m_Front = newNode;
			m_Back = newNode;
		}
		else {
			m_Back->setNext(newNode);
			m_Back = newNode;
		}
	}
	T dequeue()
	{
		if (this->m_Front == nullptr) {
			cout << "Queue is empty" << "\n";
			return -1;
		}
		Node<T>* temp = m_Front;
		T data = m_Front->getData();
		m_Front = m_Front->getnext();
		delete temp;
		return data;
	}
	bool isEmpty() { return m_Front == nullptr; }
	T front() { return m_Front->getData(); }
	void print() {
		Node<T>* temp = m_Front;
		while (temp != nullptr) {
			cout << temp->getData() << " ";
			temp = temp->getnext();
		}
		cout << "\n";
	};
};

int main()
{
	Queue<int> q;
	q.print();
	q.enqueue(1);
	q.print();
	q.enqueue(2);
	q.print();
	q.enqueue(3);
	q.print();
	q.enqueue(4);
	q.print();
	q.dequeue();
	q.print();
	q.dequeue();
	q.print();
	q.dequeue();
	q.print();
	q.dequeue();
	q.print();
	cout << q.isEmpty() << "\n";
	return 0;
}
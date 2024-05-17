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
		this->m_Data = data;//������ ����
		this->m_Next = nullptr;//���� ��带 nullptr�� �ʱ�ȭ
	}
	~Node()//�Ҹ���
	{
		this->m_Data = 0;//�����͸� 0���� �ʱ�ȭ
		this->m_Next = nullptr;//���� ��带 nullptr�� �ʱ�ȭ
	}
	//getter, setter
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
	Queue() {//������
		m_Front = nullptr;
		m_Back = nullptr;
	}
	~Queue() {
		while (m_Front != nullptr) {//ť�� ������� �ʴٸ�
			Node<T>* temp = m_Front;//�ӽ� ��忡 m_Front�� ����
			m_Front = m_Front->getnext();//m_Front�� ���� ���� �̵�
			delete temp;//�ӽ� ��� ����
		}
	}
	void enqueue(T data) {//ť�� ������ ����
		Node<T>* newNode = new Node<T>(data);//���ο� ��� ����
		if (m_Front == nullptr) {//ť�� ����ִٸ�
			m_Front = newNode;//m_Front�� ���ο� ��� ����
			m_Back = newNode;//m_Back�� ���ο� ��� ����
		}
		else {
			m_Back->setNext(newNode);//m_Back�� ���� ��带 ���ο� ���� ����
			m_Back = newNode;//m_Back�� ���ο� ���� ����
		}
	}
	T dequeue()
	{
		if (this->m_Front == nullptr) {//ť�� ����ִٸ�
			cout << "Queue is empty" << "\n";
			return -1;
		}
		Node<T>* temp = m_Front;//�ӽ� ��忡 m_Front ����
		T data = m_Front->getData();//data�� m_Front�� ������ ����
		m_Front = m_Front->getnext();//m_Front�� ���� ���� �̵�
		delete temp;//�ӽ� ��� ����
		return data;//data ��ȯ
	}
	bool isEmpty() { return m_Front == nullptr; }//ť�� ����ִ��� Ȯ��
	T front() { return m_Front->getData(); }//ť�� �� �� ������ ��ȯ
	void print() {//ť ���
		Node<T>* temp = m_Front;//�ӽ� ��忡 m_Front ����
		while (temp != nullptr) {//ť�� ������� �ʴٸ�
			cout << temp->getData() << " ";//������ ���
			temp = temp->getnext();//���� ���� �̵�
		}
		cout << "\n";
	};
};

int main()
{
	////////////����////////////
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
	///////////////////////////
	return 0;
}
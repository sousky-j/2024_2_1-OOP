#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

template <typename T>
class Node {
private:
	Node<T>* m_Next;
	T m_Data;
public:
	Node(T data) {//생성자
		this->m_Data = data;//데이터 저장
		this->m_Next = nullptr;//다음 노드를 nullptr로 초기화
	}
	~Node()//소멸자
	{
		this->m_Data = 0;//데이터를 0으로 초기화
		this->m_Next = nullptr;//다음 노드를 nullptr로 초기화
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
	Queue() {//생성자
		m_Front = nullptr;
		m_Back = nullptr;
	}
	~Queue() {
		while (m_Front != nullptr) {//큐가 비어있지 않다면
			Node<T>* temp = m_Front;//임시 노드에 m_Front를 저장
			m_Front = m_Front->getnext();//m_Front를 다음 노드로 이동
			delete temp;//임시 노드 삭제
		}
	}
	void enqueue(T data) {//큐에 데이터 삽입
		Node<T>* newNode = new Node<T>(data);//새로운 노드 생성
		if (m_Front == nullptr) {//큐가 비어있다면
			m_Front = newNode;//m_Front에 새로운 노드 저장
			m_Back = newNode;//m_Back에 새로운 노드 저장
		}
		else {
			m_Back->setNext(newNode);//m_Back의 다음 노드를 새로운 노드로 설정
			m_Back = newNode;//m_Back을 새로운 노드로 설정
		}
	}
	T dequeue()
	{
		if (this->m_Front == nullptr) {//큐가 비어있다면
			cout << "Queue is empty" << "\n";
			return -1;
		}
		Node<T>* temp = m_Front;//임시 노드에 m_Front 저장
		T data = m_Front->getData();//data에 m_Front의 데이터 저장
		m_Front = m_Front->getnext();//m_Front를 다음 노드로 이동
		delete temp;//임시 노드 삭제
		return data;//data 반환
	}
	bool isEmpty() { return m_Front == nullptr; }//큐가 비어있는지 확인
	T front() { return m_Front->getData(); }//큐의 맨 앞 데이터 반환
	void print() {//큐 출력
		Node<T>* temp = m_Front;//임시 노드에 m_Front 저장
		while (temp != nullptr) {//큐가 비어있지 않다면
			cout << temp->getData() << " ";//데이터 출력
			temp = temp->getnext();//다음 노드로 이동
		}
		cout << "\n";
	};
};

int main()
{
	////////////예시////////////
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
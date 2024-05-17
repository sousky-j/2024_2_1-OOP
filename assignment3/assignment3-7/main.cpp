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
	this->m_Data = data;//데이터 초기화
	this->m_Next = nullptr;//다음 노드 초기화
	}
	~Node()
	{
		this->m_Data = 0;//데이터 초기화
		this->m_Next = nullptr;//다음 노드 초기화
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
		while (m_Top != nullptr) {//스택이 비어있지 않다면
			Node<T>* temp = m_Top;//임시 노드에 현재 탑 노드 저장
			m_Top = m_Top->getnext();//탑 노드를 다음 노드로 이동
			delete temp;//임시 노드 삭제
		}
	}
	void push(T data) {
		Node<T>* newNode = new Node<T>(data);//새로운 노드 생성
		newNode->setNext(m_Top);//새로운 노드의 다음 노드를 현재 탑 노드로 설정
		m_Top = newNode;//새로운 노드를 탑 노드로 설정
	}
	T pop()
	{
		if (this->m_Top == nullptr) {//스택이 비어있다면
			cout << "Stack is empty" << "\n";//스택이 비어있다고 출력
			return -1;
		}
		Node<T>* temp = m_Top;//임시 노드에 현재 탑 노드 저장
		T data = m_Top->getData();//데이터 저장
		m_Top = m_Top->getnext();//탑 노드를 다음 노드로 이동
		delete temp;//임시 노드 삭제
		return data;
	}
	bool isEmpty() { return m_Top == nullptr; }//스택이 비어있는지 확인
	T top()//탑 노드의 데이터 반환
	{
		if (this->m_Top == nullptr) {//스택이 비어있다면
			cout << "Stack is empty" << "\n";
			return -1;
		}
		return m_Top->getData();//탑 노드의 데이터 반환
	}
	void print()
	{
		Node<T>* temp = m_Top;//임시 노드에 현재 탑 노드 저장
		while (temp != nullptr) {//스택이 비어있지 않다면
			cout << temp->getData() << " ";
			temp = temp->getnext();//다음 노드로 이동
		}
		cout << "\n";
	}
};

int main()
{
	/////////예시////////////
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
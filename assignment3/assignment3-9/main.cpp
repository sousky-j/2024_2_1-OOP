#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;
template <typename T>
class Node
{
private:
	Node<T>* m_left;
	Node<T>* m_right;
	T m_data;
	int depth;
public:
	Node()//생성자
	{//초기화
		m_data = 0;
		depth = 0;
		m_left = NULL;
		m_right = NULL;
	}
	~Node()//소멸자
	{//데이터 삭제
		m_data = 0;
		depth = 0;
		m_left = NULL;
		m_right = NULL;
	}
	//getter, setter
	void setLeft(Node<T>* left) { m_left = left; }
	void setRight(Node<T>* right) { m_right = right; }
	void setData(T data) { m_data = data; }
	void setDepth(int depth) { this->depth = depth; }
	Node<T>* getLeft() { return m_left; }
	Node<T>* getRight() { return m_right; }
	T getData() { return m_data; }
	int getDepth() { return depth; }
};

template <typename T>
class BST
{
private:
	Node<T>* m_root;
public:
	BST() { this->m_root = NULL; }
	~BST()
	{
		Node<T>* cur = m_root;//현재 노드를 루트로 설정
		if (cur == NULL)//현재 노드가 비어있을 경우
			return;
		if (cur->getLeft() != NULL)//현재 노드의 왼쪽 자식이 있을 경우
		{
			BST<T>* left_tree = new BST<T>;//왼쪽 서브트리 생성
			left_tree->setRoot(cur->getLeft());//왼쪽 서브트리의 루트를 현재 노드의 왼쪽 자식으로 설정
			left_tree->~BST();//왼쪽 서브트리 소멸
		}
		if (cur->getRight() != NULL)//현재 노드의 오른쪽 자식이 있을 경우
		{
			BST<T>* right_tree = new BST<T>;//오른쪽 서브트리 생성
			right_tree->setRoot(cur->getRight());//오른쪽 서브트리의 루트를 현재 노드의 오른쪽 자식으로 설정
			right_tree->~BST();//오른쪽 서브트리 소멸
		}
		delete cur;//현재 노드 삭제
	}
	void setRoot(Node<T>* root) { this->m_root = root; }
	Node<T>* getRoot() { return m_root; }
	void build(T arr[], int start, int end)
	{
		int mid = (start + end) / 2;//중간값 설정
		insert(arr[mid], 0);//중간값을 루트로 삽입
		if (start < mid)//중간값보다 작은 값이 있을 경우
			build(arr, start, mid - 1);//왼쪽 서브트리 생성
		if (mid < end)//중간값보다 큰 값이 있을 경우
			build(arr, mid + 1, end);//오른쪽 서브트리 생성
	}
	void insert(T n, int depth)
	{
		//코드와 주석 함께 작성
		Node<T>* newNode = new Node<T>;//새로운 노드 생성
		newNode->setData(n);//새로운 노드에 데이터 저장
		newNode->setDepth(depth);//새로운 노드에 깊이 저장
		if (m_root == NULL)//루트가 비어있을 경우
		{
			m_root = newNode;//새로운 노드를 루트로
			return;
		}
		Node<T>* cur = m_root;//현재 노드를 루트 노드로 설정
		while (1)
		{
			if (n < cur->getData())//삽입하려는 값이 현재 노드의 값보다 작을 경우
			{
				if (cur->getLeft() == NULL)//현재 노드의 왼쪽 자식이 비어있을 경우
				{
					newNode->setDepth(newNode->getDepth() + 1);
					cur->setLeft(newNode);//현재 노드의 왼쪽 자식에 새로운 노드 저장
					return;
				}
				else
				{
					cur = cur->getLeft();//현재 노드를 왼쪽 자식으로 변경
					newNode->setDepth(newNode->getDepth() + 1);//깊이 증가(왼쪽 자식으로 이동했으므로)
				}
			}
			else if (n > cur->getData())//삽입하려는 값이 현재 노드의 값보다 클 경우
			{
				if (cur->getRight() == NULL)//현재 노드의 오른쪽 자식이 비어있을 경우
				{
					newNode->setDepth(newNode->getDepth() + 1);
					cur->setRight(newNode);//현재 노드의 오른쪽 자식에 새로운 노드 저장
					return;
				}
				else
				{
					cur = cur->getRight();//현재 노드를 오른쪽 자식으로 변경
					newNode->setDepth(newNode->getDepth() + 1);//깊이 증가(오른쪽 자식으로 이동했으므로)
				}
			}
		}
	}
	void printTree()
	{
		BST<T>* left_tree=new BST<T>;//왼쪽 서브트리 생성
		left_tree->setRoot(m_root->getLeft());//왼쪽 서브트리의 루트를 현재 노드의 왼쪽 자식으로 설정
		BST<T>* right_tree = new BST<T>;//오른쪽 서브트리 생성
		right_tree->setRoot(m_root->getRight());//오른쪽 서브트리의 루트를 현재 노드의 오른쪽 자식으로 설정

		if (m_root->getRight() == NULL && m_root->getLeft() == NULL)//자식이 없는 경우
		{
			for (int i = 0; i < m_root->getDepth(); i++)//깊이만큼 공백 출력
				cout << "      ";
			cout << m_root->getData() << "\n";//현재 노드 출력
			return;
		}

		if (m_root->getRight() != NULL)//오른쪽 자식이 있을 경우
			right_tree->printTree();//오른쪽 서브트리 출력
		else
		{
			for (int i = 0; i < m_root->getDepth()+1; i++)//오른쪽 자식이 없을 경우 깊이만큼 공백 출력
				cout << "     ";//공백 출력
			cout << "\n";
		}

		for (int i = 0; i < m_root->getDepth(); i++)//깊이만큼 공백 출력
			cout << "      ";
		cout << m_root->getData() << "\n";//현재 노드 출력

		if (m_root->getLeft() != NULL)//왼쪽 자식이 있을 경우
		{
			if (m_root->getLeft()->getRight() == NULL)//왼쪽 자식의 오른쪽 자식이 없을 경우
				cout << "\n";
		}

		if (m_root->getLeft() != NULL)//왼쪽 자식이 있을 경우
			left_tree->printTree();//왼쪽 서브트리 출력
		else
		{
			for (int i = 0; i < m_root->getDepth() + 1; i++)//오른쪽 자식이 없을 경우 깊이만큼 공백 출력
				cout << "     ";//공백 출력
			cout << "  ";
			cout << "\n";
		}
	}
};

int main(void)
{
	BST <float> bst;//BST 객체 생성
	float arr[10] = { 12,21,37,46,59,65,74,83,89,94 };//배열 생성
	cout<<"input array = ";
	for (int i = 0; i < 10; i++)//배열 출력
		cout << arr[i] << " ";
	cout << "\n";
	bst.build(arr, 0, 9);//배열을 이용하여 BST 생성
	bst.printTree();//BST 출력
	return 0;
}
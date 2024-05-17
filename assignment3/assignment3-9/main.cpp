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
	Node()
	{
		m_data = 0;
		depth = 0;
		m_left = NULL;
		m_right = NULL;
	}
	~Node()
	{
		m_data = 0;
		depth = 0;
		m_left = NULL;
		m_right = NULL;
	}
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

	}
	void setRoot(Node<T>* root) { this->m_root = root; }
	void build(T arr[], int start, int end)
	{
		int mid = (start + end) / 2;
		insert(arr[mid], 0);
		if (start < mid)
			build(arr, start, mid - 1);
		if (mid < end)
			build(arr, mid + 1, end);
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
		BST<T>* left_tree=new BST<T>;
		left_tree->setRoot(m_root->getLeft());
		BST<T>* right_tree = new BST<T>;
		right_tree->setRoot(m_root->getRight());

		if (m_root->getRight() == NULL && m_root->getLeft() == NULL)
		{
			for (int i = 0; i < m_root->getDepth(); i++)
				cout << "\t";
			cout << m_root->getData() << "\n";
			return;
		}

		if (m_root->getRight() != NULL)
			right_tree->printTree();
		else
			cout << "\n";
		for (int i = 0; i < m_root->getDepth(); i++)
			cout << "\t";
		cout << m_root->getData() << "\n";
		if (m_root->getLeft() != NULL)
			left_tree->printTree();
		else
			cout << "\n";
	}
};

int main(void)
{
	BST <float> bst;
	float arr[50];
	for (int i = 0; i < 50; i++)
		arr[i] = i * (i + 1) / 2;

	bst.build(arr, 0, 49);
	bst.printTree();
	return 0;
}
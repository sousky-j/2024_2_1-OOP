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
		//�ڵ�� �ּ� �Բ� �ۼ�
		Node<T>* newNode = new Node<T>;//���ο� ��� ����
		newNode->setData(n);//���ο� ��忡 ������ ����
		newNode->setDepth(depth);//���ο� ��忡 ���� ����
		if (m_root == NULL)//��Ʈ�� ������� ���
		{
			m_root = newNode;//���ο� ��带 ��Ʈ��
			return;
		}
		Node<T>* cur = m_root;//���� ��带 ��Ʈ ���� ����
		while (1)
		{
			if (n < cur->getData())//�����Ϸ��� ���� ���� ����� ������ ���� ���
			{
				if (cur->getLeft() == NULL)//���� ����� ���� �ڽ��� ������� ���
				{
					newNode->setDepth(newNode->getDepth() + 1);
					cur->setLeft(newNode);//���� ����� ���� �ڽĿ� ���ο� ��� ����
					return;
				}
				else
				{
					cur = cur->getLeft();//���� ��带 ���� �ڽ����� ����
					newNode->setDepth(newNode->getDepth() + 1);//���� ����(���� �ڽ����� �̵������Ƿ�)
				}
			}
			else if (n > cur->getData())//�����Ϸ��� ���� ���� ����� ������ Ŭ ���
			{
				if (cur->getRight() == NULL)//���� ����� ������ �ڽ��� ������� ���
				{
					newNode->setDepth(newNode->getDepth() + 1);
					cur->setRight(newNode);//���� ����� ������ �ڽĿ� ���ο� ��� ����
					return;
				}
				else
				{
					cur = cur->getRight();//���� ��带 ������ �ڽ����� ����
					newNode->setDepth(newNode->getDepth() + 1);//���� ����(������ �ڽ����� �̵������Ƿ�)
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
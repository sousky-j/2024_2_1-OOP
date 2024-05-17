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
	Node()//������
	{//�ʱ�ȭ
		m_data = 0;
		depth = 0;
		m_left = NULL;
		m_right = NULL;
	}
	~Node()//�Ҹ���
	{//������ ����
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
		Node<T>* cur = m_root;//���� ��带 ��Ʈ�� ����
		if (cur == NULL)//���� ��尡 ������� ���
			return;
		if (cur->getLeft() != NULL)//���� ����� ���� �ڽ��� ���� ���
		{
			BST<T>* left_tree = new BST<T>;//���� ����Ʈ�� ����
			left_tree->setRoot(cur->getLeft());//���� ����Ʈ���� ��Ʈ�� ���� ����� ���� �ڽ����� ����
			left_tree->~BST();//���� ����Ʈ�� �Ҹ�
		}
		if (cur->getRight() != NULL)//���� ����� ������ �ڽ��� ���� ���
		{
			BST<T>* right_tree = new BST<T>;//������ ����Ʈ�� ����
			right_tree->setRoot(cur->getRight());//������ ����Ʈ���� ��Ʈ�� ���� ����� ������ �ڽ����� ����
			right_tree->~BST();//������ ����Ʈ�� �Ҹ�
		}
		delete cur;//���� ��� ����
	}
	void setRoot(Node<T>* root) { this->m_root = root; }
	Node<T>* getRoot() { return m_root; }
	void build(T arr[], int start, int end)
	{
		int mid = (start + end) / 2;//�߰��� ����
		insert(arr[mid], 0);//�߰����� ��Ʈ�� ����
		if (start < mid)//�߰������� ���� ���� ���� ���
			build(arr, start, mid - 1);//���� ����Ʈ�� ����
		if (mid < end)//�߰������� ū ���� ���� ���
			build(arr, mid + 1, end);//������ ����Ʈ�� ����
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
		BST<T>* left_tree=new BST<T>;//���� ����Ʈ�� ����
		left_tree->setRoot(m_root->getLeft());//���� ����Ʈ���� ��Ʈ�� ���� ����� ���� �ڽ����� ����
		BST<T>* right_tree = new BST<T>;//������ ����Ʈ�� ����
		right_tree->setRoot(m_root->getRight());//������ ����Ʈ���� ��Ʈ�� ���� ����� ������ �ڽ����� ����

		if (m_root->getRight() == NULL && m_root->getLeft() == NULL)//�ڽ��� ���� ���
		{
			for (int i = 0; i < m_root->getDepth(); i++)//���̸�ŭ ���� ���
				cout << "      ";
			cout << m_root->getData() << "\n";//���� ��� ���
			return;
		}

		if (m_root->getRight() != NULL)//������ �ڽ��� ���� ���
			right_tree->printTree();//������ ����Ʈ�� ���
		else
		{
			for (int i = 0; i < m_root->getDepth()+1; i++)//������ �ڽ��� ���� ��� ���̸�ŭ ���� ���
				cout << "     ";//���� ���
			cout << "\n";
		}

		for (int i = 0; i < m_root->getDepth(); i++)//���̸�ŭ ���� ���
			cout << "      ";
		cout << m_root->getData() << "\n";//���� ��� ���

		if (m_root->getLeft() != NULL)//���� �ڽ��� ���� ���
		{
			if (m_root->getLeft()->getRight() == NULL)//���� �ڽ��� ������ �ڽ��� ���� ���
				cout << "\n";
		}

		if (m_root->getLeft() != NULL)//���� �ڽ��� ���� ���
			left_tree->printTree();//���� ����Ʈ�� ���
		else
		{
			for (int i = 0; i < m_root->getDepth() + 1; i++)//������ �ڽ��� ���� ��� ���̸�ŭ ���� ���
				cout << "     ";//���� ���
			cout << "  ";
			cout << "\n";
		}
	}
};

int main(void)
{
	BST <float> bst;//BST ��ü ����
	float arr[10] = { 12,21,37,46,59,65,74,83,89,94 };//�迭 ����
	cout<<"input array = ";
	for (int i = 0; i < 10; i++)//�迭 ���
		cout << arr[i] << " ";
	cout << "\n";
	bst.build(arr, 0, 9);//�迭�� �̿��Ͽ� BST ����
	bst.printTree();//BST ���
	return 0;
}
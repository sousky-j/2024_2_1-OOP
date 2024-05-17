#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;

class Term
{
private:
	int m_Coefficient;
	int m_Exponent;
	Term* m_pNext;
public:
	Term(int m_Coefficient, int m_Exponent)//������
	{//����� ������ ���ڷ� �޾Ƽ� ���׽� ����Ʈ�� �߰��ϴ� �Լ�
		this->m_Coefficient = m_Coefficient;
		this->m_Exponent = m_Exponent;
		m_pNext = NULL;
	}
	~Term() {}
	//getter, setter
	Term* getNext() { return m_pNext; }
	int getCoe() { return m_Coefficient; }
	int getExp() { return m_Exponent; }
	void setCoe(int coe) { this->m_Coefficient = coe; }
	void setNext(Term* pNext) { m_pNext = pNext; }
};
class Polynomial
{
private:
	Term* m_pHead;
public:
	Polynomial() { m_pHead = NULL; }
	~Polynomial()
	{
		Term* tmp = m_pHead;//������ ����
		while (tmp != NULL)//���� ��尡 null�� �� ������ �ݺ�
		{
			Term* cur = tmp;//���� ��带 ����
			tmp = tmp->getNext();//���� ���� �̵�
			delete cur;//���� ��� ����
		}
	}
	Polynomial(const Polynomial& poly)//���� ������
	{
		Term* p = poly.m_pHead;//������ ���׽��� ��带 ������
		while (p != NULL)//���� ��尡 null�� �� ������ �ݺ�
		{
			addTerm(p->getCoe(), p->getExp());//����� ������ �����ͼ� ���׽Ŀ� �߰�
			p = p->getNext();//���� ���� �̵�
		}
	}
	Polynomial& operator=(const Polynomial& poly)//���� ������ �����ε�
	{
		if (this == &poly)//���� ��ü�� ���
			return *this;
		Term* tmp = m_pHead;//���� ��ü�� ��带 ������
		while (tmp != NULL)
		{
			Term* cur = tmp;//���� ��带 ����
			tmp = tmp->getNext();//���� ���� �̵�
			delete cur;//���� ��� ����
		}
		Term* p = poly.m_pHead;//������ ���׽��� ��带 ������
		while (p != NULL)//���� ��尡 null�� �� ������ �ݺ�
		{
			addTerm(p->getCoe(), p->getExp());//����� ������ �����ͼ� ���׽Ŀ� �߰�
			p = p->getNext();//���� ���� �̵�
		}
		return *this;
	}
	void addTerm(int coeff, int exp)
	{
		//����� ������ ���ڷ� �޾Ƽ� ���׽� ����Ʈ	�� �߰��ϴ� �Լ�
		//���� ũ�⿡ ���� ������������ ���ĵǰ� �߰�
		Term* tmp = m_pHead;
		Term* pre = NULL;
		while ((tmp != NULL) && (tmp->getExp() > exp))//������ ū ��带 ã�� ������ �ݺ�
		{
			pre = tmp;
			tmp = tmp->getNext();
		}
		Term* newTerm = new Term(coeff, exp);
		if (pre == NULL)//ù��° ��忡 �߰�
		{
			newTerm->setNext(m_pHead);//���ο� ����� ���� ��带 ���� ����
			//��尡 null�̹Ƿ� ���� ���� null
			m_pHead = newTerm;//��带 ���ο� ���� ����
			//��������� ���ο� ��尡 ��尡 ��
		}
		else if (tmp == NULL)
			pre->setNext(newTerm);
		else if (tmp->getExp() == newTerm->getExp())
			tmp->setCoe(tmp->getCoe() + newTerm->getCoe());
		else
		{
			pre->setNext(newTerm);//���� ����� ���� ��带 ���ο� ���� ����
			newTerm->setNext(tmp);//���ο� ����� ���� ��带 ������ ���� ���� ����
		}

	}
	void printPolynomial()
	{
		Term* p = m_pHead;//������ ����
		while (p != NULL)//���� ��尡 null�� �� ������ �ݺ�
		{
			if (p->getCoe() == 1)//����� 1�� ���
			{
				if (p->getExp() == 0)//������ 0�� ���
					cout << p->getCoe();//����� ���
				else
					cout << "x^" << p->getExp();//������ ���
			}
			else if (p->getCoe() == -1)//����� -1�� ���
			{
				cout << "-";//���̳ʽ� ��ȣ ���
				if (p->getExp() == 0)//������ 0�� ���
					cout << "1";
				else
					cout<<"x^"<<p->getExp();//������ ���
			}
			else
			{
				if (p->getExp() == 0)//������ 0�� ���
					cout << p->getCoe();//����� ���
				else
					cout << p->getCoe() << "x^" << p->getExp();//����� ������ ���
			}
			if (p->getNext() != NULL)//���� ��尡 null�� �ƴ� ���
				cout << " + ";//���ϱ� ��ȣ ���
			p = p->getNext();//���� ���� �̵�
		}
	}
	Polynomial operator+(const Polynomial& poly)
	{
		Polynomial result;//��� ���׽�
		Term* p1 = this->m_pHead;//���� ��ü�� ���
		Term* p2 = poly.m_pHead;//�ι�° ���� ��ü�� ���
		while (p1 != NULL && p2 != NULL)//�� ���׽��� ��尡 null�� �ƴ� ������ �ݺ�
		{
			if (p1->getExp() > p2->getExp())//���� ��ü�� ������ �� Ŭ ���
			{
				result.addTerm(p1->getCoe(), p1->getExp());//���� ��ü�� ����� ������ ��� ���׽Ŀ� �߰�
				p1 = p1->getNext();//���� ���� �̵�
			}
			else if (p1->getExp() < p2->getExp())//�ι�° ���� ����� �� Ŭ ���
			{
				result.addTerm(p2->getCoe(), p2->getExp());//�ι�° ���� ����� ������ ��� ���׽Ŀ� �߰�
				p2 = p2->getNext();//���� ���� �̵�
			}
			else//�� ���� ������ ���� ���
			{
				result.addTerm(p1->getCoe() + p2->getCoe(), p1->getExp());//�� ���� ����� ���ؼ� ��� ���׽Ŀ� �߰�
				p1 = p1->getNext();//���� ���� �̵�
				p2 = p2->getNext();//���� ���� �̵�
			}
		}
		while (p1 != NULL)
		{
			result.addTerm(p1->getCoe(), p1->getExp());
			p1 = p1->getNext();
		}
		while (p2 != NULL)
		{
			result.addTerm(p2->getCoe(), p2->getExp());
			p2 = p2->getNext();
		}
		return result;
	}
	Polynomial operator-(const Polynomial& poly)
	{
		Polynomial result;//��� ���׽�
		Term* p1 = this->m_pHead;//���� ��ü�� ���
		Term* p2 = poly.m_pHead;//�ι�° ���� ��ü�� ���
		while (p1 != NULL && p2 != NULL)//�� ���׽��� ��尡 null�� �ƴ� ������ �ݺ�
		{
			if (p1->getExp() > p2->getExp())//���� ��ü ������ �� Ŭ ���
			{
				result.addTerm(p1->getCoe(), p1->getExp());//���� ��ü�� ����� ������ ��� ���׽Ŀ� �߰�
				p1 = p1->getNext();
			}
			else if (p1->getExp() < p2->getExp())//�ι�° ���� ������ �� Ŭ ���
			{
				result.addTerm(-p2->getCoe(), p2->getExp());//�ι�° ���� ����� -�� �ٿ��� ��� ���׽Ŀ� �߰�
				p2 = p2->getNext();
			}
			else//�� ���� ������ ���� ���
			{
				result.addTerm(p1->getCoe() - p2->getCoe(), p1->getExp());//�� ���� ����� ���� ��� ���׽Ŀ� �߰�
				p1 = p1->getNext();
				p2 = p2->getNext();
			}
		}
		while (p1 != NULL)//���� ��ü�� ��尡 null�� �ƴ� ��
		{
			result.addTerm(p1->getCoe(), p1->getExp());//���� ��ü�� ����� ������ ��� ���׽Ŀ� �߰�
			p1 = p1->getNext();
		}
		while (p2 != NULL)//�ι�° ���� ��尡 null�� �ƴ� ��
		{
			result.addTerm(-(p2->getCoe()), p2->getExp());//�ι�° ���� ����� -�� �ٿ��� ��� ���׽Ŀ� �߰�
			p2 = p2->getNext();
		}
		return result;
	}
	Polynomial differentiation()
	{
		Polynomial result;//��� ���׽�
		Term* p = m_pHead;//������ ����
		while (p != NULL)//���� ��尡 null�� �� ������ �ݺ�
		{
			if (p->getExp() != 0)//������ 0�� �ƴ� ���
				result.addTerm(p->getCoe() * p->getExp(), p->getExp() - 1);//����� ������ ���ϰ� ������ 1 ���ҽ��Ѽ� ��� ���׽Ŀ� �߰�
			p = p->getNext();
		}
		return result;
	}
	int calculate(int x)
	{
		int result = 0;//�����
		Term* p = m_pHead;//������ ����
		while (p != NULL)//���� ��尡 null�� �� ������ �ݺ�
		{
			int tmp = 1;//x�� �ŵ������� ����ϱ� ���� ����
			for (int i = 0; i < p->getExp(); i++)//������ŭ �ݺ�
				tmp *= x;
			result += p->getCoe() * tmp;//����� x�� �ŵ������� ���ؼ� ������� ����
			p = p->getNext();
		}
		return result;
	}
	
};

int main()
{
	///////����////////
	Polynomial p1, p2;
	Polynomial result;
	p1.addTerm(2, 3);
	p1.addTerm(-4, 2);
	p1.addTerm(-4, 2);
	p1.addTerm(-7, 0);
	p1.addTerm(3, 7);
	p1.addTerm(1, 1);

	p2.addTerm(-3, 3);
	p2.addTerm(1, 2);
	p2.addTerm(6, 1);
	p2.addTerm(4, 0);

	result = p2 - p1;
	p1.printPolynomial();
	cout << "\n";
	p2.printPolynomial();
	cout << "\n";

	result.printPolynomial();
	cout << "\n";
	cout << result.calculate(2) << "\n";
	Polynomial dif=p1.differentiation();
	dif.printPolynomial();
	cout << "\n";
	/////////////////////
	return 0;
}
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
	Term(int m_Coefficient, int m_Exponent)
	{
		this->m_Coefficient = m_Coefficient;
		this->m_Exponent = m_Exponent;
		m_pNext = NULL;
	}
	~Term() {}
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
		Term* tmp = m_pHead;
		while (tmp != NULL)
		{
			Term* cur = tmp;
			tmp = tmp->getNext();
			delete cur;
		}
	}
	Polynomial(const Polynomial& poly)
	{
		Term* p = poly.m_pHead;
		while (p != NULL)
		{
			addTerm(p->getCoe(), p->getExp());
			p = p->getNext();
		}
	}
	Polynomial& operator=(const Polynomial& poly)
	{
		if (this == &poly)
			return *this;
		Term* tmp = m_pHead;
		while (tmp != NULL)
		{
			Term* cur = tmp;
			tmp = tmp->getNext();
			delete cur;
		}
		Term* p = poly.m_pHead;
		while (p != NULL)
		{
			addTerm(p->getCoe(), p->getExp());
			p = p->getNext();
		}
		return *this;
	}
	void addTerm(int coeff, int exp)
	{
		//계수와 차수를 인자로 받아서 다항식 리스트	에 추가하는 함수
		//차수 크기에 따라 내림차순으로 정렬되게 추가
		Term* tmp = m_pHead;
		Term* pre = NULL;
		while ((tmp != NULL) && (tmp->getExp() > exp))//차수가 큰 노드를 찾을 때까지 반복
		{
			pre = tmp;
			tmp = tmp->getNext();
		}
		Term* newTerm = new Term(coeff, exp);
		if (pre == NULL)//첫번째 노드에 추가
		{
			newTerm->setNext(m_pHead);//새로운 노드의 다음 노드를 헤드로 설정
			//헤드가 null이므로 다음 노드는 null
			m_pHead = newTerm;//헤드를 새로운 노드로 설정
			//결과적으로 새로운 노드가 헤드가 됨
		}
		else if (tmp == NULL)
			pre->setNext(newTerm);
		else if (tmp->getExp() == newTerm->getExp())
			tmp->setCoe(tmp->getCoe() + newTerm->getCoe());
		else
		{
			pre->setNext(newTerm);//이전 노드의 다음 노드를 새로운 노드로 설정
			newTerm->setNext(tmp);//새로운 노드의 다음 노드를 차수가 작은 노드로 설정
		}

	}
	void printPolynomial()
	{
		Term* p = m_pHead;
		while (p != NULL)
		{
			if (p->getCoe() == 1)
			{
				if (p->getExp() == 0)
					cout << p->getCoe();
				else
					cout << "x^" << p->getExp();
			}
			else if (p->getCoe() == -1)
			{
				cout << "-";
				if (p->getExp() == 0)
					cout << "1";
				else
					cout<<"x^"<<p->getExp();
			}
			else
			{
				if (p->getExp() == 0)
					cout << p->getCoe();
				else
					cout << p->getCoe() << "x^" << p->getExp();
			}
			if (p->getNext() != NULL)
				cout << " + ";
			p = p->getNext();
		}
	}
	Polynomial operator+(const Polynomial& poly)
	{
		//Polynomial 객체는 포인터를 사용하는 연결 리스트를 구현하는 객체이므로
		//연산자 오버로딩 시 반환하는 객체가 소멸하므로 문제가 발생할 수 있음
		//따라서 복사 생성자를 이용하여 객체를 복사하여 반환하도록 함
		Polynomial result;
		Term* p1 = this->m_pHead;
		Term* p2 = poly.m_pHead;
		while (p1 != NULL && p2 != NULL)
		{
			if (p1->getExp() > p2->getExp())
			{
				result.addTerm(p1->getCoe(), p1->getExp());
				p1 = p1->getNext();
			}
			else if (p1->getExp() < p2->getExp())
			{
				result.addTerm(p2->getCoe(), p2->getExp());
				p2 = p2->getNext();
			}
			else
			{
				result.addTerm(p1->getCoe() + p2->getCoe(), p1->getExp());
				p1 = p1->getNext();
				p2 = p2->getNext();
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
		Polynomial result;
		Term* p1 = this->m_pHead;
		Term* p2 = poly.m_pHead;
		while (p1 != NULL && p2 != NULL)
		{
			if (p1->getExp() > p2->getExp())
			{
				result.addTerm(p1->getCoe(), p1->getExp());
				p1 = p1->getNext();
			}
			else if (p1->getExp() < p2->getExp())
			{
				result.addTerm(-p2->getCoe(), p2->getExp());
				p2 = p2->getNext();
			}
			else
			{
				result.addTerm(p1->getCoe() - p2->getCoe(), p1->getExp());
				p1 = p1->getNext();
				p2 = p2->getNext();
			}
		}
		while (p1 != NULL)
		{
			result.addTerm(p1->getCoe(), p1->getExp());
			p1 = p1->getNext();
		}
		while (p2 != NULL)
		{
			result.addTerm(-(p2->getCoe()), p2->getExp());
			p2 = p2->getNext();
		}
		return result;
	}
	Polynomial differentiation()
	{
		Polynomial result;
		Term* p = m_pHead;
		while (p != NULL)
		{
			if (p->getExp() != 0)
				result.addTerm(p->getCoe() * p->getExp(), p->getExp() - 1);
			p = p->getNext();
		}
		return result;
	}
	int calculate(int x)
	{
		int result = 0;
		Term* p = m_pHead;
		while (p != NULL)
		{
			int tmp = 1;
			for (int i = 0; i < p->getExp(); i++)
				tmp *= x;
			result += p->getCoe() * tmp;
			p = p->getNext();
		}
		return result;
	}
	
};

int main()
{
	Polynomial p1, p2;
	Polynomial result;
	p1.addTerm(2, 3);
	p1.addTerm(-4, 2);
	p1.addTerm(-4, 2);
	p1.addTerm(-7, 0);

	p2.addTerm(-3, 3);
	p2.addTerm(1, 2);
	p2.addTerm(6, 1);
	p2.addTerm(4, 0);

	result = p1 + p2;
	p1.printPolynomial();
	cout << "\n";
	p2.printPolynomial();
	cout << "\n";

	result.printPolynomial();
	cout << "\n";
	cout << result.calculate(1) << "\n";
	Polynomial dif=p1.differentiation();
	dif.printPolynomial();
	cout << "\n";

	return 0;
}
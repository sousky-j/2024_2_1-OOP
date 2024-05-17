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
	Term(int m_Coefficient, int m_Exponent)//생성자
	{//계수와 차수를 인자로 받아서 다항식 리스트에 추가하는 함수
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
		Term* tmp = m_pHead;//헤드부터 시작
		while (tmp != NULL)//다음 노드가 null이 될 때까지 반복
		{
			Term* cur = tmp;//현재 노드를 저장
			tmp = tmp->getNext();//다음 노드로 이동
			delete cur;//현재 노드 삭제
		}
	}
	Polynomial(const Polynomial& poly)//복사 생성자
	{
		Term* p = poly.m_pHead;//복사할 다항식의 헤드를 가져옴
		while (p != NULL)//다음 노드가 null이 될 때까지 반복
		{
			addTerm(p->getCoe(), p->getExp());//계수와 차수를 가져와서 다항식에 추가
			p = p->getNext();//다음 노드로 이동
		}
	}
	Polynomial& operator=(const Polynomial& poly)//대입 연산자 오버로딩
	{
		if (this == &poly)//같은 객체인 경우
			return *this;
		Term* tmp = m_pHead;//현재 객체의 헤드를 가져옴
		while (tmp != NULL)
		{
			Term* cur = tmp;//현재 노드를 저장
			tmp = tmp->getNext();//다음 노드로 이동
			delete cur;//현재 노드 삭제
		}
		Term* p = poly.m_pHead;//복사할 다항식의 헤드를 가져옴
		while (p != NULL)//다음 노드가 null이 될 때까지 반복
		{
			addTerm(p->getCoe(), p->getExp());//계수와 차수를 가져와서 다항식에 추가
			p = p->getNext();//다음 노드로 이동
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
		Term* p = m_pHead;//헤드부터 시작
		while (p != NULL)//다음 노드가 null이 될 때까지 반복
		{
			if (p->getCoe() == 1)//계수가 1인 경우
			{
				if (p->getExp() == 0)//차수가 0인 경우
					cout << p->getCoe();//계수만 출력
				else
					cout << "x^" << p->getExp();//차수를 출력
			}
			else if (p->getCoe() == -1)//계수가 -1인 경우
			{
				cout << "-";//마이너스 기호 출력
				if (p->getExp() == 0)//차수가 0인 경우
					cout << "1";
				else
					cout<<"x^"<<p->getExp();//차수를 출력
			}
			else
			{
				if (p->getExp() == 0)//차수가 0인 경우
					cout << p->getCoe();//계수만 출력
				else
					cout << p->getCoe() << "x^" << p->getExp();//계수와 차수를 출력
			}
			if (p->getNext() != NULL)//다음 노드가 null이 아닌 경우
				cout << " + ";//더하기 기호 출력
			p = p->getNext();//다음 노드로 이동
		}
	}
	Polynomial operator+(const Polynomial& poly)
	{
		Polynomial result;//결과 다항식
		Term* p1 = this->m_pHead;//현재 객체의 헤드
		Term* p2 = poly.m_pHead;//두번째 항의 객체의 헤드
		while (p1 != NULL && p2 != NULL)//두 다항식의 노드가 null이 아닐 때까지 반복
		{
			if (p1->getExp() > p2->getExp())//현재 객체의 차수가 더 클 경우
			{
				result.addTerm(p1->getCoe(), p1->getExp());//현재 객체의 계수와 차수를 결과 다항식에 추가
				p1 = p1->getNext();//다음 노드로 이동
			}
			else if (p1->getExp() < p2->getExp())//두번째 항의 계수가 더 클 경우
			{
				result.addTerm(p2->getCoe(), p2->getExp());//두번째 항의 계수와 차수를 결과 다항식에 추가
				p2 = p2->getNext();//다음 노드로 이동
			}
			else//두 항의 차수가 같을 경우
			{
				result.addTerm(p1->getCoe() + p2->getCoe(), p1->getExp());//두 항의 계수를 더해서 결과 다항식에 추가
				p1 = p1->getNext();//다음 노드로 이동
				p2 = p2->getNext();//다음 노드로 이동
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
		Polynomial result;//결과 다항식
		Term* p1 = this->m_pHead;//현재 객체의 헤드
		Term* p2 = poly.m_pHead;//두번째 항의 객체의 헤드
		while (p1 != NULL && p2 != NULL)//두 다항식의 노드가 null이 아닐 때까지 반복
		{
			if (p1->getExp() > p2->getExp())//현재 객체 차수가 더 클 경우
			{
				result.addTerm(p1->getCoe(), p1->getExp());//현재 객체의 계수와 차수를 결과 다항식에 추가
				p1 = p1->getNext();
			}
			else if (p1->getExp() < p2->getExp())//두번째 항의 차수가 더 클 경우
			{
				result.addTerm(-p2->getCoe(), p2->getExp());//두번째 항의 계수에 -를 붙여서 결과 다항식에 추가
				p2 = p2->getNext();
			}
			else//두 항의 차수가 같을 경우
			{
				result.addTerm(p1->getCoe() - p2->getCoe(), p1->getExp());//두 항의 계수를 빼서 결과 다항식에 추가
				p1 = p1->getNext();
				p2 = p2->getNext();
			}
		}
		while (p1 != NULL)//현재 객체의 노드가 null이 아닐 때
		{
			result.addTerm(p1->getCoe(), p1->getExp());//현재 객체의 계수와 차수를 결과 다항식에 추가
			p1 = p1->getNext();
		}
		while (p2 != NULL)//두번째 항의 노드가 null이 아닐 때
		{
			result.addTerm(-(p2->getCoe()), p2->getExp());//두번째 항의 계수에 -를 붙여서 결과 다항식에 추가
			p2 = p2->getNext();
		}
		return result;
	}
	Polynomial differentiation()
	{
		Polynomial result;//결과 다항식
		Term* p = m_pHead;//헤드부터 시작
		while (p != NULL)//다음 노드가 null이 될 때까지 반복
		{
			if (p->getExp() != 0)//차수가 0이 아닌 경우
				result.addTerm(p->getCoe() * p->getExp(), p->getExp() - 1);//계수에 차수를 곱하고 차수를 1 감소시켜서 결과 다항식에 추가
			p = p->getNext();
		}
		return result;
	}
	int calculate(int x)
	{
		int result = 0;//결과값
		Term* p = m_pHead;//헤드부터 시작
		while (p != NULL)//다음 노드가 null이 될 때까지 반복
		{
			int tmp = 1;//x의 거듭제곱을 계산하기 위한 변수
			for (int i = 0; i < p->getExp(); i++)//차수만큼 반복
				tmp *= x;
			result += p->getCoe() * tmp;//계수와 x의 거듭제곱을 곱해서 결과값에 더함
			p = p->getNext();
		}
		return result;
	}
	
};

int main()
{
	///////예시////////
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
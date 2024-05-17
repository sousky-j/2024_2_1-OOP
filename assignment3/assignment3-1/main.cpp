#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <ctime>
#include <string>

using namespace std;
class node
{
private:
	int data;
	int index;
	node* next;
public:
	node(int data, int index)
	{
		this->data = data;//데이터 초기화
		this->index = index;//인덱스 초기화
		this->next = NULL;//다음 노드를 가리키는 포인터 초기화
	}
	~node()
	{
		this->data = 0;//데이터 초기화
		this->index = 0;//인덱스 초기화
		this->next = NULL;//다음 노드를 가리키는 포인터 초기화
	}
	//setter, getter
	void setnext(node* next) { this->next = next; }
	void setdata(int trans) { this->data = trans; }
	int getdata() const { return this->data; }
	int getindex() const { return this->index; }
	node* getnext() { return this->next; }
};

class list
{
private:
	node* head;//첫번째 노드를 가리키는 포인터
	node* tail;//끊길 때 메모리 해제를 위한 포인터
	node* tmp;//노드를 이동하기 위한 포인터
	node* pre;//tmp 이전 포인터
public:
	list()//생성자
	{//private 변수 초기화
		head = nullptr;
		tail = nullptr;
		tmp = nullptr;
		pre = nullptr;
	}
	~list()
	{
		if (tail == NULL)//tail이 NULL이면 head만 메모리 해제
			tmp = head;
		else
			tmp= tail;//tail이 NULL이 아니면 tail부터 head까지 메모리 해제
		while (tmp != NULL)//tmp가 NULL이 아닐 때까지 반복
		{
			pre = tmp;//pre에 tmp를 대입
			tmp = tmp->getnext();//tmp를 다음 노드로 이동
			delete pre;//pre를 메모리 해제
		}
	}
	void initialize(int* val)
	{
		for (int i = 0; i < 10; i++)//10개의 노드 생성
		{
			node* new_node = new node(val[i], i);//노드 생성
			if (head == NULL)//head가 NULL이면 head에 노드를 연결
				head = new_node;
			else
			{
				tmp = head;//tmp에 head를 대입
				for (int j = 0; j < i-1; j++)//tmp를 마지막 노드로 이동
					tmp = tmp->getnext();
				tmp->setnext(new_node);//tmp의 다음 노드에 새로운 노드를 연결
				new_node->setnext(NULL);//새로운 노드의 다음 노드를 NULL로 초기화
			}
		}
		tmp = head;//tmp에 head를 대입
		while (tmp->getnext() != NULL)//tmp가 마지막 노드가 될 때까지 이동
			tmp = tmp->getnext();
		tmp->setnext(head);//마지막 노드의 다음 노드를 head로 연결
	}
	bool transfer(int id1, int id2)
	{
		int val = 0;//데이터를 임시로 저장할 변수
		tmp = head;//tmp에 head를 대입
		while (tmp->getindex() != id1)//tmp의 인덱스가 id1이 될 때까지 이동
			tmp = tmp->getnext();
		val = tmp->getdata();//tmp의 데이터를 val에 저장
		while (tmp->getindex() != id2)//tmp의 인덱스가 id2가 될 때까지 이동
		{
			if (probabilitic_disconnected_func())//확률적으로 끊길 때
			{
				tail = tmp->getnext();//tail에 tmp의 다음 노드를 대입
				cout << "Output 	: Detected a disconnection between " << tmp->getindex() << " and " << tmp->getnext()->getindex() << "\n";
				tmp->setnext(nullptr);//tmp의 다음 노드를 NULL로 초기화
				return 1;
			}
			tmp = tmp->getnext();//tmp를 다음 노드로 이동
		}
		tmp->setdata(val);//tmp의 데이터를 val로 초기화
		return 0;
	}
	void print()
	{
		tmp = head;//tmp에 head를 대입
		cout << "Output 	:";
		while (1)//무한 루프
		{
			cout << " " << tmp->getdata();//tmp의 데이터 출력
			tmp = tmp->getnext();//tmp를 다음 노드로 이동
			if (tmp->getindex() == 0)//tmp의 인덱스가 0이면 루프 탈출
				break;
		}
		cout << "\n";
	}
	bool probabilitic_disconnected_func()//확률적으로 끊길 때
	{
		int out = rand() % 10;//0~9까지의 랜덤한 수를 out에 저장
		if (!out)	return true;//out이 0이면 true 반환
		else	return false;//out이 0이 아니면 false 반환
	}
};

int main()
{
	list a;//list 객체 생성
	string input;//입력받을 문자열
	string command[4] = { "initialize","transfer","print","exit" };//명령어 배열
	int val[10]{};//10개의 데이터를 저장할 배열
	int id1, id2;//데이터를 전송할 노드의 인덱스
	string sub_input;//transfer 명령어의 to를 저장할 문자열
	while (1)
	{
		cout << "Command : ";
		cin >> input;
		if (!input.compare(command[0]))
		{
			for (int i = 0; i < 10; i++)//10개의 데이터 입력
				cin >> val[i];
			a.initialize(val);//생성 객체의 커맨드 실행
		}
		else if (!input.compare(command[1]))//transfer 명령어
		{
			cin >> id1 >> sub_input >> id2;//데이터를 전송할 노드의 인덱스와 to, 데이터를 받을 노드의 인덱스 입력
			if (sub_input.compare("to"))//to가 아니면 continue
				continue;
			if (a.transfer(id1, id2))//transfer 함수 실행
				return 0;
		}
		else if (!input.compare(command[2])) a.print();//print 명령 실행
		else if (!input.compare(command[3])) break;//exit 명령 실행
	}
	return 0;
}
#define _CRT_SECURE_NO_WARNINGS 
#include <iostream>

using namespace std;

class node  // 연결 리스트의 개별 요소를 나타내는 'node' 클래스를 선언
{
private:  // 비공개 멤버 변수에 접근할 수 있는 접근 지정자
	int num;  // 노드의 값을 저장하는 정수 변수
	node* next;  // 연결 리스트에서 다음 노드를 가리키는 포인터
public:  // 공개 멤버 함수에 접근할 수 있는 접근 지정자
	node(int num)  // 주어진 숫자로 노드를 초기화하는 생성자
	{
		this->next = NULL;  // 'next' 포인터를 NULL로 초기화
		this->setnum(num);  // 값을 설정하는 멤버 함수를 호출
	}
	~node()  // 노드가 차지한 메모리를 해제하는 소멸자
	{
		this->next = NULL;  // 매달린 포인터를 NULL로 설정하여 댕글링 포인터를 방지
	}

	int getnum() { return this->num; }  // 'num' 값을 반환하는 멤버 함수
	node* getnext() { return this->next; }  // 다음 노드를 가리키는 포인터를 반환하는 멤버 함수

	void setnum(int num) { this->num = num; }  // 'num' 값을 설정하는 멤버 함수
	void setnext(node* next) { this->next = next; }  // 다음 노드를 설정하는 멤버 함수
};

class list  // 연결 리스트를 관리하는 'list' 클래스를 선언
{
private:  // 비공개 멤버 변수에 접근할 수 있는 접근 지정자
	node* head;  // 연결 리스트의 첫 번째 노드를 가리키는 포인터
	node* tail;  // 연결 리스트의 마지막 노드를 가리키는 포인터
public:  // 공개 멤버 함수에 접근할 수 있는 접근 지정자
	list()  // 빈 리스트를 초기화하는 생성자
	{
		this->head = NULL;  // 'head' 포인터를 NULL로 초기화
		this->tail = NULL;  // 'tail' 포인터를 NULL로 초기화
	}
	~list()  // 리스트에 있는 모든 노드가 차지한 메모리를 해제하는 소멸자입
	{
		node* prev;  // 순회 중 이전 노드를 추적하는 포인터
		if (head == NULL)  // 리스트가 이미 비어 있는지 확인
			return;  // 그렇다면 추가 작업 없이 반환
		while (head->getnext() != NULL)  // 두 번째 마지막 노드까지 리스트를 순회
		{
			prev = head;  // 현재 노드를 이전 노드로 저장합니다.
			head = head->getnext();  // 다음 노드로 이동합니다.
			delete prev;  // 이전 노드를 삭제합니다.
		}
		delete head;  // 남은 마지막 노드를 삭제합니다.
	}
	void setnode(int num)  // 주어진 숫자로 새 노드를 리스트의 시작에 삽입하는 멤버 함수
	{
		node* new_node = new node(num);  // 주어진 숫자로 새 노드를 생성
		if (head == NULL)  // 리스트가 비어 있는지 확인
		{
			head = new_node;  // 새 노드를 head로 지정합니다.
			tail = head;  // tail도 head로 지정합니다.
		}
		else  // 그렇지 않다면 리스트가 이미 존재합니다.
		{
			new_node->setnext(head);  // 새 노드의 다음 노드를 현재 head로 설정합니다.
			head = new_node;  // 새 노드를 새로운 head로 지정합니다.
		}
	}
	void print()  // 리스트를 출력하는 멤버 함수입니다.
	{
		node* tmp = head;  // 현재 노드를 추적하기 위한 임시 포인터입니다.
		cout << "Linked list : ";  // 연결 리스트를 나타내는 문자열을 출력합니다.
		if (head == NULL)  // 리스트가 비어 있는지 확인합니다.
		{
			cout << "\n";  // 비어 있다면 개행합니다.
			return;  // 추가 작업 없이 반환합니다.
		}
		if (tmp->getnext() != NULL)  // 현재 노드가 마지막 노드가 아닌지 확인
		{
			cout << tmp->getnum();  // 현재 노드의 값을 출력
			tmp = tmp->getnext();  // 다음 노드로 이동
		}
		else  // 현재 노드가 마지막 노드라면
		{
			cout << tmp->getnum() << "\n";  // 현재 노드의 값을 출력하고 개행합니다.
			return;  // 추가 작업 없이 반환합니다.
		}
		while (tmp != NULL)  // 리스트의 모든 노드를 출력합니다.
		{
			cout << " -> " << tmp->getnum();  // 다음 노드의 값을 출력합니다.
			tmp = tmp->getnext();  // 다음 노드로 이동합니다.
		}
		cout << "\n";  // 출력을 마무리하기 위해 개행합니다.
	}
	void del(int num)  // 주어진 숫자와 일치하는 노드를 삭제하는 멤버 함수입니다.
	{
		node* tmp = NULL;  // 삭제할 노드를 추적하기 위한 임시 포인터입니다.
		if (head->getnum() == num)  // 삭제할 노드가 첫 번째 노드인지 확인합니다.
		{
			tmp = head;  // 삭제할 노드를 저장합니다.
			head = head->getnext();  // head를 다음 노드로 이동합니다.
			delete tmp;  // 삭제할 노드를 해제합니다.
		}
		else  // 삭제할 노드가 첫 번째 노드가 아닌 경우
		{
			node* pre = head;  // 이전 노드를 추적하기 위한 포인터입니다.
			tmp = pre->getnext();  // 삭제할 노드를 가리키는 포인터를 설정합니다.
			while (tmp != NULL)  // 리스트를 순회합니다.
			{
				if (tmp->getnum() == num)  // 삭제할 노드를 찾았는지 확인합니다.
				{
					if (pre->getnext() != NULL)  // 삭제할 노드가 마지막 노드가 아닌지 확인합니다.
						pre->setnext(tmp->getnext());  // 이전 노드의 포인터를 갱신합니다.
					delete tmp;  // 삭제할 노드를 해제합니다.
					break;  // 반복문을 종료합니다.
				}
				pre = tmp;  // 이전 노드를 현재 노드로 갱신합니다.
				tmp = pre->getnext();  // 현재 노드를 다음 노드로 갱신합니다.
			}
		}
	}
};

int my_strcmp(const char* input, const char* command);  // 문자열을 비교하는 사용자 정의 함수의 프로토타입 선언입니다.

int main()  // 프로그램의 시작점입니다.
{
	int num = 0;  // 입력 받을 숫자를 저장하는 변수입니다.
	char command[20] = {};  // 입력 받을 명령어를 저장하는 배열입니다.
	list a;  // 리스트 객체를 생성합니다.

	while (1)  // 무한 루프를 시작합니다.
	{
		cin >> command;  // 사용자로부터 명령어를 입력 받습니다.
		if (my_strcmp(command, "insert"))  // 입력된 명령어가 "insert"인지 확인합니다.
		{
			cin >> num;  // 숫자를 입력 받습니다.
			a.setnode(num);  // 리스트에 숫자를 삽입합니다.
			a.print();  // 리스트를 출력합니다.
		}
		else if (my_strcmp(command, "delete"))  // 입력된 명령어가 "delete"인지 확인합니다.
		{
			cin >> num;  // 숫자를 입력 받습니다.
			a.del(num);  // 리스트에서 숫자와 일치하는 노드를 삭제합니다.
			a.print();  // 리스트를 출력합니다.
		}
		else if (my_strcmp(command, "exit"))  // 입력된 명령어가 "exit"인지 확인합니다.
		{
			break;  // 무한 루프를 종료합니다.
		}
		else  // 그 외의 경우
		{
			cout << "error command\n";  // 잘못된 명령어임을 알리는 메시지를 출력합니다.
		}
	}
	return 0;  // 프로그램을 종료합니다.
}

int my_strcmp(const char* input, const char* command)  // 문자열을 비교하는 사용자 정의 함수입니다.
{
	for (int i = 0; input[i] != '\0'; i++)  // 입력된 두 문자열을 비교합니다.
	{
		if (input[i] != command[i])  // 문자가 일치하지 않는 경우
			return 0;  // 0을 반환하고 비교를 종료합니다.
	}
	return 1;  // 문자열이 일치하는 경우 1을 반환합니다.
}

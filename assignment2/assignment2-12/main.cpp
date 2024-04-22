#define _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include <fstream>

using namespace std;

int my_strcmp(const char* input, const char* command);
void my_strcpy(char* arr1, char* arr2, int arr2_len);
int my_strlen(const char* arr);

class node
{
private:
	char* name; // 노드의 이름 저장
	node* next; // 다음 노드 가리킴
	node* down; // 동일 이니셜 다음 노드 가리킴
public:
	node(char* name)
	{
		this->name = NULL; // 이름 초기화
		this->next = NULL; // 다음 노드 초기화
		this->down = NULL; // 다음 이니셜 노드 초기화
		int len = my_strlen(name); // 이름 길이 구함
		this->name = new char[len + 1]; // 이름 메모리 할당
		my_strcpy(this->name, name, len); // 이름 복사
	}
	~node()
	{
		delete[] name; // 메모리 해제
		this->next = NULL; // 다음 노드 NULL로 설정
		this->down = NULL; // 다음 이니셜 노드 NULL로 설정
	}
	char getinitial()
	{
		char c = this->name[0]; // 첫 글자 가져옴
		if (c >= 97 && c <= 122) // 소문자인 경우 대문자 변환
			c -= 32;
		return c; // 이니셜 반환
	}
	void setnext(node* next) { this->next = next; } // 다음 노드 설정
	void setdown(node* down) { this->down = down; } // 다음 이니셜 노드 설정
	char* getname() { return this->name; } // 이름 반환
	node* getnext() { return this->next; } // 다음 노드 반환
	node* getdown() { return this->down; } // 다음 이니셜 노드 반환
};

class list
{
private:
	node* head; // 리스트 첫 번째 노드 가리킴
	node* tmp; // 현재 노드 가리킴
	node* pre; // 이전 노드 가리킴
	node* cur; // 현재 이니셜 노드 가리킴
public:
	list()
	{
		this->head = NULL; // 헤드 NULL로 초기화
		this->cur = NULL; // 현재 이니셜 노드 NULL로 초기화
		this->pre = NULL; // 이전 노드 NULL로 초기화
		this->tmp = NULL; // 현재 노드 NULL로 초기화
	}
	~list()
	{
		node* prev;
		while (head->getnext() != NULL) // 리스트 순회하며 메모리 해제
		{
			prev = head;
			head = head->getnext();
			delete prev;
		}
		delete head; // 남은 마지막 노드 해제
	}
	node* gethead() { return head; } // 리스트 헤드 반환
	void setnode(char* name)
	{
		node* new_node = new node(name); // 새 노드 생성
		if (head == NULL) // 리스트 비어 있는 경우
			head = new_node; // 헤드에 새 노드 연결
		else
		{
			tmp = head;
			pre = NULL;
			while (1)
			{
				int a = new_node->getinitial() - tmp->getinitial(); // 이니셜 비교
				if (a < 0) // 새 노드 이니셜 더 작은 경우
				{
					new_node->setdown(tmp); // 새 노드 다음 이니셜 노드 설정
					if (tmp == head) // 헤드 이니셜과 같은 경우
						head = new_node; // 새 노드 헤드로 설정
					else
						pre->setdown(new_node); // 이전 노드와 새 노드 연결
					break;
				}
				else if (a > 0) // 새 노드 이니셜 더 큰 경우
				{
					if (tmp->getdown() == NULL) // 다음 이니셜 노드 없는 경우
					{
						tmp->setdown(new_node); // 새 노드 다음 이니셜 노드 설정
						break;
					}
					else
					{
						pre = tmp; // 이전 노드 현재 노드로 설정
						tmp = tmp->getdown(); // 다음 이니셜 노드로 이동
					}
				}
				else if (a == 0) // 이니셜 같은 경우
				{
					while (1)
					{
						int b = my_strcmp(new_node->getname(), tmp->getname()); // 이름 비교
						if (b < 0) // 새 노드 이름 더 작은 경우
						{
							if (pre == NULL) // 헤드 노드인 경우
							{
								new_node->setnext(tmp); // 새 노드 다음 노드 설정
								head = new_node; // 새 노드 헤드로 설정
							}
							else if (pre->getinitial() != tmp->getinitial()) // 다른 이니셜 노드인 경우
							{
								new_node->setnext(tmp); // 새 노드 다음 노드 설정
								if (tmp->getdown() != NULL)
									new_node->setdown(tmp->getdown()); // 다음 이니셜 노드와 연결
								pre->setdown(new_node); // 이전 노드와 새 노드 연결
							}
							else // 같은 이니셜 노드인 경우
							{
								new_node->setnext(tmp); // 새 노드 다음 노드 설정
								pre->setnext(new_node); // 이전 노드와 새 노드 연결
							}
							break;
						}
						else if (b > 0) // 새 노드 이름 더 큰 경우
						{
							if (tmp->getnext() == NULL) // 다음 노드 없는 경우
							{
								tmp->setnext(new_node); // 새 노드 다음 노드 설정
								break;
							}
							else
							{
								pre = tmp; // 이전 노드 현재 노드로 설정
								tmp = tmp->getnext(); // 다음 노드로 이동
							}
						}
					}
					break;
				}
			}
		}
	}
	void print()
	{
		tmp = head;
		cur = head;
		while (cur != NULL)
		{
			cout << tmp->getinitial() << " : "; // 이니셜 출력
			while (tmp != NULL)
			{
				cout << tmp->getname(); // 이름 출력
				if (tmp->getnext() != NULL)
					cout << " -> "; // 다음 노드 있는 경우 화살표 출력
				tmp = tmp->getnext(); // 다음 노드로 이동
			}
			cout << "\n"; // 줄 바꿈 수행
			cur = cur->getdown(); // 다음 이니셜 노드로 이동
			tmp = cur; // 현재 노드 설정
		}
	}
};

int main(void)
{
	list a;
	ifstream read_file;
	read_file.open("./Input.dat");
	if (read_file.fail())
		cout << "파일 호출 실패"; // 파일 호출 실패 메시지 출력
	char input[51];
	while (!read_file.eof()) // 파일 끝까지 반복
	{
		read_file.getline(input, 50); // 한 줄씩 입력 받음
		a.setnode(input); // 입력된 문자열 리스트에 추가
	}
	a.print(); // 리스트 출력
	read_file.close(); // 파일 닫음
	return 0; // 프로그램 종료
}

int my_strcmp(const char* input1, const char* input2)
{
	int input1_len = my_strlen(input1); // 첫 문자열 길이 구함
	int input2_len = my_strlen(input2); // 두 번째 문자열 길이 구함
	int chai = input1_len - input2_len; // 길이 차이 계산
	int short_len = input1_len; // 짧은 문자열 길이 설정
	if (chai > 0)
		short_len = input2_len;
	for (int i = 0; i < short_len; i++) // 짧은 문자열 길이만큼 반복
	{
		char input1_token = input1[i]; // 첫 문자열 문자 가져옴
		char input2_token = input2[i]; // 두 번째 문자열 문자 가져옴
		if (input1_token >= 65 && input1_token <= 90) // 대문자인 경우 소문자 변환
			input1_token += 32;
		if (input2_token >= 65 && input2_token <= 90) // 대문자인 경우 소문자 변환
			input2_token += 32;
		if (input1_token > input2_token) // 첫 문자열 문자 더 큰 경우
			return 1; // 양수 반환
		else if (input1_token < input2_token) // 두 번째 문자열 문자 더 큰 경우
			return -1; // 음수 반환
	}
	if (chai > 0) // 첫 문자열 길이 더 긴 경우
		return 1; // 양수 반환
	else if (chai < 0) // 두 번째 문자열 길이 더 긴 경우
		return -1; // 음수 반환
	return 0; // 두 문자열 같은 경우 0 반환
}

int my_strlen(const char* arr)
{
	int len = 0; // 문자열 길이 저장 변수 초기화
	for (int i = 0; i < 1000; i++) // 최대 길이까지 반복
	{
		if (arr[i] == '\0') // 문자열 끝을 만나면
			return len; // 길이 반환
		len++; // 길이 증가
	}
	return len; // 길이 반환
}

void my_strcpy(char* arr1, char* arr2, int arr2_len)
{
	for (int i = 0; i < arr2_len; i++) // 두 번째 문자열 길이만큼 반복
		arr1[i] = arr2[i]; // 두 번째 문자열을 첫 번째 문자열에 복사
	*(arr1 + arr2_len) = '\0'; // 문자열 끝에 NULL 문자 추가
}

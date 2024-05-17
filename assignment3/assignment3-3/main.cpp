#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
struct Member
{
	char id[20];
	char password[20];
};

class membership
{
private:
	Member* list;
	int cnt; //멤버의 수를 체크하는 변수
public:
	membership()//멤버쉽 클래스를 선언하면 파일에서 멤버쉽 리스트를 전부 가져옴
	{
		this->cnt = 0;//멤버 수 초기화
		ifstream read_file;//파일 읽기
		read_file.open("member_list.txt");//멤버십 리스트 파일 열기
		if (read_file.fail())//파일이 없으면
			list = NULL;//리스트를 NULL로 초기화
		else
		{
			list = NULL;
			char line[51];//입력받을 정보
			while (!read_file.eof())//파일 길이 측정
			{
				read_file.getline(line, 50);//아이디 가져오기
				read_file.getline(line, 50);//비번 가져오기
				this->cnt++;//멤버 수 증가
			}
			if (this->cnt > 0)
			{
				read_file.seekg(0, ios::beg);// 파일 포인터 처음 위치로
				list = new Member[cnt];//리스트 수 + 등록 시 추가할 여유 공간만큼 할당
				for(int i=0;i<this->cnt;i++)
				{
					read_file.getline(line, 50);//아이디 가져오기
					strcpy(list[i].id, line);//비번 가져오기
					read_file.getline(line, 50);//아이디 가져오기
					strcpy(list[i].password, line);//비번 가져오기
			}
			}
			read_file.close();//파일 닫기
		}
	}
	~membership()//멤버쉽 리스트를 파일에 저장함
	{
		ofstream write_file;//파일 쓰기
		write_file.open("member_list.txt");//멤버십 리스트 파일 열기
		for (int i = 0; i < this->cnt; i++)//멤버 수만큼 반복
		{
			if (this->list[i].id[0] != '\0')//멤버가 있는 경우에만
			{
				write_file << this->list[i].id << "\n";//아이디 파일에 출력
				write_file << this->list[i].password;//비번 파일에 출력
				if (i < cnt - 1)//마지막 멤버가 아니면
					write_file << "\n";//개행
			}
		}
		write_file.close();//파일 닫기
	}
	bool login_correct(Member& a) const//아이디, 비번 확인해서 로그인 확인, 로그인 성공하면 아이디, 비번을 a에 저장
	{
		for (int i = 0; i < this->cnt; i++)//멤버 리스트에서 아이디 찾아서 비밀번호 확인
		{
			if (strcmp(a.id, this->list[i].id) == 0)//아이디가 같으면
			{
				Member tmp = decoding(this->list[i]);//복호화
				if (strcmp(a.password, tmp.password) == 0)//비밀번호가 같으면
				{
					strcpy(a.id, tmp.id);//아이디 저장
					strcpy(a.password, tmp.password);//비밀번호 저장
					return 1;
				}
			}
		}
		return 0;
	}
	bool register_member(Member a)//회원가입 함수 성공하면 1, 실패하면 0 반환
	{
		for (int i = 0; i < this->cnt; i++)//리스트에 이미 있는 아이디인지 확인
		{
			if (strcmp(a.id, this->list[i].id) == 0)
				return 0;//이미 있는 아이디면 실패
		}
		if (!ps_correct(a))//비밀번호가 조건에 맞지 않으면
			return 0;//실패
		if (this->cnt == 0)//리스트가 비어있으면
			this->list = new Member[1];
		else//멤버가 늘어날 때마다 한칸씩	늘려줌
		{
			Member* tmp = new Member[this->cnt + 1];//새로운 리스트 생성
			for (int i = 0; i < this->cnt; i++)//기존 리스트 복사
				tmp[i] = this->list[i];
			delete[] this->list;//기존 리스트 삭제
			this->list = tmp;//새로운 리스트로 대체
		}
		this->list[this->cnt] = Encoding(a);//리스트에 추가
		this->cnt++;//멤버 수 증가
		return 1;//성공
	}
	bool ps_correct(Member a) const//비밀번호가 조건에 맞는지 확인, 맞으면 1, 아니면 0 반환
	{
		int alpha = 0, num = 0, special = 0;//알파벳, 숫자, 특수문자가 있는지 확인하는 변수
		if (strlen(a.password) < 10 || strlen(a.password) > 20)//비밀번호 길이가 10자리 미만이거나 20자리 초과이면
			return 0;
		for (int i = 0; i < strlen(a.password); i++)//비밀번호를 한 글자씩 확인
		{
			if (a.password[i] >= 'a' && a.password[i] <= 'z')//소문자
				alpha = 1;
			else if (a.password[i] >= 'A' && a.password[i] <= 'Z')//대문자
				alpha = 1;
			else if (a.password[i] >= '0' && a.password[i] <= '9')//숫자
				num = 1;
			else if (a.password[i] == '!' || a.password[i] == '@' || a.password[i] == '#' || a.password[i] == '$' || a.password[i] == '%' || a.password[i] == '^' || a.password[i] == '&' || a.password[i] == '*')//특수문자
				special = 1;
		}
		if (alpha && num && special)//알파벳, 숫자, 특수문자가 모두 있으면
			return 1;
		else
			return 0;
	}
	void withdraw(Member a)//탈퇴
	{
		for (int i = 0; i < this->cnt; i++)//멤버 리스트에서 아이디 찾아서 삭제
		{
			if (strcmp(a.id, this->list[i].id) == 0)//아이디가 같으면
			{
				this->list[i].id[0] = '\0';//아이디 삭제
				this->list[i].password[0] = '\0';//비밀번호 삭제
			}
		}

	}
	int get_cnt() { return this->cnt; }
	Member Encoding(Member a) const//시저 암호화 함수
	{
		Member b{};
		strcpy(b.id, a.id);
		for (int i = 0; i < strlen(a.password); i++)
		{
			if (a.password[i] >= 'a' && a.password[i] <= 'z')//소문자
			{
				int c = a.password[i] - 'a';
				c+=strlen(a.id);
				c %= 26;
				b.password[i] = c + 'a';//아이디 길이만큼 오른쪽으로 이동
			}
			else if (a.password[i] >= 'A' && a.password[i] <= 'Z')//대문자
			{
				int c = a.password[i] - 'A';
				c += strlen(a.id);
				c %= 26;
				b.password[i] = c + 'A';//아이디 길이만큼 오른쪽으로 이동
			}
			else
				b.password[i] = a.password[i];//알파벳이 아니면 그대로 저장
		}
		return b;
	}
	Member decoding(Member a) const//시저 복호화 함수
	{
		Member b{};//복호화된 정보 저장할 멤버
		strcpy(b.id, a.id);//아이디 복사
		for (int i = 0; i < strlen(a.password); i++)
		{
			if (a.password[i] >= 'a' && a.password[i] <= 'z')//소문자
			{
				int c = a.password[i] - 'a';//알파벳 위치
				c -= strlen(a.id);//아이디 길이만큼 왼쪽으로 이동
				if(c<0)//음수일 때
					c += 26;
				b.password[i] = c + 'a';//아이디 길이만큼 왼쪽으로 이동
			}
			else if (a.password[i] >= 'A' && a.password[i] <= 'Z')//대문자
			{
				int c = a.password[i] - 'A';//알파벳 위치
				c -= strlen(a.id);//아이디 길이만큼 왼쪽으로 이동
				if (c < 0)//음수일 때
					c += 26;
				b.password[i] = c + 'A';//아이디 길이만큼 왼쪽으로 이동
			}
			else
				b.password[i] = a.password[i];//알파벳이 아니면 그대로 저장
		}
		return b;
	}
};

int main()
{
	membership a;
	Member input_user{};//입력받을 멤버
	int input;//입력받을 숫자
	Member login_user{};//로그인한 유저
	int login_flag = 0;//로그인 여부

	while (1)
	{	
		cout << "====================\n";
		if (login_flag)
			cout << "Logged in user : (" << login_user.id << ")\n";//로그인한 유저 출력
		cout << "Menu.\n";
		cout << "1. Login\n";
		cout << "2. Register\n";
		cout << "3. withdraw\n";
		cout << "4. exit\n  :  ";
		cin >> input;
		cout << "--------------------\n";
		if (input == 1)//로그인
		{
			cout << "User id: ";
			cin >> login_user.id;
			cout << "password: ";
			cin >> login_user.password;//아이디와 비밀번호 입력
			cout << "--------------------\n";
			/////로그인 확인
			if (a.login_correct(login_user))//로그인 성공
			{
				cout << "Login successful.\n";//로그인 성공 메시지 출력
				login_flag = 1;//로그인 플래그 설정
			}
			else//로그인 실패
				cout << "Login failed. Invalid user id or password.\n";//로그인 실패 메시지 출력
		}
		else if (input == 2)//등록
		{
			cout << "User id: ";
			cin>>input_user.id;//아이디 입력
			cout << "password: ";
			cin>>input_user.password;//비밀번호 입력
			cout << "--------------------\n";
			if (!a.register_member(input_user))//등록 실패
				cout << "Invalid.\n";
			else
				cout<<"Registeration Successful.\n";//등록 성공 메시지 출력
		}
		else if (input == 3)//탈퇴
		{
			if(!login_flag)
				cout<<"Invalid.\n";//로그인 안했을 때
			else
			{
				a.withdraw(login_user);//탈퇴
				login_flag = 0;//로그인 플래그 해제
				login_user.id[0] = '\0';//로그인한 유저 정보 삭제
				login_user.password[0] = '\0';//로그인한 유저 정보 삭제
				cout<<"Successful withdraw.\n";//탈퇴 성공 메시지 출력
			}
		}
		else if (input ==4)	break;//종료
	}	

	return 0;
}
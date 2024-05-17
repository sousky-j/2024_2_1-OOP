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
		this->cnt = 0;
		ifstream read_file;
		read_file.open("member_list.txt");
		if (read_file.fail())
			list = NULL;
		else
		{
			list = NULL;
			char line[51];//입력받을 정보
			while (!read_file.eof())//파일 길이 측정
			{
				read_file.getline(line, 50);
				read_file.getline(line, 50);
				this->cnt++;
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
			read_file.close();
		}
	}
	~membership()//멤버쉽 리스트를 파일에 저장함
	{
		ofstream write_file;
		write_file.open("member_list.txt");
		for (int i = 0; i < this->cnt; i++)
		{
			if (this->list[i].id[0] != '\0')
			{
				write_file << this->list[i].id << "\n";
				write_file << this->list[i].password;
				if (i < cnt - 1)
					write_file << "\n";
			}
		}
		write_file.close();
	}
	bool login_correct(Member& a) const//아이디, 비번 확인해서 로그인 확인, 로그인 성공하면 아이디, 비번을 a에 저장
	{
		for (int i = 0; i < this->cnt; i++)
		{
			if (strcmp(a.id, this->list[i].id) == 0)
			{
				Member tmp = decoding(this->list[i]);
				if (strcmp(a.password, tmp.password) == 0)
				{
					strcpy(a.id, tmp.id);
					strcpy(a.password, tmp.password);
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
	bool ps_correct(Member a) const
	{
		//비밀번호에 적어도 하나의 알파벳, 하나의 숫자, 하나의 특수문자(!@#$%^&*())가 포함되어야 함
		//최소 10자리 이상, 최대 20자리여야 한다
		int alpha = 0, num = 0, special = 0;
		if (strlen(a.password) < 10 || strlen(a.password) > 20)
			return 0;
		for (int i = 0; i < strlen(a.password); i++)
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
		if (alpha && num && special)
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
		//비밀번호를 시저 암호화
		//알파벳은 대소문자 구분 있게 암호화
		//숫자와 특수문자는 암호화하지 않음
		//암호화는 아이디의 길이만큼 오른쪽으로 이동
		Member b{};
		strcpy(b.id, a.id);
		for (int i = 0; i < strlen(a.password); i++)
		{
			if (a.password[i] >= 'a' && a.password[i] <= 'z')//소문자
			{
				b.password[i] = a.password[i] + strlen(a.id);
				if (b.password[i] > 'z')
					b.password[i] -= 26;
			}
			else if (a.password[i] >= 'A' && a.password[i] <= 'Z')//대문자
			{
				b.password[i] = a.password[i] + strlen(a.id);
				if (b.password[i] > 'Z')
					b.password[i] -= 26;
			}
			else
				b.password[i] = a.password[i];
		}
		return b;
	}
	Member decoding(Member a) const//시저 복호화 함수
	{
		//비밀번호를 시저 복호화
		//알파벳은 대소문자 구분 있게 복호화
		//숫자와 특수문자는 복호화하지 않음
		//복호화는 아이디의 길이만큼 왼쪽으로 이동
		Member b{};
		strcpy(b.id, a.id);
		for (int i = 0; i < strlen(a.password); i++)
		{
			if (a.password[i] >= 'a' && a.password[i] <= 'z')//소문자
			{
				b.password[i] = a.password[i] - strlen(a.id);
				if (b.password[i] < 'a')
					b.password[i] += 26;
			}
			else if (a.password[i] >= 'A' && a.password[i] <= 'Z')//대문자
			{
				b.password[i] = a.password[i] - strlen(a.id);
				if (b.password[i] < 'A')
					b.password[i] += 26;
			}
			else
				b.password[i] = a.password[i];
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
			cin>>input_user.id;
			cout << "password: ";
			cin>>input_user.password;
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
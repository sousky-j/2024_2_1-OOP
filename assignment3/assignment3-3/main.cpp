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
	int cnt; //����� ���� üũ�ϴ� ����
public:
	membership()//����� Ŭ������ �����ϸ� ���Ͽ��� ����� ����Ʈ�� ���� ������
	{
		this->cnt = 0;//��� �� �ʱ�ȭ
		ifstream read_file;//���� �б�
		read_file.open("member_list.txt");//����� ����Ʈ ���� ����
		if (read_file.fail())//������ ������
			list = NULL;//����Ʈ�� NULL�� �ʱ�ȭ
		else
		{
			list = NULL;
			char line[51];//�Է¹��� ����
			while (!read_file.eof())//���� ���� ����
			{
				read_file.getline(line, 50);//���̵� ��������
				read_file.getline(line, 50);//��� ��������
				this->cnt++;//��� �� ����
			}
			if (this->cnt > 0)
			{
				read_file.seekg(0, ios::beg);// ���� ������ ó�� ��ġ��
				list = new Member[cnt];//����Ʈ �� + ��� �� �߰��� ���� ������ŭ �Ҵ�
				for(int i=0;i<this->cnt;i++)
				{
					read_file.getline(line, 50);//���̵� ��������
					strcpy(list[i].id, line);//��� ��������
					read_file.getline(line, 50);//���̵� ��������
					strcpy(list[i].password, line);//��� ��������
			}
			}
			read_file.close();//���� �ݱ�
		}
	}
	~membership()//����� ����Ʈ�� ���Ͽ� ������
	{
		ofstream write_file;//���� ����
		write_file.open("member_list.txt");//����� ����Ʈ ���� ����
		for (int i = 0; i < this->cnt; i++)//��� ����ŭ �ݺ�
		{
			if (this->list[i].id[0] != '\0')//����� �ִ� ��쿡��
			{
				write_file << this->list[i].id << "\n";//���̵� ���Ͽ� ���
				write_file << this->list[i].password;//��� ���Ͽ� ���
				if (i < cnt - 1)//������ ����� �ƴϸ�
					write_file << "\n";//����
			}
		}
		write_file.close();//���� �ݱ�
	}
	bool login_correct(Member& a) const//���̵�, ��� Ȯ���ؼ� �α��� Ȯ��, �α��� �����ϸ� ���̵�, ����� a�� ����
	{
		for (int i = 0; i < this->cnt; i++)//��� ����Ʈ���� ���̵� ã�Ƽ� ��й�ȣ Ȯ��
		{
			if (strcmp(a.id, this->list[i].id) == 0)//���̵� ������
			{
				Member tmp = decoding(this->list[i]);//��ȣȭ
				if (strcmp(a.password, tmp.password) == 0)//��й�ȣ�� ������
				{
					strcpy(a.id, tmp.id);//���̵� ����
					strcpy(a.password, tmp.password);//��й�ȣ ����
					return 1;
				}
			}
		}
		return 0;
	}
	bool register_member(Member a)//ȸ������ �Լ� �����ϸ� 1, �����ϸ� 0 ��ȯ
	{
		for (int i = 0; i < this->cnt; i++)//����Ʈ�� �̹� �ִ� ���̵����� Ȯ��
		{
			if (strcmp(a.id, this->list[i].id) == 0)
				return 0;//�̹� �ִ� ���̵�� ����
		}
		if (!ps_correct(a))//��й�ȣ�� ���ǿ� ���� ������
			return 0;//����
		if (this->cnt == 0)//����Ʈ�� ���������
			this->list = new Member[1];
		else//����� �þ ������ ��ĭ��	�÷���
		{
			Member* tmp = new Member[this->cnt + 1];//���ο� ����Ʈ ����
			for (int i = 0; i < this->cnt; i++)//���� ����Ʈ ����
				tmp[i] = this->list[i];
			delete[] this->list;//���� ����Ʈ ����
			this->list = tmp;//���ο� ����Ʈ�� ��ü
		}
		this->list[this->cnt] = Encoding(a);//����Ʈ�� �߰�
		this->cnt++;//��� �� ����
		return 1;//����
	}
	bool ps_correct(Member a) const//��й�ȣ�� ���ǿ� �´��� Ȯ��, ������ 1, �ƴϸ� 0 ��ȯ
	{
		int alpha = 0, num = 0, special = 0;//���ĺ�, ����, Ư�����ڰ� �ִ��� Ȯ���ϴ� ����
		if (strlen(a.password) < 10 || strlen(a.password) > 20)//��й�ȣ ���̰� 10�ڸ� �̸��̰ų� 20�ڸ� �ʰ��̸�
			return 0;
		for (int i = 0; i < strlen(a.password); i++)//��й�ȣ�� �� ���ھ� Ȯ��
		{
			if (a.password[i] >= 'a' && a.password[i] <= 'z')//�ҹ���
				alpha = 1;
			else if (a.password[i] >= 'A' && a.password[i] <= 'Z')//�빮��
				alpha = 1;
			else if (a.password[i] >= '0' && a.password[i] <= '9')//����
				num = 1;
			else if (a.password[i] == '!' || a.password[i] == '@' || a.password[i] == '#' || a.password[i] == '$' || a.password[i] == '%' || a.password[i] == '^' || a.password[i] == '&' || a.password[i] == '*')//Ư������
				special = 1;
		}
		if (alpha && num && special)//���ĺ�, ����, Ư�����ڰ� ��� ������
			return 1;
		else
			return 0;
	}
	void withdraw(Member a)//Ż��
	{
		for (int i = 0; i < this->cnt; i++)//��� ����Ʈ���� ���̵� ã�Ƽ� ����
		{
			if (strcmp(a.id, this->list[i].id) == 0)//���̵� ������
			{
				this->list[i].id[0] = '\0';//���̵� ����
				this->list[i].password[0] = '\0';//��й�ȣ ����
			}
		}

	}
	int get_cnt() { return this->cnt; }
	Member Encoding(Member a) const//���� ��ȣȭ �Լ�
	{
		Member b{};
		strcpy(b.id, a.id);
		for (int i = 0; i < strlen(a.password); i++)
		{
			if (a.password[i] >= 'a' && a.password[i] <= 'z')//�ҹ���
			{
				int c = a.password[i] - 'a';
				c+=strlen(a.id);
				c %= 26;
				b.password[i] = c + 'a';//���̵� ���̸�ŭ ���������� �̵�
			}
			else if (a.password[i] >= 'A' && a.password[i] <= 'Z')//�빮��
			{
				int c = a.password[i] - 'A';
				c += strlen(a.id);
				c %= 26;
				b.password[i] = c + 'A';//���̵� ���̸�ŭ ���������� �̵�
			}
			else
				b.password[i] = a.password[i];//���ĺ��� �ƴϸ� �״�� ����
		}
		return b;
	}
	Member decoding(Member a) const//���� ��ȣȭ �Լ�
	{
		Member b{};//��ȣȭ�� ���� ������ ���
		strcpy(b.id, a.id);//���̵� ����
		for (int i = 0; i < strlen(a.password); i++)
		{
			if (a.password[i] >= 'a' && a.password[i] <= 'z')//�ҹ���
			{
				int c = a.password[i] - 'a';//���ĺ� ��ġ
				c -= strlen(a.id);//���̵� ���̸�ŭ �������� �̵�
				if(c<0)//������ ��
					c += 26;
				b.password[i] = c + 'a';//���̵� ���̸�ŭ �������� �̵�
			}
			else if (a.password[i] >= 'A' && a.password[i] <= 'Z')//�빮��
			{
				int c = a.password[i] - 'A';//���ĺ� ��ġ
				c -= strlen(a.id);//���̵� ���̸�ŭ �������� �̵�
				if (c < 0)//������ ��
					c += 26;
				b.password[i] = c + 'A';//���̵� ���̸�ŭ �������� �̵�
			}
			else
				b.password[i] = a.password[i];//���ĺ��� �ƴϸ� �״�� ����
		}
		return b;
	}
};

int main()
{
	membership a;
	Member input_user{};//�Է¹��� ���
	int input;//�Է¹��� ����
	Member login_user{};//�α����� ����
	int login_flag = 0;//�α��� ����

	while (1)
	{	
		cout << "====================\n";
		if (login_flag)
			cout << "Logged in user : (" << login_user.id << ")\n";//�α����� ���� ���
		cout << "Menu.\n";
		cout << "1. Login\n";
		cout << "2. Register\n";
		cout << "3. withdraw\n";
		cout << "4. exit\n  :  ";
		cin >> input;
		cout << "--------------------\n";
		if (input == 1)//�α���
		{
			cout << "User id: ";
			cin >> login_user.id;
			cout << "password: ";
			cin >> login_user.password;//���̵�� ��й�ȣ �Է�
			cout << "--------------------\n";
			/////�α��� Ȯ��
			if (a.login_correct(login_user))//�α��� ����
			{
				cout << "Login successful.\n";//�α��� ���� �޽��� ���
				login_flag = 1;//�α��� �÷��� ����
			}
			else//�α��� ����
				cout << "Login failed. Invalid user id or password.\n";//�α��� ���� �޽��� ���
		}
		else if (input == 2)//���
		{
			cout << "User id: ";
			cin>>input_user.id;//���̵� �Է�
			cout << "password: ";
			cin>>input_user.password;//��й�ȣ �Է�
			cout << "--------------------\n";
			if (!a.register_member(input_user))//��� ����
				cout << "Invalid.\n";
			else
				cout<<"Registeration Successful.\n";//��� ���� �޽��� ���
		}
		else if (input == 3)//Ż��
		{
			if(!login_flag)
				cout<<"Invalid.\n";//�α��� ������ ��
			else
			{
				a.withdraw(login_user);//Ż��
				login_flag = 0;//�α��� �÷��� ����
				login_user.id[0] = '\0';//�α����� ���� ���� ����
				login_user.password[0] = '\0';//�α����� ���� ���� ����
				cout<<"Successful withdraw.\n";//Ż�� ���� �޽��� ���
			}
		}
		else if (input ==4)	break;//����
	}	

	return 0;
}
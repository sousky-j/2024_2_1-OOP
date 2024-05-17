#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <ctime>
using namespace std;
class Time
{
private:
	int hour;
	int minute;
	int second;
public:
	Time(int hour, int minute, int sec)//������
	{//�ð� ����
		this->hour = hour;
		this->minute = minute;
		this->second = sec;
	}
	~Time()//�Ҹ���
	{//�ð� �ʱ�ȭ
		this->hour = 0;
		this->minute = 0;
		this->second = 0;
	}
	void setTime(int hour, int min, int sec)//�ð� ����
	{//���ڷ� ���� ���� �ð��� ������
		this->hour = hour;
		this->minute = min;
		this->second = sec;
	}
	void addTime(int sec)//�ð� �߰�
	{
		this->second += sec;//�� �߰�
		if (this->second >= 60)//�� �߰�
		{
			this->minute += this->second / 60;//���� �п� ����
			this->second %= 60;//�ʸ� 60���� ���� �������� �ʷ� ����
		}
		if (this->minute >= 60)//�ð� �߰�
		{
			this->hour += this->minute / 60;//���� �ð��� ����
			this->hour %= 24;//�ð��� 24�� ���� �������� �ð����� ����
			this->minute %= 60;//���� 60���� ���� �������� ������ ����
		}
	}
	void printTime()
	{
		cout.fill('0');//���ڸ��� 0���� ä��
		cout.width(2);//��� ���� 2�� ����
		cout << this->hour << ":";//�ð� ���
		cout.fill('0');//���ڸ��� 0���� ä��
		cout.width(2);//��� ���� 2�� ����
		cout << this->minute << ":";//�� ���
		cout.fill('0');//���ڸ��� 0���� ä��
		cout.width(2);//��� ���� 2�� ����
		cout << this->second << "\n";//�� ���
	}
};

class Korea : public Time
{
public:
	Korea(int hour, int minute, int sec) : Time(hour, minute, sec)//������ ȣ�� �� Time ������ ȣ��
	{
		setTime(hour, minute, sec);//�ѱ� �ð��� ����
	}
	~Korea() {	}
};
class WashingtonDC : public Time
{
public:
	WashingtonDC(int hour, int minute, int sec) : Time(hour, minute, sec)//������ ȣ�� �� Time ������ ȣ��
	{
		setTime(hour, minute, sec);//�̱� �ð��� ����
	}
	~WashingtonDC() {	}
};
class Paris : public Time
{
public:
Paris(int hour, int minute, int sec) : Time(hour, minute, sec)//������ ȣ�� �� Time ������ ȣ��
	{
		setTime(hour, minute, sec);//������ �ð��� ����
	}
	~Paris() {	}
};
class GreenwichObservatory : public Time
{
public:
	GreenwichObservatory(int hour, int minute, int sec) : Time(hour, minute, sec)//������ ȣ�� �� Time ������ ȣ��
	{
		setTime(hour, minute, sec);//�׸���ġ �ð��� ����
	}
	~GreenwichObservatory() {	}
};

int main()
{
	//create object
	Korea korea_time(0, 0, 0);
	WashingtonDC washingtonDC_time(0, 0, 0);
	Paris paris_time(0, 0, 0);
	GreenwichObservatory greenwich_time(0, 0, 0);

	string input;
	string command[4] = { "setting","add","print","exit" };//command
	while (1)
	{
		cout << "Command : ";
		cin >> input;
		if (!input.compare(command[0]))//setting
		{
			int init=static_cast<unsigned int>(time(0));//current time
			srand(init);//seed setting
			int hour = rand() % 24;//random time setting
			int minute = rand() % 60;//random time setting
			int sec = rand() % 60;//random time setting
			greenwich_time.setTime(hour, minute, sec);//greenwich time setting
			if(hour-5<0)
				washingtonDC_time.setTime(hour + 24 - 5, minute, sec);
			else
				washingtonDC_time.setTime(hour - 5, minute, sec);
			if(hour+1>=24)
				paris_time.setTime(hour + 1 - 24, minute, sec);//paris time setting
			else
				paris_time.setTime(hour + 1, minute, sec);//paris time setting 
			if(hour+8>=24)
				korea_time.setTime(hour + 8 - 24, minute, sec);//korea time setting
			else
				korea_time.setTime(hour + 8, minute, sec);//korea time setting
		}
		else if (!input.compare(command[1]))//add
		{
			int sec;
			cin>> sec;
			korea_time.addTime(sec);//�ð� �߰�
			washingtonDC_time.addTime(sec);//�ð� �߰�
			paris_time.addTime(sec);//�ð� �߰�
			greenwich_time.addTime(sec);//�ð� �߰�
		}
		else if (!input.compare(command[2]))//print
		{//�ð� ���
			cout << "\nOutput :\n";

			cout << "Korea\t\t\t = ";//�ѱ� �ð���
			korea_time.printTime();
			cout << "WashingtonDC\t\t = ";//�̱� �ð���
			washingtonDC_time.printTime();
			cout << "Paris\t\t\t = ";//������ �ð���
			paris_time.printTime();
			cout << "GreenwichObservatory\t = ";//�׸���ġ �ð���
			greenwich_time.printTime();
			cout << "\n";
		}
		else if (!input.compare(command[3]))	break;//exit
	}
	return 0;
}
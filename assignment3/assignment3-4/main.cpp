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
	Time(int hour, int minute, int sec)//생성자
	{//시간 설정
		this->hour = hour;
		this->minute = minute;
		this->second = sec;
	}
	~Time()//소멸자
	{//시간 초기화
		this->hour = 0;
		this->minute = 0;
		this->second = 0;
	}
	void setTime(int hour, int min, int sec)//시간 설정
	{//인자로 전달 받은 시간을 세팅함
		this->hour = hour;
		this->minute = min;
		this->second = sec;
	}
	void addTime(int sec)//시간 추가
	{
		this->second += sec;//초 추가
		if (this->second >= 60)//분 추가
		{
			this->minute += this->second / 60;//몫을 분에 더함
			this->second %= 60;//초를 60으로 나눈 나머지를 초로 설정
		}
		if (this->minute >= 60)//시간 추가
		{
			this->hour += this->minute / 60;//몫을 시간에 더함
			this->hour %= 24;//시간을 24로 나눈 나머지를 시간으로 설정
			this->minute %= 60;//분을 60으로 나눈 나머지를 분으로 설정
		}
	}
	void printTime()
	{
		cout.fill('0');//빈자리를 0으로 채움
		cout.width(2);//출력 폭을 2로 설정
		cout << this->hour << ":";//시간 출력
		cout.fill('0');//빈자리를 0으로 채움
		cout.width(2);//출력 폭을 2로 설정
		cout << this->minute << ":";//분 출력
		cout.fill('0');//빈자리를 0으로 채움
		cout.width(2);//출력 폭을 2로 설정
		cout << this->second << "\n";//초 출력
	}
};

class Korea : public Time
{
public:
	Korea(int hour, int minute, int sec) : Time(hour, minute, sec)//생성자 호출 시 Time 생성자 호출
	{
		setTime(hour, minute, sec);//한국 시간대 설정
	}
	~Korea() {	}
};
class WashingtonDC : public Time
{
public:
	WashingtonDC(int hour, int minute, int sec) : Time(hour, minute, sec)//생성자 호출 시 Time 생성자 호출
	{
		setTime(hour, minute, sec);//미국 시간대 설정
	}
	~WashingtonDC() {	}
};
class Paris : public Time
{
public:
Paris(int hour, int minute, int sec) : Time(hour, minute, sec)//생성자 호출 시 Time 생성자 호출
	{
		setTime(hour, minute, sec);//프랑스 시간대 설정
	}
	~Paris() {	}
};
class GreenwichObservatory : public Time
{
public:
	GreenwichObservatory(int hour, int minute, int sec) : Time(hour, minute, sec)//생성자 호출 시 Time 생성자 호출
	{
		setTime(hour, minute, sec);//그리니치 시간대 설정
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
			korea_time.addTime(sec);//시간 추가
			washingtonDC_time.addTime(sec);//시간 추가
			paris_time.addTime(sec);//시간 추가
			greenwich_time.addTime(sec);//시간 추가
		}
		else if (!input.compare(command[2]))//print
		{//시간 출력
			cout << "\nOutput :\n";

			cout << "Korea\t\t\t = ";//한국 시간대
			korea_time.printTime();
			cout << "WashingtonDC\t\t = ";//미국 시간대
			washingtonDC_time.printTime();
			cout << "Paris\t\t\t = ";//프랑스 시간대
			paris_time.printTime();
			cout << "GreenwichObservatory\t = ";//그리니치 시간대
			greenwich_time.printTime();
			cout << "\n";
		}
		else if (!input.compare(command[3]))	break;//exit
	}
	return 0;
}
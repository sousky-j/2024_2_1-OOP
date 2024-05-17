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
	Time(int hour, int minute, int sec)
	{
		this->hour = hour;
		this->minute = minute;
		this->second = sec;
	}
	~Time()
	{
		this->hour = 0;
		this->minute = 0;
		this->second = 0;
	}
	void setTime(int hour, int min, int sec)
	{
		this->hour = hour;
		this->minute = min;
		this->second = sec;
	}
	void addTime(int sec)
	{
		this->second += sec;
		if (this->second >= 60)
		{
			this->minute += this->second / 60;
			this->second %= 60;
		}
		if (this->minute >= 60)
		{
			this->hour += this->minute / 60;
			this->hour %= 24;
			this->minute %= 60;
		}
	}
	void printTime()
	{
		cout.fill('0');
		cout.width(2);
		cout << this->hour << ":";
		cout.fill('0');
		cout.width(2);
		cout << this->minute << ":";
		cout.fill('0');
		cout.width(2);
		cout << this->second << "\n";
	}
};

class Korea : public Time
{
public:
	Korea(int hour, int minute, int sec) : Time(hour, minute, sec)
	{
		setTime(hour, minute, sec);
	}
	~Korea() {	}
};
class WashingtonDC : public Time
{
public:
	WashingtonDC(int hour, int minute, int sec) : Time(hour, minute, sec)
	{
		setTime(hour, minute, sec);
	}
	~WashingtonDC() {	}
};
class Paris : public Time
{
public:
Paris(int hour, int minute, int sec) : Time(hour, minute, sec)
	{
		setTime(hour, minute, sec);
	}
	~Paris() {	}
};
class GreenwichObservatory : public Time
{
public:
	GreenwichObservatory(int hour, int minute, int sec) : Time(hour, minute, sec)
	{
		setTime(hour, minute, sec);
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
			korea_time.addTime(sec);
			washingtonDC_time.addTime(sec);
			paris_time.addTime(sec);
			greenwich_time.addTime(sec);
		}
		else if (!input.compare(command[2]))//print
		{
			cout << "\nOutput :\n";

			cout << "Korea\t\t\t = ";
			korea_time.printTime();
			cout << "WashingtonDC\t\t = ";
			washingtonDC_time.printTime();
			cout << "Paris\t\t\t = ";
			paris_time.printTime();
			cout << "GreenwichObservatory\t = ";
			greenwich_time.printTime();
			cout << "\n";
		}
		else if (!input.compare(command[3]))	break;//exit
	}
	return 0;
}
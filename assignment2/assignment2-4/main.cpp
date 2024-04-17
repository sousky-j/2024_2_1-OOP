#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

char input_string[101];
char delimiter[11];
bool check[100];
int my_strlen(char* arr);
bool Iscorrect(int i, int delimiter_len);
int main(void)
{
	cout << "Enter the string : ";
	cin.getline(input_string, 100);
	cout << "Enter the delimiter : ";
	cin.getline(delimiter, 10);
	cout << "\n";

	int string_len = my_strlen(input_string), delimiter_len = my_strlen(delimiter);
	int search_len = string_len - delimiter_len;
	
	for (int i = 0; i < search_len; i++)
	{
		if (Iscorrect(i, delimiter_len))
		{
			for (int k = 0; k < delimiter_len; k++)
				check[i + k] = true;
		}
	}

	bool sequence_flag = true;
	
	cout << "Separated tokens :\n";
	for (int i = 0; i < string_len; i++)
	{
		if (!check[i])
		{
			if (!sequence_flag)
			{
				cout << "\n" << input_string[i];
				sequence_flag = true;
			}
			else	cout << input_string[i];
		}
		else	sequence_flag = false;
	}
	return 0;
}

int my_strlen(char* arr)
{
	int len = 0;
	for (int i = 0; i < 100; i++)
	{
		if (arr[i] == '\0')
			return len;
		len++;
	}
	return len;
}

bool Iscorrect(int i, int delimiter_len)
{
	for (int k = 0; k < delimiter_len; k++)
	{
		if (input_string[i + k] != delimiter[k])
			return false;
	}
	return true;
}
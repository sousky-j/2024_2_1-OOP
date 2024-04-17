#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <ctime>
#define SWP(x,y,tmp) ( (tmp)=(x), (x)=(y), (y)=(tmp) )
using namespace std;

void print_matrix(int** mat);
void print_marix(int** mat, int* sum);
void rows_Descending_sort(int** mat);
void sum_ascending_sort(int** mat, int* sum);

int main(void)
{
	int init = static_cast<unsigned int>(time(NULL)); //현재 시간을 시드값으로 초기화 설정
	srand(init);// 시드값 설정
	int** mat = new int* [10];
	for (int i = 0; i < 10; i++)
		*(mat + i) = new int[10];
	int* sum = new int[10];
	for (int i = 0; i < 10; i++)
	{
		*(sum + i) = 0;
		for (int j = 0; j < 10; j++)
		{
			*(*(mat + i) + j) = rand() % 101;
			*(sum + i) += *(*(mat + i) + j);
		}
	}
	cout << "Original Matrix:\n";
	print_matrix(mat);
	rows_Descending_sort(mat);
	cout << "Sort of Row (Descending Order):\n";
	print_marix(mat, sum);
	sum_ascending_sort(mat, sum);
	cout << "Sort of Sum (Ascending Order):\n";
	print_marix(mat, sum);
	for (int i = 0; i < 10; i++)
		delete[] * (mat + i);
	delete[] mat;
	delete[] sum;
	return 0;
}

void print_matrix(int** mat)
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
			cout << *(*(mat + i) + j) << "\t";
		cout << "\n";
	}
	cout << "\n";
}

void print_marix(int** mat, int* sum)
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
			cout << *(*(mat + i) + j) << "\t";
		cout << "| Sum: " << *(sum + i);
		cout << "\n";
	}
	cout << "\n";
}

void rows_Descending_sort(int** mat)
{
	int tmp;
	for (int rows = 0; rows < 10; rows++)
	{
		for (int i = 0; i < 9; i++)
		{
			int k = i;
			for (int j = i + 1; j < 10; j++)
			{
				if (*(*(mat + rows) + k) < *(*(mat + rows) + j))
					k = j;
			}
			if (k != i)
				SWP(*(*(mat + rows) + i), *(*(mat + rows) + k), tmp);
		}
	}
}

void sum_ascending_sort(int** mat, int* sum)
{
	for (int i = 0; i < 9; i++)
	{
		int k = i;
		for (int j = i + 1; j < 10; j++)
		{
			if (*(sum + k) > *(sum + j))
				k = j;
		}
		if (k != i)
		{
			int tmp;
			for (int j = 0; j < 10; j++)
				SWP(*(*(mat + i) + j), *(*(mat + k) + j), tmp);
			SWP(*(sum + i), *(sum + k), tmp);
		}
	}
}
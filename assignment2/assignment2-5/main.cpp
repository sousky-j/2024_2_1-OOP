#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;
void hadamard_mat(int rows, int cols, int power_n, bool invert_minus);
int** mat;
int main(void)
{
	int n, power_n = 1;
	cout << "Enter the value of n for Hadamard matrix (2^n x 2^n): ";
	cin >> n;
	for (int i = 0; i < n; i++)
		power_n *= 2;
	mat = new int* [power_n];
	for (int i = 0; i < power_n; i++)
		*(mat + i) = new int[power_n];
	hadamard_mat(0, 0, power_n, 0);
	cout << "\nHadamard Matrix of size " << power_n << "x" << power_n << ":\n";
	for (int i = 0; i < power_n; i++)
	{
		for (int j = 0; j < power_n; j++)
			cout << *(*(mat + i) + j) << "\t";
		cout << "\n";
	}
	for (int i = 0; i < power_n; i++)
		delete[] mat[i];
	delete[] mat;
	return 0;
}

void hadamard_mat(int rows, int cols, int power_n, bool invert_minus)
{
	if (power_n == 1)
	{
		if (!invert_minus) mat[rows][cols] = 1;
		else mat[rows][cols] = -1;
	}
	else
	{
		power_n /= 2;
		if(invert_minus)
		{
			hadamard_mat(rows, cols, power_n, 1);
			hadamard_mat(rows, cols + power_n, power_n, 1);
			hadamard_mat(rows + power_n, cols, power_n, 1);
			hadamard_mat(rows + power_n, cols + power_n, power_n, 0);
		}
		else
		{
			hadamard_mat(rows, cols, power_n, 0);
			hadamard_mat(rows, cols + power_n, power_n, 0);
			hadamard_mat(rows + power_n, cols, power_n, 0);
			hadamard_mat(rows + power_n, cols + power_n, power_n, 1);
		}
	}
}
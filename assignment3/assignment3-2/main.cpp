#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <ctime>
using namespace std;

class Matrix {
private:
	double data[4][4];
public:
	Matrix();
	~Matrix();
	Matrix operator+(Matrix& mtx)
	{
		Matrix out;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				out.data[i][j] = this->data[i][j] + mtx.data[i][j];
		return out;
	}
	Matrix operator-(Matrix& mtx)
	{
		Matrix out;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				out.data[i][j] = this->data[i][j] - mtx.data[i][j];
		return out;
	}
	Matrix operator*(Matrix& mtx)
	{
		Matrix out;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				for (int k = 0; k < 4; k++)
					out.data[i][j] += this->data[i][k] * mtx.data[k][j];
			}
		}
		return out;
	}
	Matrix operator+(int Scalar)
	{
		Matrix out;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				out.data[i][j] = this->data[i][j] + Scalar;
		return out;
	}
	Matrix operator-(int Scalar)
	{
		Matrix out;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				out.data[i][j] = this->data[i][j] - Scalar;
		return out;
	}
	Matrix operator*(int Scalar)
	{
		Matrix out;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				out.data[i][j] = this->data[i][j] * Scalar;
		return out;
	}
	Matrix operator/(int Scalar)
	{
		Matrix out;
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				out.data[i][j] = this->data[i][j] / Scalar;
		return out;
	}
	void setValue(double arr[4][4])
	{
		for (int i = 0; i < 4; i++)
			for (int j = 0; j < 4; j++)
				this->data[i][j] = arr[i][j];
	}
	void display()
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
				cout << this->data[i][j] << " ";
			cout << "\n";
		}
		cout << "\n";
	}
};

int main()
{
	Matrix mat1, mat2;

	double arr1[4][4]{
		{0,0,0,0},
		{1,1,1,1},
		{2,2,2,2},
		{3,3,3,3}
	};

	double arr2[4][4]{
		{0,1,2,3},
		{0,1,2,3},
		{0,1,2,3},
		{0,1,2,3},
	};

	mat1.setValue(arr1);
	mat2.setValue(arr2);

	Matrix mat3 = mat1 + mat2;

	cout << "Matrix 1:" << "\n";
	mat1.display();
	cout << "Matrix 2:" << "\n";
	mat2.display();
	cout << "Matrix 3:" << "\n";
	mat3.display();
	return 0;
}

Matrix:: Matrix()
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			this->data[i][j] = 0;
}
Matrix::~Matrix()
{
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			this->data[i][j] = 0;
}
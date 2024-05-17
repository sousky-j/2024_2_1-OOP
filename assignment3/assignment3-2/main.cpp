#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <ctime>
using namespace std;

class Matrix {
private:
	double data[4][4];// 4x4 matrix
public:
	Matrix();
	~Matrix();
	Matrix operator+(Matrix& mtx)
	{
		Matrix out;//반환할 객체
		for (int i = 0; i < 4; i++)//행만큼
			for (int j = 0; j < 4; j++)//열만큼
				out.data[i][j] = this->data[i][j] + mtx.data[i][j];//두 행렬의 같은 위치의 원소를 더함
		return out;//결과 반환
	}
	Matrix operator-(Matrix& mtx)
	{
		Matrix out;//반환할 객체
		for (int i = 0; i < 4; i++)//행만큼
			for (int j = 0; j < 4; j++)//열만큼
				out.data[i][j] = this->data[i][j] - mtx.data[i][j];//두 행렬의 같은 위치의 원소를 뺌
		return out;//결과 반환
	}
	Matrix operator*(Matrix& mtx)
	{
		Matrix out;//반환할 객체
		for (int i = 0; i < 4; i++)//행만큼
		{
			for (int j = 0; j < 4; j++)//열만큼
			{
				for (int k = 0; k < 4; k++)//곱셈을 위한 반복문
					out.data[i][j] += this->data[i][k] * mtx.data[k][j];//행렬의 곱셈
			}
		}
		return out;//결과 반환
	}
	Matrix operator+(int Scalar)
	{
		Matrix out;//반환할 객체
		for (int i = 0; i < 4; i++)//행만큼
			for (int j = 0; j < 4; j++)//열만큼
				out.data[i][j] = this->data[i][j] + Scalar;//스칼라 덧셈
		return out;//결과 반환
	}
	Matrix operator-(int Scalar)
	{
		Matrix out;//반환할 객체
		for (int i = 0; i < 4; i++)//행만큼
			for (int j = 0; j < 4; j++)//열만큼
				out.data[i][j] = this->data[i][j] - Scalar;//스칼라 뺄셈
		return out;//결과 반환
	}
	Matrix operator*(int Scalar)
	{
		Matrix out;//반환할 객체
		for (int i = 0; i < 4; i++)//행만큼
			for (int j = 0; j < 4; j++)//열만큼
				out.data[i][j] = this->data[i][j] * Scalar;//스칼라 곱셈
		return out;//결과 반환
	}
	Matrix operator/(int Scalar)
	{
		Matrix out;//반환할 객체
		for (int i = 0; i < 4; i++)//행만큼
			for (int j = 0; j < 4; j++)//열만큼
				out.data[i][j] = this->data[i][j] / Scalar;//스칼라 나눗셈
		return out;//결과 반환
	}
	void setValue(double arr[4][4])
	{
		for (int i = 0; i < 4; i++)//행만큼
			for (int j = 0; j < 4; j++)//열만큼
				this->data[i][j] = arr[i][j];//배열을 행렬에 대입
	}
	void display()
	{
		for (int i = 0; i < 4; i++)//행만큼
		{
			for (int j = 0; j < 4; j++)//열만큼
				cout << this->data[i][j] << " ";//행렬 요소 출력
			cout << "\n";
		}
		cout << "\n";
	}
};

int main()
{
	Matrix mat1, mat2;//행렬 객체 생성

	double arr1[4][4]{//행렬 초기화
		{0,0,0,0},
		{1,1,1,1},
		{2,2,2,2},
		{3,3,3,3}
	};

	double arr2[4][4]{//행렬 초기화
		{0,1,2,3},
		{0,1,2,3},
		{0,1,2,3},
		{0,1,2,3},
	};

	mat1.setValue(arr1);//행렬 값 세팅
	mat2.setValue(arr2);//행렬 값 세팅

	Matrix mat3 = mat1 + mat2;//행렬 덧셈

	//////////출력//////////
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
	for (int i = 0; i < 4; i++)//행만큼
		for (int j = 0; j < 4; j++)//열만큼
			this->data[i][j] = 0;//행렬 초기화
}
Matrix::~Matrix()
{
	for (int i = 0; i < 4; i++)//행만큼
		for (int j = 0; j < 4; j++)//열만큼
			this->data[i][j] = 0;//행렬 초기화
}
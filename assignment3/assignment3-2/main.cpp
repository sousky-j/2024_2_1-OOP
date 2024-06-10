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
		Matrix out;//��ȯ�� ��ü
		for (int i = 0; i < 4; i++)//�ุŭ
			for (int j = 0; j < 4; j++)//����ŭ
				out.data[i][j] = this->data[i][j] + mtx.data[i][j];//�� ����� ���� ��ġ�� ���Ҹ� ����
		return out;//��� ��ȯ
	}
	Matrix operator-(Matrix& mtx)
	{
		Matrix out;//��ȯ�� ��ü
		for (int i = 0; i < 4; i++)//�ุŭ
			for (int j = 0; j < 4; j++)//����ŭ
				out.data[i][j] = this->data[i][j] - mtx.data[i][j];//�� ����� ���� ��ġ�� ���Ҹ� ��
		return out;//��� ��ȯ
	}
	Matrix operator*(Matrix& mtx)
	{
		Matrix out;//��ȯ�� ��ü
		for (int i = 0; i < 4; i++)//�ุŭ
		{
			for (int j = 0; j < 4; j++)//����ŭ
			{
				for (int k = 0; k < 4; k++)//������ ���� �ݺ���
					out.data[i][j] += this->data[i][k] * mtx.data[k][j];//����� ����
			}
		}
		return out;//��� ��ȯ
	}
	Matrix operator+(int Scalar)
	{
		Matrix out;//��ȯ�� ��ü
		for (int i = 0; i < 4; i++)//�ุŭ
			for (int j = 0; j < 4; j++)//����ŭ
				out.data[i][j] = this->data[i][j] + Scalar;//��Į�� ����
		return out;//��� ��ȯ
	}
	Matrix operator-(int Scalar)
	{
		Matrix out;//��ȯ�� ��ü
		for (int i = 0; i < 4; i++)//�ุŭ
			for (int j = 0; j < 4; j++)//����ŭ
				out.data[i][j] = this->data[i][j] - Scalar;//��Į�� ����
		return out;//��� ��ȯ
	}
	Matrix operator*(int Scalar)
	{
		Matrix out;//��ȯ�� ��ü
		for (int i = 0; i < 4; i++)//�ุŭ
			for (int j = 0; j < 4; j++)//����ŭ
				out.data[i][j] = this->data[i][j] * Scalar;//��Į�� ����
		return out;//��� ��ȯ
	}
	Matrix operator/(int Scalar)
	{
		Matrix out;//��ȯ�� ��ü
		for (int i = 0; i < 4; i++)//�ุŭ
			for (int j = 0; j < 4; j++)//����ŭ
				out.data[i][j] = this->data[i][j] / Scalar;//��Į�� ������
		return out;//��� ��ȯ
	}
	void setValue(double arr[4][4])
	{
		for (int i = 0; i < 4; i++)//�ุŭ
			for (int j = 0; j < 4; j++)//����ŭ
				this->data[i][j] = arr[i][j];//�迭�� ��Ŀ� ����
	}
	void display()
	{
		for (int i = 0; i < 4; i++)//�ุŭ
		{
			for (int j = 0; j < 4; j++)//����ŭ
				cout << this->data[i][j] << " ";//��� ��� ���
			cout << "\n";
		}
		cout << "\n";
	}
};

int main()
{
	Matrix mat1, mat2;//��� ��ü ����

	double arr1[4][4]{//��� �ʱ�ȭ
		{0,0,0,0},
		{1,1,1,1},
		{2,2,2,2},
		{3,3,3,3}
	};

	double arr2[4][4]{//��� �ʱ�ȭ
		{0,1,2,3},
		{0,1,2,3},
		{0,1,2,3},
		{0,1,2,3},
	};

	mat1.setValue(arr1);//��� �� ����
	mat2.setValue(arr2);//��� �� ����

	Matrix mat3 = mat1 + mat2;//��� ����

	//////////���//////////
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
	for (int i = 0; i < 4; i++)//�ุŭ
		for (int j = 0; j < 4; j++)//����ŭ
			this->data[i][j] = 0;//��� �ʱ�ȭ
}
Matrix::~Matrix()
{
	for (int i = 0; i < 4; i++)//�ุŭ
		for (int j = 0; j < 4; j++)//����ŭ
			this->data[i][j] = 0;//��� �ʱ�ȭ
}
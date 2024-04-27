#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

void hadamard_mat(int rows, int cols, int power_n, bool invert_minus); // �ϴٸ��� ����� �����ϴ� �Լ� ����

int** mat; // 2���� �迭�� ����Ű�� ���� �����͸� ����

int main(void)
{
    int n, power_n = 1; // ���� n�� power_n�� �����ϰ�, power_n�� 1�� �ʱ�ȭ

    cout << "Enter the value of Hadamard matrix (2^n x 2^n): "; // ����ڿ��� �޽����� ���
    cin >> n; // ����ڷκ��� n ���� �Է¹޽��ϴ�.

    for (int i = 0; i < n; i++) // n�� �ݺ�
        power_n *= 2; // power_n�� 2�辿 �����ݴϴ�.

    mat = new int* [power_n]; // mat�� power_n��ŭ�� �����͸� �������� �Ҵ�

    for (int i = 0; i < power_n; i++) // power_n�� �ݺ�
        *(mat + i) = new int[power_n]; // mat�� �� ��ҿ� power_n��ŭ�� �迭�� �������� �Ҵ�

    hadamard_mat(0, 0, power_n, 0); // �ϴٸ��� ����� �����ϴ� �Լ��� ȣ��

    cout << "Hadamard Matrix of size " << power_n << "x" << power_n << ":\n"; // �ϴٸ��� ����� ũ�⸦ ���
    for (int i = 0; i < power_n; i++) // power_n�� �ݺ�
    {
        for (int j = 0; j < power_n; j++) // power_n�� �ݺ�
            cout << *(*(mat + i) + j) << "\t"; // mat�� �� ��Ҹ� ������ �����Ͽ� ���

        cout << "\n"; // ���� �ٷ� �̵�
    }

    for (int i = 0; i < power_n; i++) // power_n�� �ݺ�
        delete[] mat[i]; // mat�� �� ���� ����

    delete[] mat; // mat�� ����

    return 0; // ���α׷� ���Ḧ ��Ÿ���ϴ�.
}

void hadamard_mat(int rows, int cols, int power_n, bool invert_minus)
{
    if (power_n == 1) // power_n�� 1�� ���:
    {
        if (!invert_minus) // invert_minus�� false�� ���:
            mat[rows][cols] = 1; // �ش� ��ġ�� 1�� ����
        else // invert_minus�� true�� ���:
            mat[rows][cols] = -1; // �ش� ��ġ�� -1�� ����
    }
    else // power_n�� 1�� �ƴ� ���:
    {
        power_n /= 2; // power_n�� �������� ���Դϴ�.

        if (invert_minus) // invert_minus�� true�� ���: 1�� ����
        {
            hadamard_mat(rows, cols, power_n, 1); // ���� �� ��и鿡 ���� ��� ȣ��
            hadamard_mat(rows, cols + power_n, power_n, 1); // ������ �� ��и鿡 ���� ��� ȣ��
            hadamard_mat(rows + power_n, cols, power_n, 1); // ���� �Ʒ� ��и鿡 ���� ��� ȣ��
            hadamard_mat(rows + power_n, cols + power_n, power_n, 0); // ������ �Ʒ� ��и鿡 ���� ��� ȣ��
        }
        else // invert_minus�� false�� ���:-1�� ����
        {
            hadamard_mat(rows, cols, power_n, 0); // ���� �� ��и鿡 ���� ��� ȣ��
            hadamard_mat(rows, cols + power_n, power_n, 0); // ������ �� ��и鿡 ���� ��� ȣ��
            hadamard_mat(rows + power_n, cols, power_n, 0); // ���� �Ʒ� ��и鿡 ���� ��� ȣ��
            hadamard_mat(rows + power_n, cols + power_n, power_n, 1); // ������ �Ʒ� ��и鿡 ���� ��� ȣ��
        }
    }
}

#define _CRT_SECURE_NO_WARNINGS
#include <iostream> 
#include <ctime> 
#define SWP(x,y,tmp) ( (tmp)=(x), (x)=(y), (y)=(tmp) ) // �� ������ ���� ��ȯ�ϴ� ��ũ��

using namespace std;

// �Լ� ������Ÿ�� ����
void print_matrix(int** mat); // ��Ʈ���� ��� �Լ�
void print_marix(int** mat, int* sum); // ��Ʈ���� �� �� ���� �� ��� �Լ�
void rows_Descending_sort(int** mat); // �� ���� �������� ���� �Լ�
void sum_ascending_sort(int** mat, int* sum); // �� ���� �������� ���� �Լ�

// main �Լ�
int main(void)
{
    // ���� �ð��� �õ尪���� ����
    int init = static_cast<unsigned int>(time(NULL));
    srand(init); // ���� �õ� ����

    // 10x10 ũ���� 2���� �迭 ���� �Ҵ�
    int** mat = new int* [10];
    for (int i = 0; i < 10; i++)
        *(mat + i) = new int[10];

    // �� ���� ���� ������ �迭 ���� �Ҵ�
    int* sum = new int[10];

    // ��Ʈ���� �� �� ���� �� �ʱ�ȭ
    for (int i = 0; i < 10; i++)
    {
        *(sum + i) = 0;
        for (int j = 0; j < 10; j++)
        {
            *(*(mat + i) + j) = rand() % 101; // 0���� 100 ������ ������ ������ �ʱ�ȭ
            *(sum + i) += *(*(mat + i) + j); // �� ���� �� ���
        }
    }

    // ���� ��Ʈ���� ���
    cout << "Original Matrix:\n";
    print_matrix(mat);

    // �� ���� �������� ����
    rows_Descending_sort(mat);
    cout << "Sort of Row (Descending Order):\n";
    print_marix(mat, sum);

    // �� ���� �������� ����
    sum_ascending_sort(mat, sum);
    cout << "Sort of Sum (Ascending Order):\n";
    print_marix(mat, sum);

    // ���� �Ҵ�� �޸� ����
    for (int i = 0; i < 10; i++)
        delete[] * (mat + i);
    delete[] mat;
    delete[] sum;
    return 0;
}

// ��Ʈ���� ��� �Լ�
void print_matrix(int** mat)
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
            cout << *(*(mat + i) + j) << "\t"; // �� ���� ���
        cout << "\n";
    }
    cout << "\n";
}

// ��Ʈ���� �� �� ���� �� ��� �Լ�
void print_marix(int** mat, int* sum)
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < 10; j++)
            cout << *(*(mat + i) + j) << "\t"; // �� ���� ���
        cout << "| Sum: " << *(sum + i); // ���� �� ���
        cout << "\n";
    }
    cout << "\n";
}

// �� ���� �������� ���� �Լ�
void rows_Descending_sort(int** mat)
{
    int tmp;
    for (int rows = 0; rows < 10; rows++)
    {
        for (int i = 0; i < 9; i++)
        {
            int k = i;//�ε��� ����
            for (int j = i + 1; j < 10; j++)//�� loop
            {
                if (*(*(mat + rows) + k) < *(*(mat + rows) + j))//�� ��
                    k = j;
            }
            if (k != i)//�ε��� �ٲ��
                SWP(*(*(mat + rows) + i), *(*(mat + rows) + k), tmp); // ��ȯ ��ũ�� ȣ��
        }
    }
}

// �� ���� �������� ���� �Լ�
void sum_ascending_sort(int** mat, int* sum)
{
    for (int i = 0; i < 9; i++)
    {
        int k = i;//�ε��� ����
        for (int j = i + 1; j < 10; j++)
        {
            if (*(sum + k) > *(sum + j))//�� ��
                k = j;//�ε��� ��ȭ
        }
        if (k != i)//�ε��� �ٲ��
        {
            int tmp;
            for (int j = 0; j < 10; j++)//�� �� ����
                SWP(*(*(mat + i) + j), *(*(mat + k) + j), tmp); // ��ȯ ��ũ�� ȣ��
            SWP(*(sum + i), *(sum + k), tmp); // ���� �յ� ��ȯ
        }
    }
}

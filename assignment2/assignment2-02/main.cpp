#include <iostream>
#include <ctime>
using namespace std;

// �Լ� ����
void quick_sort(int* arr, int st, int en); // �� ���� �Լ� ����
void merge_sort(int* arr, int st, int en); // ���� ���� �Լ� ����
void merge(int* arr, int st, int en);
void my_insertion(int* arr, int en, int input);

int tmp[10]; // �ӽ� �迭 ����

int main(void)
{
    // �õ� �� �ʱ�ȭ
    int init = static_cast<unsigned int>(time(NULL)); // ���� �ð��� �õ� ������ �ʱ�ȭ ����
    srand(init); // �õ� �� ����

    // �迭 �� ���� �ʱ�ȭ
    int* arr = new int[11]; // �迭 ���� �Ҵ�
    int input, st = 0, en = 9; // �Է� ���� �� �迭 ���� ���� ���� �� �ʱ�ȭ

    // ������ �� ����
    cout << "Random values : ";
    for (int i = 0; i < 10; i++)
    {
        arr[i] = rand() % 101; // 0���� 100������ ������ �� �Ҵ�
        cout << " " << arr[i]; // ������ �� ���
    }
    cout << "\n";

    // ���� ��� ����
    cout << "Select sorting method (1: Quick Sort, 2: Merge Sort) : ";
    cin >> input; // ����� �Է� �ޱ�

    // ���õ� ���� ����� ���� ���� ����
    if (input == 1)
    {
        quick_sort(arr, 0, 10);//�� ����
        cout << "Sorted numbers (Quick Sort): ";
    }
    else if (input == 2)
    {
        merge_sort(arr, 0, 10);//���� ����
        cout << "Sorted numbers (Merge Sort): ";
    }

    // ���ĵ� �迭 ���
    for (int i = 0; i < 10; i++)
        cout << " " << arr[i];
    cout << "\nEnter a value to search : ";
    cin >> input;

    // ���� Ž�� ����
    int mid = (st + en) / 2;
    while (1)
    {
        if (st > en)
        {
            my_insertion(arr, en, input); // ���� ���� ȣ��
            cout << "Updated numbers:";
            for (int i = 0; i < 11; i++)
                cout << " " << *(arr + i); // ������Ʈ�� �迭 ���
            break;
        }
        else if (input == *(arr + mid))//�Է°��� ã���� ��
        {
            cout << "Searched number index : " << mid;
            break;
        }
        else if (input > *(arr + mid))//�Է°��� �߰����� Ŭ��
        {
            st = mid + 1;//������ ��ȭ
            mid = (st + en) / 2;//�߰� ��ȭ
        }
        else if (input < *(arr + mid))//�Է°��� �߰����� ������
        {
            en = mid - 1;//���� ��ȭ
            mid = (st + en) / 2;//�߰� ��ȭ
        }
    }
    return 0;
}


void merge_sort(int* arr, int st, int en)// ���� ���� �Լ� ����
{
    if (en == (st + 1))
        return;              // ���� ����
    int mid = (st + en) / 2; // �߰� �� ���
    merge_sort(arr, st, mid);     // ��� ȣ��
    merge_sort(arr, mid, en);     // ��� ȣ��
    merge(arr, st, en);           // ���� �Լ� ȣ��
}

// ���� �Լ� ����
void merge(int* arr, int st, int en)
{
    int mid = (st + en) / 2; // �߰� �� ���
    int idx1 = st;           // ���� ���� �ʱ�ȭ
    int idx2 = mid;          // �� ���� �ʱ�ȭ
    for (int i = st; i < en; i++)
    {
        if (idx2 == en)
            tmp[i] = arr[idx1++]; // �� ��° �迭�� ���� ���
        else if (idx1 == mid)
            tmp[i] = arr[idx2++]; // ù ��° �迭�� ���� ���
        else if (arr[idx1] <= arr[idx2])
            tmp[i] = arr[idx1++]; // �� �� �� ����
        else
            tmp[i] = arr[idx2++]; // �� �� �� ����
    }
    for (int i = st; i < en; i++) // �ӽ� �迭���� ���� �迭�� �̵�
        arr[i] = tmp[i];
}

// �� ���� �Լ� ����
void quick_sort(int* arr, int st, int en)
{
    if (en <= st + 1) // ���� ����
        return;
    int pivot = arr[st]; // �ǹ� �� ����
    int id1 = st + 1;  // �ε��� �ʱ�ȭ
    int id2 = en - 1;  // �ε��� �ʱ�ȭ

    while (1)
    {
        while (id1 <= id2 && arr[id1] <= pivot)
            id1++; // �ε��� �̵�
        while (id1 <= id2 && arr[id2] > pivot)
            id2--; // �ε��� �̵�
        if (id1 > id2)
            break;// �ݺ� ���� ����
        // �� �� �� ��ȯ
        int temp = arr[id1];
        arr[id1] = arr[id2];
        arr[id2] = temp;
    }
    // �ǹ��� �ǹ����� ���� ���� ��ȯ
    int temp = arr[st];
    arr[st] = arr[id2];
    arr[id2] = temp;
    quick_sort(arr, st, id2);	 // ��� ȣ��
    quick_sort(arr, id2 + 1, en); // ��� ȣ��
}

// ���� ���� �Լ� ����
void my_insertion(int* arr, int en, int input)
{
    for (int i = 10; i > en + 1; i--)
        *(arr + i) = *(arr + i - 1); // ���� �̵�
    *(arr + en + 1) = input; // �� ����
}

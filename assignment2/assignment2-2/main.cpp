#include <iostream>
#include <ctime>
using namespace std;

void quick_sort(int* arr, int st, int en); //quick sort funcion declare
void merge_sort(int* arr, int st, int en); //merge sort
void merge(int* arr, int st, int en);
void my_insertion(int* arr, int en, int input);

int tmp[10];

int main(void)
{
    int init = static_cast<unsigned int>(time(NULL)); //현재 시간을 시드값으로 초기화 설정
    srand(init);// 시드값 설정

    int* arr = new int[11];
    int input, st = 0, en = 9;

    cout << "Random values : ";
    for (int i = 0; i < 10; i++)
    {
        arr[i] = rand() % 101;
        cout << " " << arr[i];
    }
    cout << "\n";

    cout << "Select sorting method (1: Quick Sort, 2: Merge Sort) : ";

    cin >> input;

    if (input == 1)
    {
        quick_sort(arr, 0, 10);
        cout << "Sorted numbers (Quick Sort): ";
    }
    else if (input == 2)
    {
        merge_sort(arr, 0, 10);
        cout << "Sorted numbers (Merge Sort): ";
    }

    for (int i = 0; i < 10; i++)
        cout << " " << arr[i];
    cout << "\nEnter a value to search : ";
    cin >> input;


    ///////binary search
    int mid = (st + en) / 2;
    while (1)
    {
        if (st > en)
        {
            my_insertion(arr, en, input);
            cout << "Updated numbers:";
            for (int i = 0; i < 11; i++)
                cout << " " << *(arr + i);
            break;
        }
        else if (input == *(arr + mid))
        {
            cout << "Searched number index : " << mid;
            break;
        }
        else if (input > *(arr + mid))
        {
            st = mid + 1;
            mid = (st + en) / 2;
        }
        else if (input < *(arr + mid))
        {
            en = mid - 1;
            mid = (st + en) / 2;
        }
    }
    return 0;
}

void merge_sort(int* arr, int st, int en)
{
    if (en == (st + 1))
        return;              // base condition
    int mid = (st + en) / 2; // mid reset
    merge_sort(arr, st, mid);     // recursive call
    merge_sort(arr, mid, en);     // recursive call
    merge(arr, st, en);           // merge func call
}

void merge(int* arr, int st, int en)
{
    int mid = (st + en) / 2; // mid reset
    int idx1 = st;           // start point reset
    int idx2 = mid;          // end point reset
    for (int i = st; i < en; i++)
    {
        if (idx2 == en)
            tmp[i] = arr[idx1++]; // idx2 val end
        else if (idx1 == mid)
            tmp[i] = arr[idx2++]; // idx1 val end
        else if (arr[idx1] <= arr[idx2])
            tmp[i] = arr[idx1++]; // value compare
        else
            tmp[i] = arr[idx2++]; // value compare
    }
    for (int i = st; i < en; i++) // move to std arr from the temp arr
        arr[i] = tmp[i];
}

void quick_sort(int* arr, int st, int en)
{
    if (en <= st + 1) // base condition
        return;
    int pivot = arr[st]; // pivot reset
    int id1 = st + 1;  // index reset
    int id2 = en - 1;  // index reset

    while (1)
    {
        while (id1 <= id2 && arr[id1] <= pivot)
            id1++; // index move
        while (id1 <= id2 && arr[id2] > pivot)
            id2--; // index move
        if (id1 > id2)
            break;// loop break if
        // swap afte value compare
        int temp = arr[id1];
        arr[id1] = arr[id2];
        arr[id2] = temp;
    }
    // pivot and smaller than pivot value swap
    int temp = arr[st];
    arr[st] = arr[id2];
    arr[id2] = temp;
    quick_sort(arr, st, id2);	 // recursive call
    quick_sort(arr, id2 + 1, en); // recursive call
}

void my_insertion(int* arr, int en, int input)
{
    for (int i = 10; i > en + 1; i--)
        *(arr + i) = *(arr + i - 1);
    *(arr + en+1) = input;
}
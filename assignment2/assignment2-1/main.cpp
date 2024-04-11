#include <iostream>
#include <ctime>
using namespace std;

int main(void)
{
	int init = static_cast<unsigned int>(time(NULL)); //���� �ð��� �õ尪���� �ʱ�ȭ ����
	srand(init);// �õ尪 ����
	int input, min = 101, max = -1;//�Է°�, �ִ�, �ּڰ� ���� ����
	int min_index = 0;//�ּڰ� �ε��� ���� ����
	int max_index = 0;//�ִ� �ε��� ���� ����
	cout << "Size of the array : ";//�Է� ��û ���
	cin >> input;//����� �Է�
	int* arr = new int[input];//�Է¿� ���� �迭 ���� �Ҵ�
	cout << "Random numbers :";//��� ��Ʈ ���
	for (int i = 0; i < input; i++)//�迭 ��ȸ �ݺ���
	{
		arr[i] = rand() % 101;//�迭�� ���� �Է�
		cout << " " << arr[i];//�Էµ� ���� ���
	}
	for (int i = 0; i < input; i++)//�迭 ���� Ž��
	{
		if (min > arr[i])//�ּڰ� ���� ����
		{
			min = arr[i];//�ּڰ� ��ȯ
			min_index = i;//�ε��� ��ȯ
		}
		if (max < arr[i])//�ִ� ���� ����
		{
			max = arr[i];//�ִ� ��ȯ
			max_index = i;//�ε��� ��ȯ
		}
	}
	cout << "\n"<<"Maximum value : " << min << "\t, Address: " << arr + min_index << "\n";//�ּڰ��� �ε��� �ּ� ���
	cout << "Maximum value: " << max << "\t, Address: " << arr + max_index << "\n";//�ִ񰪰� �ε��� �ּ� ���

	delete[] arr;//�Ҵ�� �޸� ����
	return 0;
}
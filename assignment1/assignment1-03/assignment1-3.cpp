#include <iostream>
using namespace std;

int main() {
    char arr[10]{}; // ũ�Ⱑ 10�� ���� �迭 ���� �� �ʱ�ȭ
    cout << "Enter ten characters: "; // ����ڷκ��� 10���� ���� �Է� ��û
    for (int i = 0; i < 10; i++) // 10�� �ݺ��Ͽ� ���� �Է� �ޱ�
        cin >> arr[i];
    cout << "Input characters are:\n"; // �Էµ� ���� ��� ��Ʈ
    for (int i = 0; i < 5; i++) // �迭�� 1-10 ���ں��� 5-6 ���ڱ��� �ݺ�
        cout << arr[i] << " " << arr[9 - i] << "\n"; // �迭�� ��Ī �� ���� ���
    return 0;
}
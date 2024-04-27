// �ʿ��� ��� ������ ����
#define _CRT_SECURE_NO_WARNINGS // Visual Studio���� ��� ����� ��Ƽ��
#include <iostream> // ǥ�� ����� ��Ʈ�� ���̺귯��
#include <fstream> // ���� ����� ��Ʈ�� ���̺귯��

using namespace std; // ǥ�� ���ӽ����̽��� ���

// ���ڿ� �� �Լ�
int my_strcmp(const char* input, const char* command);
// ���ڿ��� ���̸� ��ȯ�ϴ� �Լ�
int my_strlen(const char* arr);
// ���ڿ� ���� �Լ�
void my_strcpy(char* arr1, char* arr2, int arr2_len);
// ���ڿ� ���� �Լ�
void my_strcat(char* arr1, char* arr2);
// �迭 �ʱ�ȭ �Լ�
void array_clear(char* arr);

// �ܾ� �˻� �Լ� (search command��)
void search_word(char* inputline, char* input_command2, int* count, const int rows_count);
// �ܾ� �˻� �� ���� �Լ� (delete��)
void search_word(char* inputline, char* word);
// �ܾ� �˻� �� ���� �Լ� (change��)
void search_word(char*& inputline, char* word1, char* word2);
// ���ڿ� ���� �Լ� (change&insert��)
void insert(char*& line, char* word, int front_id, int back_id);
// �ܾ� ���� �� ���ڿ� ���� �Լ� (delete��)
void delete_N_merge(char* line, int word_len, int cols);

// ���� ���� ����
char frontpart[1000]; // �պκ� ���� �迭
char backpart[1000]; // �޺κ� ���� �迭
int rows[10000]; // �˻��� �� ��ȣ ���� �迭
int cols[10000]; // �˻��� �� ��ȣ ���� �迭

int main(void)
{
    // ��ɾ� ���
    char command[7][10] = { "open","search","change", "insert", "delete", "save", "exit" };
    // ����� �Է��� ������ ������
    char input_command[21];
    char input_command2[21];
    char input_command3[21];
    char inputline[1001];

    char** script = NULL; // ���� ������ ������ ���� ������

    int count = 0; // �˻��� �ܾ� ����
    int row_count = 0; // �� ����
    ifstream read_file; // ���� �б� ��Ʈ��

    // ����ڰ� ������ ������ �ݺ�
    while (1)
    {
        // ����ڷκ��� ��ɾ� �Է� �ޱ�
        cin >> input_command;

        // open ��ɾ� ó�� �κ�
        if (!my_strcmp(input_command, command[0]))
        {
            cin >> input_command2; // ���ϸ� �Է� �ޱ�
            read_file.open(input_command2); // ���� ����

            // ���� ������ �о script�� ����
            while (!read_file.eof())
            {
                read_file.getline(inputline, 1000);
                row_count++;
            }
            read_file.seekg(0, ios::beg); // ���� ������ �ʱ�ȭ
            script = new char* [row_count]; // �� ������ŭ �޸� �Ҵ�
            row_count = 0;

            // ���� ������ �о script�� ����
            while (!read_file.eof())
            {
                read_file.getline(inputline, 1000);
                int line_len = my_strlen(inputline);
                *(script + row_count) = new char[line_len + 1];
                my_strcpy(*(script + row_count), inputline, line_len);
                row_count++;
            }
        }
        // search ��ɾ� ó�� �κ�
        else if (!my_strcmp(input_command, command[1]))
        {
            array_clear(input_command2);
            array_clear(inputline);
            cin >> input_command2; // �˻��� �ܾ� �Է� �ޱ�

            // �� �࿡�� �ܾ� �˻�
            for (int i = 0; i < row_count; i++)
                search_word(*(script + i), input_command2, &count, i);

            // �˻� ��� ���
            cout << "==='" << input_command2 << "' search(" << count << ")===\n";
            for (int i = 0; i < count; i++)
            {
                cout << "(" << rows[i] << ", " << cols[i] << ")";
                if (i < count - 1)
                    cout << ", ";
                rows[i] = 0;
                cols[i] = 0;
            }
            cout << "\n--------------------\n";
            count = 0;
        }
        // change ��ɾ� ó�� �κ�
        else if (!my_strcmp(input_command, command[2]))
        {
            cin >> input_command2;
            cin >> input_command3;

            // �� �࿡�� �ܾ� ����
            for (int i = 0; i < row_count; i++)
                search_word(*(script + i), input_command2, input_command3);
            cout << "===change===\n" << input_command2 << " -> " << input_command3;
            cout << "\n--------------------\n";
        }
        // insert ��ɾ� ó�� �κ�
        else if (!my_strcmp(input_command, command[3]))
        {
            int r, l;
            cin >> r >> l >> input_command2;
            int insert_word_len = my_strlen(input_command2);
            insert(script[r], input_command2, l, l);
            cout << "===insert===\n" << input_command2 << " Inserted into (" << r << ", " << l << ")";
            cout << "\n--------------------\n";
        }
        // delete ��ɾ� ó�� �κ�
        else if (!my_strcmp(input_command, command[4]))
        {
            cin >> input_command2;
            count = 0;
            int word_len = my_strlen(input_command2);

            // �� �࿡�� �ܾ� ����
            for (int i = 0; i < row_count; i++)
                search_word(*(script + i), input_command2);
            cout << "===delete===\nDelete " << input_command2;
            cout << "\n--------------------\n";
        }
        // save ��ɾ� ó�� �κ�
        else if (!my_strcmp(input_command, command[5]))
        {
            cin >> input_command2;
            ofstream write_file; // ���� ���� ��Ʈ��
            write_file.open(input_command2); // ���� ����

            // ��ũ��Ʈ�� ���Ͽ� ����
            for (int i = 0; i < row_count; i++)
            {
                write_file << *(script + i);
                if (i < row_count - 1)
                    write_file << "\n";
            }
            if (write_file.is_open())
                write_file.close(); // ���� �ݱ�
            cout << "===save===\nSave the file as \"" << input_command2 << "\"\n";
        }
        // exit ��ɾ� ó�� �κ�
        else if (!my_strcmp(input_command, command[6]))
            break;
        // �߸��� ��ɾ� ó�� �κ�
        else
            cout << "error command\n";
    }
    cout << "Exit the program";

    // ���� �Ҵ� ����
    if (script != NULL)
    {
        for (int i = 0; i < row_count; i++)
            delete[] * (script + i);
        delete[] script;
    }
    if (read_file.is_open())
        read_file.close();

    return 0;
}

// �ܾ� �˻� �Լ� (search command��)
void search_word(char* inputline, char* input_command2, int* count, const int rows_count)
{
    int word_len = my_strlen(input_command2);
    int line_len = my_strlen(inputline);
    int search_len = line_len - word_len;

    for (int i = 0; i <= search_len; i++)
    {
        bool found = true;
        for (int j = 0; j < word_len; j++)
        {
            if (inputline[i + j] != input_command2[j])
            {
                found = false;
                break;
            }
        }
        if (found)
        {
            rows[*count] = rows_count;
            cols[*count] = i;
            *count = *count + 1;
        }
    }
}

// �ܾ� �˻� �� ���� �Լ� (delete��)
void search_word(char* inputline, char* word)
{
    int word_len = my_strlen(word);
    int line_len = my_strlen(inputline);
    int search_len = line_len - word_len;

    for (int i = 0; i <= search_len; i++)
    {
        bool found = true;
        for (int j = 0; j < word_len; j++)
        {
            if (inputline[i + j] != word[j])
            {
                found = false;
                break;
            }
        }
        if (found)
            delete_N_merge(inputline, word_len, i);
    }
}

// �ܾ� �˻� �� ���� �Լ� (change��)
void search_word(char*& inputline, char* word1, char* word2)
{
    int word_len = my_strlen(word1);
    int line_len = my_strlen(inputline);
    int search_len = line_len - word_len;

    for (int i = 0; i <= search_len; i++)
    {
        bool found = true;
        for (int j = 0; j < word_len; j++)
        {
            if (inputline[i + j] != word1[j])
            {
                found = false;
                break;
            }
        }
        if (found)
            insert(inputline, word2, i, i + word_len);
    }
}

// �ܾ� ���� �� ���ڿ� ���� �Լ� (delete��)
void delete_N_merge(char* line, int word_len, int cols)
{
    array_clear(frontpart);
    array_clear(backpart);
    my_strcpy(frontpart, line, cols);
    my_strcpy(backpart, line + cols + word_len, (my_strlen(line) - cols - word_len + 1));
    my_strcat(frontpart, backpart);
    int line_len = my_strlen(frontpart);
    my_strcpy(line, frontpart, line_len);
    array_clear(frontpart);
    array_clear(backpart);
}

// ���ڿ� ���� �Լ� (change&insert��)
void insert(char*& line, char* word, int front_id, int back_id)
{
    int word_len = my_strlen(word);//����
    int line_len = my_strlen(line);//����
    array_clear(frontpart);//�迭 ����
    array_clear(backpart);
    my_strcpy(frontpart, line, front_id);
    my_strcat(frontpart + front_id, word);
    int front_len = my_strlen(frontpart);
    my_strcat(frontpart + front_len, line + back_id);
    front_len = my_strlen(frontpart);
    delete[] line;
    line = nullptr;
    line = new char[front_len + 1];
    my_strcpy(line, frontpart, front_len);
    array_clear(frontpart);
}

// ���ڿ� �� �Լ�
int my_strcmp(const char* input, const char* command)
{
    for (int i = 0; command[i] != '\0'; i++)
    {
        if (input[i] > command[i])
            return 1;
        else if (input[i] < command[i])
            return -1;
    }
    return 0;
}

// ���ڿ��� ���̸� ��ȯ�ϴ� �Լ�
int my_strlen(const char* arr)
{
    int len = 0;
    for (int i = 0; i < 1000; i++)
    {
        if (arr[i] == '\0')
            return len;
        len++;
    }
    return len;
}

// ���ڿ� ���� �Լ�
void my_strcpy(char* arr1, char* arr2, int arr2_len)
{
    for (int i = 0; i < arr2_len; i++)
        arr1[i] = arr2[i];
    *(arr1 + arr2_len) = '\0';
}

// ���ڿ� ���� �Լ�
void my_strcat(char* arr1, char* arr2)
{
    int i = 0;
    while (arr1[i] != '\0')
        i++;
    for (int j = 0; arr2[j] != '\0'; j++)
    {
        arr1[i + j] = arr2[j];
        if (arr2[j + 1] == '\0')
            arr1[i + j + 1] = '\0';
    }
}

// �迭 �ʱ�ȭ �Լ�
void array_clear(char* arr)
{
    int i = 0;
    while (arr[i] != '\0')
    {
        arr[i] = NULL;
        if (arr[i + 1] == '\0')
            arr[i + 1] = NULL;
    }
}

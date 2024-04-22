// 필요한 헤더 파일을 포함
#define _CRT_SECURE_NO_WARNINGS // Visual Studio에서 경고를 숨기는 디렉티브
#include <iostream> // 표준 입출력 스트림 라이브러리
#include <fstream> // 파일 입출력 스트림 라이브러리

using namespace std; // 표준 네임스페이스를 사용

// 문자열 비교 함수
int my_strcmp(const char* input, const char* command);
// 문자열의 길이를 반환하는 함수
int my_strlen(const char* arr);
// 문자열 복사 함수
void my_strcpy(char* arr1, char* arr2, int arr2_len);
// 문자열 연결 함수
void my_strcat(char* arr1, char* arr2);
// 배열 초기화 함수
void array_clear(char* arr);

// 단어 검색 함수 (search command용)
void search_word(char* inputline, char* input_command2, int* count, const int rows_count);
// 단어 검색 및 삭제 함수 (delete용)
void search_word(char* inputline, char* word);
// 단어 검색 및 변경 함수 (change용)
void search_word(char*& inputline, char* word1, char* word2);
// 문자열 삽입 함수 (change&insert용)
void insert(char*& line, char* word, int front_id, int back_id);
// 단어 삭제 및 문자열 병합 함수 (delete용)
void delete_N_merge(char* line, int word_len, int cols);

// 전역 변수 선언
char frontpart[1000]; // 앞부분 저장 배열
char backpart[1000]; // 뒷부분 저장 배열
int rows[10000]; // 검색된 행 번호 저장 배열
int cols[10000]; // 검색된 열 번호 저장 배열

int main(void)
{
    // 명령어 목록
    char command[7][10] = { "open","search","change", "insert", "delete", "save", "exit" };
    // 사용자 입력을 저장할 변수들
    char input_command[21];
    char input_command2[21];
    char input_command3[21];
    char inputline[1001];

    char** script = NULL; // 파일 내용을 저장할 이중 포인터

    int count = 0; // 검색된 단어 개수
    int row_count = 0; // 행 개수
    ifstream read_file; // 파일 읽기 스트림

    // 사용자가 종료할 때까지 반복
    while (1)
    {
        // 사용자로부터 명령어 입력 받기
        cin >> input_command;

        // open 명령어 처리 부분
        if (!my_strcmp(input_command, command[0]))
        {
            cin >> input_command2; // 파일명 입력 받기
            read_file.open(input_command2); // 파일 열기

            // 파일 내용을 읽어서 script에 저장
            while (!read_file.eof())
            {
                read_file.getline(inputline, 1000);
                row_count++;
            }
            read_file.seekg(0, ios::beg); // 파일 포인터 초기화
            script = new char* [row_count]; // 행 개수만큼 메모리 할당
            row_count = 0;

            // 파일 내용을 읽어서 script에 저장
            while (!read_file.eof())
            {
                read_file.getline(inputline, 1000);
                int line_len = my_strlen(inputline);
                *(script + row_count) = new char[line_len + 1];
                my_strcpy(*(script + row_count), inputline, line_len);
                row_count++;
            }
        }
        // search 명령어 처리 부분
        else if (!my_strcmp(input_command, command[1]))
        {
            array_clear(input_command2);
            array_clear(inputline);
            cin >> input_command2; // 검색할 단어 입력 받기

            // 각 행에서 단어 검색
            for (int i = 0; i < row_count; i++)
                search_word(*(script + i), input_command2, &count, i);

            // 검색 결과 출력
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
        // change 명령어 처리 부분
        else if (!my_strcmp(input_command, command[2]))
        {
            cin >> input_command2;
            cin >> input_command3;

            // 각 행에서 단어 변경
            for (int i = 0; i < row_count; i++)
                search_word(*(script + i), input_command2, input_command3);
            cout << "===change===\n" << input_command2 << " -> " << input_command3;
            cout << "\n--------------------\n";
        }
        // insert 명령어 처리 부분
        else if (!my_strcmp(input_command, command[3]))
        {
            int r, l;
            cin >> r >> l >> input_command2;
            int insert_word_len = my_strlen(input_command2);
            insert(script[r], input_command2, l, l);
            cout << "===insert===\n" << input_command2 << " Inserted into (" << r << ", " << l << ")";
            cout << "\n--------------------\n";
        }
        // delete 명령어 처리 부분
        else if (!my_strcmp(input_command, command[4]))
        {
            cin >> input_command2;
            count = 0;
            int word_len = my_strlen(input_command2);

            // 각 행에서 단어 삭제
            for (int i = 0; i < row_count; i++)
                search_word(*(script + i), input_command2);
            cout << "===delete===\nDelete " << input_command2;
            cout << "\n--------------------\n";
        }
        // save 명령어 처리 부분
        else if (!my_strcmp(input_command, command[5]))
        {
            cin >> input_command2;
            ofstream write_file; // 파일 쓰기 스트림
            write_file.open(input_command2); // 파일 열기

            // 스크립트를 파일에 쓰기
            for (int i = 0; i < row_count; i++)
            {
                write_file << *(script + i);
                if (i < row_count - 1)
                    write_file << "\n";
            }
            if (write_file.is_open())
                write_file.close(); // 파일 닫기
            cout << "===save===\nSave the file as \"" << input_command2 << "\"\n";
        }
        // exit 명령어 처리 부분
        else if (!my_strcmp(input_command, command[6]))
            break;
        // 잘못된 명령어 처리 부분
        else
            cout << "error command\n";
    }
    cout << "Exit the program";

    // 동적 할당 해제
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

// 단어 검색 함수 (search command용)
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

// 단어 검색 및 삭제 함수 (delete용)
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

// 단어 검색 및 변경 함수 (change용)
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

// 단어 삭제 및 문자열 병합 함수 (delete용)
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

// 문자열 삽입 함수 (change&insert용)
void insert(char*& line, char* word, int front_id, int back_id)
{
    int word_len = my_strlen(word);//길이
    int line_len = my_strlen(line);//길이
    array_clear(frontpart);//배열 정리
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

// 문자열 비교 함수
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

// 문자열의 길이를 반환하는 함수
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

// 문자열 복사 함수
void my_strcpy(char* arr1, char* arr2, int arr2_len)
{
    for (int i = 0; i < arr2_len; i++)
        arr1[i] = arr2[i];
    *(arr1 + arr2_len) = '\0';
}

// 문자열 연결 함수
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

// 배열 초기화 함수
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

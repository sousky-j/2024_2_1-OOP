#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>

using namespace std;

int my_strcmp(const char* input, const char* command);
int my_strlen(const char* arr);
void my_strcpy(char* arr1, char* arr2, int arr2_len);
void my_strcat(char* arr1, char* arr2);
void array_clear(char* arr);

void search_word(char* inputline, char* input_command2, int* count, const int rows_count);//search command용
void search_word(char* inputline, char* word);//delete용
void search_word(char*& inputline, char* word1, char* word2);//change용

//insert: change&insert 용 (파라미터: 한 줄 정보, 삽입할 단어, front의 마지막 인덱스(삽입 시 backpart인덱스 이전 인덱스), backpart의 첫 인덱스)
void insert(char*& line, char* word, int front_id, int back_id);//change&insert용
void delete_N_merge(char* line, int word_len, int cols);//delete용

char frontpart[1000];
char backpart[1000];
int rows[10000];
int cols[10000];

int main(void)
{
	///////variable declaration///////
	char command[7][10] = { "open","search","change", "insert", "delete", "save", "exit" };
	char input_command[21];
	char input_command2[21];
	char input_command3[21];
	char inputline[1001];

	char** script = NULL;

	int count = 0;
	int row_count = 0;
	ifstream read_file;
	//////////////////////////////////
	while (1)
	{
		cin >> input_command;
		if (!my_strcmp(input_command, command[0]))//open command part code
		{
			cin >> input_command2;
			read_file.open(input_command2);
			while (!read_file.eof())
			{
				read_file.getline(inputline, 1000);
				row_count++;
			}
			read_file.seekg(0, ios::beg);
			script = new char* [row_count];//전체 행 길이 포인터 배열 동적할당 생성
			row_count = 0;//처음부터 돌기 위해 0으로 초기화
			while (!read_file.eof())//파일 마지막 줄까지
			{
				read_file.getline(inputline, 1000);//파일에서 한줄 받아오기
				int line_len = my_strlen(inputline);//각 행의 길이 구함
				*(script + row_count) = new char[line_len + 1];//행의 길이만큼 동적할당
				my_strcpy(*(script + row_count), inputline, line_len);//파일에서 받아온 한 줄을 동적할당한 배열에 copy
				row_count++;//행 길이 증가
			}
		}//open command code end
		else if (!my_strcmp(input_command, command[1]))//search command part code
		{
			array_clear(input_command2);
			array_clear(inputline);
			cin >> input_command2;//찾을 단어 입력
			for(int i=0;i<row_count;i++)
				search_word(*(script + i), input_command2, &count, i);

			///////////print index////////////////
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
			//////////////////////////////////////
			count = 0;
		}
		else if (!my_strcmp(input_command, command[2]))//change command part code
		{
			cin >> input_command2;
			cin >> input_command3;

			for (int i = 0; i < row_count; i++)
				search_word(*(script + i), input_command2, input_command3);
			cout << "===change===\n" << input_command2 << " -> " << input_command3;
			cout << "\n--------------------\n";
		}
		else if (!my_strcmp(input_command, command[3]))//insert command part code
		{
			int r, l;
			cin >> r >> l >> input_command2;
			int insert_word_len = my_strlen(input_command2);
			insert(script[r], input_command2, l, l);
			cout << "===insert===\n" << input_command2 << " Inserted into (" << r << ", " << l << ")";
			cout << "\n--------------------\n";
		}
		else if (!my_strcmp(input_command, command[4]))//delete command part code
		{
			cin >> input_command2;
			count = 0;
			int word_len = my_strlen(input_command2);
			for (int i = 0; i < row_count; i++)
				search_word(*(script + i), input_command2);
			cout << "===delete===\nDelete" << input_command2;
			cout << "\n--------------------\n";
		}
		else if (!my_strcmp(input_command, command[5]))//save command part code
		{
			cin >> input_command2;
			ofstream write_file;
			write_file.open(input_command2);
			for (int i = 0; i < row_count; i++)
			{
				write_file << *(script + i);
				if (i < row_count - 1)
					write_file << "\n";
			}
			if(write_file.is_open())
				write_file.close();
			cout << "===save===\nSave the file as \"" << input_command2 << "\"\n";
		}
		else if (!my_strcmp(input_command, command[6]))//exit command part code
			break;
		else//error command part code
			cout << "error command\n";
	}
	cout << "Exit the program";
	////////////////free memory/////////////////
	if (script != NULL)
	{
		for (int i = 0; i < row_count; i++)
			delete[] * (script + i);
		delete[] script;
	} 
	if(read_file.is_open())
		read_file.close();
	///////////////////////////////////////////
	return 0;
}

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
void search_word(char* inputline, char* word1)
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
			delete_N_merge(inputline, word_len, i);
	}
}
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
void insert(char*& line, char* word, int front_id, int back_id)
{
	int word_len = my_strlen(word);
	int line_len = my_strlen(line);
	array_clear(frontpart);
	array_clear(backpart);
	my_strcpy(frontpart, line, front_id);
	my_strcat(frontpart + front_id, word);
	int front_len = my_strlen(frontpart);
	my_strcat(frontpart + front_len, line + back_id);
	front_len = my_strlen(frontpart);
	delete[](line = NULL);
	line = new char[front_len + 1];
	my_strcpy(line, frontpart, front_len);
	array_clear(frontpart);
}

int my_strcmp(const char* input, const  char* command)
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
void my_strcpy(char* arr1, char* arr2, int arr2_len)
{
	for (int i = 0; i < arr2_len; i++)
		arr1[i] = arr2[i];
	*(arr1 + arr2_len) = '\0';
}
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
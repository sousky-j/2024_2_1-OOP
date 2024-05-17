#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <conio.h>
#include <windows.h>
#include <string>
#include <cstdlib>
#include <ctime>
using namespace std;

class TaggerState
{
public:
    virtual void toward() = 0;
};

class Back : public TaggerState
{
public:
    void toward()
    {
        cout << "Back" << endl;
    }
};

class Front : public TaggerState
{
    void toward()
    {
        cout << "Front" << endl;
    }
};

class Player
{
private:
    TaggerState* state;
    int progess;
public:
    Player()
    {
        state = new Front();
		progess = 0;
    }
    ~Player()
    {
        if(state != NULL)
            delete state;
    }
    void set_state()
    {
		if (state == NULL)
			state = new Front();
        else
        {
			/*if (state->toward() == "Front")
				state = new Back();
			else
				state = new Front();*/
		}
    }
    void toward()
    {
        state->toward();
    }
    int GetProgress()
    {
		return progess;
	}
};

int main() {

    Player player;
    int phrase_cursor = 0;
    int temp = -1;
    int randNum;
    short cursor = 0;

    std::string phrase = "This is the source code to help you understand the problem. ! ";

    while (phrase_cursor <= phrase.size()) {

        time_t now = time(0); // To change the input of a rand function over time, you can use the 
        srand(now);

        // Measure the current time 
        char* dt = ctime(&now);
        std::string timeStr(dt);
        std::string sec = timeStr.substr(17, 2);

        // Perform  in 1-second increments
        if (temp != stoi(sec)) {
            temp = stoi(sec);

            // print 5 characters in 1 second 
            randNum = 2;


            // Prints a string to the console at a specified location
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { (short)(phrase_cursor),0 });
            for (int i = phrase_cursor; i < phrase_cursor + randNum; i++) {
                std::cout << phrase[i];
                if (i >= phrase.size()) {
                    break;
                }
            }

            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,3 });
            std::cout << " start | ";
            for (int i = 0; i < phrase_cursor/5 ; i++)
                std::cout << "@@";
            for (int i = 0; i < 20 - phrase_cursor / 5; i++)
                std::cout << "--";
            std::cout << " | end ";
            std::cout << " ( " << phrase_cursor / 5 << "/12 )\n";
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { 0,6 });

            phrase_cursor += randNum;


            cout << "Typing on the keyboard :  ";
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { cursor,7 });
        }

        // Accept keyboard input 
        if (_kbhit()) {
            char input = _getch();
            SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), { cursor++ , 7 });
            cout << input;
        }
    }

    return 0;
}
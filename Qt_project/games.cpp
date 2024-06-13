#include "games.h"
#include <Qtime>

Game::Game(int row, int col, int length)
{

    ROW = row;
    COL = col;
    LENGTH = length;

    //색상 매트리스 할당///
    board = new string*[ROW];
    for (int i = 0; i < ROW; i++)
        board[i] = new string[COL];

    //인코딩 매트리스 할당//
    encoding_board = new int*[ROW];
    for (int i = 0; i < ROW; i++)
        encoding_board[i] = new int[COL];

    //매트리스 초기화//
    for(int i=0;i<ROW;i++)
        for(int j=0;j<COL;j++)
        {
            encoding_board[i][j]=0;
            board[i][j] = "White";
            if(i<2)
                board[i][j]="Gray";
        }

    //현재 생성한 블록////
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            curblock.cur_block[i][j]="White";
            curblock.cur_encoding_block[i][j]=0;
        }
    }

    next = new string[length];//다음 블록 배열 할당

    front_id=0,back_id=LENGTH-1;//양 끝을 인덱스로 초기화

    gameover = false;//시작 시 over 하지 않음

    block_stop=true;//처음엔 블록이 멈췄다고 해서 블록이 생성되도록 만듬

    axis_row = 0;//어차피 모든 게임의 4*4배열의 처음 위치는 모두 맨 위에서 시작함
    axis_col = (COL/2)-2;
}
Game::~Game()
{
    delete[] next;

    for (int i = 0; i < ROW; i++)
        delete[] board[i];
    delete[] board;

    for(int i=0;i<ROW;i++)
        delete[] encoding_board[i];
    delete[] encoding_board;
}

PuyopuyoGame::PuyopuyoGame() : Game(14, 6, 2)
{
    uniform_int_distribution<int> distribution(0, 100);
    int cnt=0;
    for(int i=front_id;cnt!=LENGTH;i++)
    {
        next[i]=combi[distribution(rd)%25];
        if(i==LENGTH) i=0;
        cnt++;
    }

    score = 0;
}

TetrisGame::TetrisGame() : Game(22, 10, 5)
{
    uniform_int_distribution<int> distribution(0, 100);
    int cnt=0;
    for(int i=front_id;cnt!=LENGTH;i++)
    {
        next[i]=combi[25+distribution(rd)%7];
        if(i==LENGTH) i=0;
        cnt++;
    }

    score = 1;
}

PuyopuyoTetrisGame::PuyopuyoTetrisGame() : Game(18, 8, 5)
{
    uniform_int_distribution<int> distribution(0, 100);
    int cnt=0;
    for(int i=front_id;cnt!=LENGTH;i++)
    {
        next[i]=combi[distribution(rd)%32];
        if(i==LENGTH) i=0;
        cnt++;
    }
    score = 2;
}

PuyopuyoGame::~PuyopuyoGame()
{
    ;
}
TetrisGame::~TetrisGame()
{
    ;
}
PuyopuyoTetrisGame::~PuyopuyoTetrisGame()
{
    ;
}


#ifndef GAMES_H
#define GAMES_H

#include <string>
#include <random>
#include <QVector>
#include <QQueue>
using namespace std;

struct Curblock
{
    string cur_block[4][4];//색상 담을 배열
    int cur_encoding_block[4][4];//인코딩 할 변수
    string shape;
    int axis[2];//뿌요면 사용, 0은 row, 1은 col
};

class Game
{
public:
    Game(int row, int col, int length);
    ~Game();

public:
    int ROW;
    int COL;
    int LENGTH;

    string** board;//색상 들어가 있는
    string* next;//다음 블록 배열
    int front_id, back_id;//next 배열의 양 끝 인덱스
    int** encoding_board;//줄 지우거나 뿌요 지울 인코딩 테이블
    //0이면 빈칸, -1이면 고정 테트로미노, 1이면 움직이는 테트로미노, 2 3 4 5 6은 차례대로 R, Y, G, B, P를 매핑, 7이면 움직이는 뿌요

    Curblock curblock;//생성된 블록 객체

    int block[8][4][4]={
        {{0,0,0,0},
         {1,1,1,1},
         {0,0,0,0},
         {0,0,0,0}},//I

        {{1,0,0,0},
         {1,1,1,0},
         {0,0,0,0},
         {0,0,0,0}},//J

        {{0,0,1,0},
         {1,1,1,0},
         {0,0,0,0},
         {0,0,0,0}},//L

        {{0,1,1,0},
         {1,1,0,0},
         {0,0,0,0},
         {0,0,0,0}},//S

        {{1,1,0,0},
         {0,1,1,0},
         {0,0,0,0},
         {0,0,0,0}},//Z

        {{0,1,0,0},
         {1,1,1,0},
         {0,0,0,0},
         {0,0,0,0}},//ㅗ

        {{0,1,1,0},
         {0,1,1,0},
         {0,0,0,0},
         {0,0,0,0}},//O

        {{0,7,0,0},
         {0,7,0,0},
         {0,0,0,0},
         {0,0,0,0}}//뿌요뿌요
    };

    string combi[32] =
        {"RR", "RY", "RG", "RB", "RP",
         "YR", "YY", "YG", "YB", "YP",
         "GR", "GY", "GG", "GB", "GP",
         "BR", "BY", "BG", "BB", "BP",
         "PR", "PY", "PG", "PB", "PP",
         "T", "J", "L", "O", "I", "S", "Z"};

    int score;//점수
    int axis_row;//현재 위치 row
    int axis_col;//현재 위치 col
    bool gameover;//게임 오버인지 체크
    bool block_stop;//false면 생성 X, true면 생성하기

    random_device rd;//난수를 위한 변수 선언
};

class PuyopuyoGame : public Game
{
public:
    PuyopuyoGame();
    ~PuyopuyoGame();

};

class TetrisGame : public Game
{
public:
    TetrisGame();
    ~TetrisGame();
};

class PuyopuyoTetrisGame : public Game
{
public:
    PuyopuyoTetrisGame();
    ~PuyopuyoTetrisGame();
};


#endif // GAMES_H

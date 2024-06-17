#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QPainter>
#include <QTimerEvent>
#include <QKeyEvent>
#include <QTimer>
#include "Games.h"
#include "GameOverWindow.h"

const int BLOCK_SIZE=40;
const int MARGIN=5;
const int SPEED_MS = 700;

class GameWindow : public QWidget
{
    Q_OBJECT

public:
    GameWindow(QString gamename, QWidget *parent = nullptr);
    ~GameWindow();

    void paintEvent(QPaintEvent* event);
    void keyPressEvent(QKeyEvent* event);
    void timerEvent(QTimerEvent* event);

    void generateblock();//next에 있는 블록을 가져와서 보드에 놓음
    void drawNext();//블록이 멈추면 블록 생성 후 next에 다음 블록 생성, 아니면 드롭블록
    void dropblock(); // //아랫키나 타이머로 drop, soft drop
    void movecol(int a); //왼,오 눌렀을 때
    void rotate(int a); //0이면 x(시계), 1이면 z(반시계)로 회전
    void harddrop(); // hard drop
    bool blockcorrect(int tmp[4][4], int posX, int posY); // 블록이 멈추도록 하는 함수
    void over();//게임 오버 됐을 때 실행되는 함수
    void delpreinfo();//delete previous informaion function
    void blockplace(Curblock block, int a); //place the block on board
    //->a=0이면 테트로미노(p_game 객체 사용), a=1이면 객체 내부 위치 사용
    void encoding_update(Curblock block, int a);//블록 고정시 인코딩 정보를 보드에 없데이트
    //blockplace 후에 놓인 정보를 바탕으로 encoding됨
    void overcheck();//회색 칸에 블록이 있으면 게임 오버
    void generate_pu(Curblock* pu);//curblock에서 뿌요 객체 분리
    void del_line();//테트리스에서 지우는 함수
    bool is_valid(int x, int y); // 인덱스 유효성 검사 함수
    void bfs_pu(int x, int y, vector<vector<bool>>& visited, vector<pair<int, int>>& to_pop);//완탐을 위해 bfs하는 함수
    void main_delete_puyo();//뿌요 지울 때 호출하는 메인 삭제 함수
    void pu_drop();//뿌요 지우고 중력 적용하는 함수
    bool del_pu();//실질적으로 뿌요 지우는 함수
    void drop_tet_on_pu();//테트로미노가 내려가고 내리는 로직 함수
    bool pu_under_correct();//테트로미노가 내려갈 때 비어있거나 뿌요만 있는지
    void swap_drop_tet();//뿌요 아래로 테트가 내려가도록 보드를 조정하는 함수
    unordered_map<string, QColor> Colors = {
        {"White", QColor(255, 255, 255)},//literally
        {"Gray", QColor(128,128,128)},  //literally
        {"I", QColor(0, 255, 255)},     // Cyan
        {"L", QColor(255, 128, 0)},     // Orange
        {"J", QColor(0, 0, 255)},       // Blue
        {"B", QColor(0, 0, 255)},       // Blue
        {"O", QColor(255, 255, 0)},     // Yellow
        {"Y", QColor(255, 255, 0)},     // Yellow
        {"S", QColor(0, 255, 0)},       // Green
        {"G", QColor(0, 255, 0)},       // Green
        {"T", QColor(255, 0, 255)},     // Purple
        {"P", QColor(255, 0, 255)},     // Purple
        {"Z", QColor(255, 0, 0)},       // Red
        {"R", QColor(255, 0, 0)}        // Red
    };
    string block_shape[7]={"I", "J", "L", "S", "Z", "T", "O"};//block 테이블과 인덱스의 블록 모양이 동일한 배열
    int dx[4] = {1,0,-1,0}; // 상하좌우 네 방향을 의미
    int dy[4] = {0,1,0,-1}; // 상하좌우 네 방향을 의미

    int wiro[4];//칸이 얼마나 올라가야 하는지 저장해놓는 배열
    int timer;

    random_device rd;

private:
    Game* p_game;
    QString GAMENAME;
    GameoverWindow* gameoverwindow;

};

#endif // GAMEWINDOW_H

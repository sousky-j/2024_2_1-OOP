#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QPainter>
#include <QTimerEvent>
#include <QKeyEvent>
#include "Games.h"
#include "GameOverWindow.h"

const int BLOCK_SIZE=40;
const int MARGIN=5;
const int SPEED_MS = 1000;

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
    void drawNext(); //아랫키나 타이머로 drop, soft drop
    void dropblock(); // 블록 드롭 함수 추가
    void movecol(int a); //왼,오 눌렀을 때
    void rotate(int a); //0이면 x(시계), 1이면 z(반시계)로 회전
    void harddrop(); // hard drop
    bool blockcorrect(int tmp[4][4], int posX, int posY); // 블록이 멈추도록 하는 함수
    void over();//게임 오버 됐을 때 실행되는 함수
    void delpreinfo();//delete previous informaion function
    void blockplace(); //place the block on board
    void encoding_update();//블록 고정시 인코딩 정보를 보드에 없데이트
    void overcheck();//회색 칸에 블록이 있으면 게임 오버


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
    int timer;

    random_device rd;

private:
    Game* p_game;
    QString GAMENAME;
    GameoverWindow* gameoverwindow;
};

#endif // GAMEWINDOW_H

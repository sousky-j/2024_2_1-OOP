#include "GameWindow.h"

GameWindow::GameWindow(QString gamename, QWidget *parent) : QWidget(parent)
{
    timer=startTimer(SPEED_MS);
    GAMENAME = gamename;

    if (GAMENAME == "Puyopuyo")
    {
        p_game = new PuyopuyoGame();
        resize(500, 800);
    }
    else if (GAMENAME == "Tetris")
    {
        p_game = new TetrisGame();
        resize(700, 1100);
    }
    else if (GAMENAME == "PuyopuyoTetris")
    {
        p_game = new PuyopuyoTetrisGame();
        resize(700, 900);
    }
    setWindowTitle(gamename);
}
GameWindow::~GameWindow()
{
    delete p_game;
    delete gameoverwindow;
}
void GameWindow::paintEvent(QPaintEvent *event)
{
    int ROW = p_game->ROW;
    int COL = p_game->COL;
    int LENGTH = p_game->LENGTH;
    string** cur_board = p_game->board;
    string* cur_next = p_game->next;

    int score = p_game->score;

    QPainter painter(this);
    painter.setBrush(QBrush(Qt::white,Qt::SolidPattern));
    painter.drawRect(MARGIN,MARGIN,COL*BLOCK_SIZE,ROW*BLOCK_SIZE);

    int cnt=0;
    for(int k = p_game->front_id; cnt<LENGTH;k++)
    {
        if(k==LENGTH)
            k=0;
        cnt++;
        std::string current_color = cur_next[k];

        int current_col = MARGIN*10+COL*(BLOCK_SIZE/1)+0*(BLOCK_SIZE/1);
        int current_row = MARGIN*10+0*(BLOCK_SIZE/2) + 100 * cnt;
        int one = (BLOCK_SIZE/2);

        if (cur_next[k].length() == 2)
        {
            for (int l = 0; l < 2; l++)
            {
                if (cur_next[k][l] == 'R')
                {
                    painter.setBrush(QBrush(QColor(255, 0, 0),Qt::SolidPattern));
                    painter.drawEllipse(current_col, current_row + l * one, one, one);
                }

                if (cur_next[k][l] == 'Y')
                {
                    painter.setBrush(QBrush(QColor(255, 255, 0),Qt::SolidPattern));
                    painter.drawEllipse(current_col, current_row + l * one, one, one);
                }

                if (cur_next[k][l] == 'G')
                {
                    painter.setBrush(QBrush(QColor(0, 255, 0),Qt::SolidPattern));
                    painter.drawEllipse(current_col, current_row + l * one, one, one);
                }

                if (cur_next[k][l] == 'B')
                {
                    painter.setBrush(QBrush(QColor(0, 0, 255),Qt::SolidPattern));
                    painter.drawEllipse(current_col, current_row + l * one, one, one);
                }

                if (cur_next[k][l] == 'P')
                {
                    painter.setBrush(QBrush(QColor(255, 0, 255),Qt::SolidPattern));
                    painter.drawEllipse(current_col, current_row + l * one, one, one);
                }
            }
        }
        if (cur_next[k] == "O")
        {
            painter.setBrush(QBrush(QColor(255, 255, 0),Qt::SolidPattern));
            painter.drawRect(current_col, current_row, one, one);
            painter.drawRect(current_col, current_row + one, one, one);
            painter.drawRect(current_col + one, current_row, one, one);
            painter.drawRect(current_col + one, current_row + one, one, one);
        }
        else if (cur_next[k] == "T")
        {
            painter.setBrush(QBrush(QColor(255, 0, 255),Qt::SolidPattern));
            painter.drawRect(current_col + one, current_row, one, one);
            painter.drawRect(current_col, current_row + one, one, one);
            painter.drawRect(current_col + one, current_row + one, one, one);
            painter.drawRect(current_col + 2 * one, current_row + one, one, one);
        }
        else if (cur_next[k] == "S")
        {
            painter.setBrush(QBrush(QColor(0, 255, 0),Qt::SolidPattern));
            painter.drawRect(current_col + one, current_row, one, one);
            painter.drawRect(current_col + 2 * one, current_row, one, one);
            painter.drawRect(current_col, current_row + one, one, one);
            painter.drawRect(current_col + one, current_row + one, one, one);
        }
        else if (cur_next[k] == "Z")
        {
            painter.setBrush(QBrush(QColor(255, 0, 0),Qt::SolidPattern));
            painter.drawRect(current_col, current_row, one, one);
            painter.drawRect(current_col + one, current_row, one, one);
            painter.drawRect(current_col + one, current_row + one, one, one);
            painter.drawRect(current_col + 2 * one, current_row + one, one, one);
        }
        else if (cur_next[k] == "J")
        {
            painter.setBrush(QBrush(QColor(0, 0, 255),Qt::SolidPattern));
            painter.drawRect(current_col, current_row, one, one);
            painter.drawRect(current_col, current_row + one, one, one);
            painter.drawRect(current_col + one, current_row + one, one, one);
            painter.drawRect(current_col + 2 * one, current_row + one, one, one);
        }
        else if (cur_next[k] == "L")
        {
            painter.setBrush(QBrush(QColor(255, 128, 0),Qt::SolidPattern));
            painter.drawRect(current_col + 2 * one, current_row, one, one);
            painter.drawRect(current_col, current_row + one, one, one);
            painter.drawRect(current_col + one, current_row + one, one, one);
            painter.drawRect(current_col + 2 * one, current_row + one, one, one);
        }
        else if (cur_next[k] == "I")
        {
            painter.setBrush(QBrush(QColor(0, 255, 255),Qt::SolidPattern));
            painter.drawRect(current_col, current_row + one, one, one);
            painter.drawRect(current_col + one, current_row + one, one, one);
            painter.drawRect(current_col + 2 * one, current_row + one, one, one);
            painter.drawRect(current_col + 3 * one, current_row + one, one, one);
        }
    }


    ///////////보드 출력////////////
    for(int i=0;i<2;i++)
    {
        for(int j=0;j<COL;j++)
        {
            painter.setBrush(QBrush(Colors["Gray"],Qt::SolidPattern));
            painter.drawRect(j*BLOCK_SIZE+MARGIN,i*BLOCK_SIZE+MARGIN,BLOCK_SIZE,BLOCK_SIZE);
        }
    }
    for(int i=0; i<ROW; i++)
    {
        for(int j=0; j<COL; j++)
        {
            QColor print_color=Colors[cur_board[i][j]];
            painter.setBrush(QBrush(print_color,Qt::SolidPattern));
            if(p_game->encoding_board[i][j]>=2 && p_game->encoding_board[i][j]<=7)
                painter.drawEllipse(j*BLOCK_SIZE+MARGIN,i*BLOCK_SIZE+MARGIN,BLOCK_SIZE,BLOCK_SIZE);
            else
                painter.drawRect(j*BLOCK_SIZE+MARGIN,i*BLOCK_SIZE+MARGIN,BLOCK_SIZE,BLOCK_SIZE);
        }
    }
    //격자판 그림
    painter.setPen(Qt::black);
    for (int i = 0; i <= ROW; i++)
        painter.drawLine(MARGIN, MARGIN + i * BLOCK_SIZE, MARGIN + COL * BLOCK_SIZE, MARGIN + i * BLOCK_SIZE); // 가로선 그리기
    for (int j = 0; j <= COL; j++)
        painter.drawLine(MARGIN + j * BLOCK_SIZE, MARGIN, MARGIN + j * BLOCK_SIZE, MARGIN + ROW * BLOCK_SIZE); // 세로선 그리기

    //////////////////////////////
    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial",14));
    painter.drawText(QRect(MARGIN*5+COL*BLOCK_SIZE,MARGIN,2*BLOCK_SIZE,BLOCK_SIZE),Qt::AlignCenter,"NEXT");

    painter.setPen(Qt::black);
    painter.setFont(QFont("Arial",14));
    if (GAMENAME == "Puyopuyo")
        painter.drawText(QRect(MARGIN*3+COL*BLOCK_SIZE,MARGIN*2+4*BLOCK_SIZE,BLOCK_SIZE*4,BLOCK_SIZE*4 + 300),Qt::AlignCenter,"current chain : " + QString::number(score));
    if (GAMENAME == "Tetris")
        painter.drawText(QRect(MARGIN*3+COL*BLOCK_SIZE,MARGIN*2+4*BLOCK_SIZE,BLOCK_SIZE*4,BLOCK_SIZE*4 + 800),Qt::AlignCenter,"current line : " + QString::number(score));
    if (GAMENAME == "PuyopuyoTetris")
        painter.drawText(QRect(MARGIN*3+COL*BLOCK_SIZE, MARGIN*2+4*BLOCK_SIZE ,BLOCK_SIZE*6, BLOCK_SIZE*4 + 800),Qt::AlignCenter,"current chain&line : " + QString::number(score));
}
void GameWindow::keyPressEvent(QKeyEvent *event)
{
    if (p_game->gameover == true)
        return;

    if(!p_game->block_stop)
    {
        switch(event->key())
        {
        case Qt::Key_Down:
            drawNext();
            break;
        case Qt::Key_Left:
            movecol(-1);
            break;
        case Qt::Key_Right:
            movecol(1);
            break;
        case Qt::Key_Space:
            harddrop();
            break;
        case Qt::Key_Z:
            rotate(1);
            break;
        case Qt::Key_X:
            rotate(0);
            break;
        case Qt::Key_Q:
            over();
            break;
        default:
            break;
        }
    }
}
void GameWindow::timerEvent(QTimerEvent* event)
{
    if (p_game->gameover == true)
        return;

    if(event->timerId()==timer)
        drawNext();
}
void GameWindow::drawNext()
{
    uniform_int_distribution<int> distribution(0, 100);

    int LENGTH = p_game->LENGTH;
    string* cur_next = p_game->next;
    if(p_game->block_stop)//블록이 멈춰서 true면 생성하기, 생성
    {
        generateblock();
        if(GAMENAME=="Puyopuyo")
            cur_next[p_game->front_id]=p_game->combi[distribution(rd)%25];
        else if (GAMENAME == "Tetris")
            cur_next[p_game->front_id]=p_game->combi[25+distribution(rd)%7];
        else if(GAMENAME == "PuyopuyoTetris")
            cur_next[p_game->front_id]=p_game->combi[distribution(rd)%32];
        p_game->front_id=(p_game->front_id+1)%LENGTH;
        p_game->back_id=(p_game->back_id+1)%LENGTH;

        (p_game->score)++;
    }
    else
        dropblock();//드롭
    update();
}
void GameWindow::dropblock() // 블록 드롭 함수 추가
{
    delpreinfo(); //이전 정보 제거

    if (blockcorrect(p_game->curblock.cur_encoding_block, p_game->axis_row + 1, p_game->axis_col))
        p_game->axis_row++;//블록 내려가도 되면 row 증가
    else
        p_game->block_stop = true;//블록을 보드에 고정시킴

    blockplace(p_game->curblock, 0);
    if(p_game->block_stop)//블록이 멈추면 인코딩 정보를 보드에 업데이트
        harddrop();
    update();
}
void GameWindow::generateblock()
{
    //첫 생성 좌표 축 초기화//
    p_game->axis_row=0;
    if(GAMENAME=="Puyopuyo") p_game->axis_col=1;
    else if (GAMENAME == "Tetris") p_game->axis_col=3;
    else if (GAMENAME == "PuyopuyoTetris") p_game->axis_col=2;
    /////////////////

    //변수 가져오기//
    int f_id=p_game->front_id;//next 배열에서 가져올 블록의 인덱스
    string* cur_next = p_game->next;//next 배열
    ///////////////

    if(cur_next[f_id].length() == 2)//가져올 게 뿌요뿌요면
    {
        p_game->curblock.shape=cur_next[f_id];
        p_game->curblock.cur_block[0][1] = cur_next[f_id][0];//뿌요 색상 가져오기
        p_game->curblock.cur_block[1][1] = cur_next[f_id][1];//뿌요 색상 가져오기
        for(int i=0;i<4;i++)
            for(int j=0;j<4;j++)
                p_game->curblock.cur_encoding_block[i][j]=p_game->block[7][i][j];//뿌요면 block테이블에서 7번에 매핑된 정보를 가져옴
    }
    else
    {
        //block 매핑 테이블에서 해당 인덱스를 가져옴///
        int block_id=-1;
        if(p_game->next[f_id]=="T") block_id=5;
        else if(cur_next[f_id]=="L") block_id=2;
        else if(cur_next[f_id]=="J") block_id=1;
        else if(cur_next[f_id]=="I") block_id=0;
        else if(cur_next[f_id]=="Z") block_id=4;
        else if(cur_next[f_id]=="S") block_id=3;
        else if(cur_next[f_id]=="O") block_id=6;
        p_game->curblock.shape=block_shape[block_id];
        //정보가 있으면//
        if(block_id>=0)
        {
            for(int i=0;i<4;i++)
            {
                for(int j=0;j<4;j++)
                {
                    p_game->curblock.cur_encoding_block[i][j]=p_game->block[block_id][i][j];//block 테이블에서 매핑 인덱스의 배열을 가져옴
                    if(p_game->curblock.cur_encoding_block[i][j]==1)//인코딩 테이블에 정보가 존재하면 색상을 가져옴
                        p_game->curblock.cur_block[i][j]=cur_next[f_id];
                }
            }
        }
    }
    p_game->block_stop=false; //블록 생성하면 stop을 false
    if(!blockcorrect(p_game->curblock.cur_encoding_block, p_game->axis_row, p_game->axis_col))
        over();
    else
        blockplace(p_game->curblock, 0);
    update();
}
void GameWindow::movecol(int a) //왼,오 방향키 눌렀을 때
{
    delpreinfo();
    if(blockcorrect(p_game->curblock.cur_encoding_block, p_game->axis_row, p_game->axis_col+a))
        p_game->axis_col+=a;
    blockplace(p_game->curblock, 0);
    update();
}
void GameWindow::rotate(int a) //0이면 x(시계), 1이면 z(반시계)로 회전
{
    if(p_game->curblock.shape=="O")
        return;
    int tmp[4][4];
    string color_tmp[4][4];
    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
        {
            tmp[i][j]=0;
            color_tmp[i][j]="White";
        }
    int n;
    if(p_game->curblock.shape=="I")
        n=4;
    else
        n=3;

    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            if(a==1)
            {
                tmp[n-1-j][i]=p_game->curblock.cur_encoding_block[i][j];
                color_tmp[n-1-j][i]=p_game->curblock.cur_block[i][j];
            }
            else if(a==0)
            {
                tmp[j][n-1-i]=p_game->curblock.cur_encoding_block[i][j];
                color_tmp[j][n-1-i]=p_game->curblock.cur_block[i][j];
            }
        }
    }
    delpreinfo();

    if(blockcorrect(tmp, p_game->axis_row, p_game->axis_col))
    {
        for(int i=0;i<4;i++)
        {
            for(int j=0;j<4;j++)
            {
                p_game->curblock.cur_encoding_block[i][j]=tmp[i][j];
                p_game->curblock.cur_block[i][j]=color_tmp[i][j];
            }
        }
    }
    blockplace(p_game->curblock, 0);
    update();
}
void GameWindow::harddrop()// 하드 드롭
{
    p_game->block_stop=true;
    delpreinfo();
    int ROW=p_game->ROW;
    for(int i=0;i<ROW;i++)
    {
        if(blockcorrect(p_game->curblock.cur_encoding_block,p_game->axis_row+1, p_game->axis_col))
            p_game->axis_row++;
    }
    if(p_game->curblock.shape.length()==2)//뿌요는 분리되도록 만듬
    {
        Curblock* pu;//0은 중심블록, 1은 옆 블록
        pu = new Curblock[2];
        generate_pu(pu);

        if(pu[0].axis[0]>=pu[1].axis[0])//중심 뿌요가 옆 뿌요보다 아래거나 같으면 중심부터 아니면 옆부터
        {

            for(int i=0;i<ROW;i++)
            {
                if(blockcorrect(pu[0].cur_encoding_block,pu[0].axis[0]+1, pu[0].axis[1]))
                    pu[0].axis[0]++;
            }
            blockplace(pu[0], 1);
            encoding_update(pu[0], 1);

            for(int i=0;i<ROW;i++)
            {
                if(blockcorrect(pu[0].cur_encoding_block,pu[1].axis[0]+1, pu[1].axis[1]))
                    pu[1].axis[0]++;
            }
            blockplace(pu[1], 1);
            encoding_update(pu[1], 1);
        }
        else
        {
            for(int i=0;i<ROW;i++)
            {
                if(blockcorrect(pu[0].cur_encoding_block,pu[1].axis[0]+1, pu[1].axis[1]))
                    pu[1].axis[0]++;
            }
            blockplace(pu[1], 1);
            encoding_update(pu[1], 1);

            for(int i=0;i<ROW;i++)
            {
                if(blockcorrect(pu[0].cur_encoding_block,pu[0].axis[0]+1, pu[0].axis[1]))
                    pu[0].axis[0]++;
            }
            blockplace(pu[0], 1);
            encoding_update(pu[0], 1);
        }
        delete[] pu;
    }
    else
    {
        blockplace(p_game->curblock, 0);
        drop_tet_on_pu();
        encoding_update(p_game->curblock, 0);
    }
    del_line();
    main_delete_puyo();
    overcheck();
    update();
}
void GameWindow::drop_tet_on_pu()
{
    int ROW=p_game->ROW;
    for(int i=0;i<5;i++)//변환 배열 초기화
    {
        for(int j=0;j<5;j++)
        {
            pute_encoding_block[i][j]=0;
            pute_block[i][j]="White";
            if(i>0 && j>0)
            {
                pute_encoding_block[i][j]=p_game->curblock.cur_encoding_block[i][j];
                pute_block[i][j]=p_game->curblock.cur_block[i][j];
            }
        }
    }
    for(int i=0;i<ROW;i++)
    {
        if(pu_under_correct())
        {

        }
    }
}
void GameWindow::del_line()
{
    int ROW=p_game->ROW;
    int COL=p_game->COL;
    int tmp_row=ROW-1;//보드의 맨 아래 인덱스
    int flag=0;
    for(int i=0;i<ROW;i++)
    {
        flag=COL;//블록이 전부 -1인지 체크==전부 테트로미노인지.
        for(int j=0;j<COL;j++)
        {
            if(p_game->encoding_board[i][j]==-1)
                flag--;
        }
        if(flag==0)//모든 줄에 -1이었으므로 테트로미노가 지워져야 함
        {
            for(int j=0;j<COL;j++)
            {
                p_game->encoding_board[i][j]=0;
                p_game->board[i][j]="White";
            }
        }
    }

    int **encoding_tmp=new int*[ROW];//인코딩 tmp 테이블
    string **tmp=new string*[ROW];//컬러 tmp 테이블
    for(int i=0;i<ROW;i++)
    {
        encoding_tmp[i]=new int[COL];
        tmp[i]=new string[COL];
    }
    for(int i=0;i<ROW;i++)//tmp 테이블들 초기화
    {
        for(int j=0;j<COL;j++)
        {
            tmp[i][j]="White";
            if(i<2)
                tmp[i][j]="Gray";
            encoding_tmp[i][j]=0;
        }
    }

    for(int i=0;i<ROW;i++)
    {
        flag=COL;
        for(int j=0;j<COL;j++)
        {
            if(p_game->encoding_board[ROW-1-i][j]==0)
                flag--;
            else
                break;
        }
        if(flag!=0)//빈 칸이 아니므로 == 정보가 있으므로
        {
            for(int j=0;j<COL;j++)
            {
                encoding_tmp[tmp_row][j]=p_game->encoding_board[ROW-1-i][j];
                tmp[tmp_row][j]=p_game->board[ROW-1-i][j];
            }
            tmp_row--;
        }//정보가 없으면 tmp에 정보를 저장하지 않음 -> 한 줄을 뛰어넘음
    }
    for(int i=0;i<ROW;i++)
    {
        delete[] p_game->board[i];
        delete[] p_game->encoding_board[i];
    }
    delete[] p_game->board;
    delete[] p_game->encoding_board;
    p_game->board=tmp;
    p_game->encoding_board=encoding_tmp;
    update();
}
void GameWindow::main_delete_puyo()//뿌요 지울 때 호출하는 메인 삭제 함수
{
    while(1)
    {
        if (!del_pu())// 더 이상 지울 뿌요가 없으면 종료
            break;
    }
    pu_drop();  // 중력 적용
}
void GameWindow::bfs_pu(int x, int y, vector<vector<bool>>& visited, vector<pair<int, int>>& to_pop)
{
    char color = p_game->encoding_board[x][y];  // 현재 뿌요의 색상
    QQueue<pair<int, int>> q;   // BFS를 위한 큐
    q.enqueue({x, y});
    visited[x][y] = true;

    vector<pair<int, int>> connected;  // 연결된 같은 색 뿌요의 좌표
    connected.push_back({x, y});

    while (!q.empty())
    {
        int cx=q.front().first;  // 현재 큐의 첫번째 요소
        int cy=q.front().second;  // 현재 큐의 첫번째 요소
        q.dequeue();

        for (int i=0;i<4;i++)// 모든 방향으로 탐색
        {
            int nx = cx + dx[i];
            int ny = cy + dy[i];

            if (is_valid(nx, ny) && !visited[nx][ny] && p_game->encoding_board[nx][ny] == color)
            {
                visited[nx][ny] = true;
                q.enqueue({nx, ny});
                connected.push_back({nx, ny});
            }
        }
    }

    // 최소 개수 이상의 뿌요가 연결된 경우, 지울 리스트에 추가
    if (connected.size() >= 4)
    {
        for (int i=0;i<connected.size();i++)
            to_pop.push_back({connected[i].first, connected[i].second});
    }
}
void GameWindow::pu_drop()//뿌요 지우고 중력 적용하는 함수
{
    int ROW=p_game->ROW;
    int COL=p_game->COL;
    for (int j = 0; j < COL; ++j)
    {
        int write_pos = ROW - 1;  // 뿌요를 떨어뜨릴 위치
        for (int i = ROW - 1; i >= 0; i--)
        {
            if (p_game->encoding_board[i][j] >=2 && p_game->encoding_board[i][j]<=6)
            {
                p_game->encoding_board[write_pos][j] = p_game->encoding_board[i][j];
                p_game->board[write_pos][j]=p_game->board[i][j];
                if(write_pos != i)
                {
                p_game->encoding_board[i][j] = 0;
                p_game->board[i][j]="White";
                }
                write_pos--;
            }
            else if(p_game->encoding_board[i][j]==-1)
                write_pos=i-1;
        }
    }
}
bool GameWindow::del_pu()//실질적으로 뿌요 지우는 함수
{
    int ROW=p_game->ROW;
    int COL=p_game->COL;
    vector<vector<bool>> visited(ROW, vector<bool>(COL, false));
    vector<pair<int, int>> to_pop;
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            if (p_game->encoding_board[i][j] >= 2 && p_game->encoding_board[i][j]<=6 && !visited[i][j])
                bfs_pu(i, j, visited, to_pop);
        }
    }
    int size=to_pop.size();
    for(int i=0;i<size;i++)
    {
        int x=to_pop[i].first;
        int y=to_pop[i].second;
        p_game->encoding_board[x][y] = 0;
        p_game->board[x][y]="White";
    }
    pu_drop();  // 중력 적용
    return !to_pop.empty();
}
void GameWindow::generate_pu(Curblock* pu)
{
    //(1,1)의 좌표를 curblock과 같게 초기화
    pu[0].axis[0]=p_game->axis_row;
    pu[0].axis[1]=p_game->axis_col;

    for(int i=0;i<4;i++)//encoding matrix initialization to 0
    {
        for(int j=0;j<4;j++)
        {
            pu[0].cur_encoding_block[i][j]=0;
            pu[1].cur_encoding_block[i][j]=0;
        }
    }

    //옆 블록 위치 찾기
    for(int i=0;i<3;i++)
    {
        for(int j=0;j<3;j++)
        {
            if(p_game->curblock.cur_encoding_block[i][j]==7 && (i!=j))
            {
                pu[1].cur_block[1][1]=p_game->curblock.cur_block[i][j];
                pu[1].axis[0]=p_game->axis_row+i-1;
                pu[1].axis[1]=p_game->axis_col+j-1;
            }
        }
    }
    //중심블록 위치는 항상 [1,1]
    pu[0].cur_encoding_block[1][1]=7;
    pu[1].cur_encoding_block[1][1]=7;//옆 블록 위치도 [1,1]로 고정
    pu[0].cur_block[1][1]=p_game->curblock.cur_block[1][1];
}
void GameWindow::delpreinfo()
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            int rows=p_game->axis_row + i;
            int cols=p_game->axis_col + j;
            if (p_game->curblock.cur_encoding_block[i][j] != 0)
            {
                if (is_valid(rows,cols))
                {
                    p_game->board[rows][cols] = "White"; //이전 색상 정보를 지움
                    p_game->encoding_board[rows][cols] = 0; //이전 인코딩 정보를 지움
                }
            }
        }
    }
    for(int i=0;i<2;i++)
        for(int j=0;j<p_game->COL;j++)
            p_game->board[i][j]="Gray";//맨 위 두 칸은 보드의 색상을 회색으로 유지함.
}
void GameWindow::blockplace(Curblock block, int a)// 블록을 보드에 놓기
{
    int axis_row, axis_col;
    if(a)
    {
        axis_row=block.axis[0];
        axis_col=block.axis[1];
    }
    else
    {
        axis_row=p_game->axis_row;
        axis_col=p_game->axis_col;
    }
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {

            int rows=axis_row + i;
            int cols=axis_col + j;
            if (block.cur_encoding_block[i][j] != 0 && is_valid(rows,cols))
            {
                p_game->board[rows][cols] = block.cur_block[i][j];//색상을 보드에 업데이트
                p_game->encoding_board[rows][cols]=block.cur_encoding_block[i][j];//인코딩 정보를 보드에 업데이트
            }
        }
    }
}
void GameWindow::encoding_update(Curblock block, int a)
{
    int ROW=p_game->ROW;
    int COL=p_game->COL;
    int axis_row, axis_col;
    if(a)
    {
        axis_row=block.axis[0];
        axis_col=block.axis[1];
    }
    else
    {
        axis_row=p_game->axis_row;
        axis_col=p_game->axis_col;
    }
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            int rows=axis_row + i;
            int cols=axis_col + j;
            if(block.cur_encoding_block[i][j] != 0 && rows >= 0 && rows < ROW && cols >= 0 && cols < COL)
            {
                if(p_game->encoding_board[rows][cols]==1)
                    p_game->encoding_board[rows][cols]=-1;
                else if(p_game->encoding_board[rows][cols]==7)
                {
                    if(p_game->board[rows][cols]=="R")
                        p_game->encoding_board[rows][cols]=2;
                    else if(p_game->board[rows][cols]=="Y")
                        p_game->encoding_board[rows][cols]=3;
                    else if(p_game->board[rows][cols]=="G")
                        p_game->encoding_board[rows][cols]=4;
                    else if(p_game->board[rows][cols]=="B")
                        p_game->encoding_board[rows][cols]=5;
                    else if(p_game->board[rows][cols]=="P")
                        p_game->encoding_board[rows][cols]=6;
                }
            }
        }
    }
}
void GameWindow::overcheck()
{
    if(GAMENAME=="Puyopuyo")
    {
        if(p_game->encoding_board[2][2]!=0)
            over();
    }
    else if(GAMENAME=="Tetris")
    {
        for(int j=0;j<p_game->COL;j++)
        {
            if(p_game->encoding_board[1][j]!=0)
                over();
        }
    }
    else if(GAMENAME=="PuyopuyoTetris")
    {
        for(int i=0;i<4;i++)
        {
            if(p_game->encoding_board[2][i+2]!=0)
                over();
        }
    }
}
bool GameWindow::blockcorrect(int tmp[4][4], int posX, int posY) {
    int ROW = p_game->ROW;
    int COL = p_game->COL;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (tmp[i][j] != 0) {
                int x = posX + i;
                int y = posY + j;
                if (x<0 || x>=ROW || y<0 && y>=COL)
                    return false;
                if(p_game->encoding_board[x][y] != 0)
                    return false;
            }
        }
    }
    return true;
}
bool GameWindow::pu_under_correct()
{
    int ROW=p_game->ROW;
    int COL=p_game->COL;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (p_game->curblock.cur_encoding_block[i][j] != 0)
            {
                int x = p_game->axis_row + i;
                int y = p_game->axis_col + j;
                if (x<0 || x>=ROW || y<0 || y>=COL)
                    return false;
                if(p_game->encoding_board[x][y] == -1)
                    return false;
            }
        }
    }
    return true;
}
bool GameWindow::is_valid(int x, int y) {
    return (x >= 0 && x < p_game->ROW && y >= 0 && y < p_game->COL);
}
void GameWindow::over()
{
    p_game->gameover = true;
    killTimer(timer);
    gameoverwindow = new GameoverWindow;
    gameoverwindow->show();
}

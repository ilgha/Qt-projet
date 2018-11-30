#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "player.h"
#include "ui_mainwindow.h"
#include <QMainWindow>
#include <utility>
#include <QtNetwork>
#include <QTimer>
#include "infantery.h"
#include "building.h"
#include "game.h"
#include <vector>

namespace Ui {
class MainWindow;
}

typedef std::pair <int, int> IntPair;

class MainWindow : public QMainWindow
{
    Q_OBJECT



    //map 25087
    int t[17][21] = {{8,12,12,12,12,12,18,3,1,2,18,15,15,34,1,1,1,2,30,30,33},
                     {11,34,1,1,1,2,1,18,15,15,34,1,1,3,1,3,1,1,1,3,30},
                     {11,2,1,3,2,18,15,35,1,1,1,3,1,1,1,1,15,15,19,1,2},
                     {19,2,34,15,15,34,1,1,2,2,2,2,2,3,1,13,23,1,21,19,1},
                     {4,4,8,3,1,1,1,2,2,2,2,34,2,1,34,25,13,1,3,21,34},
                     {2,34,5,1,1,1,2,2,34,2,2,2,2,3,1,16,1,1,1,1,3},
                     {3,1,26,1,3,2,2,1,16,3,2,2,34,1,3,16,34,1,3,2,7},
                     {1,18,26,1,1,2,34,3,16,1,1,3,1,1,18,20,1,1,7,4,9},
                     {36,20,5,3,1,3,18,15,24,15,15,15,22,15,20,3,1,3,5,18,36},
                     {7,4,9,1,1,18,20,1,1,3,1,1,16,3,34,2,1,1,26,20,1},
                     {9,2,3,1,34,16,3,1,34,2,2,3,16,1,2,2,3,1,26,1,3},
                     {3,1,1,1,1,16,1,3,2,2,2,2,34,2,2,1,1,1,5,34,2},
                     {34,19,3,1,2,23,34,1,2,34,2,2,2,2,1,1,1,3,10,4,4},
                     {1,21,19,1,25,9,1,3,2,2,2,2,2,1,1,34,15,15,34,2,17},
                     {2,1,21,15,5,1,1,1,1,3,1,1,1,35,15,20,2,3,1,2,11},
                     {29,3,1,1,1,3,1,3,1,1,34,15,15,20,1,2,1,1,1,34,11},
                     {33,29,29,2,1,1,1,34,15,15,20,2,1,3,11,2,2,2,2,2,6}};


//    int t[12][18] = {{1,1,1,1,1,1,1,1,35,1,35,1,1,1,1,1,34,3},
//                     {1,1,3,3,3,3,3,3,3,34,1,34,1,1,1,1,1,34},
//                     {1,1,1,1,34,35,34,1,34,1,34,1,1,1,1,1,34,1},
//                     {35,1,1,2,1,1,1,3,1,34,1,1,3,34,1,35,1,2},
//                     {34,1,1,34,2,1,3,1,1,3,1,1,1,1,3,1,1,1},
//                     {1,1,1,1,1,1,1,1,1,1,1,3,1,1,1,1,1,1},
//                     {28,35,1,1,1,1,1,1,1,3,2,1,3,1,1,34,1,34},
//                     {28,28,27,28,28,28,28,3,28,3,3,3,1,1,1,1,1,1},
//                     {1,1,1,1,1,35,28,28,28,28,3,3,1,1,34,1,35,1},
//                     {1,1,1,1,1,34,1,26,1,1,2,1,34,1,34,1,1,1},
//                     {1,1,1,1,1,1,1,34,28,28,1,1,1,1,34,1,3,1},
//                     {1,1,1,1,1,1,34,28,28,3,3,1,3,34,1,3,34,3}};

    Player* player = nullptr;
    Game* game = nullptr;
    std::vector<Unit*> *army;
    std::vector<IntPair> cases;
    std::vector<int> depl;
    bool inMenu = false;
    bool inMove = false;
    bool isConfigured = false;


    Ui::MainWindow *ui;
    quint32 currentSize = 0;
    QTimer timer;
    int a = 5;
    unsigned int x = 21;
    unsigned int y = 17;

    QTcpServer* server = nullptr;
    QTcpSocket* other = nullptr;
    int posX = 100, posY = 150;
    bool myTurn = false;

public:
    explicit MainWindow(QWidget *parent, Game* game);
    ~MainWindow();

    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent* event);
    void keyPressEvent(QKeyEvent *event);
    void showMove(Unit* unit);
    void showMenu(Building* b, Unit* u);
    void unitMove(QMouseEvent *event);
    int getXIm(int ID);
    int getYIm(int ID);
    int moveUnit(Unit* unit, int x, int y, int MP);
    void createUnit();
    
private:
    void sendJson(QJsonObject obj);

public slots:
    void tick();
    void onNewConnection();
    void onConnected();
    void onDisconnected();
    void onData();
};

#endif // MAINWINDOW_H



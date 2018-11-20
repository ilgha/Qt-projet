#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "player.h"
#include "ui_mainwindow.h"
#include <QMainWindow>
#include <utility>
//#include <QtNetwork>
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
    int t[12][18] = {{1,1,1,1,1,1,1,1,44,1,44,1,1,1,1,1,34,3},
                       {1,1,15,15,15,15,15,15,15,47,1,43,1,1,1,1,1,34},
                       {1,1,1,1,34,35,34,1,34,1,43,1,1,1,1,1,34,1},
                       {35,1,1,2,1,1,1,3,1,43,1,1,3,34,1,35,1,2},
                       {34,1,1,34,2,1,3,1,1,3,1,1,1,1,3,1,1,1},
                       {1,1,1,1,1,1,1,1,1,1,1,3,1,1,1,1,1,1},
                       {28,35,1,1,1,1,1,1,1,3,2,1,3,1,1,34,1,34},
                       {28,28,27,28,28,28,28,3,28,3,3,3,1,1,1,1,1,1},
                       {1,1,1,1,1,35,28,28,28,28,3,3,1,1,34,1,35,1},
                       {1,1,1,1,1,34,1,26,1,1,2,1,34,1,34,1,1,1},
                       {1,1,1,1,1,1,1,34,28,28,1,1,1,1,34,1,3,1},
                       {1,1,1,1,1,1,34,28,28,3,3,1,3,34,1,3,34,3}};
    Player* player = nullptr;
    Game* game = nullptr;
    std::vector<Unit*> *army;
    std::vector<IntPair> cases;
    bool inMenu = false;
    bool inMove = false;

    Ui::MainWindow *ui;
    QTimer timer;
    int a = 5;
    unsigned int x = 18;
    unsigned int y = 12;

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
    void moveUnit(Unit unit);
    void createUnit();
    //QTcpServer* server = nullptr;

public slots:
    void tick();
};

#endif // MAINWINDOW_H



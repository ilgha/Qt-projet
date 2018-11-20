#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "player.h"
#include "ui_mainwindow.h"
#include <QMainWindow>
#include <utility>
//#include <QtNetwork>
#include <QTimer>
#include "infantery.h"
#include "game.h"
#include <vector>

namespace Ui {
class MainWindow;
}

typedef std::pair <int, int> IntPair;

class MainWindow : public QMainWindow
{
    Q_OBJECT
    int t[12][18];
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
    //QTcpServer* server = nullptr;

public slots:
    void tick();
};

#endif // MAINWINDOW_H



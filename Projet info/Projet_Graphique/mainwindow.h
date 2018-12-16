#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Player.h"
#include "ui_mainwindow.h"
#include <QMainWindow>
#include <utility>
#include <QtNetwork>
#include <QTimer>
#include "infantry.h"
#include "building.h"
#include "game.h"
#include "node.h"
#include <vector>
#include <QLabel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT



    //map 25087
typedef std::pair <int, int> IntPair;
    Game* game = nullptr;
    bool inMenu = false;
    bool inMove = false;
    bool isConfigured = false;
    Ui::MainWindow *ui;
    quint32 currentSize = 0;
    QTimer timer;
    int a = 5;
    unsigned int x = 26;
    unsigned int y = 17;
    int t[17][26];
    QTcpServer* server = nullptr;
    QTcpSocket* other = nullptr;
    std::vector<int> posX;
    std::vector<int> posY;
    std::vector<IntPair> fight;
    bool myTurn = false;
    QLabel *textWidget = new QLabel(tr("Text Widget"), this);
    void combat(QMouseEvent *event);


public:
    explicit MainWindow(QWidget *parent, Game* game);
    ~MainWindow();
    void unitMove(int i);
    void capture(int i);
    void ShowCombat(int i);
private:
    QJsonObject unitMove(QMouseEvent *event);
    void sendJson(QJsonObject obj);
    void music();
    int tDtoIsoX(int x, int y);
    int isoToTDX(int x, int y);
    int tDtoIsoY(int x, int y);
    int isoToTDY(int x, int y);
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent* event);
    void keyPressEvent(QKeyEvent *event);
    void showMove(Unit* unit);
    QJsonObject changeTurn();
    int getXIm(int ID);
    int getYIm(int ID);
    void createUnit(QMouseEvent *event);
    int actionOnUnit(QMouseEvent *event);
    int smallestF(std::vector<node*> open);
    bool compareNode(node n1, node n2);
    std::vector<node*> bestPath(node target);
public slots:
    void tick();
    void onNewConnection();
    void onConnected();
    void onDisconnected();
    void onData();
    void playIA(Player* player);

};

#endif // MAINWINDOW_H



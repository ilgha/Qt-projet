#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Player.h"
#include "ui_mainwindow.h"
#include <QMainWindow>
#include <QTimer>
#include "infantery.h"
#include "game.h"
#include <vector>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    int t[12][18];
    Player* player = nullptr;
    Game* game = nullptr;
    std::vector<Unit> *army;
    bool inMenu;

    Ui::MainWindow *ui;
    QTimer timer;
    int a = 5;
    int x = 18;
    int y = 12;
public:
    explicit MainWindow(QWidget *parent, Game* game);
    ~MainWindow();

    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent* event);
    void keyPressEvent(QKeyEvent *event);
    void showMove();

public slots:
    void tick();
};

#endif // MAINWINDOW_H

#include "mainwindow.h"
#include <QApplication>
#include <QPushButton>
#include "game.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Player player1 = Player(0, 100000);
    Player player2 = Player(0, 100000);
    Game* game = new Game(&player1, &player2);
    MainWindow w(nullptr, game);
    w.showFullScreen();
    w.show();
    return a.exec();
}

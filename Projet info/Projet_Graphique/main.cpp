#include "mainwindow.h"
#include <QApplication>
#include "game.h"
int main(int argc, char *argv[])
{
    Player player1 = Player(0, 1000);
    Player player2 = Player(0, 1000);
    Game* game = new Game(&player1, &player2);
    QApplication a(argc, argv);
    MainWindow w(nullptr, &player1, game);
    w.show();

    return a.exec();
}

#include "mainwindow.h"
#include <QApplication>
#include <QPushButton>
#include "game.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
<<<<<<< HEAD
    Player player1 = Player(0, 100000);
=======
    Player player1 = Player(1, 100000);
>>>>>>> 86a10cf29935ebb0c49b6ede31dc9be1b0cf2c00
    Player player2 = Player(2, 100000);
    Game* game = new Game(&player1, &player2);
    MainWindow w(nullptr, game);
    //w.showMaximized();
    w.show();
    return a.exec();
}

#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include "game.h"
#include <QComboBox>
#include <string>

class Menu : public QWidget
{
    Q_OBJECT
    int type;
    QComboBox* list;
    Game* game;
    int building;
    string name;
    string getName(int type);
public:
    explicit Menu(QWidget *parent = nullptr, Game* game = nullptr, int i = NULL);

signals:

public slots:
void recruitAction();

};

#endif // MENU_H

#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include "game.h"

class Menu : public QWidget
{
    Q_OBJECT
public:
    explicit Menu(QWidget *parent = nullptr, Game* game = nullptr, int i = NULL);

signals:

public slots:
    //void recruit();
};

#endif // MENU_H

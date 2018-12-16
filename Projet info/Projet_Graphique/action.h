#ifndef ACTION_H
#define ACTION_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include "mainwindow.h"

class Action : public QWidget{

    Q_OBJECT
    MainWindow* mainWindow;
    int unit;
public:
    Action(QWidget *parent = nullptr, int unit = 0, bool capt = false, bool attack = false, bool movable= false, MainWindow* mainWindow = nullptr);

public slots:
    void moveAction();
    void attackAction();
    void captureAction();
};

#endif // ACTION_H

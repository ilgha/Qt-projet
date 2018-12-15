#ifndef ACTION_H
#define ACTION_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include "mainwindow.h"

class Action : public QWidget{

    Q_OBJECT
    QMouseEvent* click;
    MainWindow* mainWindow;
public:
    Action(QWidget *parent = nullptr, QMouseEvent* click = nullptr, MainWindow* mainWindow = nullptr);

public slots:
    void moveAction();
    void attackAction();
    void captureAction();
};

#endif // ACTION_H

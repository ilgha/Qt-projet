#include "action.h"

Action::Action(QWidget *parent, QMouseEvent* click, MainWindow* mainWindow)
{
    this->click = click;
    this->mainWindow = mainWindow;
    QVBoxLayout* layout = new QVBoxLayout();
    QPushButton* moveButton = new QPushButton(this);
    moveButton->setText("move");
    moveButton->setMinimumHeight(60);
layout->addWidget(moveButton);
    QPushButton *attackButton = new QPushButton(this);
    attackButton->setText("attack");
    attackButton->setMinimumHeight(60);
    attackButton->setEnabled(false);
  layout->addWidget(attackButton);
    QPushButton *captureButton = new QPushButton(this);
    captureButton->setText("capture");
    captureButton->setMinimumHeight(60);
    captureButton->setEnabled(false);




    layout->addWidget(captureButton);

    moveButton->show();
    attackButton->show();
    captureButton->show();

    QObject::connect(moveButton,SIGNAL(clicked()), this, SLOT(moveAction()));
    QObject::connect(attackButton,SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(captureButton,SIGNAL(clicked()),this, SLOT(close()));
    QObject::connect(moveButton,SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(attackButton,SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(captureButton,SIGNAL(clicked()),this, SLOT(close()));
}

void Action::moveAction(){
    mainWindow->unitMove(click);
}
void Action::attackAction(){

}
void Action::captureAction(){

}

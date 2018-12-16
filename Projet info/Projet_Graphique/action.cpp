#include "action.h"
#include <iostream>

Action::Action(QWidget *parent, int unit, bool capt, bool attack,bool movable, MainWindow* mainWindow)
{
    this->unit = unit;
    this->mainWindow = mainWindow;

    QPushButton* moveButton = new QPushButton(this);
    moveButton->setText("move");
    moveButton->setMinimumHeight(30);
    if (movable==false){
        moveButton->setEnabled(false);
    }

    QPushButton *attackButton = new QPushButton(this);
    attackButton->setText("attack");
    attackButton->setMinimumHeight(30);
    if(attack == false){
        attackButton->setEnabled(false);
    }

    QPushButton *captureButton = new QPushButton(this);
    captureButton->setText("capture");
    captureButton->setMinimumHeight(30);
    if( capt == false || movable == false ){
        captureButton->setEnabled(false);
    }

    QPushButton *fusionButton = new QPushButton(this);
    fusionButton->setText("fusion");
    fusionButton->setMinimumHeight(30);
    if(movable == false ){
        fusionButton->setEnabled(false);
    }

    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(moveButton);
    layout->addWidget(attackButton);
    layout->addWidget(captureButton);
    layout->addWidget(fusionButton);
    this->setLayout(layout);

    moveButton->show();
    attackButton->show();
    captureButton->show();
    fusionButton->show();

    QObject::connect(moveButton,SIGNAL(clicked()), this, SLOT(moveAction()));
    QObject::connect(attackButton,SIGNAL(clicked()), this, SLOT(attackAction()));
    QObject::connect(captureButton,SIGNAL(clicked()),this, SLOT(captureAction()));
    QObject::connect(fusionButton,SIGNAL(clicked()), this, SLOT(fusionAction()));
    QObject::connect(moveButton,SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(attackButton,SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(captureButton,SIGNAL(clicked()),this, SLOT(close()));
    QObject::connect(fusionButton,SIGNAL(clicked()), this, SLOT(close()));
}

void Action::moveAction(){
    mainWindow->unitMove(unit);
}

void Action::attackAction(){
    mainWindow->showCombat(unit);
}

void Action::captureAction(){
    mainWindow->capture(unit);
}

void Action::fusionAction(){
    mainWindow->showFusion(unit);
}

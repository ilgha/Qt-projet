#include "menu.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QMessageBox>
#include "mainwindow.h"
#include <iostream>

Menu::Menu(QWidget *parent, Game* game, int i)
{
    this->game = game;
    building = i;
    list = new QComboBox(this);
    QPushButton *button = new QPushButton(this);
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(list);
    layout->addWidget(button);
    button->setText("Select");
    button->setMaximumWidth(100);


    if (game->getBuildings().at(i).getID()==0){
        list->addItem("BCopter: 9000$");
        list->addItem("Bomber: 22000$");
        list->addItem("Fighter: 20000$");
    }

    else if (game->getBuildings().at(i).getID()==2){
        list->addItem("Anti Air: 8000$");
        list->addItem("Infantry: 1000$");
        list->addItem("Md Tank: 1600$");
        list->addItem("Mech: 3000$");
        list->addItem("Mega Tank: 28000$");
        list->addItem("Neo Tank: 22000$");
        list->addItem("Recon: 15000$");
        list->addItem("Tank: 7000$");
    }


    button->show();
    list->show();
    QObject::connect(button,SIGNAL(clicked()), this, SLOT(recruitAction()));
    QObject::connect(button,SIGNAL(clicked()),this, SLOT(close()));

}

void Menu::recruitAction(){
    type = list->currentIndex();
    name = getName(type);
    if (game->recruit(&game->getBuildings().at(building), name)== false){
        QMessageBox::critical(this, " ", "You don't have enough money");
    }
    else{
        game->recruit(&game->getBuildings().at(building), name);
    }

}

string Menu::getName(int type){
    if (game->getBuildings().at(building).getID()==0){
        switch(type){
        case 0:{
            return "BCopter";
        }
        case 1:{
            return "Bomber";
        }
        case 2:{
            return "Fighter";
        }
        }
    }

    else if (game->getBuildings().at(building).getID()==2){
        switch(type){
        case 0:{
            return "AntiAir";
        }
        case 1:{
            return "Infantry";
        }
        case 2:{
            return "MdTank";
            }
        case 3:{
            return "Mech";
        }
        case 4:{
            return "MegaTank";
        }
        case 5:{
            return "NeoTank";
        }
        case 6:{
            return "Recon";
            }
        case 7:{
            return "Tank";
        }
        }
    }
}

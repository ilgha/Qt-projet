#include "menu.h"
#include <QVBoxLayout>
#include <QPushButton>
#include "mainwindow.h"
#include <iostream>

Menu::Menu(QWidget *parent, Game* game, int i) : QWidget(parent)
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
    if (game->getBuildings().at(building).getID()==0){

        switch(type){
        case 0:{
            name = "BCopter";
        }
        case 1:{
            name = "Bomber";
        }
        case 2:{
            name = "Fighter";
            }
        }
    }

    else if (game->getBuildings().at(building).getID()==2){
        switch(type){
        case 0:{
            name = "Anti Air";
        }
        case 1:{
            name = "Infantry";
        }
        case 2:{
            name = "Md Tank";
            }
        case 3:{
            name = "Mech";
        }
        case 4:{
            name = "Mega Tank";
        }
        case 5:{
            name = "Neo Tank";
        }
        case 6:{
            name = "Recon";
            }
        case 7:{
            name = "Tank";
        }
        }
    }
std::cout << name << std::endl;
    //game->recruit(&game->getBuildings().at(building), name);
}

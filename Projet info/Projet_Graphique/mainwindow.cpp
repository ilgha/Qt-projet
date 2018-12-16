#include "mainwindow.h"
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QPainter>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QDebug>
#include <QtWidgets>
#include <QMessageBox>
#include <QWindow>
#include <algorithm>
#include <iostream>
#include <typeinfo>
#include <string>
#include <QString>
#include "Plain.h"
#include "menu.h"
#include "action.h"

typedef std::pair <int, int> IntPair;

MainWindow::MainWindow(QWidget *parent, Game* game) : QMainWindow(parent), ui(new Ui::MainWindow){

    showFullScreen();
    textWidget->setWindowTitle("Menu");
    textWidget->setStyleSheet("QLabel { font-weight: bold; font: 20pt; background-color : grey; color : black; }");

    this->game = game;
    this->posX.resize(game->getArmy()->size());
    this->posY.resize(game->getArmy()->size());
    ui->setupUi(this);

    music();


    server = new QTcpServer();

    if(! server->listen(QHostAddress::Any, 8123)) {
        std::cout << "I am a client" << std::endl;
        other = new QTcpSocket();
        connect(other, SIGNAL(connected()), this, SLOT(onConnected()));
        other->connectToHost("127.0.0.1", 8123);
        connect(other, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
        game->endTurn();

    } else {
        std::cout << "I am the server" << std::endl;
        other = nullptr;
    }
    connect(server, SIGNAL(newConnection()), this, SLOT(onNewConnection()));


}


MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::onNewConnection() {
    std::cout << "A new client is connecting !" << std::endl;
    other = server->nextPendingConnection();
    connect(other, SIGNAL(disconnected()), this, SLOT(onDisconnected()));
    connect(other, SIGNAL(readyRead()), this, SLOT(onData()));


    QJsonObject info;

    for(unsigned int i = 0; i<game->getArmy()->size(); i++){
        posX.at(i) = game->getArmy()->at(i)->getX();
        posY.at(i) = game->getArmy()->at(i)->getY();
        QString x = "x";
        QString y = "y";
        QString n = QString::number(i);
        info.insert(x.append(n),posX.at(i));
        info.insert(y.append(n),posY.at(i));
    }


    isConfigured = true;
    myTurn = false;

    sendJson(info);

}


void MainWindow::onConnected() {
    std::cout << "I am connected" << std::endl;
    connect(other, SIGNAL(readyRead()), this, SLOT(onData()));
}

void MainWindow::onDisconnected() {
    std::cout << "The other guy just disconnected" << std::endl;
}

void MainWindow::onData() {
    std::cout << "Some data !" << std::endl;
    if(currentSize == 0) {
            if(other->bytesAvailable() < 4)
                return;
            QDataStream in(other);
            in >> currentSize;
        }
         if(other->bytesAvailable() < currentSize)
            return;

    QByteArray data = other->read(currentSize);
    std::cout << data.toStdString() << std::endl;
    currentSize = 0;

    QJsonDocument doc = QJsonDocument::fromJson(data);
    QJsonObject json = doc.object();


        if(! isConfigured) {
            for(unsigned int i = 0; i<game->getArmy()->size(); i++){
                QString x = "x";
                QString y = "y";
                QString n = QString::number(i);

                posY.at(i) = json[y.append(n)].toInt();
                posX.at(i) = json[x.append(n)].toInt();
            }

            update();
            isConfigured = true;
            myTurn = true;
        } else {
            myTurn = json["turn"].toBool();
            for(unsigned int i = 0; i<game->getArmy()->size(); i++){
                QString n = QString::number(i);
                QString newx = "newX";
                QString newy = "newY";
                int newX = json[newx.append(n)].toInt();
                int newY = json[newy.append(n)].toInt();
                posX.at(i) = newX;
                posY.at(i) = newY;
                game->getArmy()->at(i)->setX(posX.at(i));
                game->getArmy()->at(i)->setY(posY.at(i));
            }



        }

        if(myTurn == true){

            std::cout << game->getActive() << std::endl;
            std::cout << game->getActive()->typeIA() << std::endl;
            playIA(game->getActive());
            std::cout << game->getActive() << std::endl;

        }

        update();
}



void MainWindow::sendJson(QJsonObject obj) {
    QByteArray data = QJsonDocument(obj).toJson();
    QDataStream out(other);
    out << (quint32) data.length();
    other->write(data);
    //std::cout << "Sending " << data.toStdString() << std::endl;
}


int MainWindow::tDtoIsoX(int x, int y){
    x = x-y;
    return x;
}

int MainWindow::tDtoIsoY(int x, int y){
    y = (x+y)/2;
    return y;
}

int MainWindow::isoToTDX(int x, int y){
    x = (2*y+y)/2;
    return x;
}

int MainWindow::isoToTDY(int x, int y){
    y = (2*y-x)/2;
    return y;
}

void MainWindow::paintEvent(QPaintEvent *event){

    textWidget->setText("Income : " + QString::fromStdString(std::to_string(game->getPlayer1()->getIncome())) +
                       "\nMoney : " + QString::fromStdString(std::to_string(game->getPlayer1()->getMoney())) +
                        "\nmy Turn: " + myTurn );
    textWidget->setFixedSize(5+5*width()/x,height());
    textWidget->move(width()-1-5*width()/x,0);

    //map tiles
    for(unsigned int j = 0; j<y; j++){
        for(unsigned int i = 0; i<x; i++){
            try {
                t[j][i] = game->getMap().getValue(j, i);
            } catch (const char* msg) {
                t[j][i] = 0;
            }

        }
    }

    for(unsigned int j = 0; j<x; j++){
        for(unsigned int i = 0; i<y; i++){
            QRectF target(j*width()/x, i*height()/y, (width()/x)+1, (height()/y)+1);
            QRectF source((t[i][j]-1)*16, 15, 16, 16);
            QImage image(":/sprt/advance wars sprites/tileset projet");
            QPainter painter(this);
            painter.drawImage(target, image, source);
        }
    }

    //Buildings
    for(unsigned int u = 0; u < game->getBuildings().size(); u++){
        if(game->getBuildings().at(u).getTeam() == game->getPlayer2()){
            QRectF target(game->getBuildings().at(u).getX()*width()/x, game->getBuildings().at(u).getY()*height()/y, width()/x, height()/y);
            QRectF source((t[game->getBuildings().at(u).getY()][game->getBuildings().at(u).getX()]+3)*16, 15, 16, 16);
            QImage image(":/sprt/advance wars sprites/tileset projet");
            QPainter painter(this);
            painter.drawImage(target, image, source);
        }else if(game->getBuildings().at(u).getTeam() == game->getPlayer1()){
            QRectF target(game->getBuildings().at(u).getX()*width()/x, game->getBuildings().at(u).getY()*height()/y, width()/x, height()/y);
            QRectF source((t[game->getBuildings().at(u).getY()][game->getBuildings().at(u).getX()]+8)*16, 15, 16, 16);
            QImage image(":/sprt/advance wars sprites/tileset projet");
            QPainter painter(this);
            painter.drawImage(target, image, source);
        }

        QPainter painter(this);
        painter.setPen(QPen(Qt::yellow));
        painter.setFont(QFont("Times", 20, QFont::Bold));
        QRectF target(game->getBuildings().at(u).getX()*width()/x, game->getBuildings().at(u).getY()*height()/y, width()/x, height()/y);
        painter.drawText(target, Qt::AlignBottom, QString::fromStdString(std::to_string(game->getBuildings().at(u).getHp())));
    }

    //units
    QPainter painter(this);
    for(unsigned int i = 0; i<game->getCases().size(); i++){
        painter.fillRect(game->getCases().at(i).first*width()/x, game->getCases().at(i).second*height()/y, width()/x, height()/y, QBrush(QColor(230, 128, 128, 128)));
    }
    for(unsigned int i = 0; i<fight.size(); i++){
        painter.fillRect(fight.at(i).first*width()/x, fight.at(i).second*height()/y, width()/x, height()/y, QBrush(QColor(230, 128, 128, 128)));
    }


    for(unsigned int i = 0; i<game->getArmy()->size(); i++){
        if(!game->getArmy()->at(i)->getDead()){
            QRectF target( game->getArmy()->at(i)->getX()*width()/x, game->getArmy()->at(i)->getY()*height()/y, width()/x, height()/y);
            QRectF source(getXIm(game->getArmy()->at(i)->getID()), getYIm(game->getArmy()->at(i)->getID()), 16, 16);
            if(game->getArmy()->at(i)->getTeam() == game->getPlayer1()){
                QImage image(":/sprt/advance wars sprites/Orange_Star");
                QPainter painter(this);
                painter.drawImage(target, image, source);
                painter.setPen(QPen(Qt::white));
                painter.setFont(QFont("Times", 20, QFont::Bold));
                painter.drawText(target, Qt::AlignBottom, QString::fromStdString(std::to_string(game->getArmy()->at(i)->getHealth())));
            }else {
                QImage image(":/sprt/advance wars sprites/Blue_Moon");
                QPainter painter(this);
                painter.drawImage(target, image, source);
                painter.setPen(QPen(Qt::white));
                painter.setFont(QFont("Times", 20, QFont::Bold));
                painter.drawText(target, Qt::AlignBottom, QString::fromStdString(std::to_string(game->getArmy()->at(i)->getHealth())));
            }
        }
    }



}



void MainWindow::mousePressEvent(QMouseEvent *event){
    if(fight.size() == 0 && game->getActiveUnit() == nullptr){
        int united = actionOnUnit(event);
        if(united == 0){
            createUnit(event);
        }
    }else if (fight.size() != 0){
        combat(event);
    }else{
        sendJson(unitMove(event));
    }

    //réseau
    if(! myTurn)
           return;

    update();

}

void MainWindow::keyPressEvent(QKeyEvent *event){
    qDebug() << event->key();
    switch(event->key()){
    case Qt::Key_P: {
        if(! myTurn)
               return;
        game->endTurn();
        myTurn = false;
        sendJson(changeTurn());

        break;
    }

    case Qt::Key_Space: {
        this->close();
        break;
    }
    }
    update();
}

int MainWindow::smallestF(std::vector<node*> open)
{
    std::vector<int> listF;
    int index;
    for (auto node : open) {
        listF.push_back(node->getF());
        index = distance(listF.begin(),min_element(listF.begin(),listF.end()));
    }
    return index;
}

bool MainWindow::compareNode(node n1, node n2)
{
    return ((n1.getX() == n2.getX() && (n1.getY() == n2.getY())));
}

std::vector<node*> MainWindow::bestPath(node target)
{
    std::vector<node*> bestPath;
    while(target.getChild()){
        bestPath.push_back(&target);
        target = *target.getChild();
        bestPath.push_back(&target);
    }

    return  bestPath;
}

void MainWindow::playIA(Player* player)
{/*
    if(player->typeIA() == 0){
        return;

    }else if(player->typeIA() == 1){ //IA immobile

        game->endTurn();
        myTurn = false;
        sendJson(changeTurn());
        std::cout << "ia end" << std::endl;

    }else if(player->typeIA() == 2){ //IA-PathFind A*
        for (auto u : *game->getArmy()) {
            if(u->getTeam() == game->getActive()){
                std::vector<node*> open;
                std::vector<node*> close;
                int endX = 14;
                int endY = 4;
                node begin = node(u->getX(),u->getY(),game->getMap().getTile(u->getX(),u->getY()).getMoved(u->getMT()), std::abs(u->getX()-endX)+std::abs(u->getY()-endY));
                begin.setParenting(nullptr);
                node end = node(endX, endY, game->getMap().getTile(endX,endY).getMoved(u->getMT()), 0);
                open.push_back(&begin);
                while(!open.empty()){

                    node current = *open.at(smallestF(open));
<<<<<<< HEAD
                    node* pcurrent = &current;
                    std::cout << "current node: " << current.getX() << "," << current.getY() << std::endl;

                    open.erase(open.begin()+smallestF(open)-1);
                    std::cout << "open: ";
                    for (auto nodeO : open) {
                        std::cout << "(" << nodeO->getX() << "," << nodeO->getY() << ")" << ' ';
                    }
                    std::cout << std::endl;

                    std::cout << pcurrent << std::endl;

                    close.push_back(pcurrent);
                    std::cout << close.size() << std::endl;
                    std::cout << "close: ";
                    for (auto nodeC : open) {
                        std::cout << "(" << nodeC->getX() << "," << nodeC->getY() << ")" << ' ';
                    }
                    std::cout << std::endl;
=======

                    open.erase(open.begin()+smallestF(open));

                    close.push_back(&current);
>>>>>>> 4ad1f00ce179bfc4c41ee3390373e50367852a60

                    if(compareNode(current,end)){
                        game->clearCases();
                        game->moveUnit(u,u->getX(),u->getY(),u->getMP());
                        node nextPos = begin;
                        for (auto position : bestPath(current)) {
                            for (auto possible : game->getCases()) {
                                if(position->getX() == possible.first &&
                                        position->getY() == possible.second &&
                                        position->getF() <= nextPos.getF()){

                                    nextPos = *position;

                                }
                            }
                        }

                        u->setX(nextPos.getX());
                        u->setY(nextPos.getY());

                        game->endTurn();
                        myTurn = false;
                        sendJson(changeTurn());
                        std::cout << "ia end" << std::endl;

                        break;



                    }else{                 //calcul du meilleur chemin

                        std::vector<node*> listNeighbour;
                        node neighbourN = node(current.getX(), current.getY()-1, game->getMap().getTile(current.getX(),current.getY()-1).getMoved(u->getMT()), std::abs(current.getX()-endX)+std::abs(current.getY()-endY));
                        node neighbourS = node(current.getX(), current.getY()+1, game->getMap().getTile(current.getX(),current.getY()+1).getMoved(u->getMT()), std::abs(current.getX()-endX)+std::abs(current.getY()-endY));
                        node neighbourE = node(current.getX()+1, current.getY(), game->getMap().getTile(current.getX()+1,current.getY()).getMoved(u->getMT()), std::abs(current.getX()-endX)+std::abs(current.getY()-endY));
                        node neighbourO = node(current.getX()-1, current.getY(), game->getMap().getTile(current.getX()-1,current.getY()).getMoved(u->getMT()), std::abs(current.getX()-endX)+std::abs(current.getY()-endY));

                        listNeighbour.push_back(&neighbourN);
                        listNeighbour.push_back(&neighbourS);
                        listNeighbour.push_back(&neighbourE);
                        listNeighbour.push_back(&neighbourO);
<<<<<<< HEAD

                        for (auto neighbour : listNeighbour) {
=======
                      for (auto neighbour : listNeighbour) {
>>>>>>> 4ab769867943f1624e57f47b635b1592aa504eb6
                            if((neighbour->getCost()>0 || !(std::find(close.begin(), close.end(), neighbour) != close.end()))
                                    && !(std::find(open.begin(), open.end(), neighbour) != open.end())) {
                                neighbour->setParenting(&current);
                                open.push_back(neighbour);

                            }

                        }
                    }
                }
            }
        }
    }*/
}

QJsonObject MainWindow::unitMove(QMouseEvent *event){
    QJsonObject move;
    for(unsigned int i = 0; i<game->getArmy()->size(); i++){
        if(game->getArmy()->at(i)->isMovable() && game->getActiveUnit() == game->getArmy()->at(i)){
            if(event->x() > game->getArmy()->at(i)->getX()*this->width()/x && event->x() < (game->getArmy()->at(i)->getX()*this->width()/x + this->width()/x) &&
                event->y() > game->getArmy()->at(i)->getY()*this->height()/y && event->y() < (game->getArmy()->at(i)->getY()*this->height()/y + this->height()/y)){
                game->setActiveUnit(nullptr);
                game->clearCases();
            }
        }
    }

    for(unsigned int i = 0; i<game->getArmy()->size(); i++){
        int oldX = game->getArmy()->at(i)->getX();
        int oldY = game->getArmy()->at(i)->getY();
        QString oldx = "oldX";
        QString oldy = "oldY";
        QString n = QString::number(i);
        move[oldx.append(n)] = oldX;
        move[oldy.append(n)] = oldY;


        int wx = width()/x;
        int hy = height()/y;

        if(game->getArmy()->at(i)->getTeam() == game->getActive() && !game->getArmy()->at(i)->getDead()){
            if(game->getArmy()->at(i) == game->getActiveUnit()){
                for(unsigned int u = 0; u <game->getCases().size(); u++){

                    if((floor(event->x()/wx) == game->getCases().at(u).first && floor(event->y()/hy) == game->getCases().at(u).second)){
                        for(unsigned int t = 0; t < game->getBuildings().size(); t++){
                            if(game->getArmy()->at(i)->getX() == game->getBuildings().at(t).getX() && game->getArmy()->at(i)->getX() == game->getBuildings().at(t).getX()){
                                game->getBuildings().at(u).reset();
                            }
                        }
                        game->getArmy()->at(i)->setX(floor(event->x()/wx));
                        game->getArmy()->at(i)->setY(floor(event->y()/hy));

                        //game->checkFusion(game->getArmy()->at(i));
                        game->getArmy()->at(i)->setMovable(false);
                        game->resetActiveUnit();

                        game->clearCases();

                    }
                }
            }

        }
        QString newx = "newX";
        QString newy = "newY";
        move[newx.append(n)] = game->getArmy()->at(i)->getX();
        move[newy.append(n)] = game->getArmy()->at(i)->getY();

    }

    return move;
}


void MainWindow::unitMove(int i){
    showMove(game->getArmy()->at(i));
    game->getArmy()->at(i)->setMovable(true);
    game->setActiveUnit(game->getArmy()->at(i));
}


void MainWindow::capture(int i){
    game->checkBuildings(game->getArmy()->at(i)->getX(), game->getArmy()->at(i)->getY())->setHp(game->getArmy()->at(i));
    game->getArmy()->at(i)->setMovable(false);
}


QJsonObject MainWindow::changeTurn()
{
    QJsonObject turn;

    turn["turn"] = (myTurn == false);

    for(unsigned int i = 0; i<game->getArmy()->size(); i++){

        int oldX = game->getArmy()->at(i)->getX();
        int oldY = game->getArmy()->at(i)->getY();
        QString oldx = "oldX";
        QString oldy = "oldY";
        QString n = QString::number(i);
        turn[oldx.append(n)] = oldX;
        turn[oldy.append(n)] = oldY;
        QString newx = "newX";
        QString newy = "newY";
        turn[newx.append(n)] = oldX;
        turn[newy.append(n)] = oldY;
    }
    game->endTurn();
    int k=0;
    for(unsigned int j=0; j< game->getBuildings().size(); j++ ){
        if (game->getBuildings().at(j).getTeam()== game->getActive()){
            k++;
        }
    }
    if (k==0){
        game->endGame();
        QMessageBox::information(this, " ", "Game over");
    }
    return turn;
}


void MainWindow::showMove(Unit* unit){

    game->clearCases();
    game->moveUnit(unit, unit->getX(), unit->getY(), unit->getMP());
    game->checkBlocked();

    update();
}

void MainWindow::showCombat(int i){
    game->setActiveUnit(game->getArmy()->at(i));
    for(int u=0; u<game->getArmy()->size(); u++){
        if(game->getArmy()->at(u)->getX()+1 == game->getArmy()->at(i)->getX() && game->getArmy()->at(u)->getY() == game->getArmy()->at(i)->getY()
           || game->getArmy()->at(u)->getX()-1 == game->getArmy()->at(i)->getX() && game->getArmy()->at(u)->getY() == game->getArmy()->at(i)->getY()
           || game->getArmy()->at(u)->getX() == game->getArmy()->at(i)->getX() && game->getArmy()->at(u)->getY()+1 == game->getArmy()->at(i)->getY()
           || game->getArmy()->at(u)->getX() == game->getArmy()->at(i)->getX() && game->getArmy()->at(u)->getY()-1 == game->getArmy()->at(i)->getY()){
            IntPair pos = std::make_pair(game->getArmy()->at(u)->getX(),game->getArmy()->at(u)->getY());
            fight.push_back(pos);
        }
    }
}

void MainWindow::combat(QMouseEvent *event){
    for(int i=0; i<game->getArmy()->size(); i++){
        if(event->x() > game->getArmy()->at(i)->getX()*this->width()/x && event->x() < (game->getArmy()->at(i)->getX()*this->width()/x + this->width()/x) &&
            event->y() > game->getArmy()->at(i)->getY()*this->height()/y && event->y() < (game->getArmy()->at(i)->getY()*this->height()/y + this->height()/y)){
            game->attack(game->getActiveUnit(), game->getArmy()->at(i), false);
            game->getActiveUnit()->setMovable(false);
            game->getActiveUnit()->setAggressive(false);
            game->setActiveUnit(nullptr);
            fight.clear();

        }
    }
}


void MainWindow::tick(){
    update();
}


int MainWindow::getXIm(int ID){
    switch(ID){
    case 0:{
        return 21;
    }
    case 1:{
        return 21;
    }
    case 2:{
        return 40;
    }
    case 3:{
        return 59;
    }
    case 4:{
        return 55;
    }
    case 5:{
        return 40;
    }
    case 6:{
        return 36;
    }
    case 7:{
        return 40;
    }
    case 8:{
        return 3;
    }
    case 9:{
        return 20;
    }
    case 10:{
        return 56;
    }
    default: {
        return 143;
    }
    }
}

int MainWindow::getYIm(int ID){
    switch(ID){
    case 0:{
        return 73;
    }
    case 1:{
        return 113;
    }
    case 2:{
        return 113;
    }
    case 3:{
        return 113;
    }
    case 4:{
        return 36;
    }
    case 5:{
        return 74;
    }
    case 6:{
        return 35;
    }
    case 7:{
        return 74;
    }
    case 8:{
        return 73;
    }
    case 9:{
        return 37;
    }
    case 10:{
        return 76;
    }
    default: {
        return 47;
    }
    }
}


void MainWindow::createUnit(QMouseEvent *event){
    int wx = width()/x;
    int hy = height()/y;
    for (unsigned int i=0; i<game->getBuildings().size(); i++){

        if(floor(event->x()/wx) == game->getBuildings().at(i).getX() && floor(event->y()/hy) == game->getBuildings().at(i).getY() && game->getBuildings().at(i).getID() != 1 && game->getBuildings().at(i).getTeam()== game->getActive()){

            Menu* window = new Menu(nullptr, game, i);
            window->setVisible(true);
            window->setFixedSize(600,300);
            window->setWindowTitle("Production of units");
            window->show();
        }
    }
}

int MainWindow::actionOnUnit(QMouseEvent *event){

    int wx = width()/x;
    int hy = height()/y;
    for (unsigned int i=0; i<game->getArmy()->size(); i++){
        if (floor(event->x()/wx) == game->getArmy()->at(i)->getX() && floor(event->y()/hy) == game->getArmy()->at(i)->getY()){
            if (game->getArmy()->at(i)->getTeam() == game->getActive() && !game->getArmy()->at(i)->getDead() && myTurn== true){
                bool onFeet = (game->getArmy()->at(i)->getID()==4 || game->getArmy()->at(i)->getID()==6);
                bool capt = (game->checkBuildings(game->getArmy()->at(i)->getX(), game->getArmy()->at(i)->getY()) != nullptr
                        && game->checkBuildings(game->getArmy()->at(i)->getX(), game->getArmy()->at(i)->getY())->getTeam()!= game->getActive()
                        && onFeet);
                bool attack = (game->ennemyNear(game->getArmy()->at(i)) && game->getArmy()->at(i)->isAggressive());
                bool movable = (game->getArmy()->at(i)->isMovable());
                bool fus = false;
                for(int u=0; u<game->getArmy()->size(); u++){
                    if((game->getArmy()->at(u)->getX()+1 == game->getArmy()->at(i)->getX() && game->getArmy()->at(u)->getY() == game->getArmy()->at(i)->getY())
                       || (game->getArmy()->at(u)->getX()-1 == game->getArmy()->at(i)->getX() && game->getArmy()->at(u)->getY() == game->getArmy()->at(i)->getY())
                       || (game->getArmy()->at(u)->getX() == game->getArmy()->at(i)->getX() && game->getArmy()->at(u)->getY()+1 == game->getArmy()->at(i)->getY())
                       || (game->getArmy()->at(u)->getX() == game->getArmy()->at(i)->getX() && game->getArmy()->at(u)->getY()-1 == game->getArmy()->at(i)->getY())){
                        if(game->getArmy()->at(u)->getTeam() == game->getArmy()->at(i)->getTeam()){
                            fus = true;
                        }
                    }
                }
                Action* window = new Action(nullptr, i, capt, attack,movable, fus, this);
                window->setVisible(true);
                window->setFixedSize(200,150);
                window->setWindowTitle("Choose an action");
                window->show();
                return 1;
            }
        }
    }
    return 0;
}

void MainWindow::music(){
    QMediaPlayer* mus = new QMediaPlayer;
    QMediaPlaylist* playlist = new QMediaPlaylist(mus);
    playlist->addMedia(QUrl("qrc:/msc/advance wars sprites/take.mp3"));
    playlist->addMedia(QUrl("qrc:/msc/advance wars sprites/valk.mp3"));
    playlist->addMedia(QUrl("qrc:/msc/advance wars sprites/Wesn.mp3"));
    mus->setVolume(100);
    mus->setPlaylist(playlist);
    playlist->shuffle();
    mus->play();
}
<<<<<<< HEAD


=======
>>>>>>> d70a3c84eae334f15f19e8d7d83f1dd349e049fd

void MainWindow::showFusion(int i){
    game->setActiveUnit(game->getArmy()->at(i));
    for(int u=0; u<game->getArmy()->size(); u++){
        if((game->getArmy()->at(u)->getX()+1 == game->getArmy()->at(i)->getX() && game->getArmy()->at(u)->getY() == game->getArmy()->at(i)->getY())
           || (game->getArmy()->at(u)->getX()-1 == game->getArmy()->at(i)->getX() && game->getArmy()->at(u)->getY() == game->getArmy()->at(i)->getY())
           || (game->getArmy()->at(u)->getX() == game->getArmy()->at(i)->getX() && game->getArmy()->at(u)->getY()+1 == game->getArmy()->at(i)->getY())
           || (game->getArmy()->at(u)->getX() == game->getArmy()->at(i)->getX() && game->getArmy()->at(u)->getY()-1 == game->getArmy()->at(i)->getY())){
            if(game->getArmy()->at(u)->getTeam() == game->getArmy()->at(i)->getTeam()){
                IntPair pos = std::make_pair(game->getArmy()->at(u)->getX(),game->getArmy()->at(u)->getY());
                fight.push_back(pos);
            }
        }
    }
}

void MainWindow::fusion(QMouseEvent *event){
    for(int i=0; i<game->getArmy()->size(); i++){
        if(event->x() > game->getArmy()->at(i)->getX()*this->width()/x && event->x() < (game->getArmy()->at(i)->getX()*this->width()/x + this->width()/x) &&
            event->y() > game->getArmy()->at(i)->getY()*this->height()/y && event->y() < (game->getArmy()->at(i)->getY()*this->height()/y + this->height()/y)){

            game->checkFusion(game->getActiveUnit());
            game->setActiveUnit(nullptr);
            fight.clear();
        }
    }
}
<<<<<<< HEAD

=======
>>>>>>> d70a3c84eae334f15f19e8d7d83f1dd349e049fd

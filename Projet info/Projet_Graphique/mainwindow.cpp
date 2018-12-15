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

typedef std::pair <int, int> IntPair;

MainWindow::MainWindow(QWidget *parent, Game* game) : QMainWindow(parent), ui(new Ui::MainWindow){

    this->army[0] = army[0];

    textWidget->setWindowTitle("Menu");
    textWidget->setStyleSheet("QLabel { font-weight: bold; font: 20pt; background-color : grey; color : black; }");

    this->game = game;
    this->army = game->getArmy();
    this->posX.resize(army->size());
    this->posY.resize(army->size());
    ui->setupUi(this);

    //music();


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

    for(unsigned int i = 0; i<army->size(); i++){
        posX.at(i) = army->at(i)->getX();
        posY.at(i) = army->at(i)->getY();
        QString x = "x";
        QString y = "y";
        QString n = QString::number(i);
        info.insert(x.append(n),posX.at(i));
        info.insert(y.append(n),posY.at(i));
    }


    isConfigured = true;
    myTurn = false;

    sendJson(info);
    update();
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
            for(unsigned int i = 0; i<army->size(); i++){
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
            for(unsigned int i = 0; i<army->size(); i++){
                QString n = QString::number(i);
                QString newx = "newX";
                QString newy = "newY";
                int newX = json[newx.append(n)].toInt();
                int newY = json[newy.append(n)].toInt();
                posX.at(i) = newX;
                posY.at(i) = newY;
                army->at(i)->setX(posX.at(i));
                army->at(i)->setY(posY.at(i));
            }



        }

        //std::cout << game->getActive() << std::endl;


        update();
}



void MainWindow::sendJson(QJsonObject obj) {
    QByteArray data = QJsonDocument(obj).toJson();
    QDataStream out(other);
    out << (quint32) data.length();
    other->write(data);
    std::cout << "Sending " << data.toStdString() << std::endl;
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
                       "\nNombre de villes : " + QString::fromStdString(std::to_string(game->getBuildings().size())));
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
    }

    //units
    QPainter painter(this);
    for(unsigned int i = 0; i<game->getCases().size(); i++){
        painter.fillRect(game->getCases().at(i).first*width()/x, game->getCases().at(i).second*height()/y, width()/x, height()/y, QBrush(QColor(230, 128, 128, 128)));
    }


    for(unsigned int i = 0; i<army->size(); i++){
        if(!army->at(i)->getDead()){
            QRectF target( army->at(i)->getX()*width()/x, army->at(i)->getY()*height()/y, width()/x, height()/y);
            QRectF source(getXIm(army->at(i)->getID()), getYIm(army->at(i)->getID()), 16, 16);
            if(army->at(i)->getTeam() == game->getPlayer1()){
                QImage image(":/sprt/advance wars sprites/Orange_Star");
                QPainter painter(this);
                painter.drawImage(target, image, source);
                painter.setPen(QPen(Qt::white));
                painter.setFont(QFont("Times", 20, QFont::Bold));
                painter.drawText(target, Qt::AlignBottom, QString::fromStdString(std::to_string(army->at(i)->getHealth())));
            }else {
                QImage image(":/sprt/advance wars sprites/Blue_Moon");
                QPainter painter(this);
                painter.drawImage(target, image, source);
                painter.setPen(QPen(Qt::white));
                painter.setFont(QFont("Times", 20, QFont::Bold));
                painter.drawText(target, Qt::AlignBottom, QString::fromStdString(std::to_string(army->at(i)->getHealth())));
            }
        }
    }
    std::cout << "myTurn: " << myTurn << std::endl;

}



void MainWindow::mousePressEvent(QMouseEvent *event){
    createUnit(event);
    //actionOnUnit(event);


    //réseau
    if(! myTurn)
           return;

    sendJson(unitMove(event));

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

int MainWindow::smallestF(std::vector<node> open)
{
    std::vector<int> listF;
    int index;
    for (auto node : open) {
        listF.push_back(node.getF());
        index = distance(listF.begin(),min_element(listF.begin(),listF.end()));
    }
    return index;
}

bool MainWindow::compareNode(node n1, node n2)
{
    return ((n1.getX() == n2.getX() && (n1.getY() == n2.getY())));
}

std::vector<node> MainWindow::bestPath(node target)
{
    std::vector<node> bestPath;
    while(target.getChild()){
        bestPath.push_back(target);
        target = *target.getChild();
        bestPath.push_back(target);
    }

    return  bestPath;
}

void MainWindow::playIA(Player* player)
{
    if(player->typeIA() == 0){

    }else if(player->typeIA() == 1){ //IA-PathFind A*
        QJsonObject move;
        for (auto u : *army) {
            std::vector<node> open;
            std::vector<node> close;
            int endX = 4;
            int endY = 14;
            node begin = node(u->getX(),u->getY(),game->getMap().getTile(u->getX(),u->getY()).getMoved(u->getMT()), std::abs(u->getX()-endX)+std::abs(u->getY()-endY));
            begin.setParenting(nullptr);
            node end = node(endX, endY, game->getMap().getTile(endX,endY).getMoved(u->getMT()), 0);
            open.push_back(begin);

            while(!open.empty()){

                node current = open.at(smallestF(open));
                open.erase(open.begin()+smallestF(open)-1);
                close.push_back(current);

                if(compareNode(current,end)){
                    game->clearCases();
                    game->moveUnit(u,u->getX(),u->getY(),u->getMP());
                    node nextPos = begin;
                    for (auto position : bestPath(current)) {
                        for (auto possible : game->getCases()) {
                            if(position.getX() == possible.first &&
                                    position.getY() == possible.second &&
                                    position.getF() <= nextPos.getF()){

                                nextPos = position;

                            }
                        }
                    }

                    for(unsigned int i = 0; i<army->size(); i++){
                        int oldX = army->at(i)->getX();
                        int oldY = army->at(i)->getY();
                        QString oldx = "oldX";
                        QString oldy = "oldY";
                        QString n = QString::number(i);
                        move[oldx.append(n)] = oldX;
                        move[oldy.append(n)] = oldY;


                        int wx = width()/this->x;
                        int hy = height()/y;
                        QString newx = "newX";
                        QString newy = "newY";
                        move[newx.append(n)] = army->at(i)->getX();
                        move[newy.append(n)] = army->at(i)->getY();



                    }

                    u->setX(nextPos.getX());
                    u->setY(nextPos.getY());

                    sendJson(move);



                }else{                 //calcul du meilleur chemin

                    std::vector<node> listNeighbour;
                    node neighbourN = node(current.getX(), current.getY()-1, game->getMap().getTile(current.getX(),current.getY()-1).getMoved(u->getMT()), std::abs(current.getX()-endX)+std::abs(current.getY()-endY));
                    node neighbourS = node(current.getX(), current.getY()+1, game->getMap().getTile(current.getX(),current.getY()+1).getMoved(u->getMT()), std::abs(current.getX()-endX)+std::abs(current.getY()-endY));
                    node neighbourE = node(current.getX()+1, current.getY(), game->getMap().getTile(current.getX()+1,current.getY()).getMoved(u->getMT()), std::abs(current.getX()-endX)+std::abs(current.getY()-endY));
                    node neighbourO = node(current.getX()-1, current.getY(), game->getMap().getTile(current.getX()-1,current.getY()).getMoved(u->getMT()), std::abs(current.getX()-endX)+std::abs(current.getY()-endY));

                    listNeighbour.push_back(neighbourN);
                    listNeighbour.push_back(neighbourS);
                    listNeighbour.push_back(neighbourE);
                    listNeighbour.push_back(neighbourO);

                    for (auto neighbour : listNeighbour) {
                        if((neighbour.getCost()>0 || !(std::find(close.begin(), close.end(), neighbour) != close.end()))
                                && !(std::find(open.begin(), open.end(), neighbour) != open.end())) {
                            neighbour.setParenting(&current);
                            open.push_back(neighbour);

                        }
                    }
                }
            }
        }

        game->endTurn();
    }
}


QJsonObject MainWindow::unitMove(QMouseEvent *event){
    QJsonObject move;

    for(unsigned int i = 0; i<army->size(); i++){

        if(army->at(i)->getTeam() == game->getActive() && !army->at(i)->getDead()){
            if(!army->at(i)->isMovable() && game->getActiveUnit() == nullptr){
                if(event->x() > army->at(i)->getX()*this->width()/x && event->x() < (army->at(i)->getX()*this->width()/x + this->width()/x) &&
                        event->y() > army->at(i)->getY()*this->height()/y && event->y() < (army->at(i)->getY()*this->height()/y + this->height()/y)){
                    showMove(army->at(i));
                    army->at(i)->setMovable(true);
                    game->setActiveUnit(army->at(i));
                }

            }else if(army->at(i)->isMovable() && game->getActiveUnit() == army->at(i)){
                if(event->x() > army->at(i)->getX()*this->width()/x && event->x() < (army->at(i)->getX()*this->width()/x + this->width()/x) &&
                    event->y() > army->at(i)->getY()*this->height()/y && event->y() < (army->at(i)->getY()*this->height()/y + this->height()/y)){
                    game->setActiveUnit(nullptr);
                    army->at(i)->setMovable(false);
                }
            }
        }
    }

    for(unsigned int i = 0; i<army->size(); i++){
        int oldX = army->at(i)->getX();
        int oldY = army->at(i)->getY();
        QString oldx = "oldX";
        QString oldy = "oldY";
        QString n = QString::number(i);
        move[oldx.append(n)] = oldX;
        move[oldy.append(n)] = oldY;


        int wx = width()/x;
        int hy = height()/y;

        if(army->at(i)->getTeam() == game->getActive() && !army->at(i)->getDead()){
            if(army->at(i) == game->getActiveUnit()){
                for(unsigned int u = 0; u <game->getCases().size(); u++){

                    if((floor(event->x()/wx) == game->getCases().at(u).first && floor(event->y()/hy) == game->getCases().at(u).second)){

                        army->at(i)->setX(floor(event->x()/wx));
                        army->at(i)->setY(floor(event->y()/hy));

                        //game->checkFusion(army->at(i));
                        army->at(i)->setMovable(false);
                        game->resetActiveUnit();
                        game->clearCases();

                    }
                }
            }

        }
        QString newx = "newX";
        QString newy = "newY";
        move[newx.append(n)] = army->at(i)->getX();
        move[newy.append(n)] = army->at(i)->getY();



    }

    return move;
}



QJsonObject MainWindow::changeTurn()
{
    QJsonObject turn;

    turn["turn"] = (myTurn == false);

    for(unsigned int i = 0; i<army->size(); i++){

        int oldX = army->at(i)->getX();
        int oldY = army->at(i)->getY();
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

    return turn;
}


void MainWindow::showMove(Unit* unit){

    game->clearCases();
    game->moveUnit(unit, unit->getX(), unit->getY(), unit->getMP());
    game->checkBlocked();
    update();
}

void MainWindow::showMenu(Building* b, Unit* u){
    if(b != nullptr){

        QRectF target(11*this->width()/18, this->height()/12, this->width()/5,this->height()/3);
        QRectF source(0,0,41,62);
        QImage image(":/sprt/advance wars sprites/menu");
        QPainter painter(this);
        painter.drawImage(target, image, source);
    }

    if(this->game->ennemyNear(u)){
        std::cout << "combat" << std::endl;
        QRectF target(11*this->width()/18, this->height()/12, this->width()/5,this->height()/3);
        QRectF source(0,42,41,62);
        QImage image(":/sprt/advance wars sprites/menu");
        QPainter painter(this);
        painter.drawImage(target, image, source);
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
        return 76;
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
        return 58;
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
        if(floor(event->x()/wx) == game->getBuildings().at(i).getX() && floor(event->y()/hy) == game->getBuildings().at(i).getY() && game->getBuildings().at(i).getID() != 1){
            Menu* window = new Menu(this, game, i);
            window->setVisible(true);
            window->setFixedSize(600,300);
            window->setWindowTitle("Production of units");
            window->show();
        }
    }
}

void MainWindow::actionOnUnit(QMouseEvent *event){
    int wx = width()/x;
    int hy = height()/y;
    for (unsigned int i=0; i<army->size(); i++){
        if (floor(event->x()/wx) == army->at(i)->getX() && floor(event->y()/hy) == army->at(i)->getY()){
            if (army->at(i)->getTeam() == game->getActive() && !army->at(i)->getDead() && myTurn== true){
                QWidget* window = new QWidget();
                window->setVisible(true);
                window->setFixedSize(600,300);
                window->setWindowTitle("Choose an action");

                QPushButton *moveButton = new QPushButton(window);
                QVBoxLayout *layout = new QVBoxLayout(window);
                layout->addWidget(moveButton);
                moveButton->setText("move");
                moveButton->setMaximumWidth(100);

                QPushButton *attackButton = new QPushButton(window);
                layout->addWidget(attackButton);
                attackButton->setText("attack");
                attackButton->setMaximumWidth(100);

                QPushButton *captureButton = new QPushButton(window);
                layout->addWidget(captureButton);
                captureButton->setText("capture");
                captureButton->setMinimumWidth(100);

                moveButton->show();
                attackButton->show();
                captureButton->show();
                window->show();

                QObject::connect(moveButton,SIGNAL(clicked()), window, SLOT(close()));
           //     QObject::connect(moveButton, SIGNAL(clicked()), this, SLOT(move(event)) );


            }
        }
    }



}

void MainWindow::music(){
    QMediaPlayer* mus = new QMediaPlayer;
    QMediaPlaylist* playlist = new QMediaPlaylist(mus);
    playlist->addMedia(QUrl("qrc:/msc/advance wars sprites/take.mp3"));
    playlist->addMedia(QUrl("qrc:/msc/advance wars sprites/valk.mp3"));
    mus->setVolume(100);
    mus->setPlaylist(playlist);
    playlist->shuffle();
    mus->play();
}

void MainWindow::recruitAction(){
    std::cout << "test" << std::endl;
}

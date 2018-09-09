#include "gomoku.h"
#include "matchqueue.h"
#include "menu.h"
#include "test.h"
#include "ui_menu.h"

menu::menu(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::menu)
{
    ui->setupUi(this);    

    ui->Version->setText("Version: "+QString(__TIMESTAMP__));
}

menu::~menu()
{
    delete ui;
}

void menu::on_start_gomoku_game_clicked()
{
    ui->start_gomoku_game->setEnabled(false);
    ui->start_gomoku_game->setText("Gaming");
    QEventLoop loopqueue;
    MatchQueue *matchQueue=new MatchQueue(NULL,"Gomoku",2,&loopqueue);
    matchQueue->show();
    loopqueue.exec();
    if (matchQueue->queuenumbersnames.isEmpty())
    {
        ui->start_gomoku_game->setEnabled(true);
        ui->start_gomoku_game->setText("Match Error!");
        delete matchQueue;
        return;
    }
    Gomoku *G=new Gomoku(NULL,matchQueue->queuenumbersnames);
    G->connect(G,&Gomoku::destroyed,this,[&]{
        ui->start_gomoku_game->setEnabled(true);
        ui->start_gomoku_game->setText("Start!");
    });
    G->show();
    delete matchQueue;
}

void menu::on_start_test_clicked()
{
    test t;
    t.show();
}

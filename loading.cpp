#include "loading.h"
#include "ui_loading.h"
#include <string>
loading::loading(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::loading)
{
    ui->setupUi(this);        
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Tool);
    ui->commandLinkButton->hide();
    ui->commandLinkButton_2->hide();
    ui->commandLinkButton_3->hide();
    ui->commandLinkButton_4->hide();
    ui->commandLinkButton_5->hide();
    ui->commandLinkButton_6->hide();
    ui->commandLinkButton_7->hide();
    ui->commandLinkButton_8->hide();
    timer->connect(timer,SIGNAL(timeout()),this,SLOT(next()));
    timer->start(150);
}

loading::~loading()
{
    delete ui;
}
void loading::closeEvent(QCloseEvent *e) {

    e->ignore();
}
void loading::next() {
    QCommandLinkButton *lines[8]={ui->commandLinkButton,ui->commandLinkButton_2,ui->commandLinkButton_3,ui->commandLinkButton_4,ui->commandLinkButton_5,ui->commandLinkButton_6,ui->commandLinkButton_7,ui->commandLinkButton_8};
    lines[now]->show();
    if (now>0)
    {
        QGraphicsOpacityEffect *opacityEffect=new QGraphicsOpacityEffect;
        lines[now-1]->setGraphicsEffect(opacityEffect);
        opacityEffect->setOpacity(0.7);
        if (now>1)
        {
            QGraphicsOpacityEffect *opacityEffect=new QGraphicsOpacityEffect;
            lines[now-2]->setGraphicsEffect(opacityEffect);
            opacityEffect->setOpacity(0.5);
        }
        if (now>2)
        {
            QGraphicsOpacityEffect *opacityEffect=new QGraphicsOpacityEffect;
            lines[now-3]->setGraphicsEffect(opacityEffect);
            opacityEffect->setOpacity(0.2);
        }
        if (now>3)
        {
            QGraphicsOpacityEffect *opacityEffect=new QGraphicsOpacityEffect;
            lines[now-4]->setGraphicsEffect(opacityEffect);
            opacityEffect->setOpacity(1);
            lines[now-4]->hide();
        }
    }
    if (now==0)
    {
        QGraphicsOpacityEffect *opacityEffect=new QGraphicsOpacityEffect;
        lines[7]->setGraphicsEffect(opacityEffect);
        opacityEffect->setOpacity(0.7);
        opacityEffect=new QGraphicsOpacityEffect;
        lines[6]->setGraphicsEffect(opacityEffect);
        opacityEffect->setOpacity(0.5);
        opacityEffect=new QGraphicsOpacityEffect;
        lines[5]->setGraphicsEffect(opacityEffect);
        opacityEffect->setOpacity(0.2);
        opacityEffect=new QGraphicsOpacityEffect;
        lines[4]->setGraphicsEffect(opacityEffect);
        opacityEffect->setOpacity(1);
        lines[4]->hide();
    }
    if (now==1)
    {
        QGraphicsOpacityEffect *opacityEffect=new QGraphicsOpacityEffect;
        lines[7]->setGraphicsEffect(opacityEffect);
        opacityEffect->setOpacity(0.5);
        opacityEffect=new QGraphicsOpacityEffect;
        lines[6]->setGraphicsEffect(opacityEffect);
        opacityEffect->setOpacity(0.2);
        opacityEffect=new QGraphicsOpacityEffect;
        lines[5]->setGraphicsEffect(opacityEffect);
        opacityEffect->setOpacity(1);
        lines[5]->hide();
    }
    if (now==3)
    {
        QGraphicsOpacityEffect *opacityEffect=new QGraphicsOpacityEffect;
        lines[7]->setGraphicsEffect(opacityEffect);
        opacityEffect->setOpacity(0.2);
        opacityEffect=new QGraphicsOpacityEffect;
        lines[6]->setGraphicsEffect(opacityEffect);
        opacityEffect->setOpacity(1);
        lines[6]->hide();
    }
    if (now==4)
    {
        QGraphicsOpacityEffect *opacityEffect=new QGraphicsOpacityEffect;
        lines[7]->setGraphicsEffect(opacityEffect);
        opacityEffect->setOpacity(1);
        lines[7]->hide();
    }
    now++;
    if (now>=8)
    {
        now=0;
    }
}
void loading::setloadingtext(QString text) {
    ui->pushButton->setText(text);
}

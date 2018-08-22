#include "gomoku.h"
#include "ui_gomoku.h"

#include <QCloseEvent>
#include <QDebug>

Gomoku::Gomoku(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Gomoku)
{
    ui->setupUi(this);
    for (int y=1;y<25;y++)
    {
        for (int x=1;x<25;x++) {
            zi[x][y]=new QPushButton("",this);
            zi[x][y]->setGeometry(0,0,0,0);
            zi[x][y]->connect(zi[x][y], &QPushButton::clicked, this, [ = ] {
                           drop(x,y);
            });
            zi[x][y]->setFlat(true);
            zi[x][y]->setEnabled(true);
            zi[x][y]->show();
        }
    }
    datas.append("Information :\n");
    datas.append("Testing Gomoku Pan");
}
void Gomoku::paintEvent( QPaintEvent * )
{
     qreal w=size().width()/100;
     qreal h=size().height()/100;
     if (w!=h)
     {
         if (w>h)
         {
            w=h;
         }
         else
         {
            h=w;
         }
     }
     QPainter painter(this);
     QFont font = painter.font();
     font.setPixelSize(36);
     font.setBold(false);
     QPen grey;
     grey.setColor(Qt::gray);
     painter.setFont(font);
     painter.setPen(grey);
     painter.drawText(this->rect(), Qt::AlignRight, datas);
     QPen pen;
     pen.setWidthF(w/10);
     painter.setPen(pen);
     for (int x=1;x<=24;x++)
         painter.drawLine(w*4,h*4*x,w*96,h*4*x);
     for (int x=1;x<=24;x++)
         painter.drawLine(w*4*x,h*4,w*4*x,h*96);
     for (int yi=1;yi<=24;yi++)
        for (int xi=1;xi<=24;xi++)
            zi[xi][yi]->setGeometry(w*4*(xi-0.5),h*4*(yi-0.5),w*4,h*4);

}

void Gomoku::checkwinlost(){
    int winner=0;
    for (int x=0;x<25&&winner==0;x++)
    {
        for(int y=0;y<21&&winner==0;y++) {
            if (p[x][y]=="1"&&p[x+1][y]=="1"&&p[x+2][y]=="1"&&p[x+3][y]=="1"&&p[x+4][y]=="1"){
                winner=1;
            }
            else if (p[x][y]=="1"&&p[x-1][y]=="1"&&p[x-2][y]=="1"&&p[x-3][y]=="1"&&p[x-4][y]=="1"){
                winner=1;
            }
            else if (p[x][y+1]=="1"&&p[x][y+2]=="1"&&p[x][y+3]=="1"&&p[x][y+4]=="1"&&p[x][y]=="1"){
                winner=1;
            }
            else if (p[x][y-1]=="1"&&p[x][y-2]=="1"&&p[x][y-3]=="1"&&p[x][y-4]=="1"&&p[x][y]=="1"){
                winner=1;
            }
            else if (p[x+1][y+1]=="1"&&p[x+2][y+2]=="1"&&p[x+3][y+3]=="1"&&p[x+4][y+4]=="1"&&p[x][y]=="1"){
                winner=1;
            }
            else if (p[x-1][y-1]=="1"&&p[x-2][y-2]=="1"&&p[x-3][y-3]=="1"&&p[x-4][y-4]=="1"&&p[x][y]=="1"){
                winner=1;
            }
            else if (p[x-1][y+1]=="1"&&p[x-2][y+2]=="1"&&p[x-3][y+3]=="1"&&p[x-4][y+4]=="1"&&p[x][y]=="1"){
                winner=1;
            }
            else if (p[x+1][y-1]=="1"&&p[x+2][y-2]=="1"&&p[x+3][y-3]=="1"&&p[x+4][y-4]=="1"&&p[x][y]=="1"){
                winner=1;
            }
            //#
            if (p[x][y]=="2"&&p[x+1][y]=="2"&&p[x+2][y]=="2"&&p[x+3][y]=="2"&&p[x+4][y]=="2"){
                winner=2;
            }
            else if (p[x][y]=="2"&&p[x-1][y]=="2"&&p[x-2][y]=="2"&&p[x-3][y]=="2"&&p[x-4][y]=="2"){
                winner=2;
            }
            else if (p[x][y+1]=="2"&&p[x][y+2]=="2"&&p[x][y+3]=="2"&&p[x][y+4]=="2"&&p[x][y]=="2"){
                winner=2;
            }
            else if (p[x][y-1]=="2"&&p[x][y-2]=="2"&&p[x][y-3]=="2"&&p[x][y-4]=="2"&&p[x][y]=="2"){
                winner=2;
            }
            else if (p[x+1][y+1]=="2"&&p[x+2][y+2]=="2"&&p[x+3][y+3]=="2"&&p[x+4][y+4]=="2"&&p[x][y]=="2"){
                winner=2;
            }
            else if (p[x-1][y-1]=="2"&&p[x-2][y-2]=="2"&&p[x-3][y-3]=="2"&&p[x-4][y-4]=="2"&&p[x][y]=="2"){
                winner=2;
            }
            else if (p[x-1][y+1]=="2"&&p[x-2][y+2]=="2"&&p[x-3][y+3]=="2"&&p[x-4][y+4]=="2"&&p[x][y]=="2"){
                winner=2;
            }
            else if (p[x+1][y-1]=="2"&&p[x+2][y-2]=="2"&&p[x+3][y-3]=="2"&&p[x+4][y-4]=="2"&&p[x][y]=="2"){
                winner=2;
            }
            if(winner!=0)
            {
                //Process that someone win
                if (winner==1)
                {
                    win(true);
                }
                else
                {
                    win(false);
                }
            }
        }
    }
}
Gomoku::~Gomoku()
{
    delete ui;
}
void Gomoku::win(bool who) {

}
void Gomoku::drop(int x, int y) {

}

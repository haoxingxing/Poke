#include "serverforward.h"
#include "ui_serverforward.h"

serverforward::serverforward(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::serverforward)
{
    ui->setupUi(this);
    net->connect(net,&network::connectedsignal,this,[=]{net->send(T_LOGIN_TOKEN,"NULL");show();});
    net->connect(net,SIGNAL(disconnectedsignal()),this,SLOT(hide()));
    net->connect(net,SIGNAL(readyreadsignal(QString)),this,SLOT(readyread(QString)));
    net->connectToHost();
}

serverforward::~serverforward()
{
    delete ui;
}

void serverforward::readyread(QString data) {
    ui->textBrowser->append(data);
}


void serverforward::on_pushButton_clicked()
{
    if (!isconected)
    {
        net->send(T_SERVERFORWARD(ui->lineEdit->text()));
        isconected=true;
    }
    else
    {
        net->send(ui->lineEdit->text());
    }
}

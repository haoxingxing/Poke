#include "verification.h"
#include "ui_verification.h"

verification::verification(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::verification)
{
    ui->setupUi(this);
    net->connect(net,SIGNAL(connectedsignal()),this,SLOT(show()));
    net->connect(net,SIGNAL(disconnectedsignal()),this,SLOT(hide()));
    net->connect(net,SIGNAL(readyreadsignal(QString)),this,SLOT(readyread(QString)));
    net->connectToHost();
}

verification::~verification()
{
    delete ui;
}
void verification::readyread(QString data)
{
    QJsonObject ret=QJsonDocument::fromJson(data.toLocal8Bit()).object();
    if (ret.value("status").toString()!="200") {
        ui->label->setText("错误:"+ret.value("status").toString()+ret.value("message").toString());
        ui->username->setReadOnly(false);
        ui->Password->setReadOnly(false);
        ui->pushButton->show();
        ui->pushButton_2->show();
        ui->Password->clear();
        return;
    }
    ui->label->setText("OK:"+ret.value("status").toString()+ret.value("message").toString());
    token=ret.value("parameter").toObject().value("token").toString();
}

void verification::on_pushButton_clicked()
{
    ui->pushButton->hide();
    ui->pushButton_2->hide();
    ui->username->setReadOnly(true);
    ui->Password->setReadOnly(true);
    QString md5;
    QByteArray bb;
    bb = QCryptographicHash::hash (("T#S#a#l#t#"+ui->Password->text().toLocal8Bit()+ui->username->text().toLocal8Bit()), QCryptographicHash::Md5);
    md5.append(bb.toHex());
    net->send(T_LOGIN(ui->username->text(),md5));
}

void verification::on_pushButton_2_clicked()
{
    ui->pushButton->hide();
    ui->pushButton_2->hide();
    ui->username->setReadOnly(true);
    ui->Password->setReadOnly(true);
    QString md5;
    QByteArray bb;
    bb = QCryptographicHash::hash (("T#S#1a#l#t#"+ui->Password->text().toLocal8Bit()+ui->username->text().toLocal8Bit()), QCryptographicHash::Md5);
    md5.append(bb.toHex());
    net->send(T_REGISTER(ui->username->text(),md5));
}

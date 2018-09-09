#include "matchqueue.h"
#include "ui_matchqueue.h"
#include <QDebug>
MatchQueue::MatchQueue(QWidget *parent,QString queuename,int queuenumber,QEventLoop *wait) :
    QWidget(parent),
    ui(new Ui::MatchQueue)
{
    ui->setupUi(this);
    net.connect(&net,&network::connectedsignal,this,[&]{
        net.send(T_LOGIN_TOKEN,"NULL");
    });
    loop=wait;
    this->queuename=queuename;
    this->queuenumbers=queuenumber;
    net.connect(&net,SIGNAL(readyreadsignal(QString)),this,SLOT(readyread(QString)));
    net.connectToHost();
    timer.connect(&timer,SIGNAL(timeout()),this,SLOT(numsupdate()));
    this->show();
    ui->lcdNumber->display(0);
    timer.start(1000);
    ui->textBrowser->append("Connecting to Server...");
}
void MatchQueue::readyread(QString data)
{
    QJsonObject o=QJsonDocument::fromJson(data.toLocal8Bit()).object();
    if (o.value("class").toString()=="user")
        if (o.value("status").toString()=="200") {
            net.send(T_MATCHQUEUE(queuename,QString::number(queuenumbers)));
            ui->textBrowser->append(o.value("message").toString());
            ui->textBrowser->append("Matching");
        }
    if (o.value("class").toString()=="matchqueue") {
        int all=0;
        if (o.value("status").toString()=="102")
        {
            queuenumbersnames.clear();
            QJsonObject p=QJsonDocument::fromJson(data.toLocal8Bit()).object().value("parameter").toObject().value("queue").toObject();
            for (int a=1;a<=queuenumbers;a++) {
                if (p.contains("number-"+QString::number(a)))
                {
                    if (p.value("number-"+QString::number(a))!="")all++;
                    queuenumbersnames.append(p.value("number-"+QString::number(a)).toString());
                }
                else
                {
                    break;
                }
            }
            ui->textBrowser->setText(ui->textBrowser->document()->toPlainText()+".");
            ui->status->setText(QString::number(all)+"/"+QString::number(queuenumbers));
        }
        if (o.value("status").toString()=="200")
        {
            queuenumbersnames.clear();
            timer.stop();
            QJsonObject p=QJsonDocument::fromJson(data.toLocal8Bit()).object().value("parameter").toObject().value("queue").toObject();
            for (int a=1;a<=queuenumbers;a++) {
                if (p.contains("number-"+QString::number(a)))
                {
                    if (p.value("number-"+QString::number(a))!="")all++;
                    if (p.value("number-"+QString::number(a)).toString()==""){queuenumbersnames.append(QString::number(p.value("number-"+QString::number(a)).toInt()));}
                    else
                    {
                        queuenumbersnames.append(p.value("number-"+QString::number(a)).toString());
                    }
                }
                else
                {
                    break;
                }
            }
            ui->textBrowser->append("Matched");
            ui->info->setText("Matched");
            ui->status->setText(QString::number(all)+"/"+QString::number(queuenumbers));
            loop->quit();
        }
    }
}
void MatchQueue::numsupdate() {
    ui->lcdNumber->display(ui->lcdNumber->value()+1);
}
MatchQueue::~MatchQueue()
{
    delete ui;
}
void MatchQueue::closeEvent(QCloseEvent *event)
{
    event->accept();
    queuenumbersnames.clear();
    loop->exit();
}

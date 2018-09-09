#ifndef MATCHQUEUE_H
#define MATCHQUEUE_H

#include "network.h"
#include <QEventLoop>
#include <QTimer>
#include <QWidget>

namespace Ui {
class MatchQueue;
}

class MatchQueue : public QWidget
{
    Q_OBJECT

public:
    explicit MatchQueue(QWidget *parent = 0,QString queuename="e",int queuenumber=999,QEventLoop *wait=new QEventLoop);
    ~MatchQueue();
    QStringList queuenumbersnames;
private slots:
    void readyread(QString data);
    void numsupdate();
private:
    void closeEvent(QCloseEvent *event);
    QString queuename;
    QEventLoop *loop;
    int queuenumbers;
    QTimer timer;
    network net;
    Ui::MatchQueue *ui;
};

#endif // MATCHQUEUE_H

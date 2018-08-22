#ifndef MATCHQUEUE_H
#define MATCHQUEUE_H

#include "network.h"
#include <QTimer>
#include <QWidget>

namespace Ui {
class MatchQueue;
}

class MatchQueue : public QWidget
{
    Q_OBJECT

public:
    explicit MatchQueue(QWidget *parent = 0,QString queuename="e",int queuenumber=999);
    ~MatchQueue();
private slots:
    void readyread(QString data);
    void numsupdate();
private:
    QString queuename;
    QStringList queuenumbersnames;
    int queuenumbers;
    QTimer timer;
    network net;
    Ui::MatchQueue *ui;
};

#endif // MATCHQUEUE_H

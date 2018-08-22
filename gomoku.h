#ifndef GOMOKU_H
#define GOMOKU_H

#include <QMainWindow>
#include <QPainter>
#include "tcpserverforward.h"
#include <QPushButton>
#include <QMessageBox>
namespace Ui {
class Gomoku;
}

class Gomoku : public QMainWindow
{
    Q_OBJECT

public:
    explicit Gomoku(QWidget *parent = 0,QStringList players=QStringList());
    ~Gomoku();

private slots:
    void drop(int x,int y,bool issender);
    void readyread(QString data);
private:   
    void init();
    void win(bool who);
    void paintEvent(QPaintEvent *event);
    Ui::Gomoku *ui;
    QString object;
    QPushButton *zi[25][25];
    QString datas;
    TcpServerForward *tsf;
    std::string p[25][25];
    bool luod[25][25];
    bool whoIam;
    bool inited=false;
    bool whoNowLuo=true;
    void checkwinlost();
};

#endif // GOMOKU_H

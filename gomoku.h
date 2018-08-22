#ifndef GOMOKU_H
#define GOMOKU_H

#include <QMainWindow>
#include <QPainter>
#include <QPushButton>
namespace Ui {
class Gomoku;
}

class Gomoku : public QMainWindow
{
    Q_OBJECT

public:
    explicit Gomoku(QWidget *parent = 0);
    ~Gomoku();

private slots:
    void drop(int x,int y);
private:   
    void win(bool who);
    void paintEvent(QPaintEvent *event);
    Ui::Gomoku *ui;
    QPushButton *zi[25][25];
    QString datas;
    std::string p[25][25];
    //bool luod[25][25];
    //bool whoIam;
    //bool whoNowLuo;
    void checkwinlost();
};

#endif // GOMOKU_H

#ifndef VERIFICATION_H
#define VERIFICATION_H
#include <QEventLoop>
#include <QMainWindow>
#include "network.h"
namespace Ui {
class verification;
}

class verification : public QMainWindow
{
    Q_OBJECT

public:
    explicit verification(QWidget *parent = 0);
    ~verification();
    QEventLoop *wait;
private slots:
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void readyread(QString data);
private:
    network *net=new network();
    Ui::verification *ui;
};

#endif // VERIFICATION_H

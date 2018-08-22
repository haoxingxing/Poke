#ifndef TEST_H
#define TEST_H
#include "tcpserverforward.h"
#include <QWidget>

namespace Ui {
class test;
}

class test : public QWidget
{
    Q_OBJECT

public:
    explicit test(QWidget *parent = 0);
    ~test();

private slots:
    void readyread(QString data);
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
   TcpServerForward tsf;
    Ui::test *ui;
};

#endif // TEST_H

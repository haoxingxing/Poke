#ifndef SERVERFORWARD_H
#define SERVERFORWARD_H
#include <network.h>
#include <QWidget>

namespace Ui {
class serverforward;
}

class serverforward : public QWidget
{
    Q_OBJECT

public:
    explicit serverforward(QWidget *parent = 0);
    ~serverforward();

private slots:
    void readyread(QString data);
    void on_pushButton_clicked();
private:
    network *net=new network;
    Ui::serverforward *ui;
    bool isconected=false;
};

#endif // SERVERFORWARD_H

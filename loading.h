#ifndef LOADING_H
#define LOADING_H
#include <QWidget>
#include <QTImer>
#include <QCloseEvent>
#include <QGraphicsOpacityEffect>
namespace Ui {
class loading;
}

class loading : public QWidget
{
    Q_OBJECT

public:
    explicit loading(QWidget *parent = 0);
    ~loading();
    void setloadingtext(QString text);
    QTimer *timer=new QTimer(this);
private slots:
    void next();
private:
    void closeEvent(QCloseEvent *e);
    int now=0;
    Ui::loading *ui;
};

#endif // LOADING_H

#ifndef NETWORK_H
#define NETWORK_H
#include <QTimer>
#include <QObject>
#include <QTcpSocket>
#include <QUdpSocket>
#include <QJsonArray>
#include <QJsonObject>
#include <QStringList>
#include <QMessageBox>
#include <QJsonDocument>
#include <QCryptographicHash>
#include "loading.h"
#define SERVERHOST "localhost"
#define SERVERPORT 8864
#define T_P_N_P(username,password) network::jsonencode(QStringList()<<"username"<<"password",QStringList()<<username<<password)
#define T_C_F QStringList()<<"class"<<"func"
#define T_LOGIN(u,p) network::addjsontojson(network::jsonencode(T_C_F,QStringList()<<"user"<<"login"),"parameter",T_P_N_P(u,p))
#define T_REGISTER(u,p) network::addjsontojson(network::jsonencode(T_C_F,QStringList()<<"user"<<"register"),"parameter",T_P_N_P(u,p))
QString extern token;
class network : public QObject
{
    Q_OBJECT
public:
    explicit network(QObject *parent = nullptr);
    void connectToHost();
    void send(QJsonObject json);
    static QJsonObject jsonencode(QStringList key,QStringList value);
    static QString jsontostring(QJsonObject json);
    static QJsonObject addjsontojson(QJsonObject a,QString key,QJsonObject value);
    QTcpSocket *socket;
signals:
    void connectedsignal();
    void disconnectedsignal();
    void readyreadsignal(QString data);
private slots:
    void readyread();
    void connected();
    void timeoutconnecting();
    void disconnected();
private:
    loading *loadbuf;
    QTimer *timeouttm;   
    bool isconnected=false;
};

#endif // NETWORK_H

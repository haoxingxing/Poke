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
#define SERVERHOST "monstars.cn"
#define SERVERPORT 8864

#define T_P_N_P(username,password) network::jsonencode(QStringList()<<"username"<<"password",QStringList()<<username<<password)
#define T_P_N_T(username,token) network::jsonencode(QStringList()<<"username"<<"token",QStringList()<<username<<token)
#define T_C_F QStringList()<<"class"<<"func"
#define T_C QStringList()<<"class"
#define T_LOGIN(u,p) network::addjsontojson(network::jsonencode(T_C_F,QStringList()<<"user"<<"login"),"parameter",T_P_N_P(u,p))
#define T_REGISTER(u,p) network::addjsontojson(network::jsonencode(T_C_F,QStringList()<<"user"<<"register"),"parameter",T_P_N_P(u,p))
#define T_LOGIN_TOKEN network::addjsontojson(network::jsonencode(T_C_F,QStringList()<<"user"<<"tokenlogin"),"parameter",T_P_N_T(username,token))
#define T_SERVERFORWARD(o) network::jsonencode(T_C<<"object",QStringList()<<"tcpserverforward"<<o)
#define T_SERVERFORWARD_DISCONNECT "disconnect"
#define T_MATCHQUEUE(name,all) network::addjsontojson(network::jsonencode(T_C_F,QStringList()<<"matchqueue"<<"join"),"parameter",network::jsonencode(QStringList()<<"queuename"<<"queueall",QStringList()<<name<<all))

#define T_P2P_GOMOKU_DROP(x,y) network::addjsontojson(network::jsonencode(T_C_F,QStringList()<<"Gomoku"<<"drop"),"parameter",network::jsonencode(QStringList()<<"x"<<"y",QStringList()<<QString::number(x)<<QString::number(y)))

QString extern token;
QString extern username;
class network : public QObject
{
    Q_OBJECT
public:
    explicit network(QObject *parent = nullptr);
    void connectToHost();
    void send(QJsonObject json);
    void send(QString data);
    void send(QJsonObject json,QString tokenpowered);
    void disconnectFromHost();
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

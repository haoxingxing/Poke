#ifndef TCPSERVERFORWARD_H
#define TCPSERVERFORWARD_H
#include "network.h"

class TcpServerForward : public QObject
{
    Q_OBJECT
public:    
    explicit TcpServerForward(QObject *parent = nullptr);
    void send(QJsonObject data);
    void send(QString data);
    void connectp2p(QString object);
private:
    network net;
    bool isconnectedtoserver=false;
    bool isconnectedp2p=false;

signals:
    void ctss();
    void readyreadsignal(QString);
    void connectedsignal();
    void disconnectedsignal();
private slots:
    void disconnected();
    void conected();
    void readyread(QString data);

};

#endif // TCPSERVERFORWARD_H

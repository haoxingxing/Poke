#ifndef TCPSERVERFORWARD_H
#define TCPSERVERFORWARD_H
#include "network.h"

class TcpServerForward : public network
{
    Q_OBJECT
public:    
    explicit TcpServerForward(QObject *parent = nullptr);
    ~TcpServerForward();
    void connectp2p(QString object);
    void disconnectFromP2P();
private:
    bool isconnectedtoserver=false;
    bool isconnectedp2p=false;

signals:
    void ctss();
    void readyreadp2psignal(QString);
    void connectedp2psignal();
    void disconnectedp2psignal();
private slots:
    void disconnectedp2p();
    void conectedtoserver();
    void readyreadp2p(QString data);

};

#endif // TCPSERVERFORWARD_H

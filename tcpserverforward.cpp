#include "tcpserverforward.h"

TcpServerForward::TcpServerForward(QObject *parent) : network(parent)
{
    connect(this,SIGNAL(connectedsignal()),this,SLOT(conectedtoserver()));
    connect(this,SIGNAL(disconnectedsignal()),this,SLOT(disconnectedp2p()));
    connect(this,SIGNAL(readyreadsignal(QString)),this,SLOT(readyreadp2p(QString)));
    connectToHost();
}
void TcpServerForward::conectedtoserver() {
    send(T_LOGIN_TOKEN,"NULL");
}
TcpServerForward::~TcpServerForward(){
    disconnectFromHost();
}
void TcpServerForward::readyreadp2p(QString data) {
    QJsonObject recvjson=QJsonDocument::fromJson(data.toLocal8Bit()).object();
    if (recvjson.value("class").toString()=="user")
    {
        if (recvjson.value("status").toString()=="200")
        {
            isconnectedtoserver=true;
            emit ctss();
        }
        else
        {
            isconnectedtoserver=false;
        }
    }
    else if (recvjson.value("class").toString()=="tcpserverforward")
    {
        if (recvjson.value("func").toString()=="connect")
        {
            if (recvjson.value("status").toString()=="200")
            {
                isconnectedp2p=true;
                emit connectedp2psignal();
            }
            else
            {
                isconnectedp2p=false;
            }
        }
        else if (recvjson.value("func").toString()=="datatransloop")
        {
            isconnectedp2p=false;
            emit disconnectedp2psignal();
        }
    }
    else
    {
        emit readyreadp2psignal(data);
    }
}
void TcpServerForward::connectp2p(QString object) {
    if (isconnectedtoserver)
    {
        send(T_SERVERFORWARD(object));
    }
}
void TcpServerForward::disconnectedp2p()
{
    if (isconnectedp2p)
    {
        isconnectedtoserver=false;
        isconnectedp2p=false;
        emit disconnectedsignal();
    }
}
void TcpServerForward::disconnectFromP2P() {
    if (isconnectedp2p)
    {
        isconnectedp2p=false;
        send(T_SERVERFORWARD_DISCONNECT);
    }
}

#include "tcpserverforward.h"

TcpServerForward::TcpServerForward(QObject *parent) : QObject(parent)
{
    net.connect(&net,SIGNAL(connectedsignal()),this,SLOT(conected()));
    net.connect(&net,&network::disconnectedsignal,this,&TcpServerForward::disconnected);
    net.connect(&net,SIGNAL(readyreadsignal(QString)),this,SLOT(readyread(QString)));
    net.connectToHost();
}
void TcpServerForward::conected() {
    net.send(T_LOGIN_TOKEN,"NULL");
}
void TcpServerForward::readyread(QString data) {
    QJsonObject recvjson=QJsonDocument::fromJson(data.toLocal8Bit()).object();
    if (recvjson.value("class").toString()=="user")
    {
        if (recvjson.value("status").toString()=="200")
        {
            isconnectedtoserver=true;
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
                emit connectedsignal();
            }
            else
            {
                isconnectedp2p=false;
            }
        }
        else if (recvjson.value("func").toString()=="datatransloop")
        {
            isconnectedp2p=false;
            emit disconnectedsignal();
        }
    }
    else
    {
        emit readyreadsignal(data);
    }
}
void TcpServerForward::connectp2p(QString object) {
    if (isconnectedtoserver)
    {
        net.send(T_SERVERFORWARD(object));
    }
}
void TcpServerForward::send(QJsonObject data) {
    if (isconnectedp2p) {
        net.send(data);
    }
}
void TcpServerForward::send(QString data) {
    if (isconnectedp2p) {
        net.send(data);
    }
}
void TcpServerForward::disconnected()
{
    isconnectedtoserver=false;
    isconnectedp2p=false;
    emit disconnectedsignal();
}

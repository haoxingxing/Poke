#include "network.h"
QString token="NULL";
network::network(QObject *parent) : QObject(parent)
{
    socket=new QTcpSocket;
    loadbuf=new loading(NULL);
    timeouttm=new QTimer;    
}

void network::connectToHost() {
    if (!isconnected)
    {

        loadbuf->show();
        loadbuf->setloadingtext("Connecting To Host...");
        socket->disconnect();
        socket->connect(socket,SIGNAL(connected()),this,SLOT(connected()));
        socket->connectToHost(SERVERHOST,SERVERPORT);
        timeouttm->disconnect();
        timeouttm->connect(timeouttm,SIGNAL(timeout()),this,SLOT(timeoutconnecting()));
        timeouttm->start(6000);
    }
}
void network::connected() {
    timeouttm->stop();
    isconnected=true;
    loadbuf->setloadingtext("Connected");
    loadbuf->hide();
    timeouttm->disconnect();
    socket->connect(socket,&QTcpSocket::disconnected,this,[=] {emit disconnectedsignal();});
    socket->connect(socket,&QTcpSocket::disconnected,this,&network::disconnected,Qt::QueuedConnection);
    socket->connect(socket,&QTcpSocket::readyRead,this,&network::readyread);
    emit connectedsignal();
}
void network::readyread() {
    QJsonDocument o = QJsonDocument::fromJson(QByteArray::fromBase64(socket->readLine()));
    QString md5;
    QByteArray bb;
    bb = QCryptographicHash::hash ((o.object().value("data").toString()+o.object().value("token").toString()).toLocal8Bit(), QCryptographicHash::Md5);
    md5.append(bb.toHex());
    if (md5.toUpper()==o.object().value("md5").toString())
    {
        emit readyreadsignal(QByteArray::fromBase64(o.object().value("data").toString().toLocal8Bit()));
    }
}
void network::timeoutconnecting()
{
    timeouttm->stop();
    isconnected=false;
    loadbuf->setloadingtext("Failed Connecting");       
    QMessageBox::critical(NULL,"Network Error","Failed to connect to host",QMessageBox::Ok);
    loadbuf->hide();
}
void network::disconnected()
{
    isconnected=false;
    loadbuf->show();
    loadbuf->setloadingtext("Disconnected From Host");
    this->connectToHost();
}
void network::send(QJsonObject json)  {
    if (isconnected)
    {
        QByteArray jsonArray = jsontostring(json).toLocal8Bit();
        QString md5;
        QByteArray bb;
        bb = QCryptographicHash::hash (jsonArray.toBase64()+token.toLocal8Bit(), QCryptographicHash::Md5);
        md5.append(bb.toHex());
        QJsonObject object;
        object.insert("data",QString::fromStdString(jsonArray.toBase64().toStdString()));
        object.insert("token",token);
        object.insert("md5",md5.toUpper());
        QByteArray byteArray = jsontostring(object).toLocal8Bit();
        socket->write(byteArray.toBase64());
        socket->write("\r\n");
        socket->flush();        
    }
    else
    {
        this->connectToHost();
    }
}
QString network::jsontostring(QJsonObject json) {
    QJsonDocument strjson;
    strjson.setObject(json);
    QByteArray jsonArray = strjson.toJson(QJsonDocument::Compact);
    return jsonArray;
}
QJsonObject network::addjsontojson(QJsonObject a,QString key,QJsonObject value)
{
    a.insert(key,value);
    return a;
}
QJsonObject network::jsonencode(QStringList key,QStringList value) {
   QJsonObject obj;
   if (key.length()!=value.length()) return obj;
   for (int x=0;x<key.length();x++)
           obj.insert(key.value(x),value.value(x));
   return obj;
}

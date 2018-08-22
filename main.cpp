#include "verification.h"
#include "gomoku.h"
#include "matchqueue.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QEventLoop loopofverify;
    verification verify;
    verify.wait=&loopofverify;
    loopofverify.exec();
    QEventLoop loopqueue;
    MatchQueue *matchQueue=new MatchQueue(NULL,"Gomoku",2,&loopqueue);
    matchQueue->show();
    loopqueue.exec();
    Gomoku *G=new Gomoku(NULL,matchQueue->queuenumbersnames);
    G->show();
    delete matchQueue;
    return a.exec();
}

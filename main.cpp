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
    MatchQueue *matchQueue=new MatchQueue(NULL,"test",3);
    matchQueue->show();
    return a.exec();
}

#include "verification.h"
#include "menu.h"
#include "matchqueue.h"
#include "tcpserverforward.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QEventLoop loopofverify;
    verification verify;
    verify.wait=&loopofverify;
    loopofverify.exec();    
    menu main;
    main.show();
    return a.exec();
}

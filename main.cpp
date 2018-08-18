#include "verification.h"
#include "serverforward.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QEventLoop loopofverify;
    verification verify;
    verify.wait=&loopofverify;
    loopofverify.exec();
    serverforward sfw;
    sfw.show();
    return a.exec();
}

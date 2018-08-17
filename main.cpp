#include "verification.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    verification verify;
    a.exec();
    return 0;
}

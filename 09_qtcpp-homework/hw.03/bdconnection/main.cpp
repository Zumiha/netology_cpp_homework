#include "dbconnect.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    dbconnect w;
    w.show();
    return a.exec();
}

#include "devphysiodaq_dialog.h"

#include <QApplication>

#include "measuredevice.h"

int main(int argc, char *argv[])
{
    analogInStruct *analogInfo = nullptr;
    int n = 0;
    QApplication a(argc, argv);
    devphysiodaq_dialog w(nullptr,n,analogInfo);
    w.show();
    return a.exec();
}

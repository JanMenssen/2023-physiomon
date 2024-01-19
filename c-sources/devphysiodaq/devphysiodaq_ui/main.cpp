#include "devphysiodaq_dialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    devphysiodaq_dialog w;
    w.show();
    return a.exec();
}

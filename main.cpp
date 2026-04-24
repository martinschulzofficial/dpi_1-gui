#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    Widget w;
    // w.show();
    a.setQuitOnLastWindowClosed(false);
    return QCoreApplication::exec();
}

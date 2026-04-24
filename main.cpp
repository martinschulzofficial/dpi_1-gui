#include "widget.h"


// #include <ApplicationServices/ApplicationServices.h>
#include <QApplication>

int main(int argc, char *argv[])
{

    // ProcessSerialNumber psn = { 0, kCurrentProcess };
    // TransformProcessType(&psn, kProcessTransformToUIElementApplication);
    QApplication a(argc, argv);
    Widget w;
    w.show();
    a.setQuitOnLastWindowClosed(false);
    return QCoreApplication::exec();
}

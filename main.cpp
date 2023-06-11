//https://stackoverflow.com/questions/19822211/qt-parsing-json-using-qjsondocument-qjsonobject-qjsonarray
//https://stackoverflow.com/questions/47278354/libcurl-x64-dll-was-not-found
//https://forum.qt.io/topic/137815/how-to-use-libcurl-in-qt?_=1686442587385
//https://stackoverflow.com/questions/33394461/how-to-statically-link-to-libcurl-in-qt-on-windows

#include "mainwindow.h"

#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

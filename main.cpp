#include "mainwindow.h"

#include <QApplication>
#include <QTranslator>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    a.setWindowIcon(QIcon("clubber.ico"));

    QTranslator translator_fi;
    translator_fi.load("qt-harkka_fi_FI");

    // Check and load translation
    if (QLocale::system().name() == "fi_FI") {
        a.installTranslator(&translator_fi);
    }

    MainWindow w;
    w.show();
    return a.exec();
}

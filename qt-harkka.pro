QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    closedialog.cpp \
    helpdialog.cpp \
    holiday.cpp \
    infodialog.cpp \
    main.cpp \
    mainwindow.cpp \
    searchdialog.cpp

HEADERS += \
    closedialog.h \
    helpdialog.h \
    holiday.h \
    infodialog.h \
    mainwindow.h \
    searchdialog.h

FORMS += \
    closedialog.ui \
    helpdialog.ui \
    infodialog.ui \
    mainwindow.ui \
    searchdialog.ui

TRANSLATIONS += \
    qt-harkka_fi_FI.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    clubber.ico

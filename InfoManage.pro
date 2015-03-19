#-------------------------------------------------
#
# Project created by QtCreator 2015-02-26T18:57:04
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets


TARGET = InfoManage
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dlglogin.cpp \
    AccountTable.cpp

HEADERS  += mainwindow.h \
    dlglogin.h \
    AccountTable.h

FORMS    += mainwindow.ui \
    dlglogin.ui

OTHER_FILES += \
    army.PNG

RESOURCES += \
    InfoManageImages.qrc

QT += sql

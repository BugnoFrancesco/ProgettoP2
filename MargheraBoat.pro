#-------------------------------------------------
#
# Project created by QtCreator 2021-08-31T11:27:38
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MargheraBoat
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        Modello/Gerarchia/imbarcazione.cpp \
        Modello/Gerarchia/motore.cpp \
        Modello/Gerarchia/vela.cpp \
        Modello/Gerarchia/termico.cpp \
        Modello/Gerarchia/elettrico.cpp \
        Modello/model.cpp \
    Vista/mainwindow.cpp \
    Vista/menubar.cpp \
    Vista/mainlayout.cpp \
    Vista/insertlayout.cpp \
    Vista/modifylayout.cpp


HEADERS += \
        Modello/Gerarchia/imbarcazione.h \
        Modello/Gerarchia/motore.h \
        Modello/Gerarchia/vela.h \
        Modello/Gerarchia/termico.h \
        Modello/Gerarchia/elettrico.h \
        Modello/deepptr.h \
        Modello/container.h \
        Modello/model.h \
    Vista/mainwindow.h \
    Vista/menubar.h \
    Vista/mainlayout.h \
    Vista/insertlayout.h \
    Vista/modifylayout.h


#-------------------------------------------------
#
# Project created by QtCreator 2019-06-21T15:11:56
#
#-------------------------------------------------

QT       += core gui
QT       += serialport
QT       += 3drender
QT       += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Bupt_Reserves_Score_indicator
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
        mainwindow.cpp \
    informui.cpp \
    choose_ui.cpp \
    game_ui.cpp \
    com_ui.cpp \
    score_ui.cpp

HEADERS  += mainwindow.h \
    informui.h \
    choose_ui.h \
    game_ui.h \
    com_ui.h \
    score_ui.h

FORMS    += mainwindow.ui \
    informui.ui \
    choose_ui.ui \
    game_ui.ui \
    com_ui.ui \
    score_ui.ui

RESOURCES += \
    mysource.qrc

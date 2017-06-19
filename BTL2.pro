#-------------------------------------------------
#
# Project created by QtCreator 2017-05-31T23:14:49
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BTL2
TEMPLATE = app
DESTDIR = $$PWD
# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    lib.cpp \
    info.cpp \
    admin.cpp \
    library.cpp \
    add_user.cpp \
    add_book.cpp \
    mess.cpp \
    contact.cpp \
    user_message.cpp \
    lib_message.cpp \
    history.cpp \
    request.cpp

HEADERS += \
        mainwindow.h \
    lib.h \
    info.h \
    admin.h \
    library.h \
    add_user.h \
    add_book.h \
    mess.h \
    contact.h \
    user_message.h \
    lib_message.h \
    history.h \
    request.h

FORMS += \
    lib.ui \
    mainwindow.ui \
    info.ui \
    admin.ui \
    library.ui \
    add_user.ui \
    add_book.ui \
    mess.ui \
    contact.ui \
    user_message.ui \
    lib_message.ui \
    history.ui \
    request.ui

RESOURCES += \
    design.qrc

#-------------------------------------------------
#
# Project created by QtCreator 2016-04-10T09:21:25
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = KenNomina
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    conndb.cpp \
    model.cpp \
    empleadomodel.cpp \
    empleado.cpp \
    empleadowidget.cpp \
    asignacionmodel.cpp \
    nominamodel.cpp \
    asignacion.cpp \
    deduccion.cpp \
    deduccionmodel.cpp \
    deduccionwidget.cpp \
    parentwidget.cpp \
    logindialog.cpp \
    loginmodel.cpp \
    usuario.cpp

HEADERS  += mainwindow.h \
    conndb.h \
    model.h \
    empleadomodel.h \
    empleado.h \
    empleadowidget.h \
    asignacionmodel.h \
    nominamodel.h \
    asignacion.h \
    deduccion.h \
    deduccionmodel.h \
    deduccionwidget.h \
    parentwidget.h \
    logindialog.h \
    loginmodel.h \
    usuario.h

FORMS    += mainwindow.ui \
    empleadowidget.ui \
    deduccionwidget.ui \
    logindialog.ui

QMAKE_CXXFLAGS += -std=c++14
CONFIG += c++14

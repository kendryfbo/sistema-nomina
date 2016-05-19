#-------------------------------------------------
#
# Project created by QtCreator 2016-05-18T15:16:26
#
#-------------------------------------------------

QT       += core gui printsupport script sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = KenNomina
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    usuario.cpp \
    uppercasevalidator.cpp \
    reportmodel.cpp \
    parentwidget.cpp \
    nominawidget.cpp \
    nominaprocesadawidget.cpp \
    nominamodeldialog.cpp \
    nominamodel.cpp \
    nominacargardialog.cpp \
    nominacargadawidget.cpp \
    nomina.cpp \
    model.cpp \
    loginmodel.cpp \
    logindialog.cpp \
    empleadowidget.cpp \
    empleadomodel.cpp \
    empleado.cpp \
    deduccionwidget.cpp \
    deduccionmodel.cpp \
    deducciondialog.cpp \
    deduccion.cpp \
    conndb.cpp \
    coduppercasevalidator.cpp \
    clasificacion.cpp \
    asignacionwidget.cpp \
    asignacionmodel.cpp \
    asignaciondialog.cpp \
    asignacion.cpp \
    areawidget.cpp \
    areamodel.cpp \
    area.cpp

HEADERS  += mainwindow.h \
    usuario.h \
    uppercasevalidator.h \
    reportmodel.h \
    parentwidget.h \
    nominawidget.h \
    nominaprocesadawidget.h \
    nominamodeldialog.h \
    nominamodel.h \
    nominacargardialog.h \
    nominacargadawidget.h \
    nomina.h \
    model.h \
    loginmodel.h \
    logindialog.h \
    empleadowidget.h \
    empleadomodel.h \
    empleado.h \
    deduccionwidget.h \
    deduccionmodel.h \
    deducciondialog.h \
    deduccion.h \
    conndb.h \
    coduppercasevalidator.h \
    clasificacion.h \
    asignacionwidget.h \
    asignacionmodel.h \
    asignaciondialog.h \
    asignacion.h \
    areawidget.h \
    areamodel.h \
    area.h

FORMS    += mainwindow.ui \
    nominawidget.ui \
    nominaprocesadawidget.ui \
    nominamodeldialog.ui \
    nominacargardialog.ui \
    nominacargadawidget.ui \
    logindialog.ui \
    empleadowidget.ui \
    deduccionwidget.ui \
    deducciondialog.ui \
    asignacionwidget.ui \
    asignaciondialog.ui \
    areawidget.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../LimeReport-master/build/5.6.0/win32/debug/lib/ -llimereport
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../LimeReport-master/build/5.6.0/win32/debug/lib/ -llimereport
else:unix: LIBS += -L$$PWD/../LimeReport-master/build/5.6.0/win32/debug/lib/ -llimereport

INCLUDEPATH += $$PWD/../LimeReport-master/include
DEPENDPATH += $$PWD/../LimeReport-master/include

RESOURCES += \
    recursos.qrc

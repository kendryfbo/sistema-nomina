#-------------------------------------------------
#
# Project created by QtCreator 2016-05-18T15:16:26
#
#-------------------------------------------------

QT       += core gui printsupport script sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = KenNomina
TEMPLATE = app
RC_FILE = myapp.rc
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
    area.cpp \
    empresamodel.cpp \
    empresadialog.cpp \
    anticipowidget.cpp \
    anticipodialog.cpp \
    anticipomodel.cpp \
    anticipolistadialog.cpp \
    aportefaovinsertdialog.cpp

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
    area.h \
    empresamodel.h \
    empresadialog.h \
    anticipowidget.h \
    anticipodialog.h \
    anticipomodel.h \
    anticipolistadialog.h \
    aportefaovinsertdialog.h

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
    areawidget.ui \
    empresadialog.ui \
    anticipowidget.ui \
    anticipodialog.ui \
    anticipolistadialog.ui \
    aportefaovinsertdialog.ui

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../limereport_1_3_11/build/5.6.0/win32/release/lib/ -llimereport
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../limereport_1_3_11/build/5.6.0/win32/release/lib/ -llimereport
else:unix: LIBS += -L$$PWD/../limereport_1_3_11/build/5.6.0/win32/release/lib/ -llimereport

INCLUDEPATH += $$PWD/../limereport_1_3_11/build/5.6.0/win32/release/lib/include
DEPENDPATH += $$PWD/../limereport_1_3_11/build/5.6.0/win32/release/lib/include

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../limereport_1_3_11/build/5.6.0/win32/release/lib/liblimereport.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../limereport_1_3_11/build/5.6.0/win32/release/lib/liblimereport.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../limereport_1_3_11/build/5.6.0/win32/release/lib/limereport.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../limereport_1_3_11/build/5.6.0/win32/release/lib/limereport.lib
else:unix: PRE_TARGETDEPS += $$PWD/../limereport_1_3_11/build/5.6.0/win32/release/lib/liblimereport.a

RESOURCES += \
    recursos.qrc

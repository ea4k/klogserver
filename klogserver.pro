QT -= gui
QT += core \
    network


CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        locator.cpp \
        main.cpp \
        mainclass.cpp \
        qso.cpp \
        udpserver.cpp \
        utilities.cpp

TRANSLATIONS += \
    translations/klogserver_es_ES.ts

CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    klogdefinitions.h \
    locator.h \
    mainclass.h \
    qso.h \
    udpserver.h \
    utilities.h

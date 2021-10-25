#/***************************************************************************
#                          klogserver.pro  -  description
#                             -------------------
#    begin                : aug 2021
#    copyright            : (C) 2021 by Jaime Robles
#    user                 : jaime@robles.es
# ***************************************************************************/

#/*****************************************************************************
# * This file is part of KLogServer                                           *
# *                                                                           *
# *    KLog is free software: you can redistribute it and/or modify           *
# *    it under the terms of the GNU General Public License as published by   *
# *    the Free Software Foundation, either version 3 of the License, or      *
# *    (at your option) any later version.                                    *
# *                                                                           *
# *    KLog is distributed in the hope that it will be useful,                *
# *    but WITHOUT ANY WARRANTY; without even the implied warranty of         *
# *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
# *    GNU General Public License for more details.                           *
# *                                                                           *
# *    You should have received a copy of the GNU General Public License      *
# *    along with KLog.  If not, see <https://www.gnu.org/licenses/>.         *
# *                                                                           *
# *****************************************************************************/
QT -= gui
QT += core \
    network

VERSION = 0.0.1
DEFINES += APP_VERSION=\\\"$$VERSION\\\"

CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        filemanager.cpp \
        locator.cpp \
        main.cpp \
        mainclass.cpp \
        parsen1mm.cpp \
        parsewsjtx.cpp \
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
    filemanager.h \
    klogdefinitions.h \
    locator.h \
    mainclass.h \
    parsen1mm.h \
    parsewsjtx.h \
    qso.h \
    udpserver.h \
    utilities.h

OTHER_FILES += \
        Changelog \
        COPYING \
        AUTHORS \
        README

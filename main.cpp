/***************************************************************************
                          main.cpp  -  description
                             -------------------
    begin                : aug 2021
    copyright            : (C) 2021 by Jaime Robles
    user                 : jaime@robles.es
 ***************************************************************************/

/*****************************************************************************
 * This file is part of KLogServer                                           *
 *                                                                           *
 *    KLogsServer is free software: you can redistribute it and/or modify    *
 *    it under the terms of the GNU General Public License as published by   *
 *    the Free Software Foundation, either version 3 of the License, or      *
 *    (at your option) any later version.                                    *
 *                                                                           *
 *    KLogserver is distributed in the hope that it will be useful,          *
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *    GNU General Public License for more details.                           *
 *                                                                           *
 *    You should have received a copy of the GNU General Public License      *
 *    along with KLogServer.  If not, see <https://www.gnu.org/licenses/>.   *
 *                                                                           *
 *****************************************************************************/

#include <QCoreApplication>
#include <QCommandLineParser>
#include <QObject>
#include "mainclass.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    app.setApplicationName(QString("KLogServer"));
    app.setOrganizationName("EA4K");
    app.setOrganizationDomain("klog.xyz");
    app.setApplicationVersion(QString(APP_VERSION));
    QStringList arguments;
    QTextStream cout(stdout);

    MainClass main;


    return app.exec();
}

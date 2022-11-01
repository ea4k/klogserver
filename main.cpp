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


void showHelp()
{
    QTextStream cout(stdout);
    cout << "Usage: klog [OPTION]...\n";
    cout << "Options:\n" ;
    cout << "     -?           Display this help\n" ;
    cout << "     -h           Display this help\n";
    cout << "     --help       Display this help\n";
    cout << "     -v           Display program version\n";
    //cout << "     -p port      Defines the UDP port to listen (default 2237)\n";
}

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    app.setApplicationName(QString("KLogServer"));
    app.setOrganizationName("EA4K");
    app.setOrganizationDomain("klog.xyz");
    app.setApplicationVersion(QString(APP_VERSION));
    int port = 2237;
    QStringList arguments;
    QTextStream cout(stdout);
    arguments.clear();
    arguments << app.arguments();
    if (arguments.length()>1)
    {
        if (arguments.contains("-h"))
        {
            showHelp();
        }
        else if (arguments.contains("-?"))
        {
            showHelp();
        }
        else if (arguments.contains("--help"))
        {
            showHelp();
        }
        else if (arguments.contains("-v"))
        {
            cout << "Version: KLogServer-" << app.applicationVersion() << QT_ENDL;
        }
        //else if (arguments.contains("-p"))
        //{
        //    port =
        //}
        else
        {
            showHelp();
        }
        app.quit();
        return 0;
    }
    MainClass main;
    if (port!=2237)
    {
        main.setPort (port);
    }
    return app.exec();
}


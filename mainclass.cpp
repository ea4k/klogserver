/***************************************************************************
                          mainclass.cpp  -  description
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
#include "mainclass.h"

MainClass::MainClass(QObject *parent) : QObject(parent)
{
    fileManager = new FileManager;
    udpserver = new UDPServer;
    udpserver->setNetworkInterface("lo0");
    udpserver->setPort (12060);
    //udpserver->setPort (2237);
    if (udpserver->start())
    {qDebug() << Q_FUNC_INFO << ": Start OK";}
    else
    {
        qDebug() << Q_FUNC_INFO << ": Start NOK";
    }

    //Qt::ConnectionType ctype = Qt::DirectConnection;
    //connect(udpserver, SIGNAL(logged_qso(QSO)), this, SLOT(slotWSJTXQSOReceived(QSO)), ctype);
}



/***************************************************************************
                          parsewsjtx.cpp  -  description
                             -------------------
    begin                : ocy 2021
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
#include "parsewsjtx.h"

ParseWSJTX::ParseWSJTX()
{

}

ParseWSJTX::~ParseWSJTX(){}

void ParseWSJTX::parse(const QByteArray &msg)
{
    qDebug() << "UDPServer::parse: " << msg << QT_ENDL;
    qDebug() <<Q_FUNC_INFO << ": " << QString::fromStdString(msg.toStdString());
    //in >> time_off >> dx_call >> dx_grid >> frequency >> mode >> report_sent >> report_received >>
    //        tx_power >> comments >> name >> time_on >> operatorCall >> de_call >> de_grid >>
    //        exchange_sent >> exchange_received;

    quint32 magic;
    quint32 schema;
    quint32 type;
    QByteArray id;
    QByteArray adifReceived;

    QDateTime time_off, time_on;
    QByteArray dx_call;
    QByteArray operatorCall;
    QByteArray dx_grid;


    QByteArray mode;
    QByteArray report_sent;
    QByteArray report_received;
    QByteArray exchange_sent;
    QByteArray exchange_received;
    QByteArray tx_power;
    QByteArray comments;
    QByteArray name;

    QByteArray report;
    QByteArray tx_mode;

    QByteArray de_call;
    QByteArray de_grid;
    QByteArray sub_mode;

    QDataStream in(msg);
    //QDataStream out(msgOut, QIODevice::ReadWrite);
    in.setVersion(16);
    in.setByteOrder(QDataStream::BigEndian);


    in >> magic >> schema >> type >> id;
    //QByteArray ba4(QByteArray::fromRawData(cart, 6));
    //in.readRawData(type, size)
       qDebug() << "UDPServer::parse: -  Magic = " << QString::number(magic)<< QT_ENDL;
       qDebug() << "UDPServer::parse: - schema = " << QString::number(schema)<< QT_ENDL;
       qDebug() << "UDPServer::parse: -   type = " << QString::number(type)<< QT_ENDL;
       qDebug() << "UDPServer::parse: -   id = " << id << QT_ENDL;


    //if ((magic != 2914831322) || (id != "WSJT-X"))
    if (magic != 2914831322)
    {
        qDebug() << "UDPServer::parse: - Magic BAD FORMAT = " << QString::number(magic)<< QT_ENDL;
        return;
    }

    qDebug() << "UDPServer::parse: TYPE: " << QString::number(type)<< QT_ENDL;
    //QDateTime dateTime, dateTimeOff;
    //QString line;
    switch (type)
    {
        case QSOLogged:
        {
            qDebug() << "UDPServer::parse: -   type = QSOLogged "  << QT_ENDL;

            quint64 frequency = 0; //  In Hz??
            in >> time_off >> dx_call >> dx_grid >> frequency >> mode >> report_sent >> report_received >>
                tx_power >> comments >> name >> time_on >> operatorCall >> de_call >> de_grid >>
                exchange_sent >> exchange_received;
            qDebug() << "UDPServer::parse: QSOLogged -   Time_off = " << time_off.toString("yyyyMMdd-hhmmss") << QT_ENDL;
            qDebug() << "UDPServer::parse: QSOLogged -   DXCall = " << dx_call << QT_ENDL;
            qDebug() << "UDPServer::parse: QSOLogged -   Grid = " << dx_grid << QT_ENDL;
            qDebug() << "UDPServer::parse: QSOLogged -   Freq = " << QString::number(frequency) << QT_ENDL;
            qDebug() << "UDPServer::parse: QSOLogged -   Mode = " << mode << QT_ENDL;
            qDebug() << "UDPServer::parse: QSOLogged -   ReportSent = " << report_sent << QT_ENDL;
            qDebug() << "UDPServer::parse: QSOLogged -   ReportReceived = " << report_received << QT_ENDL;
            qDebug() << "UDPServer::parse: QSOLogged -   TX_PWR = " << tx_power << QT_ENDL;
            qDebug() << "UDPServer::parse: QSOLogged -   Comments = " << comments << QT_ENDL;
            qDebug() << "UDPServer::parse: QSOLogged -   Name = " << name << QT_ENDL;
            qDebug() << "UDPServer::parse: QSOLogged -   Time = " << time_on.toString("yyyyMMdd-hhmmss");
            qDebug() << "UDPServer::parse: QSOLogged -   DeCall = " << de_call << QT_ENDL;
            qDebug() << "UDPServer::parse: QSOLogged -   DeGrid = " << de_grid << QT_ENDL;
            qDebug() << "UDPServer::parse: QSOLogged -   Exch Sent = " << exchange_sent << QT_ENDL;
            qDebug() << "UDPServer::parse: QSOLogged -   Exch Recv = " << exchange_received << QT_ENDL;
            qDebug() << "UDPServer::parse: QSO to be logged: Time_on: " << time_on << QT_ENDL;
            qDebug() << "UDPServer::parse: QSO to be logged: Time_off: " << time_off << QT_ENDL;
                double frequencyDouble = (double)frequency;
                frequencyDouble = frequencyDouble/1000000; // Change to MHz

                QSO qso;
                emit logged_qso(qso);
                break;
            }
        case Close:
            qDebug() << "UDPServer::parse: -   type = Close"  << QT_ENDL;
            //socketServer->close();
            // Emit a signal to close the socket
            qDebug() << "UDPServer::parse: -   type = " << QString::number(type) << " - OUT - Close " << QT_ENDL;
        break;


        default: //NO
               qDebug() << "UDPServer::parse: -   type = " << QString::number(type) << " - ERROR on Type" << QT_ENDL;
        break;

    }
       qDebug() << "UDPServer::parse: - Magic: = " << QString::number(magic)<< QT_ENDL;
}

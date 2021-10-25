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
    //qDebug() << "UDPServer::parse: " << msg << QT_ENDL;
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
    quint64 frequency = 0; //  In Hz??
    double frequencyDouble;

    QByteArray mode;
    QByteArray report_sent;
    QByteArray report_received;
    QByteArray exchange_sent;
    QByteArray exchange_received;
    QByteArray tx_power;
    QByteArray comments;
    QByteArray name;
    //QByteArray time_on; // Note: LOTW uses TIME_ON for their +/- 30-minute time

    QByteArray report;
    QByteArray tx_mode;
    bool tx_enabled = false;
    bool transmitting = false;
    bool decoding = false;

    // WSPRDecode
    bool newDecode = false;
    QTime time;
    qint32 snr;
    double deltaTime = 0.0;
    qint32 drift;
    QByteArray decodedCall, decodedGrid;
    qint32 power;
    bool offAir;

    // DECODE
    QByteArray message;
    bool lowConfidence = false;


    qint32 rx_df = -1;  // Delta frequency
    qint32 tx_df = -1;  // Delta time
    QByteArray de_call;
    QByteArray de_grid;
    bool watchdog_timeout = false;
    QByteArray sub_mode;
    bool fast_mode = false;
    quint8 specialOpMode;
    quint32 freqTolerance;
    quint32 TRPeriod;
    QByteArray confName;


    //QByteArray msgOut;

    QDataStream in(msg);
    //QDataStream out(msgOut, QIODevice::ReadWrite);
    in.setVersion(16);
    in.setByteOrder(QDataStream::BigEndian);


    in >> magic >> schema >> type >> id;
    //QByteArray ba4(QByteArray::fromRawData(cart, 6));
    //in.readRawData(type, size)
       //qDebug() << "UDPServer::parse: -  Magic = " << QString::number(magic)<< QT_ENDL;
       //qDebug() << "UDPServer::parse: - schema = " << QString::number(schema)<< QT_ENDL;
       //qDebug() << "UDPServer::parse: -   type = " << QString::number(type)<< QT_ENDL;
       //qDebug() << "UDPServer::parse: -   id = " << id << QT_ENDL;


    //if ((magic != 2914831322) || (id != "WSJT-X"))
    if (magic != 2914831322)
    {
        //qDebug() << "UDPServer::parse: - Magic BAD FORMAT = " << QString::number(magic)<< QT_ENDL;
        return;
    }

    //qDebug() << "UDPServer::parse: TYPE: " << QString::number(type)<< QT_ENDL;
    //QDateTime dateTime, dateTimeOff;
    //QString line;
    switch (type)
    {
        case Heartbeat:
            //qDebug() << "UDPServer::parse: -   type = " << QString::number(type) << " - OUT/IN - Heartbeat" << QT_ENDL;
        break;
        case Status:
            //qDebug() << "UDPServer::parse: -   type" << QString::number(type) << " - OUT - Status" << QT_ENDL;

        break;
        case Decode:
            //() << "UDPServer::parse: -   type = " << QString::number(type) << " - OUT - Decode" << QT_ENDL;

        break;
        case Clear:
            //qDebug() << "UDPServer::parse: -   type = " << QString::number(type) << " - OUT - Clear" << QT_ENDL;
            //emit clearSignal();
        break;
        case Reply:
            //qDebug() << "UDPServer::parse: -   type = " << QString::number(type) << " - IN - Replay " << QT_ENDL;
        break;
        case QSOLogged:
            //qDebug() << "UDPServer::parse: -   type = QSOLogged "  << QT_ENDL;


        in >> time_off >> dx_call >> dx_grid >> frequency >> mode >> report_sent >> report_received >>
                    tx_power >> comments >> name >> time_on >> operatorCall >> de_call >> de_grid >>
                    exchange_sent >> exchange_received;
            //qDebug() << "UDPServer::parse: QSOLogged -   Time_off = " << time_off.toString("yyyyMMdd-hhmmss") << QT_ENDL;
            //qDebug() << "UDPServer::parse: QSOLogged -   DXCall = " << dx_call << QT_ENDL;
            //qDebug() << "UDPServer::parse: QSOLogged -   Grid = " << dx_grid << QT_ENDL;
            //qDebug() << "UDPServer::parse: QSOLogged -   Freq = " << QString::number(frequency) << QT_ENDL;
            //qDebug() << "UDPServer::parse: QSOLogged -   Mode = " << mode << QT_ENDL;
            //qDebug() << "UDPServer::parse: QSOLogged -   ReportSent = " << report_sent << QT_ENDL;
            //qDebug() << "UDPServer::parse: QSOLogged -   ReportReceived = " << report_received << QT_ENDL;
            //qDebug() << "UDPServer::parse: QSOLogged -   TX_PWR = " << tx_power << QT_ENDL;
            //qDebug() << "UDPServer::parse: QSOLogged -   Comments = " << comments << QT_ENDL;
            //qDebug() << "UDPServer::parse: QSOLogged -   Name = " << name << QT_ENDL;
            //qDebug() << "UDPServer::parse: QSOLogged -   Time = " << time_on.toString("yyyyMMdd-hhmmss") << QT_ENDL;
            //qDebug() << "UDPServer::parse: QSOLogged -   DeCall = " << de_call << QT_ENDL;
            //qDebug() << "UDPServer::parse: QSOLogged -   DeGrid = " << de_grid << QT_ENDL;
            //qDebug() << "UDPServer::parse: QSOLogged -   Exch Sent = " << exchange_sent << QT_ENDL;
            //qDebug() << "UDPServer::parse: QSOLogged -   Exch Recv = " << exchange_received << QT_ENDL;
                //qDebug() << "UDPServer::parse: QSO to be logged: Time_on: " << time_on << QT_ENDL;
                //qDebug() << "UDPServer::parse: QSO to be logged: Time_off: " << time_off << QT_ENDL;
                frequencyDouble = (double)frequency;
                frequencyDouble = frequencyDouble/1000000; // Change to MHz

                //qDebug() << "UDPServer::parse: Data to be logged: Comment: " << comments << QT_ENDL;

                //dateTime.setDate(QDate::currentDate());
                //dateTime.setTime(QTime::fromString(time_on, "hhmmss"));

                //dateTimeOff.setDate(QDate::currentDate());
                //dateTimeOff.setTime(QTime::fromString(time_off, "hhmmss"));

                emit logged_qsos(dx_call);
        break;
        case Close:
            //qDebug() << "UDPServer::parse: -   type = Close"  << QT_ENDL;
            //socketServer->close();
            // Emit a signal to close the socket
            //qDebug() << "UDPServer::parse: -   type = " << QString::number(type) << " - OUT - Close " << QT_ENDL;
        break;
        case Replay:
            //qDebug() << "UDPServer::parse: -   type = Reply"  << QT_ENDL;
               //qDebug() << "UDPServer::parse: -   type = " << QString::number(type) << " - IN - Replay" << QT_ENDL;
        break;
        case HaltTx:
            //qDebug() << "UDPServer::parse: -   type = HaltTx"  << QT_ENDL;
               //qDebug() << "UDPServer::parse: -   type = " << QString::number(type) << " - IN - Halt TX" << QT_ENDL;
        break;
        case FreeText:
            //qDebug() << "UDPServer::parse: -   type = FreeText"  << QT_ENDL;
               //qDebug() << "UDPServer::parse: -   type = " << QString::number(type) << " - IN - Free Text" << QT_ENDL;
        break;
        case WSPRDecode:
            //qDebug() << "UDPServer::parse: -   type = WSPRDecode"  << QT_ENDL;

        break;
        case Location:
            //qDebug() << "UDPServer::parse: -   type = Location"  << QT_ENDL;
        break;
        case LoggedADIF:
           //qDebug() << "UDPServer::parse: -   type = LoggedADIF"  << QT_ENDL;

        break;
        case HighlightCallsign:
            //qDebug() << "UDPServer::parse: -   type = HighlightCallsign"  << QT_ENDL;
        break;
        case SwitchConfiguration:
            //qDebug() << "UDPServer::parse: -   type = SwitchConfiguration"  << QT_ENDL;
        break;
        case Configure:
            //qDebug() << "UDPServer::parse: -   type = Configure"  << QT_ENDL;
        break;
        default: //NO
               //qDebug() << "UDPServer::parse: -   type = " << QString::number(type) << " - ERROR on Type" << QT_ENDL;
        break;

    }
       //qDebug() << "UDPServer::parse: - Magic: = " << QString::number(magic)<< QT_ENDL;
}

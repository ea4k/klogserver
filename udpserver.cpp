/***************************************************************************
                          udpserver.cpp  -  description
                             -------------------
    begin                : oct 2020
    copyright            : (C) 2020 by Jaime Robles
    user                : jaime@robles.es
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

#include "udpserver.h"
#include <QDateTime>
//https://sourceforge.net/p/wsjt/wsjtx/ci/master/tree/UDPExamples/MessageServer.cpp
// Read Network\NetworkMessage.hpp in the WSJT-x sources wsjtx

UDPServer::UDPServer(QObject *parent) :
    QObject(parent)
{
        //qDebug() << "UDPServer::UDPServer"  ;
       //address = QString("127.0.0.1");
    lastQso = new QSO;
    port = 2237;
    haveNetworkInterface = false;
    socketServer = new QUdpSocket(this);
    groupAddress = QHostAddress::Any;
    networkInterface = QNetworkInterface();
       /*
       //if (socketServer->bind(QHostAddress::AnyIPv4, port, QAbstractSocket::ShareAddress))
       if (socketServer->bind(port, QAbstractSocket::ShareAddress))
       {
             //qDebug() << "UDPServer::UDPServer - Multicast group joined OK"  ;
       }
       else
       {
             //qDebug() << "UDPServer::UDPServer - Multicast group joined NOK"  ;
       }
       */
    util = new Utilities;
    logging = false;
    realtime = false;
    parseN1MM = new ParseN1MM;
    parseWSJTX = new ParseWSJTX;

    connect(socketServer,SIGNAL(readyRead()),this,SLOT(slotReadPendingDatagrams()));
    //connect(parseWSJTX,SIGNAL(logged_qso(QSO)),this,SLOT(slotLoggedQSO(QSO)));
    connect(parseN1MM,SIGNAL(logged_qso(QSO*)),this,SLOT(slotLoggedQSO(QSO*)));
}

void UDPServer::slotReadPendingDatagrams()
{
    //qDebug() << Q_FUNC_INFO;
    while (socketServer->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(socketServer->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;
        //qDebug() << "UDPServer::slotReadPendingDatagrams: length = " << QString::number(socketServer->pendingDatagramSize()) ;
        socketServer->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
        parse (datagram);
        //qDebug() << "UDPServer::slotReadPendingDatagrams: = " << datagram ;
    }

    //qDebug() << Q_FUNC_INFO << " - END";
}

bool UDPServer::start()
{
     //qDebug() << "UDPServer::start " ;
    if ( (port>0) && (port<65535) )
    {
         //qDebug() << "UDPServer::start: calling startNow " ;
        return startNow(port, groupAddress);
    }
    else
    {
         //qDebug() << "UDPServer::start FALSE" ;
        return false;
    }
}

bool UDPServer::startNow(quint16 _port, QHostAddress const& _multicast_group_address)
{
     //qDebug() << "UDPServer::startNow ";
    //if ((_port != port) || (_multicast_group_address != groupAddress))
    if (1)
    {
         //qDebug() << "UDPServer::startNow starting...";
        leaveMultiCastGroup();
        if (socketServer->state() == QAbstractSocket::BoundState)
        {
             //qDebug() << "UDPServer::startNow: closing socket";
            socketServer->close();
        }
        groupAddress = _multicast_group_address;
        auto address = _multicast_group_address.isNull ()
                || QAbstractSocket::IPv4Protocol != groupAddress.protocol () ? QHostAddress::Any : QHostAddress::AnyIPv4;
        if (_port && socketServer->bind(groupAddress, _port, QAbstractSocket::ShareAddress | QAbstractSocket::ReuseAddressHint))
        {
            port = _port;
            joinMultiCastGroup();

        }
        else
        {
             //qDebug() << "UDPServer::startNow port = 0";
            port = 0;
        }
    }
    else
    {
        //qDebug() << "UDPServer::startNow exiting... ";
    }
     //qDebug() << "UDPServer::startNow exiting... ";
    return  socketServer->isValid();
}

void UDPServer::joinMultiCastGroup()
{
     //qDebug() << "UDPServer::joinMultiCastGroup: ";
    if (!haveNetworkInterface)
    {
        return;
    }

    if ((socketServer->state() == QAbstractSocket::BoundState) && (!groupAddress.isNull())  && groupAddress.isMulticast()   )
    {
        auto mcast_interface = socketServer->multicastInterface();
        if (( groupAddress.protocol() ==  QAbstractSocket::IPv4Protocol ) && (socketServer->localAddress().protocol() != QAbstractSocket::IPv4Protocol ))
        {
            socketServer->close();
            socketServer->bind(QHostAddress::AnyIPv4, port, QAbstractSocket::ShareAddress | QAbstractSocket::ReuseAddressHint);
            if (socketServer->isValid())
            {
                //qDebug() << "UDPServer::joinMultiCastGroup socket valid";
            }

        }
        bool joined {false};

        /*
        QList<QNetworkInterface> interfaces;
        interfaces.clear();
        interfaces.append(QNetworkInterface::allInterfaces());

        for (int i = 0; i < interfaces.size(); ++i)
        {
            socketServer->setMulticastInterface(interfaces.at(i));
            joined |= socketServer->joinMulticastGroup(groupAddress, interfaces.at(i));
        }
        */

        socketServer->setMulticastInterface(networkInterface);
        joined |= socketServer->joinMulticastGroup(groupAddress, networkInterface);

        if (!joined)
        {
            groupAddress.clear();
        }
        socketServer->setMulticastInterface(mcast_interface);
    }
     //qDebug() << "UDPServer::joinMultiCastGroup - END";
}

void UDPServer::leaveMultiCastGroup()
{
    //qDebug() << "UDPServer::leaveMultiCastGroup";
    if (groupAddress.isNull() && socketServer->state() && groupAddress.isMulticast())
    {
        QList<QNetworkInterface> interfaces;
        interfaces.clear();
        interfaces.append(QNetworkInterface::allInterfaces());
        for (int i = 0; i < interfaces.size(); ++i)
        {
            socketServer->leaveMulticastGroup(groupAddress, interfaces.at(i));
        }
    }
    //qDebug() << "UDPServer::leaveMultiCastGroup - END";
}

bool UDPServer::isStarted()
 {
     return  socketServer->isValid();
 }

void UDPServer::parse(const QByteArray &msg)
{
    //qDebug() << "UDPServer::parse: " << msg ;
    //qDebug() << "UDPServer::parse: " << QString::fromStdString(msg.toStdString());
    //in >> time_off >> dx_call >> dx_grid >> frequency >> mode >> report_sent >> report_received >>
    //        tx_power >> comments >> name >> time_on >> operatorCall >> de_call >> de_grid >>
    //        exchange_sent >> exchange_received;

    quint32 magic;
    quint32 schema;
    quint32 type;
    QByteArray id;

    QDataStream in(msg);
    in.setVersion(16);
    in.setByteOrder(QDataStream::BigEndian);
    in >> magic >> schema >> type >> id;

     //qDebug() << "UDPServer::parse: -  Magic = " << QString::number(magic);
     //qDebug() << "UDPServer::parse: - schema = " << QString::number(schema);
     //qDebug() << "UDPServer::parse: -   type = " << QString::number(type);
     //qDebug() << "UDPServer::parse: -   id = " << id ;

    if (msg.startsWith ("<?xml"))
    {
        //qDebug() << Q_FUNC_INFO << ": N1MM detected! *******************************";

        parseN1MM->parse(msg);
        return;
    }
    else if (magic == 2914831322)
    {
        //qDebug() << "UDPServer::parse: - Magic WSJTX = " << QString::number(magic);

        parseWSJTX->parse(msg);
        return;
    }
    //qDebug() << "UDPServer::parse: TYPE: " << QString::number(type);
}

bool UDPServer::stop()
{
     //qDebug() << "UDPServer::stop";
    socketServer->close();
    if (socketServer->isValid())
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool UDPServer::setPort(const int _port)
{
        //qDebug() << "UDPServer::setPort: " << QString::number(_port) ;
    if ((_port >= 0) && (_port<=65535))
    {
        port = _port;
        return true;
    }
    return false;
}

void UDPServer::setNetworkInterface(const QString &_t)
{
     //qDebug() << "UDPServer::setNetworkInterface: " << _t ;
    QString testInterface;
    testInterface.clear();
    QList<QNetworkInterface> ifaces;
    ifaces.clear();
    ifaces << QNetworkInterface::allInterfaces();
    foreach (QNetworkInterface i, ifaces)
    {
        testInterface = i.humanReadableName() + "-" + i.hardwareAddress();
        if (testInterface.contains(_t))
        {
             //qDebug() << "UDPServer::setNetworkInterface: FOUND! " << testInterface  ;
            if ((i.flags().testFlag(QNetworkInterface::IsUp)) )
            {
                networkInterface = i;
                haveNetworkInterface = true;
            }

        }
    }
}

void UDPServer::setLogging(const bool _t)
{
        //qDebug() << "UDPServer::setLogging: " <<   endl;
    if (_t)
    {
            //qDebug() << "UDPServer::setLogging: TRUE " <<   endl;
    }
    else
    {
            //qDebug() << "UDPServer::setLogging: FALSE" <<   endl;
    }
    logging = _t;
}

void UDPServer::setRealTimeUpdate(const bool _t)
{
        //qDebug() << "UDPServer::setRealTimeUpdate: " <<   endl;
    if (_t)
    {
            //qDebug() << "UDPServer::setRealTimeUpdate: TRUE " <<   endl;
    }
    else
    {
            //qDebug() << "UDPServer::setRealTimeUpdate: FALSE" <<   endl;
    }
       realtime = _t;
}

void UDPServer::slotLoggedQSO(QSO *_qso)
{
    //qDebug() << Q_FUNC_INFO;
    //QSO qso = _qso;

    if (lastQso->isSame (_qso))
    {
        //qDebug() << Q_FUNC_INFO << ": Same QSO, exitting!";
        return;
    }

    lastQso->setCall (_qso->getCall ());
    lastQso->setDateTimeOn (_qso->getDateTimeOn ());
    lastQso->setBand (_qso->getBand ());
    lastQso->setMode (_qso->getMode());

    if (!_qso->isValid ())
    {
        //qDebug() << Q_FUNC_INFO << ": Not valid QSO, exitting!";
        return;
    }

    FileManager fileManager;
    fileManager.saveQSO(_qso);
    _qso->clear ();

    //qDebug() << Q_FUNC_INFO << " - END";
}

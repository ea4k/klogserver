/***************************************************************************
                          parsen1mm.cpp  -  description
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
#include "parsen1mm.h"

ParseN1MM::ParseN1MM()
{
    qso = new QSO();
}

ParseN1MM::~ParseN1MM(){}

void ParseN1MM::parse(const QByteArray &msg)
{
    //qDebug() << Q_FUNC_INFO << ": " << QString::fromStdString(msg.toStdString());
     QXmlStreamReader xml(msg);
     while (!xml.atEnd()) {
        //qDebug() << Q_FUNC_INFO << ": In the while";
         xml.readNext();
        //qDebug() << Q_FUNC_INFO << ": xml.name: " << xml.name();
         if (xml.name().toString() == "contactinfo")
         {
            parseXMLContact (xml); ;
            return;
         }
     }

     if (xml.hasError()) {
        //qDebug() << xml.errorString() << xml.characterOffset();
     }
}

void ParseN1MM::parseXMLContact(QXmlStreamReader &_xml)
{
   //qDebug() << Q_FUNC_INFO;

    qso->clear ();
    while (!_xml.atEnd()) {
       //qDebug() << Q_FUNC_INFO << ": In the while";
        _xml.readNext();
        if (_xml.name ().toString() == "app")
        {
            if (_xml.readElementText () != "N1MM")
            {
               //qDebug() << Q_FUNC_INFO << "Wrong APP!";
                return;
            }
        }
        else if (_xml.name ().toString() == "")
        {}
        else if (_xml.name ().toString() == "contestname")
        {
            qso->setContestId("CQ-WW-SSB");
        }
        else if (_xml.name ().toString() == "contestnr")
        {
            //(_xml.readElementText ())
        }
        else if (_xml.name ().toString() == "timestamp")
        {   // TODO: import date / time
            // YYYY-MM-DD hh:mm:ss
            QString aux = _xml.readElementText ();
           //qDebug() << Q_FUNC_INFO << "timeStamp: " << aux;

            QDateTime dateTime = QDateTime::fromString (aux, "yyyy-MM-dd hh:mm:ss");
            if (dateTime.isValid ())
            {
               //qDebug() << Q_FUNC_INFO << " - QDatetime not valid";
                qso->setDateTimeOn (dateTime);
            }
            else
            {
               //qDebug() << Q_FUNC_INFO << " - QDatetime not valid";
            }
        }
        else if (_xml.name ().toString() == "mycall")
        {
            qso->setStationCallsign (_xml.readElementText ());
        }
        else if (_xml.name ().toString() == "band")
        {   //TODO:  14, 28,...
            QString aux = _xml.readElementText ();
            int freqInt = aux.toInt ();
            qso->setBand (util.getBandFromFreq (freqInt));
        }
        else if (_xml.name ().toString() == "rxfreq")
        {
            qso->setFreqRX ((_xml.readElementText ().toDouble ())/100000);
        }
        else if (_xml.name ().toString() == "txfreq")
        {
            qso->setFreqTX ((_xml.readElementText ().toDouble ())/100000);
        }
        else if (_xml.name ().toString() == "operator")
        {
            qso->setOperatorCallsign (_xml.readElementText ());
        }
        else if (_xml.name ().toString() == "mode")
        {
            QString aux = _xml.readElementText ();
            if ( aux == "USB" )
            {
                qso->setMode ("SSB");
                qso->setSubMode ("USB");
            }
            else if ( aux == "LSB" )
            {
                qso->setMode ("SSB");
                qso->setSubMode ("LSB");
            }
            else
            {
                qso->setMode (aux);
            }
        }
        else if (_xml.name ().toString() == "call")
        {
            qso->setCall (_xml.readElementText ());
        }
        else if (_xml.name ().toString() == "countryprefix")
        {
            qso->setPfx (_xml.readElementText ());
            //qso-> (_xml.readElementText ());
        }
        else if (_xml.name ().toString() == "wpxprefix")
        {
            //qso-> (_xml.readElementText ());
        }
        else if (_xml.name ().toString() == "stationprefix")
        {
            //qso-> (_xml.readElementText ());
        }
        else if (_xml.name ().toString() == "continent")
        {
            qso->setCont (_xml.readElementText ());
        }
        else if (_xml.name ().toString() == "snt")
        {
            qso->setRSTTX (_xml.readElementText ());
        }
        else if (_xml.name ().toString() == "sntnr")
        {
            qso->setSTx ((_xml.readElementText ()).toInt ());
        }
        else if (_xml.name ().toString() == "rcv")
        {
            qso->setRSTRX (_xml.readElementText ());
        }
        else if (_xml.name ().toString() == "rcvnr")
        {
           //qso->setSRx ((_xml.readElementText ()).toInt ());
        }
        else if (_xml.name ().toString() == "gridsquare")
        {
            qso->setGridSquare (_xml.readElementText ());
        }
        else if (_xml.name ().toString() == "exchange1")
        {
            //qso-> (_xml.readElementText ());
        }
        else if (_xml.name ().toString() == "section")
        {
            //qso-> (_xml.readElementText ());
        }
        else if (_xml.name ().toString() == "comment")
        {
            qso->setComment (_xml.readElementText ());
        }
        else if (_xml.name ().toString() == "qth")
        {
            qso->setQTH (_xml.readElementText ());
        }
        else if (_xml.name ().toString() == "name")
        {
            qso->setName (_xml.readElementText ());
        }
        else if (_xml.name ().toString() == "power")
        {
            qso->setTXPwr ((_xml.readElementText ()).toDouble ());
        }
        else if (_xml.name ().toString() == "misctext")
        {
            //qso-> (_xml.readElementText ());
        }
        else if (_xml.name ().toString() == "zone")
        {
            qso->setCQz ((_xml.readElementText ()).toInt ());
            qso->setSRx ((_xml.readElementText ()).toInt ());
        }
        else if (_xml.name ().toString() == "prec")
        {
            qso->setPrecedence (_xml.readElementText ());
        }
        else if (_xml.name ().toString() == "ck")
        {
            //qso-> (_xml.readElementText ());
        }
        else if (_xml.name ().toString() == "ismultiplier1")
        {
            //qso-> (_xml.readElementText ());
        }
        else if (_xml.name ().toString() == "ismultiplier2")
        {
            //qso-> (_xml.readElementText ());
        }
        else if (_xml.name ().toString() == "ismultiplier3")
        {
            //qso-> (_xml.readElementText ());
        }
        else if (_xml.name ().toString() == "points")
        {
            qso->setPoints((_xml.readElementText ()).toInt ());

            //qso-> (_xml.readElementText ());
        }
        else if (_xml.name ().toString() == "radionr")
        {
            //qso-> (_xml.readElementText ());
        }
        else if (_xml.name ().toString() == "run1run2")
        {
            //qso-> (_xml.readElementText ());
        }
        else if (_xml.name ().toString() == "RoverLocation")
        {
            //qso-> (_xml.readElementText ());
        }
        else if (_xml.name ().toString() == "RadioInterfaced")
        {
            //qso-> (_xml.readElementText ());
        }
        else if (_xml.name ().toString() == "NetworkedCompNr")
        {
            //qso-> (_xml.readElementText ());
        }
        else if (_xml.name ().toString() == "IsOriginal")
        {
            //qso-> (_xml.readElementText ());
        }
        else if (_xml.name ().toString() == "NetBiosName")
        {
            //qso-> (_xml.readElementText ());
        }
        else if (_xml.name ().toString() == "ID")
        {
            //qso-> (_xml.readElementText ());
        }else if (_xml.name ().toString() == "IsRunQSO")
        {
            //qso-> (_xml.readElementText ());
        }
        else if (_xml.name ().toString() == "StationName")
        { //Not ADIF
            //qso-> (_xml.readElementText ());
        }
        else if (_xml.name ().toString() == "IsClaimedQso")
        {
            //qso-> (_xml.readElementText ());
        }else if (_xml.name ().toString() == "contactinfo")
        {
            //qso-> (_xml.readElementText ());
        }
        else
        {
           //qDebug() << Q_FUNC_INFO << ": Unknown name: " << _xml.name ();
        }
       //qDebug() << Q_FUNC_INFO << ": name: " << _xml.name ();
       //qDebug() << Q_FUNC_INFO << ": text: " << _xml.text ();
       //qDebug() << Q_FUNC_INFO << ": readElementtext: " << _xml.readElementText ();
    }
    emit logged_qso (qso);
}

/*

*/

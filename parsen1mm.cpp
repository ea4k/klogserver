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

ParseN1MM::~ParseN1MM()
{
    delete qso;
}

void ParseN1MM::parse(const QByteArray &msg)
{
    //qDebug() << Q_FUNC_INFO << ": " << QString::fromStdString(msg.toStdString());
     QXmlStreamReader xml(msg);
     while (!xml.atEnd()) {
        //qDebug() << Q_FUNC_INFO << ": In the while";
         xml.readNext();
        //qDebug() << Q_FUNC_INFO << ": xml.name: " << xml.name();
         if (xml.name() == QLatin1String("contactinfo"))
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
        if (_xml.name () == QLatin1String("app"))
        {
            if (_xml.readElementText () != "N1MM")
            {
               //qDebug() << Q_FUNC_INFO << "Wrong APP!";
                return;
            }
        }
        else if (_xml.name () == QLatin1String(""))
        {}
        else if (_xml.name () == QLatin1String("contestname"))
        {
            qso->setContestId("CQ-WW-SSB");
        }
        else if (_xml.name () == QLatin1String("contestnr"))
        {
            //(_xml.readElementText ())
        }
        else if (_xml.name () == QLatin1String("timestamp"))
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
        else if (_xml.name () == QLatin1String("mycall"))
        {
            qso->setStationCallsign (_xml.readElementText ());
        }
        else if (_xml.name () == QLatin1String("band"))
        {   //TODO:  14, 28,...
            QString aux = _xml.readElementText ();
            int freqInt = aux.toInt ();
            qso->setBand (util.getBandFromFreq (freqInt));
        }
        else if (_xml.name () == QLatin1String("rxfreq"))
        {
            qso->setFreqRX ((_xml.readElementText ().toDouble ())/100000);
        }
        else if (_xml.name () == QLatin1String("txfreq"))
        {
            qso->setFreqTX ((_xml.readElementText ().toDouble ())/100000);
        }
        else if (_xml.name () == QLatin1String("operator"))
        {
            qso->setOperatorCallsign (_xml.readElementText ());
        }
        else if (_xml.name () == QLatin1String("mode"))
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
        else if (_xml.name () == QLatin1String("call"))
        {
            qso->setCall (_xml.readElementText ());
        }
        else if (_xml.name () == QLatin1String("countryprefix"))
        {
            qso->setPfx (_xml.readElementText ());
            //qso-> (_xml.readElementText ());
        }
        else if (_xml.name () == QLatin1String("wpxprefix"))
        {
            //qso-> (_xml.readElementText ());
        }
        else if (_xml.name () == QLatin1String("stationprefix"))
        {
            //qso-> (_xml.readElementText ());
        }
        else if (_xml.name () == QLatin1String("continent"))
        {
            qso->setCont (_xml.readElementText ());
        }
        else if (_xml.name () == QLatin1String("snt"))
        {
            qso->setRSTTX (_xml.readElementText ());
        }
        else if (_xml.name () == QLatin1String("sntnr"))
        {
            qso->setSTx ((_xml.readElementText ()).toInt ());
        }
        else if (_xml.name () == QLatin1String("rcv"))
        {
            qso->setRSTRX (_xml.readElementText ());
        }
        else if (_xml.name () == QLatin1String("rcvnr"))
        {
           //qso->setSRx ((_xml.readElementText ()).toInt ());
        }
        else if (_xml.name () == QLatin1String("gridsquare"))
        {
            qso->setGridSquare (_xml.readElementText ());
        }
        else if (_xml.name () == QLatin1String("exchange1"))
        {
            //qso-> (_xml.readElementText ());
        }
        else if (_xml.name () == QLatin1String("section"))
        {
            //qso-> (_xml.readElementText ());
        }
        else if (_xml.name () == QLatin1String("comment"))
        {
            qso->setComment (_xml.readElementText ());
        }
        else if (_xml.name () == QLatin1String("qth"))
        {
            qso->setQTH (_xml.readElementText ());
        }
        else if (_xml.name () == QLatin1String("name"))
        {
            qso->setName (_xml.readElementText ());
        }
        else if (_xml.name () == QLatin1String("power"))
        {
            qso->setTXPwr ((_xml.readElementText ()).toDouble ());
        }
        else if (_xml.name () == QLatin1String("misctext"))
        {
            //qso-> (_xml.readElementText ());
        }
        else if (_xml.name () == QLatin1String("zone"))
        {
            qso->setCQz ((_xml.readElementText ()).toInt ());
            qso->setSRx ((_xml.readElementText ()).toInt ());
        }
        else if (_xml.name () == QLatin1String("prec"))
        {
            qso->setPrecedence (_xml.readElementText ());
        }
        else if (_xml.name () == QLatin1String("ck"))
        {
            //qso-> (_xml.readElementText ());
        }
        else if (_xml.name () == QLatin1String("ismultiplier1"))
        {
            //qso-> (_xml.readElementText ());
        }
        else if (_xml.name () == QLatin1String("ismultiplier2"))
        {
            //qso-> (_xml.readElementText ());
        }
        else if (_xml.name () == QLatin1String("ismultiplier3"))
        {
            //qso-> (_xml.readElementText ());
        }
        else if (_xml.name () == QLatin1String("points"))
        {
            qso->setPoints((_xml.readElementText ()).toInt ());

            //qso-> (_xml.readElementText ());
        }
        else if (_xml.name () == QLatin1String("radionr"))
        {
            //qso-> (_xml.readElementText ());
        }
        else if (_xml.name () == QLatin1String("run1run2"))
        {
            //qso-> (_xml.readElementText ());
        }
        else if (_xml.name () == QLatin1String("RoverLocation"))
        {
            //qso-> (_xml.readElementText ());
        }
        else if (_xml.name () == QLatin1String("RadioInterfaced"))
        {
            //qso-> (_xml.readElementText ());
        }
        else if (_xml.name () == QLatin1String("NetworkedCompNr"))
        {
            //qso-> (_xml.readElementText ());
        }
        else if (_xml.name () == QLatin1String("IsOriginal"))
        {
            //qso-> (_xml.readElementText ());
        }
        else if (_xml.name () == QLatin1String("NetBiosName"))
        {
            //qso-> (_xml.readElementText ());
        }
        else if (_xml.name () == QLatin1String("ID"))
        {
            //qso-> (_xml.readElementText ());
        }else if (_xml.name () == QLatin1String("IsRunQSO"))
        {
            //qso-> (_xml.readElementText ());
        }
        else if (_xml.name () == QLatin1String("StationName"))
        { //Not ADIF
            //qso-> (_xml.readElementText ());
        }
        else if (_xml.name () == QLatin1String("IsClaimedQso"))
        {
            //qso-> (_xml.readElementText ());
        }else if (_xml.name () == QLatin1String("contactinfo"))
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

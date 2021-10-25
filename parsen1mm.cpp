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

ParseN1MM::ParseN1MM(){}

ParseN1MM::~ParseN1MM(){}

void ParseN1MM::parse(const QByteArray &msg)
{
     qDebug() << Q_FUNC_INFO << ": " << QString::fromStdString(msg.toStdString());
}
/*
XML received
<?xml version=\"1.0\" encoding=\"utf-8\"?>\r\n
<contactinfo>\r\n\t
    <app>N1MM</app>\r\n\t
    <contestname>CQWWSSB</contestname>\r\n\t
    <contestnr>32</contestnr>\r\n\t
    <timestamp>2021-10-25 19:06:16</timestamp>\r\n\t
    <mycall>EA4K</mycall>\r\n\t
    <band>14</band>\r\n\t
    <rxfreq>1420000</rxfreq>\r\n\t
    <txfreq>1420000</txfreq>\r\n\t
    <operator>EA4K</operator>\r\n\t
    <mode>USB</mode>\r\n\t
    <call>EA4TV</call>\r\n\t
    <countryprefix>EA</countryprefix>\r\n\t
    <wpxprefix>EA4</wpxprefix>\r\n\t
    <stationprefix>EA4K</stationprefix>\r\n\t
    <continent>EU</continent>\r\n\t
    <snt>59</snt>\r\n\t
    <sntnr>3</sntnr>\r\n\t
    <rcv>59</rcv>\r\n\t
    <rcvnr>0</rcvnr>\r\n\t
    <gridsquare></gridsquare>\r\n\t
    <exchange1></exchange1>\r\n\t
    <section></section>\r\n\t
    <comment></comment>\r\n\t
    <qth></qth>\r\n\t
    <name></name>\r\n\t
    <power></power>\r\n\t
    <misctext></misctext>\r\n\t
    <zone>14</zone>\r\n\t
    <prec></prec>\r\n\t
    <ck>0</ck>\r\n\t
    <ismultiplier1>0</ismultiplier1>\r\n\t
    <ismultiplier2>0</ismultiplier2>\r\n\t
    <ismultiplier3>0</ismultiplier3>\r\n\t
    <points>0</points>\r\n\t
    <radionr>1</radionr>\r\n\t
    <run1run2>1</run1run2>\r\n\t
    <RoverLocation></RoverLocation>\r\n\t
    <RadioInterfaced>0</RadioInterfaced>\r\n\t
    <NetworkedCompNr>0</NetworkedCompNr>\r\n\t
    <IsOriginal>True</IsOriginal>\r\n\t
    <NetBiosName>DESKTOP-B4L8KB8</NetBiosName>\r\n\t
    <IsRunQSO>0</IsRunQSO>\r\n\t
    <StationName>DESKTOP-B4L8KB8</StationName>\r\n\t
    <ID>04abc2ae70704bca9213789eaa5b62e9</ID>\r\n\t
    <IsClaimedQso>1</IsClaimedQso>\r\n
</contactinfo>
*/

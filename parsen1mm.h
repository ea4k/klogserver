/***************************************************************************
                          parsen1mm.h  -  description
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
#ifndef PARSEN1MM_H
#define PARSEN1MM_H
#include <QObject>
#include <QXmlStreamReader>
#include <QtDebug>
#include "qso.h"

class ParseN1MM  : public QObject
{
    Q_OBJECT
public:

    ParseN1MM();
    ~ParseN1MM();
    void parse(const QByteArray &msg);

private:
    void parseXMLContact(QXmlStreamReader &_xml);
    QSO *qso;
signals:
    void logged_qso (QSO *_qso);
};

#endif // PARSEN1MM_H

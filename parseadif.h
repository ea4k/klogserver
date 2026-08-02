/***************************************************************************
                          parseadif.h  -  description
                             -------------------
    begin                : aug 2026
    copyright            : (C) 2026 by Jaime Robles
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
#ifndef PARSEADIF_H
#define PARSEADIF_H

// Parses the QSOs that KLog sends to KLogServer.
//
// KLog sends one QSO per datagram, as a plain ADIF record with all the ADIF
// fields that have data, so the record is passed along untouched to be saved:
// the QSO class only models a few fields and rebuilding the record from it
// would drop all the others.

#include <QObject>
#include <QPair>
#include <QString>
#include <QStringList>
#include <QtGlobal>
#include "utilities.h"
#include "qso.h"

class ParseADIF : public QObject
{
    Q_OBJECT
public:
    ParseADIF();
    ~ParseADIF();

    // True when the datagram looks like an ADIF record instead of WSJT-X or N1MM data
    static bool isADIF(const QByteArray &_msg);

    void parse(const QByteArray &_msg);

private:
    // Returns the fields of the first complete record found, or an empty list
    // if there is no <EOR>. _record gets the record just as it was received.
    QList<QPair<QString, QString> > getFields(const QString &_data, QString &_record) const;

    QSO *qso;
    Utilities util;

signals:
    // The record is emitted verbatim; the QSO is provided to detect duplicates
    void logged_adif (const QString &_adifRecord, QSO *_qso);
};

#endif // PARSEADIF_H

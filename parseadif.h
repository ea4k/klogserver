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
// KLog sends one QSO per datagram, as an ADIF record with all the ADIF fields
// that have data, so the record is passed along untouched to be saved: the QSO
// class only models a few fields and rebuilding the record from it would drop
// all the others.
//
// The datagram has the same layout that WSJT-X uses:
//
//     magic (quint32) | schema (quint32) | type (quint32) | id (QByteArray)
//
// followed by the payload of the message, that for an ADIFLogged message is
// the ADIF record as a QByteArray. Everything is big endian. What tells a KLog
// datagram from a WSJT-X one is the magic number.

#include <QDataStream>
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
    // Identifies a datagram sent by KLog, as 2914831322 identifies a WSJT-X one
    static constexpr quint32 magicNumber = 1999030602;

    // Messages that KLog sends. The numbers are the ones that WSJT-X uses for
    // the equivalent messages, as the layout of the datagram is the same one.
    enum KLogMessageType
    {
        ADIFLogged = 12     // A logged QSO, as an ADIF record
    };

    ParseADIF();
    ~ParseADIF();

    void parse(const QByteArray &_msg);

private:
    void parseADIFRecord(const QString &_data);

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

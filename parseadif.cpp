/***************************************************************************
                          parseadif.cpp  -  description
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
#include "parseadif.h"

ParseADIF::ParseADIF()
{
    qso = new QSO();
}

ParseADIF::~ParseADIF(){}

bool ParseADIF::isADIF(const QByteArray &_msg)
{
    const QByteArray msg = _msg.trimmed();
    if (!msg.startsWith('<'))
        return false;
    if (msg.startsWith("<?xml"))    // N1MM
        return false;
    return msg.toUpper().contains("<EOR>");
}

void ParseADIF::parse(const QByteArray &_msg)
{
   //qDebug() << Q_FUNC_INFO << ": " << _msg;
    QString record;
    const QList<QPair<QString, QString> > fields = getFields(QString::fromUtf8(_msg), record);
    if (fields.isEmpty())
    {
       //qDebug() << Q_FUNC_INFO << ": No complete ADIF record received";
        return;
    }

    // The QSO is filled just to know whether this QSO has already been saved:
    // the record that will be saved is the one that has been received.
    qso->clear();
    double freq = 0.0;
    bool haveBand = false;
    for (const QPair<QString, QString> &field : fields)
    {
        if (field.first == "BAND")
            haveBand = true;
        else if (field.first == "FREQ")
            freq = field.second.toDouble();
        qso->setData(QString("<%1:%2>%3").arg(field.first, QString::number(field.second.length()), field.second));
    }

    if ((!haveBand) && (freq > 0.0))
        qso->setBand(util.getBandFromFreq(static_cast<int>(freq)));

    emit logged_adif(record, qso);
}

QList<QPair<QString, QString> > ParseADIF::getFields(const QString &_data, QString &_record) const
{
    QList<QPair<QString, QString> > fields;
    _record.clear();
    int recordStart = -1;
    int i = 0;

    while (i < _data.length())
    {
        const int open = _data.indexOf('<', i);
        if (open < 0)
            break;
        const int close = _data.indexOf('>', open);
        if (close < 0)
            break;

        const QString spec = _data.mid(open + 1, close - open - 1);
        const QString name = spec.section(':', 0, 0).trimmed().toUpper();

        if (name == "EOR")
        {
            if (recordStart < 0)
                break;                  // An <EOR> without any field is not a QSO
            _record = _data.mid(recordStart, close + 1 - recordStart);
            return fields;
        }
        if (name == "EOH")
        {   // Header of an ADIF file: the QSOs start just after it
            fields.clear();
            recordStart = -1;
            i = close + 1;
            continue;
        }

        // <FIELD:length[:type]>data, the length tells where the data ends, so
        // values containing blanks or '<' are read as they were written.
        bool ok = false;
        const int length = spec.section(':', 1, 1).toInt(&ok);
        if ((!ok) || (length < 0) || ((close + 1 + length) > _data.length()))
            break;                      // Not an ADIF field or a truncated datagram

        if (recordStart < 0)
            recordStart = open;
        fields.append(qMakePair(name, _data.mid(close + 1, length)));
        i = close + 1 + length;
    }

    fields.clear();                     // No <EOR> found: the record is not complete
    return fields;
}

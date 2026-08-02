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

ParseADIF::~ParseADIF()
{
    delete qso;
}

void ParseADIF::parse(const QByteArray &_msg)
{
   //qDebug() << Q_FUNC_INFO << ": " << _msg;
    quint32 magic;
    quint32 schema;
    quint32 type;
    QByteArray id;
    QByteArray adifReceived;

    QDataStream in(_msg);
    in.setVersion(16);      // Qt_5_4, the stream version used by the schema 3
    in.setByteOrder(QDataStream::BigEndian);

    in >> magic >> schema >> type >> id;
   //qDebug() << Q_FUNC_INFO << ": -  Magic = " << QString::number(magic);
   //qDebug() << Q_FUNC_INFO << ": - schema = " << QString::number(schema);
   //qDebug() << Q_FUNC_INFO << ": -   type = " << QString::number(type);
   //qDebug() << Q_FUNC_INFO << ": -     id = " << id;

    if (magic != magicNumber)
    {
       //qDebug() << Q_FUNC_INFO << ": - Magic BAD FORMAT = " << QString::number(magic);
        return;
    }

    switch (type)
    {
        case ADIFLogged:
        {
            in >> adifReceived;
            parseADIFRecord(QString::fromUtf8(adifReceived));
            break;
        }
        default:
           //qDebug() << Q_FUNC_INFO << ": -   type = " << QString::number(type) << " - Unknown type";
        break;
    }
}

void ParseADIF::parseADIFRecord(const QString &_data)
{
    QString record;
    const QList<QPair<QString, QString> > fields = getFields(_data, record);
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

    // The frequency is passed in MHz as it is: truncating it to a whole number
    // of MHz leaves it outside the limits of the bands that do not start on one
    // (160m, 80m, 60m, 17m, 12m, 630m and 2190m), and no band is found for them.
    if ((!haveBand) && (freq > 0.0))
        qso->setBand(util.getBandFromFreq(freq));

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

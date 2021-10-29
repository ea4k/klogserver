/***************************************************************************
                          parsewsjtx.h  -  description
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
#ifndef PARSEWSJTX_H
#define PARSEWSJTX_H

#include <QObject>
#include <QtGlobal>
#include <QString>
#include <QDir>
#include <QDateTime>
#include <QDate>
#include <QTime>
#include "locator.h"
#include <QtDebug>
#include <QDataStream>
#include "utilities.h"
#include "qso.h"

#include "klogdefinitions.h"

enum Type
    {
      Heartbeat,
      Status,
      Decode,
      Clear,
      Reply,
      QSOLogged,
      Close,
      Replay,
      HaltTx,
      FreeText,
      WSPRDecode,
      Location,
      LoggedADIF,
      HighlightCallsign,
      SwitchConfiguration,
      Configure,
      maximum_message_type_     // ONLY add new message types
                                // immediately before here
};

class ParseWSJTX : public QObject
{
    Q_OBJECT
public:
    ParseWSJTX();
    ~ParseWSJTX();
    void parse(const QByteArray &msg);

private:

signals:
    void logged_qso (QSO &_qso);
};

#endif // PARSEWSJTX_H

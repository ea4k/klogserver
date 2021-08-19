/***************************************************************************
                          filemanager.cpp  -  description
                             -------------------
    begin                : aug 2021
    copyright            : (C) 2021 by Jaime Robles
    user                : jaime@robles.es
 ***************************************************************************/

/*****************************************************************************
 * This file is part of KLogServer                                           *
 *                                                                           *
 *    KLog is free software: you can redistribute it and/or modify           *
 *    it under the terms of the GNU General Public License as published by   *
 *    the Free Software Foundation, either version 3 of the License, or      *
 *    (at your option) any later version.                                    *
 *                                                                           *
 *    KLog is distributed in the hope that it will be useful,                *
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *    GNU General Public License for more details.                           *
 *                                                                           *
 *    You should have received a copy of the GNU General Public License      *
 *    along with KLog.  If not, see <https://www.gnu.org/licenses/>.         *
 *                                                                           *
 *****************************************************************************/
#include "filemanager.h"

FileManager::FileManager()
{
    fileName = "log.adi";
}

bool FileManager::saveQSO(QSO _qso)
{
    qDebug() << Q_FUNC_INFO << ": " << _qso.getCall();
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly | QIODevice::Append))
    {
        QTextStream out(&file);
        out << "<CALL:" << QString::number(_qso.getCall().length()) << ">" << _qso.getCall();
        out << "<MODE:" << QString::number(_qso.getMode().length()) << ">" << _qso.getMode();
    }
    else
    {
        qDebug() << Q_FUNC_INFO << ": Failed to open the file to append";
        return false;
    }
    return true;
}

bool FileManager::setFileName (const QString &_fn)
{
    fileName = _fn;
    return true;
}

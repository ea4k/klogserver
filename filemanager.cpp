/***************************************************************************
                          filemanager.cpp  -  description
                             -------------------
    begin                : aug 2021
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
#include "filemanager.h"

FileManager::FileManager()
{
    fileName = "log.adi";
}

bool FileManager::saveQSO(QSO *_qso)
{

    //qDebug() << Q_FUNC_INFO << ": " << _qso->getCall();
    QFile file(fileName);
    if (!(file.open(QIODevice::WriteOnly | QIODevice::Append)))
    {
        //qDebug() << Q_FUNC_INFO << ": Failed to open the file to append";
        return false;
    }

    QString aux = _qso->getADIF();
    if (aux.length()<3)
    {
        //qDebug() << Q_FUNC_INFO << ": Empty QSO, not saved";
        return false;
    }
    //qDebug() << Q_FUNC_INFO << ": We have the ADIF: " << aux;
    QTextStream out(&file);
    out << aux << Qt::endl;
    out.flush ();
    //qDebug() << Q_FUNC_INFO << ": " << aux;
    return true;
}

bool FileManager::setFileName (const QString &_fn)
{
    fileName = _fn;
    return true;
}

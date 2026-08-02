/***************************************************************************
                          utilities.cpp  -  description
                             -------------------
    begin                : jun 2015
    copyright            : (C) 2015 by Jaime Robles
    email                : jaime@robles.es
 ***************************************************************************/

/*****************************************************************************
 * This file is part of KLog.                                                *
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
#include "utilities.h"
#include "callsign.h"

Utilities::Utilities()
{
   //qDebug() << "Utilities::Utilities"  ;
    init();

    //palRed.setColor(QPalette::Text, Qt::red);
    //palBlack.setColor(QPalette::Text, Qt::black);
   //qDebug() << "Utilities::Utilities - END"  ;
}

Utilities::~Utilities(){}

void Utilities::init()
{
    softwareVersion = "0.0";
    darkMode = false;
    callValidation = true;
}

void Utilities::setVersion(const QString &_v)
{
      //qDebug() << "Utilities::setVersion: " << _v ;
    softwareVersion = _v;
}

QString Utilities::getVersion()
{
    return softwareVersion;
}

double Utilities::getVersionDouble()
{
   //qDebug() << "Utilities::getVersionDouble: " << softwareVersion ;
    if (softwareVersion.count('.')>1)
    {
        QString first = softwareVersion.section('.', 0, 0);
        int pos = softwareVersion.indexOf('.');

        QString decimals = softwareVersion.section('.', pos, -1);
        decimals.remove('.');
        first = first + "." + decimals;
          //qDebug() << "Utilities::getVersionDouble - returning: "  << first ;
        return first.toDouble();
    }
      //qDebug() << "Utilities::getVersionDouble: no points detected" ;
    return softwareVersion.toDouble();
}

int Utilities::getProgresStepForDialog(int totalSteps)
{
      //qDebug() << "Utilities::getProgresStepForDialog";
    if (totalSteps <=100)
        return 1;
    else if (totalSteps <=1000)
        return 5;
    else if (totalSteps <=4000)
        return 10;
    else if (totalSteps <=5000)
        return 15;
    else if (totalSteps <=7000)
        return 20;
    else if (totalSteps <=9999)
        return 25;
    else if (totalSteps <=20000)
        return 100;
    else
        return 250;
}

bool Utilities::trueOrFalse(const QString &_s)
{// reads a String and return true if s.upper()== TRUE :-)
        //qDebug() << "Utilities::trueOrFalse: " << _s ;

    if ( (_s.toUpper()) == "TRUE")
    {
        return true;
    }
    else
    {
        return false;
    }
    //return false;
}

QChar Utilities::boolToCharToSQLite(const bool _b)
{
    if (_b)
    {
        return 'Y';
    }
    else
    {
        return 'N';
    }
}

QString Utilities::boolToQString(const bool _b)
{
    if (_b)
    {
        return "True";
    }
    else
    {
        return "False";
    }
}

QString Utilities::checkAndFixASCIIinADIF(const QString &_data)
{
   //qDebug() << "SetupDialog::checkAndFixASCIIinADIF " << _data ;
// This function is not really working with ASCII but with Unicode
//TODO: this function is also in the FileManager class. Maybe I should call that one and keep just one copy
    ushort unicodeVal;
    QString st = _data;
    QString newString;
    newString.clear();
    for(int i=0; i < st.length(); i++)
    {
    // Get unicode VALUE into unicodeVal
        unicodeVal = (st.at(i)).unicode();
        if ((20 <= unicodeVal ) && (unicodeVal <= 126))
        {
            newString.append(st.at(i));
        }
            //qDebug() << "SetupDialog::checkAndFixunicodeinADIF: " << st.at(i) <<" = " << QString::number(unicodeVal) ;
    }
    // Show into another lineEdit
    return newString;
}

void Utilities::printQString(const QStringList &_qs)
{
       //qDebug() << "Utilities::printQString: COMMENT THIS CALL BEFORE RELEASING" ;
    if (_qs.length()<1)
    {
           //qDebug() << "Utilities::printQString: EMPTY QStringList received!!" ;
        return;
    }
    for (int i=0; i<_qs.length()-1;i++)
    {
           //qDebug() << _qs.at(i) << "/" ;
    }
       //qDebug() << _qs.at(_qs.length()-1) ;
}

QString Utilities::getGlobalAgent(const QString &_klogversion)
{
    return QString("KLog-%1").arg(_klogversion);
}

QString Utilities::getAgent(const QString &_klogversion)
{
    QString version;
    QString ops;
    version = _klogversion;

#if defined(Q_OS_WIN32)
    ops = "KLog-Win32-";
#elif defined(Q_OS_WIN64)
    ops = "KLog-Win64-";
#elif defined(Q_OS_LINUX)
    ops = "KLog-Linux-";
#elif defined(Q_OS_WIN)
    ops = "KLog-Win-"+ version;
#elif defined(Q_OS_MACOS)
    ops = "KLog-macOS-";
#elif defined(Q_OS_OSX)
    ops = "KLog-OSX-";
#elif defined(Q_OS_MAC)
    ops = "KLog-MAC-";
#elif defined(Q_OS_DARWIN)
    ops = "KLog-DARWIN-";
#elif defined(Q_OS_AIX)
    ops = "KLog-aix-";
#elif defined(Q_OS_ANDROID)
    ops = "KLog-android-";
//#elif defined(Q_OS_BSD4)
//    ops = "KLog-bsd4-";
#elif defined(Q_OS_BSDI)
    ops = "KLog-bsdi-";
#elif defined(Q_OS_CYGWIN)
    ops = "KLog-cygwin-";
#elif defined(Q_OS_DARWIN)
    ops = "KLog-darwin-";
#elif defined(Q_OS_DGUX)
    ops = "KLog-dgux-";
#elif defined(Q_OS_DYNIX)
    ops = "KLog-dynix-";
#elif defined(Q_OS_FREEBSD)
    ops = "KLog-freebsd-";
#elif defined(Q_OS_HPUX)
    ops = "KLog-hpux-";
#elif defined(Q_OS_IOS)
    ops = "KLog-ios-";
#elif defined(Q_OS_IRIX)
    ops = "KLog-irix-";
#elif defined(Q_OS_LYNX)
    ops = "KLog-lynx-";
#elif defined(Q_OS_NETBSD)
    ops = "KLog-netbsd-";
#elif defined(Q_OS_OPENBSD)
    ops = "KLog-openbsd-";
#elif defined(Q_OS_OSF)
    ops = "KLog-osf-";
#elif defined(Q_OS_QNX)
    ops = "KLog-qnx-";
#elif defined(Q_OS_SCO)
    ops = "KLog-sco-";
#elif defined(Q_OS_SOLARIS)
    ops = "KLog-solaris-";
#elif defined(Q_OS_TVOS)
    ops = "KLog-tvos-";
#elif defined(Q_OS_UNIX)
    ops = "KLog-unix-";
#elif defined(Q_OS_UNIXWARE)
    ops = "KLog-unixware-";
#elif defined(Q_OS_WHATCHOS)
    ops = "KLog-whatchos-";
#elif defined(Q_OS_WINRT)
    ops = "KLog-winrt-";
#else
    ops = "KLog-Other-";
#endif

    return ops+version;

    //return "KLog-Unknown-" + version;
}

QString Utilities::getHomeDir()
{
//TODO: To be removed when the defaultDir is saved in the config file
#if defined(Q_OS_WIN)
        //qDebug() << "WINDOWS DETECTED!: "  << QDir::homePath() + "/klog" ;
    return QDir::homePath()+"/klog";  // We create the \klog for the logs and data

#else
        //qDebug() << "NO WINDOWS DETECTED!"  ;
    return QDir::homePath()+"/.klog";  // We create the ~/.klog for the logs and data
#endif
}

QString Utilities::getDefaultRST(const QString &_m)
{
  //qDebug() << "Utilities::getDefaultRST: " << _m ;

   if ((_m == "SSB") || (_m== "LSB") || (_m=="USB") )
   {
       //qDebug() << "MainWindow::setRSTToMode: Detected SSB/LSB/USB"  ;
       return "59";
   }
   else if ((_m == "CW") || (_m == "RTTY"))
   {
       return "599";
   }
   else if (_m == "PSK31")
   {
       return "599";
   }
   else if ( (_m.contains("FT", Qt::CaseInsensitive)) || (_m.contains("JT", Qt::CaseInsensitive)) || (_m.contains("QRA64", Qt::CaseInsensitive)) || (_m.contains("JS", Qt::CaseInsensitive)))
   {
        return "0";
   }
   else
   { // By default SSB RST is configured but anything could be added
        return "59";
   }
}

QStringList Utilities::getDefaultLogFields()
{
    QStringList fields;
    fields.clear();
    fields << "qso_date" << "call" << "rst_sent" << "rst_rcvd" << "bandid" << "modeid" << "comment";
    return fields;
}

QString Utilities::getKLogDefaultDatabaseFile()
{
//TODO: To be removed when the defaultDir is saved in the config file
    return getHomeDir() ;
}

QString Utilities::getKLogDBFile()
{
       //qDebug() << "Utilities::getKLogDBFile: start " ;

    dbPath = getKLogDefaultDatabaseFile();
    QFile file(getCfgFile());

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))  /* Flawfinder: ignore */
    {
        //return dbPath;
        //return getKLogDatabaseFile(dbPath);
    }
    else
    {
        while (!file.atEnd()) {
            QByteArray line = file.readLine();
            processConfigLine(line);
        }

        if (dbPath.length()<1)
        {
            dbPath = getKLogDefaultDatabaseFile();
        }
    }
      //qDebug() << "Utilities::getKLogDBFile: path to use: " << dbPath ;
    return dbPath + "/logbook.dat";
}

QString Utilities::getKLogDBBackupFile()
{
       //qDebug() << "Utilities::getKLogDBFile: start " ;

    dbPath = getKLogDefaultDatabaseFile();
    QFile file(getCfgFile());

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) /* Flawfinder: ignore */
    {
        //return dbPath;
        //return getKLogDatabaseFile(dbPath);
    }
    else
    {
        while (!file.atEnd()) {
            QByteArray line = file.readLine();
            processConfigLine(line);
        }
        if (dbPath.length()<1)
        {
            dbPath = getKLogDefaultDatabaseFile();
        }
    }
      //qDebug() << "Utilities::getKLogDBFile: path to use: " << dbPath ;
    return dbPath + "/" + QDateTime::currentDateTime().toString("yyyyMMdd-hhmmss") + "-backup-logbook.dat" ;
}

bool Utilities::processConfigLine(const QString &_line)
{
            //qDebug() << "Utilities::processConfigLine: " << _line ;

        QString line = _line.simplified();
        //line.simplified();
        //QString aux;
        QStringList values = line.split("=", QT_SKIP);

        if (line.startsWith('#')){
                //qDebug() << "Utilities::processConfigLine: notes Line!" ;
            return true;
        }
        if (!( (line.contains('=')) && (line.contains(';')))){
                //qDebug() << "Utilities::processConfigLine: Wrong Line!" ;
            return false;
        }
        QString field = (values.at(0)).toUpper();
        QString value = values.at(1);

        int endValue = value.indexOf(';');
        if (endValue>-1){
            value = value.left(value.length() - (value.length() - endValue));
        }

        if (field == "DBPATH")
        {
                 //qDebug() << "Utilities::processConfigLine: dbPATH found: " << value ;
            dbPath = value;
        }
        return true;
}

/*
QString Utilities::getKLogDatabaseFile(const QString &_file)
{
      //qDebug() << "Utilities::getKLogDatabaseFile:" << _file ;
    if ( QFile::exists(_file + "/logbook.dat") )
    {
          //qDebug() << "Utilities::getKLogDatabaseFile:returning: " <<  _file + "/logbook.dat" ;
        return _file + "/logbook.dat";
    }
        //qDebug() << "Utilities::getKLogDatabaseFile: Does not exist so default: " <<  getKLogDefaultDatabaseFile() ;
        return getKLogDefaultDatabaseFile();
}
*/

QString Utilities::getCfgFile()
{
//TODO: To be removed when the defaultDir is saved in the config file
#if defined(Q_OS_WIN)
        //qDebug() << "WINDOWS DETECTED!: " << getHomeDir() + "/klogrc.cfg"  ;
    return getHomeDir() + "/klogrc.cfg";

#else
        //qDebug() << "NO WINDOWS DETECTED!: " << getHomeDir() + "/klogrc.cfg"  ;
    return getHomeDir() + "/klogrc";

#endif
}

QString Utilities::getDebugLogFile()
{
#if defined(Q_OS_WIN)
        //qDebug() << "WINDOWS DETECTED!: " << getHomeDir() + "/klogrc.cfg"  ;
    return getHomeDir() + "/klogdebug.log";

#else
        //qDebug() << "NO WINDOWS DETECTED!: " << getHomeDir() + "/klogrc.cfg"  ;
    return getHomeDir() + "/klogdebug.log";

#endif
}

QString Utilities::getSaveSpotsLogFile()
{
    QString filename = "/" + (QDateTime::currentDateTime()).toString("yyyyMMdd") + "-klogdxcluster.txt";
    return getHomeDir() + filename;
}

QString Utilities::getBackupADIFile()
{
   return getHomeDir() + "/" + (QDateTime::currentDateTime()).toString("yyyyMMdd-hhmm") + "-klogbackup.adi";
}

QString Utilities::getClubLogFile()
{
    return getHomeDir() + "/klog-clublog-upload.adi";
}

QString Utilities::getEQSLFile()
{
    return getHomeDir() + "/klog-eqsl-upload.adi";
}

QString Utilities::getLoTWAdifFile()
{
    return getHomeDir() + "/klog-lotw-upload.adi";
}

QString Utilities::getTQSLsFileName()
{
     //qDebug() << "Utilities::getTQSLsFileName: "   ;

#if defined(Q_OS_WIN)
        //qDebug() << "WINDOWS DETECTED!: "   ;
    return "tqsl.exe";
#elif   defined(Q_OS_MACOS)
     //qDebug() << "macOS DETECTED!: "   ;
    return "tqsl.app";
#else
        //qDebug() << "NO WINDOWS/macOS DETECTED!: "   ;
    return "tqsl";
#endif
}

QString Utilities::getTQSLsPath()
{
     //qDebug() << "Utilities::getDefaultProgramsPath " ;

#if defined(Q_OS_WIN64)
        //qDebug() << "WINDOWS DETECTED!: "   ;
    return "C:/Program Files/TrustedQSL/";
#elif defined(Q_OS_WIN32)
    return "C:/Program Files (x86)/TrustedQSL/";
#elif defined(Q_OS_MACOS)
     //qDebug() << "macOS DETECTED!: "   ;
    return "/Applications/TrustedQSL/";
#else
        //qDebug() << "NO WINDOWS/macOS DETECTED!: "   ;
    return "/usr/bin/";
#endif
}

QString Utilities::getCTYFile()
{
    return getHomeDir() + "/cty.csv";
}

int Utilities::getNormalizedDXCCValue(const int _dxcc)
{
    ////qDebug() << Q_FUNC_INFO << QString(": %1").arg(_dxcc);
    if (_dxcc >1000)
    {
        ////qDebug() << Q_FUNC_INFO << QString(": Special: %1 / Normalized: %2").arg(_dxcc).arg(((QString::number(_dxcc)).last(3)).toInt());

#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
        return ((QString::number(_dxcc)).last(3)).toInt();
#else
        return ((QString::number(_dxcc)).rightRef(3)).toInt();  //To be replaced by .fromString in Qt6.0
#endif
    }
    else
    {
        return _dxcc;
    }
}

QDate Utilities::getDefaultDate()
{
    //return QDate::fromString("18000101", "yyyyMMdd");
    return QDate::currentDate();
}

bool Utilities::isValidContinent(const QString &c)
{
    QStringList continents;
    continents.clear ();
    continents << "NA" << "SA"  << "EU" << "AF" << "OC" << "AS" << "AN";
    return continents.contains (c.toUpper ());
}

bool Utilities::isValidDate(const QDate _d)
{
     //qDebug() << "Utilities::isValidDate: " << _d.toString("yyyyMMdd") ;
    if (_d.isValid())
    {
        if ( _d > QDate::fromString("18000101", "yyyyMMdd") )
        {
             //qDebug() << "Utilities::isValidDate: OK" ;
            return true;
        }
    }
     //qDebug() << "Utilities::isValidDate: Error" ;
    return false;
}

bool Utilities::isValidDateTime(const QString &_d)
{
      //qDebug() << "Utilities::isValidDateTime: " << _d ;
    QDateTime _dateTime = QDateTime::fromString(_d, "yyyyMMddhhmmss");
    if ( _dateTime.isValid()  )
    {
          //qDebug() << "Utilities::isValidDateTime: 1"  ;
        return isValidDate(_dateTime.date());
    }
      //qDebug() << "Utilities::isValidDateTime: Error" ;
    return false;
}

bool Utilities::isValidCQ(const int _cq)
{
    if ((_cq>0) && (_cq<(CQZones+1)))
    {
        return true;
    }
    return false;
}

bool Utilities::isValidITU(const int _itu)
{
    if ((_itu>0) && (_itu<(ITUZones+1)))
    {
        return true;
    }
    return false;
}

bool Utilities::isValidAge(const int _age)
{
    if ((_age>0) && (_age<120))
    {
        return true;
    }
    return false;
}

void Utilities::setCallValidation(const bool _b)
{
    callValidation = _b;
}

bool Utilities::isValidCall(const QString &_c)
{
    //qDebug() << Q_FUNC_INFO << ": " << _c;
    if (!callValidation)
        return true;

    Callsign _callsign(_c);
    return _callsign.isValid();
}

QString Utilities::getPrefixFromCall(const QString &_c, bool withAreaNumber)
{
    //qDebug() << Q_FUNC_INFO << ": " << _c;
    Callsign _callsign(_c);
    if (!_callsign.isValid() && !_callsign.isValidPrefix())
        return QString();

    if (withAreaNumber)
        return _callsign.getHostFullPrefix();
    return _callsign.getHostPrefix();
}


bool Utilities::isSameFreq(const double fr1, const double fr2)
{
   //qDebug() << Q_FUNC_INFO << ": " << QString::number(fr1) << "/" << QString::number(fr2) << " = " << QString::number(fabs(fr1 - fr2)) ;

    if (fabs(fr1 - fr2) < 0.001)
    {
       //qDebug() << Q_FUNC_INFO << " - true" ;
        return true;
    }
    else
    {
       //qDebug() << Q_FUNC_INFO << " - false" ;
        return false;
    }
    //return fabs(fr1 - fr2) < 0.001;
}

bool Utilities::isValidBandId(const int _b)
{
    if (_b>0)
    {
        return true;
    }
    else
    {
        return false;
    }
    //return false;
}

bool Utilities::isValidModeId(const int _m)
{
    if (_m>0)
    {
        return true;
    }
    else
    {
        return false;
    }
    //return false;
}

bool Utilities::isValidFreq(const QString &_b)
{
    if (_b.toDouble()>0)
    {
        return true;
    }
    else
    {
        return false;
    }
    //return false;
}

bool Utilities::isValidGrid(const QString &_b)
{
    Locator locator;
    return locator.isValidLocator(_b);
}

bool Utilities::isValidVUCCGrids(const QString &_b)
{
   //qDebug() << Q_FUNC_INFO << ": " << _b;
    QStringList tmp;

    //QString a = _b;
    tmp.clear ();
    tmp << _b.split (',', QT_SKIP);

    if ((tmp.length ()!=2) && (tmp.length ()!=4))
    {
       //qDebug() << Q_FUNC_INFO << ": NON VALID LENGTH";
        return false;
    }

   //qDebug() << Q_FUNC_INFO << ": tmp: " << tmp;
    QString aux;
    foreach (aux, tmp) {
        aux = aux.trimmed ();

        if ((!isValidGrid (aux)) || (aux.length ()!=4))
        {
           //qDebug() << Q_FUNC_INFO << ": NON VALID";
            return false;
        }
        else
        {
           //qDebug() << Q_FUNC_INFO << ": VALID: " << aux;
        }
    }
   //qDebug() << Q_FUNC_INFO << ": VALID-END";
    return true;
}

bool Utilities::isValidRST(const QString &_b)
{
    if (_b.length()>0)
    {
        return true;
    }
    return false;
}

bool Utilities::isValidPower(const QString &_b)
{
    if (_b.toDouble()>0)
    {
        return true;
    }
    return false;
}

bool Utilities::isValidComment(const QString &_b)
{
    if (_b.length()>0)
    {
        return true;
    }
    return false;
}

bool Utilities::isValidName(const QString &_b)
{
    if (_b.length()>0)
    {
        return true;
    }
    return false;
}

bool Utilities::isDBFileExisting()
{
   //qDebug() << "Utilities::isDBFileExisting: " << getKLogDBFile() ;
    if (QFile::exists(getKLogDBFile()))
    {
            //qDebug() << "Utilities::isDBFileExisting - true" ;
        return true;
    }
    else
    {
            //qDebug() << "Utilities::isDBFileExisting - false" ;
        return false;
    }
    //return false;
}

bool Utilities::isDBFileExisting(const QString &_file)
{
        //qDebug() << "Utilities::isDBFileExisting2: " << _file ;

    if (QFile::exists(_file))
    {
            //qDebug() << "Utilities::isDBFileExisting2 - true" ;
        return true;
    }
    else
    {
            //qDebug() << "Utilities::isDBFileExisting2 - false" ;
        return false;
    }
    //return false;
}

bool Utilities::isValidADIFField(const QString &_b)
{
      //qDebug() << "Utilities::isValidADIFField: " << _b ;
    /*
        This functions checks if the ADIF field has the proper format.
        <Field:length:Data type>Data
    */

    if (!((_b.startsWith('<')) &&  (_b.count('>')) == 1 ))
    {
          //qDebug() << "Utilities::isValidADIFField: BAD FORMAT: No < or > delimiters: " << _b ;
        return false;
    }
    if (_b.simplified() == "<EOR>")
    {
        return true;
    }

    QStringList validDataTypes = {"B", "N", "D", "T", "S", "I", "M", "G", "E", "L"};
    QStringList qs;
    qs.clear();
    qs.append(_b.split('>'));

    if (qs.size()!= 2)
    {
          //qDebug() << "Utilities::isValidADIFField-0 (not two): " << QString::number(qs.size()) ;
        return false;
    }

    QString field = (qs.at(0)).right((qs.at(0)).length() - 1);
    QString data = (qs.at(1)).simplified();
    //data = data.simplified();
    QString dataType = QString();

     //qDebug() << "Utilities::isValidADIFField-Field: " << field ;
     //qDebug() << "Utilities::isValidADIFField_Data: " << data ;

    int length = data.length();
    int separatorPosition = 0;
    int i = (field).count(":"); //Check how many ":" do we have, to see if we have a data type or not

    if (i == 2) // We have data type
    { // DATE:8:D / 20141020
        separatorPosition = (field.section(':', 1, 1)).toInt();
        dataType = field.section(':', 2, 2);
        if (!validDataTypes.contains(dataType.toUpper()))
        {
              //qDebug() << "Utilities::isValidADIFField - FORMAT ERROR: Wrong data type: " << dataType ;
            return false;
        }
    }
    else if (i == 1)
    { // DATE:8 / 20141020
        separatorPosition = (field.section(':', 1, 1)).toInt();
    }
    else
    {
          //qDebug() << "Utilities::isValidADIFField - FORMAT ERROR, more than 2 \":\" - " << field ;
        return false;
    }

    if ( length != separatorPosition)
    {
          //qDebug() << "Utilities::isValidADIFField: Data Length problem: " << (field) << "/" << data << " - " << QString::number(length) << "/" << QString::number(separatorPosition) ;
        return false;
    }

    if (separatorPosition <= 0)
    {
       //qDebug() << "Utilities::isValidADIFField: Length problem <= 0" ;
        return false;
    }

      //qDebug() << "FileManager::checkADIFValidFormat: Return true" ;
    return true;
}

bool Utilities::isValidQSL_Rcvd(const QString &c, bool rcvd)
{
    QStringList validData;
    validData.clear ();
    validData << "Y" << "N" << "R" << "I";
    if (rcvd)
    {
        validData << "V";
    }
    return validData.contains (c);
}

bool Utilities::isValidQSL_Sent(const QString &c)
{
    if ((c == "Y") || (c == "N") || (c == "R") || (c == "Q") || (c == "I"))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Utilities::isValidUpload_Status(const QString &c)
{
    if ((c == "Y") || (c == "N") || (c == "M"))
    {
        return true;
    }
    else {
        return false;
    }
}

QStringList Utilities::getValidADIFFieldAndData(const QString &_b)
{
  //qDebug() << "Utilities::getValidADIFFieldAndData: " << _b ;
    /*
        This functions checks if the ADIF field has the proper format.
        <Field:length:Data type>Data
    */
    QStringList result;
    result.clear();

    if (!(_b.startsWith('<')))
    {
       //qDebug() << "Utilities::getValidADIFFieldAndData: BAD FORMAT: No < or > delimiters: " << _b ;
        return QStringList();
    }
    if (_b.simplified() == "<EOR>")
    {
       //qDebug() << "Utilities::getValidADIFFieldAndData: EOR" ;
        result << "EOR" << "EOR";
        return result;
    }
    QString aux = _b;
    QStringList qs;
    qs.clear();

    if ((aux.contains("APP_LOTW_")) && aux.contains("//"))
    { // Trying to fix a LoTW ADIF bug
        qs.append(aux.split("//"));
        aux = qs.at(0);
    }

   //qDebug() << "Utilities::getValidADIFFieldAndData: -20" ;
    QStringList validDataTypes = {"B", "N", "D", "T", "S", "I", "M", "G", "E", "L"};

    qs.clear();
    qs.append(aux.split('>'));

    if (qs.size()!= 2)
    {
       //qDebug() << "Utilities::getValidADIFFieldAndData-0 (not two): " << QString::number(qs.size()) ;
        return result;
    }
   //qDebug() << "Utilities::getValidADIFFieldAndData: -30" ;
    //QString field = (qs.at(0)).right((qs.at(0)).length() - 1);
    QString field = (qs.at(0)).right((qs.at(0)).length() - 1);
    QString data = (qs.at(1)).simplified();
    //data = data.simplified();
    QString dataType = QString();

   //qDebug() << "Utilities::getValidADIFFieldAndData-Field: " << field ;
   //qDebug() << "Utilities::getValidADIFFieldAndData_Data: " << data ;

    int length = data.length();
    int separatorPosition = 0;
    int i = (field).count(":"); //Check how many ":" do we have, to see if we have a data type or not

    if (i == 2) // We have data type
    { // DATE:8:D / 20141020
        separatorPosition = (field.section(':', 1, 1)).toInt();
        dataType = field.section(':', 2, 2);
         //qDebug() << "Utilities::getValidADIFFieldAndData - DataType: -" << dataType << "-" ;
        if (!validDataTypes.contains(dataType.toUpper()))
        {
             //qDebug() << "Utilities::getValidADIFFieldAndData - FORMAT ERROR: Wrong data type: " << dataType ;
            return result;
        }
    }
    else if (i == 1)
    { // DATE:8 / 20141020
        separatorPosition = (field.section(':', 1, 1)).toInt();
    }
    else
    {
       //qDebug() << "Utilities::getValidADIFFieldAndData - FORMAT ERROR, more than 2 \":\" - " << field ;
        return result;
    }
   //qDebug() << "Utilities::getValidADIFFieldAndData: -60" ;
    if ( length != separatorPosition)
    {
       //qDebug() << "Utilities::getValidADIFFieldAndData: Data Length problem: " << (field) << "/" << data << " - " << QString::number(length) << "/" << QString::number(separatorPosition) ;
        return result;
    }

    if (separatorPosition <= 0)
    {
       //qDebug() << "Utilities::getValidADIFFieldAndData: Length problem <= 0" ;
        return result;
    }
    //qDebug() << "Utilities::getValidADIFFieldAndData: -90: f: " << field ;
     //qDebug() << "Utilities::getValidADIFFieldAndData: -90: d: " << data;
    //field = field.section(':', 0, 0);
    result.clear();
    result << field.section(':', 0, 0) << data;
    //qDebug() << "Utilities::checkADIFValidFormat: Return true: " << result.at(0) << "/" << result.at(1) ;
    return result;
}

QString Utilities::getDateTimeSQLiteStringFromDateTime(const QDateTime &_d)
{
    return QString(_d.toString("yyyy-MM-dd hh:mm:ss"));
}

QString Utilities::getDateSQLiteStringFromDate(const QDate &_d)
{
    return QString(_d.toString("yyyy-MM-dd"));
}

bool Utilities::isValidDateFromString(const QString &_s)
{
    return getDateFromSQliteString(_s).isValid();
}

bool Utilities::isValidTimeFromString(const QString &_s)
{
    return getDateTimeFromSQLiteString(_s).time().isValid();
}

bool Utilities::isValidDateTimeFromString(const QString &_s)
{
    return getDateTimeFromSQLiteString(_s).isValid();
}

bool Utilities::isValidDXCC(const int _d)
{//TODO: Look for a better way to check, taking into account how KLog is identifiying the DXCC
    if (((_d > 0) && (_d < 523))  || (_d == 1206) || (_d == 1279) || (_d == 1248) || (_d == 2248) || (_d == 1259) || (_d == 1390))
    {
        return true;
    }
    else
    {
        return false;
    }
}

QDateTime Utilities::getDateTimeFromSQLiteString(const QString &_s)
{
    return QDateTime::fromString(_s, "yyyy-MM-dd hh:mm:ss");
}

QTime Utilities::getTimeFromSQLiteString(const QString &_s)
{
    if (_s.length()==5)
    {
        return QTime::fromString(_s, "hh:mm");
    }
    else
    {
        return QTime::fromString(_s, "hh:mm:ss");
    }
}

QDate Utilities::getDateFromSQliteString(const QString &_s)
{
    //It may receive "just" a date or a "date time".

    if (getDateTimeFromSQLiteString(_s).isValid()) // if we have received a full date time
    {
        return (getDateTimeFromSQLiteString(_s)).date();
    }
    else // If we have received "just a date" or an error
    {
        return  QDate::fromString(_s, "yyyy-MM-dd");
    }
}

QDate Utilities::getDateFromADIFDateString(const QString &_s)
{// Expects an ADIF DATE format string: "YYYYMMDD"
  //qDebug() << "Utilities::getDateFromADIFDateString: " << _s ;
    return QDate::fromString(_s, "yyyyMMdd");
}

QTime Utilities::getTimeFromADIFTimeString(const QString &_s)
{// Expects and ADIF TIME format String "HHMMSS" or "HHMM"
   //qDebug() << "Utilities::getTimeFromADIFTimeString: " << _s ;
    if (_s.length()==4)
    {
        return QTime::fromString(_s, "hhmm");
    }
    else
    {
        return QTime::fromString(_s, "hhmmss");
    }
}

QDate Utilities::getDateFromLoTWQSLDateString(const QString &_s)
{
   //qDebug() << "Utilities::getDateFromLoTWQSLDateString: " << _s ;
    QStringList datet;
    datet.clear();
    if (_s.endsWith ('Z'))
    {
        datet << _s.split("T");
    }
    else
    {
        datet << _s.split(" ");
    }
   //qDebug() << "Utilities::getDateFromLoTWQSLDateString: " << datet.at(0) ;
    return QDate::fromString(datet.at(0), "yyyy-MM-dd");
}

QString Utilities::getADIFDateFromQDateTime(const QDateTime &_d)
{
    if (!_d.isValid())
    {
        return QString();
    }
    else
    {
        return _d.date().toString("yyyyMMdd");
    }
}

QString Utilities::getADIFDateFromQDate(const QDate &_d)
{
    if (!_d.isValid())
    {
        return QString();
    }
    else
    {
        return _d.toString("yyyyMMdd");
    }
}

QString Utilities::getADIFTimeFromQDateTime(const QDateTime &_d)
{
    if (!_d.isValid())
    {
        return QString();
    }
    else
    {
        return _d.time().toString("hhmmss");
    }
}


QString Utilities::getCabrilloDateFromQDate(const QDate &_d)
{// Will produce the Cabrillo DATE format: "YYYY-MM-DD"
    if (!_d.isValid())
    {
        return QString("0000-00-00");
    }
    else
    {
        return _d.toString("yyyy-MM-dd");
    }
}

QString Utilities::getCabrilloTimeFromQDateTime(const QDateTime &_d)
{// Will produce the Cabrillo TIME format: "HHMM"
    if (!_d.isValid())
    {
        return QString("0000");
    }
    else
    {
        return _d.time().toString("hhmm");
    }
}

QString Utilities::getOnlineServiceName(OnLineProvider _service)
{//enum OnLineProvider {ClubLog, LoTW, eQSL, QRZ}; //, HamQTH, HRDLog
    switch (_service)
    {
        case LoTW:
        {
            return "LoTW";
        }
    case ClubLog:
    {
        return "ClubLog";
    }
    case QRZ:
    {
        return "QRZ.com";
    }
    case eQSL:
    {
        return "eQSL.cc";
    }
    }
    return QString();
}

QString Utilities::getClearSQLi(QString _s)
{
    return _s.remove ('\'');
}

/*
QPalette Utilities::getPalete(bool _ok)
{
  //qDebug() << "Utilities::getPalete"  ;
    if (_ok)
    {
      //qDebug() << "Utilities::getPalete - true"  ;
        return palRed;
        //return QPalette::setColor(QPalette::Text, Qt::red);
    }
    else
    {
      //qDebug() << "Utilities::getPalete - false"  ;
        return palBlack;
    }
}
*/

void Utilities::setDarkMode(const QString &_dm)
{
    darkMode = trueOrFalse(_dm);
}

bool Utilities::isDarkMode()
{
    if (darkMode)
    {
        return true;
    }
    else
    {
        return false;
    }
}

QString Utilities::getLogColumnName(const QString &_column)
{
   //qDebug() << Q_FUNC_INFO << ": " << _column;
    if (_column == "qso_date")
        return QObject::tr("Date");
    else if (_column == "call")
        return QObject::tr("Call");
    else if (_column == "rst_sent")
        return QObject::tr("RSTtx");
    else if (_column == "rst_rcvd")
        return QObject::tr("RSTrx");
    else if (_column == "bandid")
        return QObject::tr("Band");
    else if (_column == "comment")
        return QObject::tr("Comment");
    else if (_column == "modeid")
        return QObject::tr("Mode");
    else if (_column == "cqz")
        return QObject::tr("CQz");
    else if (_column == "ituz")
        return QObject::tr("ITUz");
    else if (_column == "dxcc")
        return QObject::tr("DXCC");
    else if (_column == "address")
        return QObject::tr("Address");
    else if (_column == "age")
        return QObject::tr("Age");
    else if (_column == "cnty")
        return QObject::tr("County");
    else if (_column == "a_index")
        return QObject::tr("A_Index");
    else if (_column == "ant_az")
        return QObject::tr("Ant_Az");
    else if (_column == "ant_el")
        return QObject::tr("Ant_El");
    else if (_column == "ant_path")
        return QObject::tr("Ant_Path");
    else if (_column == "arrl_sect")
        return QObject::tr("ARRL_SECT");
    else if (_column == "award_submitted")
        return QObject::tr("Award_Submitted");
    else if (_column == "award_granted")
        return QObject::tr("Award_granted");
    else if (_column == "band_rx")
        return QObject::tr("Band_RX");
    else if (_column == "checkcontest")
        return QObject::tr("CheckContest");
    else if (_column == "class")
        return QObject::tr("Class");
    else if (_column == "clublog_qso_upload_date")
        return QObject::tr("ClubLog SDate");
    else if (_column == "clublog_qso_upload_staus")
        return QObject::tr("ClubLog status");
    else if (_column == "cont")
        return QObject::tr("Continent");
    else if (_column == "contacted_op")
        return QObject::tr("Contacted Op");
    else if (_column == "contest_id")
        return QObject::tr("Contest Id");
    else if (_column == "country")
        return QObject::tr("Country");
    else if (_column == "credit_submitted")
        return QObject::tr("Credit Submitted");
    else if (_column == "credit_granted")
        return QObject::tr("Credit granted");
    else if (_column == "dark_dok")
        return QObject::tr("Dark Dok", "Do not translate if unsure, common hamradio term.");
    else if (_column == "distance")
        return QObject::tr("Distance");
    else if (_column == "email")
        return QObject::tr("Email");
    else if (_column == "eq_call")
        return QObject::tr("EQ_Call");
    else if (_column == "eqsl_qslrdate")
        return QObject::tr("eQSL RDate");
    else if (_column == "eqsl_qslsdate")
        return QObject::tr("eQSL SDate");
    else if (_column == "eqsl_qsl_rcvd")
        return QObject::tr("eQSL Rcvd");
    else if (_column == "eqsl_qsl_sent")
        return QObject::tr("eQSL Sent");
    else if (_column == "fists")
        return QObject::tr("Fists", "Do not translate if unsure, common hamradio term.");
    else if (_column == "fists_cc")
        return QObject::tr("Fists CC", "Do not translate if unsure, common hamradio term.");
    else if (_column == "force_init")
        return QObject::tr("Force Init");
    else if (_column == "freq")
        return QObject::tr("Freq");
    else if (_column == "freq_rx")
        return QObject::tr("Freq RX");
    else if (_column == "gridsquare")
        return QObject::tr("Gridsquare");
    else if (_column == "guest_op")
        return QObject::tr("Guest OP");
    else if (_column == "hrdlog_qso_upload_date")
        return QObject::tr("HRDLog SDate");
    else if (_column == "hrdlog_qso_upload_status")
        return QObject::tr("HRDLog status");
    else if (_column == "iota")
        return QObject::tr("IOTA");
    else if (_column == "iota_island_id")
        return QObject::tr("IOTA Island id");
    else if (_column == "k_index")
        return QObject::tr("K Index");
    else if (_column == "lat")
        return QObject::tr("Lat");
    else if (_column == "lon")
        return QObject::tr("Lon");
    else if (_column == "lotw_qslrdate")
        return QObject::tr("LoTW RDate");
    else if (_column == "lotw_qslsdate")
        return QObject::tr("LoTW SDate");
    else if (_column == "lotw_qsl_rcvd")
        return QObject::tr("LoTW Rcvd");
    else if (_column == "lotw_qsl_sent")
        return QObject::tr("LoTW Sent");
    else if (_column == "max_bursts")
        return QObject::tr("Max Bursts");
    else if (_column == "multiplier")
        return QObject::tr("Multiplier");
    else if (_column == "ms_shower")
        return QObject::tr("MS Shower");
    else if (_column == "my_antenna")
        return QObject::tr("My Antenna");
    else if (_column == "my_city")
        return QObject::tr("My City");
    else if (_column == "my_cnty")
        return QObject::tr("My Cnty");
    else if (_column == "my_country")
        return QObject::tr("My Country");
    else if (_column == "my_cq_zone")
        return QObject::tr("My CQz");
    else if (_column == "my_dxcc")
        return QObject::tr("My DXCC");
    else if (_column == "my_fists")
        return QObject::tr("My Fists", "Do not translate if unsure, common hamradio term.");
    else if (_column == "my_gridsquare")
        return QObject::tr("My Gridsquare");
    else if (_column == "my_iota")
        return QObject::tr("My IOTA");
    else if (_column == "my_iota_island_id")
        return QObject::tr("My IOTA island id");
    else if (_column == "my_itu_zone")
        return QObject::tr("My ITUz");
    else if (_column == "my_lat")
        return QObject::tr("My Lat");
    else if (_column == "my_lon")
        return QObject::tr("My Lon");
    else if (_column == "my_name")
        return QObject::tr("My Name");
    else if (_column == "my_postal_code")
        return QObject::tr("My Postal code");
    else if (_column == "my_rig")
        return QObject::tr("My Rig");
    else if (_column == "my_sig")
        return QObject::tr("My Sig");
    else if (_column == "my_sig_info")
        return QObject::tr("My Sig Info");
    else if (_column == "my_sota_ref")
        return QObject::tr("My SOTA ref");
    else if (_column == "my_state")
        return QObject::tr("My State");
    else if (_column == "my_street")
        return QObject::tr("My Street");
    else if (_column == "my_usaca_counties")
        return QObject::tr("My USACA counties");
    else if (_column == "my_vucc_grids")
        return QObject::tr("My VUCC grids");
    else if (_column == "name")
        return QObject::tr("Name");
    else if (_column == "notes")
        return QObject::tr("Notes");
    else if (_column == "nr_bursts")
        return QObject::tr("Nr bursts", "Do not translate if unsure, common hamradio term.");
    else if (_column == "nr_pings")
        return QObject::tr("Nr pings", "Do not translate if unsure, common hamradio term.");
    else if (_column == "operator")
        return QObject::tr("Operator");
    else if (_column == "owner_callsign")
        return QObject::tr("Owner Callsign");
    else if (_column == "pfx")
        return QObject::tr("Pfx");
    else if (_column == "points")
        return QObject::tr("Points");
    else if (_column == "precedence")
        return QObject::tr("Precedence");
    else if (_column == "prop_mode")
        return QObject::tr("Prop Mode");
    else if (_column == "public_key")
        return QObject::tr("Public Key");
    else if (_column == "qrzcom_qso_upload_date")
        return QObject::tr("QRZcom SDate");
    else if (_column == "qrzcom_qso_upload_status")
        return QObject::tr("QRZcom status");
    else if (_column == "qslmsg")
        return QObject::tr("QSL msg");
    else if (_column == "qslrdate")
        return QObject::tr("QSL RDate");
    else if (_column == "qslsdate")
        return QObject::tr("QSL SDate");
    else if (_column == "qsl_rcvd")
        return QObject::tr("QSL Rcvd");
    else if (_column == "qsl_sent")
        return QObject::tr("QSL Sent");
    else if (_column == "qsl_rcvd_via")
        return QObject::tr("QSL rcvd via");
    else if (_column == "qsl_sent_via")
        return QObject::tr("QSL sent via");
    else if (_column == "qsl_via")
        return QObject::tr("QSL via");
    else if (_column == "qso_complete")
        return QObject::tr("QSO complete");
    else if (_column == "qso_random")
        return QObject::tr("QSO random");
    else if (_column == "qth")
        return QObject::tr("QTH");
    else if (_column == "region")
        return QObject::tr("Region");
    else if (_column == "rig")
        return QObject::tr("Rig");
    else if (_column == "rx_pwr")
        return QObject::tr("RX Pwr");
    else if (_column == "sat_mode")
        return QObject::tr("Sat mode");
    else if (_column == "sat_name")
        return QObject::tr("Sat name");
    else if (_column == "sfi")
        return QObject::tr("SFI");
    else if (_column == "sig")
        return QObject::tr("Sig");
    else if (_column == "sig_info")
        return QObject::tr("Sig Info");
    else if (_column == "silent_key")
        return QObject::tr("Silent key", "Do not translate if unsure, common hamradio term.");
    else if (_column == "skcc")
        return QObject::tr("SKCC");
    else if (_column == "sota_ref")
        return QObject::tr("SOTA Ref");
    else if (_column == "srx_string")
        return QObject::tr("SRX String");
    else if (_column == "srx")
        return QObject::tr("SRX");
    else if (_column == "stx_string")
        return QObject::tr("STX String");
    else if (_column == "state")
        return QObject::tr("State");
    else if (_column == "station_callsign")
        return QObject::tr("Station Callsign");
    else if (_column == "submode")
        return QObject::tr("Submode");
    else if (_column == "swl")
        return QObject::tr("SWL", "Do not translate if unsure, common hamradio term.");
    else if (_column == "uksmg")
        return QObject::tr("UKSMG");
    else if (_column == "usaca_counties")
        return QObject::tr("USACA counties");
    else if (_column == "ve_prov")
        return QObject::tr("VE prov");
    else if (_column == "vucc_grids")
        return QObject::tr("VUCC grids");
    else if (_column == "ten_ten")
        return QObject::tr("Ten-Ten", "Do not translate, it is a hamradio group name.");
    else if (_column == "tx_pwr")
        return QObject::tr("TX Pwr");
    else if (_column == "web")
        return QObject::tr("Web");
    else if (_column == "qso_date_off")
        return QObject::tr("QSO Date off");
    else if (_column == "transmiterid")
        return QObject::tr("Transmitter id");
    else if (_column == "lognumber")
        return QObject::tr("Log number");
    else
    {
        return _column;
    }
}

QString Utilities::getBandFromFreq(const double _f)
{// Freq in MHz.
 // The band limits are the ones KLog uses in its band table, so both programs
 // agree on the band a frequency belongs to. The previous implementation
 // switched over the frequency truncated to an integer number of MHz, which
 // only recognised nine HF bands and silently dropped 60m, 6m, 4m, 2m, 70cm...
    struct BandLimits
    {
        const char *name;
        double lower;   // MHz, included
        double upper;   // MHz, included
    };

    static const BandLimits bands[] = {
        {"2190M",      0.1357,     0.1378},
        {"630M",       0.472,      0.479},
        {"560M",       0.501,      0.504},
        {"160M",       1.8,        2.0},
        {"80M",        3.5,        4.0},
        {"60M",        5.102,      5.404},
        {"40M",        7.0,        7.3},
        {"30M",       10.0,       10.15},
        {"20M",       14.0,       14.35},
        {"17M",       18.068,     18.168},
        {"15M",       21.0,       21.45},
        {"12M",       24.89,      24.99},
        {"10M",       28.0,       29.7},
        {"8M",        40.0,       45.0},
        {"6M",        50.0,       54.0},
        {"5M",        54.000001,  69.9},
        {"4M",        70.0,       71.0},
        {"2M",       144.0,      148.0},
        {"1.25M",    222.0,      225.0},
        {"70CM",     420.0,      450.0},
        {"33CM",     902.0,      928.0},
        {"23CM",    1240.0,     1300.0},
        {"13CM",    2340.0,     2450.0},
        {"9CM",     3300.0,     3500.0},
        {"6CM",     5650.0,     5925.0},
        {"3CM",    10000.0,    10500.0},
        {"1.25CM", 24000.0,    24250.0},
        {"6MM",    47000.0,    47200.0},
        {"4MM",    75500.0,    81000.0},
        {"2.5MM", 119980.0,   120020.0},
        {"2MM",   142000.0,   149000.0},
        {"1MM",   241000.0,   250000.0},
        {"SUBMM", 300000.0,  7500000.0}
    };

    for (const BandLimits &band : bands)
    {
        if ((_f >= band.lower) && (_f <= band.upper))
        {
            //qDebug() << Q_FUNC_INFO << ": " << QString::number(_f) << " = " << band.name;
            return QString(band.name);
        }
    }
    //qDebug() << Q_FUNC_INFO << ": No band for " << QString::number(_f);
    return QString();
}

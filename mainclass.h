#ifndef MAINCLASS_H
#define MAINCLASS_H

#include <QObject>
#include "qso.h"
#include "udpserver.h"
#include "filemanager.h"

class MainClass : public QObject
{
    Q_OBJECT
public:
    explicit MainClass(QObject *parent = nullptr);

private slots:
    void slotWSJTXQSOReceived(QSO _qso) ;

private:
    UDPServer *udpserver;
    FileManager *fileManager;

};

#endif // MAINCLASS_H

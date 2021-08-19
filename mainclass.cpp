#include "mainclass.h"

MainClass::MainClass(QObject *parent) : QObject(parent)
{
    fileManager = new FileManager;
    udpserver = new UDPServer;
    udpserver->setNetworkInterface("lo0");
    if (udpserver->start())
    {qDebug() << Q_FUNC_INFO << ": Start OK";}
    else
    {
        qDebug() << Q_FUNC_INFO << ": Start NOK";
    }

    Qt::ConnectionType ctype = Qt::DirectConnection;
    connect(udpserver, SIGNAL(logged_qso(QSO)), this, SLOT(slotWSJTXQSOReceived(QSO)), ctype);
}

void MainClass::slotWSJTXQSOReceived(QSO _qso)
{
    fileManager->saveQSO(_qso);
}

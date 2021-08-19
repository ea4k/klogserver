#include "mainclass.h"

MainClass::MainClass(QObject *parent) : QObject(parent)
{
    udpserver = new UDPServer;
    udpserver->setNetworkInterface("lo0");
    udpserver->start();
    connect(udpserver, SIGNAL(logged_qso(QSO)), this, SLOT(slotWSJTXQSOReceived(&QSO)));
}

void MainClass::slotWSJTXQSOReceived(QSO _qso)
{
    qDebug() << Q_FUNC_INFO << ": " << _qso.getCall();
}

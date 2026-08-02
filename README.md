# KLogServer

KLogServer is a server that listens in an UDP port for amateur radio QSO data coming from other programs and
adds that QSO in ADIF format to an ADIF file that can, afterwards be imported to any ADIF supporting logger.

KLogServer runs from the command line as it is intended to be executed unattended (as in a server).

It can be used as a backup for your log during normal operations or contests.

Today it supports QSO data coming from WSJT-X, N1MM and KLog but other programs sending data will be added.

KLog sends every QSO that is logged in one UDP datagram, as an ADIF record with all the ADIF fields
that have data. The record is appended to the ADIF file just as it is received, so no field is lost.
It is enabled in KLog in Settings->WSJT-X->KLogServer, where the server (IP address or hostname) and
the UDP port where KLogServer is listening are also configured.

The KLog datagram has the same layout that WSJT-X uses, with KLog's own magic number (1999030602,
instead of the 2914831322 used by WSJT-X) so the sender can be identified:

    magic (quint32) | schema (quint32) | type (quint32) | id (QByteArray) | payload

Everything is big endian. The id is "KLog" and, for the ADIFLogged message (type 12), the payload is
the ADIF record as a QByteArray.

The objective of KLogServer is to provide a free software that runs in Linux, macOS and Windows.

Check https://github.com/ea4k/klogserver for news & updates.
Check https://jaime.robles.es for the author homepage.

Read the Changelog (windows users, rename to Changelog.txt) to see the changes from one version to another.

## Running KLogServer
You can run:
 - klogserver -i interface -p port
 - klogserver -h for help.

## Contact

Please send all your suggestions & bug reports.

I hope you enjoy KLogServer!

73 de Jaime, EA4K

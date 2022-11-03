# KLogServer

KLogServer is a server that listens in an UDP port for amateur radio QSO data coming from other programs and
adds that QSO in ADIF format to an ADIF file that can, afterwards be imported to any ADIF supporting logger.

KLogServer runs from the command line as it is intended to be executed unattended (as in a server).

It can be used as a backup for your log during normal operations or contests.

Today it supports QSO data coming from WSJT-X and N1MM but ther programs sending data will be added.

The objective of KLogServer is to provide a free software that runs in Linux, macOS and Windows.

Check https://github.com/ea4k/klogserver for news & updates.
Check https://jaime.robles.es for the author homepage.

Read the Changelog (windows users, rename to Changelog.txt) to see the changes from one version to another.

## Running KLogServer
 klogserver -i interface -p port
 klogserver -h for help.


Please send all your suggestions & bug reports.

I hope you enjoy KLogServer!

73 de Jaime, EA4K

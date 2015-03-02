/*
    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 2
    of the License, or (at your option) any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with this program; if not, write to the Free Software
    Foundation, Inc., 51 Franklin Street, Fifth Floor,
    Boston, MA  02110-1301, USA.
    ---
    Copyright (C) 2015, Fredrik Persson <fpersson.se@gmail.com>
*/

#include <QCoreApplication>
#include <QCommandLineParser>

#include "serialapp.h"

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QString device;
    qint32 baudrate;

    QCoreApplication::setApplicationName("SerialTest");
    QCoreApplication::setApplicationVersion("0.1");

    QCommandLineParser parser;
    parser.setApplicationDescription("SerialTest, reading serial data from Arduino");
    parser.addHelpOption();
    parser.addVersionOption();

    QCommandLineOption devicenode(QStringList() << "d" << "device",
                                  QCoreApplication::translate("main", "set device node (/dev/ttyACM0)."),
                                  QCoreApplication::translate("main", "<device>"), "/dev/ttyACM0");
    parser.addOption(devicenode);

    QCommandLineOption cmd_baudrate(QStringList() << "b" << "baudrate",
                                    QCoreApplication::translate("main", "set baudrate (9600)"),
                                    QCoreApplication::translate("main", "<baudrate>"), "9600");
    parser.addOption(cmd_baudrate);

    parser.process(app);

    device = parser.value(devicenode);
    baudrate = parser.value(cmd_baudrate).toInt();

    if(device == ""){
        device = "/dev/ttyACM0";
    }

    /** @note not a good way to validate baudrate ;) */
    if(baudrate < 1){
        baudrate = 9600;
    }

    SerialApp sa(device, baudrate);

    return app.exec();
}

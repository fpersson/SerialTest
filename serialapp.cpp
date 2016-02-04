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

#include "serialapp.h"

SerialApp::SerialApp(QString portName, qint32 baudRate, QObject *parent) : QObject(parent){
    m_serial = new QSerialPort(this);

    m_serial->setPortName(portName);
    connect(m_serial, SIGNAL(readyRead()), this, SLOT(print()));

    if(m_serial->open(QIODevice::ReadOnly)){
        m_serial->setBaudRate(baudRate);
        qDebug() << "Serial port " << portName << "@" << baudRate << " is open for reading";
    }else{
        qDebug() << "Could not open " << portName << " for reading";
    }
}

SerialApp::~SerialApp(){
    if(m_serial->isOpen()){
        qDebug() << "close serial port";
        m_serial->close();
    }
    delete m_serial;
}

void SerialApp::print(){
    if(m_serial->isOpen()){
        if (m_serial->canReadLine()) {
            QByteArray inByteArray = m_serial->readLine();
            qDebug() << "Data: " << QString(inByteArray).trimmed();
        }
    }else{
        qDebug() << "No serial port availible";
    }
}


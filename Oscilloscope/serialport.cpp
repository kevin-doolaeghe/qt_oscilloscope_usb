#include "serialport.h"

SerialPort::SerialPort(QString port, int baudRate, QSerialPort::Parity parity, QSerialPort::StopBits stopBits)
{
    serialPort = new QSerialPort(nullptr);

    setParameters(port, baudRate, parity, stopBits);
    updateParameters();
}

SerialPort::~SerialPort()
{
    close();
    delete serialPort;
}

void SerialPort::open()
{
    serialPort->open(QSerialPort::ReadWrite);
}

void SerialPort::close()
{
    if (isOpen()) serialPort->close();
}

void SerialPort::setParameters(QString port, int baudRate, QSerialPort::Parity parity, QSerialPort::StopBits stopBits)
{
    this->port = port;
    this->baudRate = baudRate;
    this->parity = parity;
    this->stopBits = stopBits;
}

void SerialPort::updateParameters()
{
    serialPort->setPortName(port);
    serialPort->setBaudRate(baudRate);
    serialPort->setDataBits(QSerialPort::Data8);
    serialPort->setParity(parity);
    serialPort->setStopBits(stopBits);
}

bool SerialPort::isOpen()
{
    return serialPort == nullptr || serialPort->isOpen();
}

QString SerialPort::read(int bytes)
{
    QString data;
    if (!isOpen()) return data;

    if (serialPort->canReadLine()) {
        char *res;
        serialPort->readLine(res, bytes);
    }

    if (serialPort->bytesAvailable() >= bytes) {
        for (int i = 0; i < bytes; i++) {
            char c;
            serialPort->read(&c, 1);
            data.append(c);
        }
    }
    return data;
}

int SerialPort::write(QString data)
{
    int writtenBytes = -1;
    if (!isOpen()) return writtenBytes;

    serialPort->write((char *) data.toStdString().c_str());
    return writtenBytes;
}

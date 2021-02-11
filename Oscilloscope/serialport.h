#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QSerialPort>
#include <QString>

class SerialPort
{
    public:
        SerialPort(
            QString port = "COM4",
            int baudRate = QSerialPort::Baud115200,
            QSerialPort::Parity parity = QSerialPort::Parity::NoParity,
            QSerialPort::StopBits stopBits = QSerialPort::StopBits::OneStop
        );
        ~SerialPort();
        void open();
        void close();
        void setParameters(
            QString port = "COM4",
            int baudRate = QSerialPort::Baud115200,
            QSerialPort::Parity parity = QSerialPort::Parity::NoParity,
            QSerialPort::StopBits stopBits = QSerialPort::StopBits::OneStop
        );
        void updateParameters();
        bool isOpen();
        QString read(int bytes);
        int write(QString data);
    private:
        QSerialPort *serialPort;
        QString port;
        int baudRate;
        QSerialPort::Parity parity;
        QSerialPort::StopBits stopBits;
};

#endif // SERIALPORT_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSerialPortInfo>
#include <QTimer>
#include <QElapsedTimer>
#include <QString>
#include <QList>
#include <QtCharts/QChartView>
#include <QtCharts/QSplineSeries>
#include "serialport.h"
#include "decoder.h"
#include "chart.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void initUi();
    QList<QSerialPortInfo> getPortList();
    void addPortListToGui(QList<QSerialPortInfo> portList);

private slots:
    void on_pushButton_send_clicked();
    void on_pushButton_connect_clicked();
    void read();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    QElapsedTimer *elapsedTimer;
    SerialPort *serialPort;
    Chart *chart;
    QChartView *chartView;
};
#endif // MAINWINDOW_H

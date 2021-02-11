#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timer = new QTimer();
    elapsedTimer = new QElapsedTimer();
    serialPort = new SerialPort();
    chart = new Chart();
    chartView = new QChartView();

    initUi();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete timer;
    delete elapsedTimer;
    delete serialPort;
    delete chart;
    delete chartView;
}

void MainWindow::initUi()
{
    this->connect(ui->action_leave, SIGNAL(triggered()), this, SLOT(close()));
    this->connect(timer, SIGNAL(timeout()), this, SLOT(read()));
    timer->start(200);
    elapsedTimer->start();

    chartView->setChart(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    ui->verticalLayout_chart->addWidget(chartView);

    ui->textEdit_response->setReadOnly(true);
    addPortListToGui(getPortList());
}

QList<QSerialPortInfo> MainWindow::getPortList()
{
    QList<QSerialPortInfo> portList = QSerialPortInfo::availablePorts();
    return portList;
}

void MainWindow::addPortListToGui(QList<QSerialPortInfo> portList)
{
    foreach (QSerialPortInfo port, portList) {
        ui->comboBox_portList->addItem(port.portName());
    }
}

void MainWindow::on_pushButton_send_clicked()
{
    if (serialPort->isOpen()) {
        QString data = ui->textEdit_dataToSend->toPlainText();
        serialPort->write(data);
    }
}

void MainWindow::on_pushButton_connect_clicked()
{
    QString portName = ui->comboBox_portList->currentText();
    serialPort->setParameters(portName);
    serialPort->updateParameters();
    serialPort->open();

    elapsedTimer->restart();
    ui->textEdit_response->clear();

    this->statusBar()->setSizeGripEnabled(false);
    this->setFixedSize(QSize(1026, 600));
}

void MainWindow::read()
{
    if (serialPort->isOpen()) {
        QString frame = serialPort->read(10);
//        ui->textEdit_response->append(frame);

        double x = ((double) elapsedTimer->elapsed()) / 1000;
        double y = Decoder::getDataFromIndex(Decoder::decode(frame), 0).toDouble();
        ui->textEdit_response->append(QString::number(x) + " --> " + QString::number(y));
        chart->appendPoint(x, y);
    }
}

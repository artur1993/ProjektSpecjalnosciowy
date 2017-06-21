#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "coloredprogressbar.h"
#include <iostream>
#include <iomanip>
#include <QCoreApplication>
#include <QList>

void MainWindow::setupBackground()
{
    int imageWidth = 1085;
    int imageHeight = 383;
    this->setFixedSize(imageWidth, imageHeight);
    QPixmap background("../res/rasia.png");
    QPalette palette;
    palette.setBrush(QPalette::Background, background);
    this->setPalette(palette);
}

void MainWindow::setFinger(QProgressBar *finger, int x, int y, int value)
{
    int barWidth = 50;
    int barHeight = 20;
    finger->setEnabled(true);
    finger->setGeometry(QRect(x, y, barWidth, barHeight));
    finger->setValue(value);
    finger->setTextVisible(false);
    finger->setOrientation(Qt::Horizontal);
    finger->setMinimum(0);
    finger->setMaximum(100);
}

void MainWindow::setupFingers()
{
    finger11 = new ColoredProgressBar(ui->centralWidget);
    finger12 = new ColoredProgressBar(ui->centralWidget);
    finger13 = new ColoredProgressBar(ui->centralWidget);
    finger21 = new ColoredProgressBar(ui->centralWidget);
    finger22 = new ColoredProgressBar(ui->centralWidget);
    finger23 = new ColoredProgressBar(ui->centralWidget);
    finger31 = new ColoredProgressBar(ui->centralWidget);
    finger32 = new ColoredProgressBar(ui->centralWidget);
    finger33 = new ColoredProgressBar(ui->centralWidget);
    finger41 = new ColoredProgressBar(ui->centralWidget);
    finger42 = new ColoredProgressBar(ui->centralWidget);
    finger43 = new ColoredProgressBar(ui->centralWidget);

    setFinger(finger11, 843, 45, 0);
    setFinger(finger12, 733, 37, 0);
    setFinger(finger13, 614, 97, 0);
    setFinger(finger21, 1015, 143, 0);
    setFinger(finger22, 910, 152, 0);
    setFinger(finger23, 824, 162, 0);
    setFinger(finger31, 1030, 248, 0);
    setFinger(finger32, 934, 242, 0);
    setFinger(finger33, 844, 238, 0);
    setFinger(finger41, 997, 338, 0);
    setFinger(finger42, 902, 326, 0);
    setFinger(finger43, 812, 314, 0);
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setupBackground();
    setupFingers();

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(changeValuePlus()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(changeValueMinus()));

    Q_FOREACH(QSerialPortInfo port, QSerialPortInfo::availablePorts()) {
         ui->comboBox->addItem(port.portName());
    }

    serialPort = new QSerialPort(this);

    connect( ui->comboBox, static_cast<void (QComboBox::*)(const QString &)>(&QComboBox::currentIndexChanged), this, &MainWindow::portChange);

    serialPort->setPortName( ui->comboBox->currentText() );
    serialPort->setBaudRate( QSerialPort::Baud115200 );
    serialPort->setDataBits( QSerialPort::Data8 );
    serialPort->setParity( QSerialPort::NoParity );
    serialPort->setStopBits( QSerialPort::OneStop );

    serialPort->open(QIODevice::ReadOnly);
    connect(serialPort, &QSerialPort::readyRead, this, &MainWindow::handleReadyRead);
}

void MainWindow::changeFingerValue(QProgressBar* finger, const int increment)
{
    if (finger->value() == 100) {
        finger->setValue(0);
    }
    else {
        finger->setValue(finger->value() + increment);
    }
}

void MainWindow::changeValuePlus()
{
    int increment = 2;
    changeFingerValue(finger11, increment);
    changeFingerValue(finger12, increment);
    changeFingerValue(finger13, increment);
    changeFingerValue(finger21, increment);
    changeFingerValue(finger22, increment);
    changeFingerValue(finger23, increment);
    changeFingerValue(finger31, increment);
    changeFingerValue(finger32, increment);
    changeFingerValue(finger33, increment);
    changeFingerValue(finger41, increment);
    changeFingerValue(finger42, increment);
    changeFingerValue(finger43, increment);
}

void MainWindow::changeValueMinus()
{
    int decrement = -2;
    changeFingerValue(finger11, decrement);
    changeFingerValue(finger12, decrement);
    changeFingerValue(finger13, decrement);
    changeFingerValue(finger21, decrement);
    changeFingerValue(finger22, decrement);
    changeFingerValue(finger23, decrement);
    changeFingerValue(finger31, decrement);
    changeFingerValue(finger32, decrement);
    changeFingerValue(finger33, decrement);
    changeFingerValue(finger41, decrement);
    changeFingerValue(finger42, decrement);
    changeFingerValue(finger43, decrement);
}

void MainWindow::handleReadyRead()
{
    uint16_t tmp;

    readData.append(serialPort->readAll());

    if ( readData.size() >= 82 )
    {
        for ( int i = 0; i < 20; ++i )
        {
            tmp = ((((uint16_t)readData[i*4+1]<<8)|readData[i*4+2])>>6);
            if ( tmp > 0 && tmp < 60000 )
            {
                sensor[i] = tmp;
            }
        }

        std::cout << (int)readData[0] << ' ';
        for ( int i = 0; i < 20; ++i )
        {
            std::cout << std::setw(5);
            std::cout << sensor[i] << ' ';
        }
        std::cout << std::endl;

        finger11->setValue( 100 - (int)((float)sensor[3] / 3.01) );
        finger12->setValue( 100 - (int)((float)sensor[11] / 4.29) );
        finger21->setValue( 100 - (int)((float)sensor[1] / 3.32) );
        finger22->setValue( 100 - (int)((float)sensor[2] / 4.32) );
        finger31->setValue( 100 - (int)((float)sensor[7] / 3.28) );
        finger32->setValue( 100 - (int)((float)sensor[16] / 2.64) );

        readData.clear();
    }
}

void MainWindow::portChange()
{
    serialPort->setPortName( ui->comboBox->currentText() );
}

MainWindow::~MainWindow()
{
    delete ui;
}

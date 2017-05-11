#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "coloredprogressbar.h"
#include <iostream>
#include <QCoreApplication>

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
    delete finger;
    finger = new ColoredProgressBar(ui->centralWidget);
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
    setFinger(ui->finger11, 843, 45, 0);
    setFinger(ui->finger12, 733, 37, 10);
    setFinger(ui->finger13, 614, 97, 20);
    setFinger(ui->finger21, 1015, 143, 30);
    setFinger(ui->finger22, 910, 152, 40);
    setFinger(ui->finger23, 824, 162, 50);
    setFinger(ui->finger31, 1030, 248, 60);
    setFinger(ui->finger32, 934, 242, 70);
    setFinger(ui->finger33, 844, 238, 80);
    setFinger(ui->finger41, 997, 338, 90);
    setFinger(ui->finger42, 902, 326, 100);
    setFinger(ui->finger43, 812, 314, 90);
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setupBackground();
    setupFingers();

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(changeValuePlus()));
    timer->start(50);

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(changeValuePlus()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(changeValueMinus()));
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
    changeFingerValue(ui->finger11, increment);
    changeFingerValue(ui->finger12, increment);
    changeFingerValue(ui->finger13, increment);
    changeFingerValue(ui->finger21, increment);
    changeFingerValue(ui->finger22, increment);
    changeFingerValue(ui->finger23, increment);
    changeFingerValue(ui->finger31, increment);
    changeFingerValue(ui->finger32, increment);
    changeFingerValue(ui->finger33, increment);
    changeFingerValue(ui->finger41, increment);
    changeFingerValue(ui->finger42, increment);
    changeFingerValue(ui->finger43, increment);
}

void MainWindow::changeValueMinus()
{
    int decrement = -5;
    changeFingerValue(ui->finger11, decrement);
    changeFingerValue(ui->finger12, decrement);
    changeFingerValue(ui->finger13, decrement);
    changeFingerValue(ui->finger21, decrement);
    changeFingerValue(ui->finger22, decrement);
    changeFingerValue(ui->finger23, decrement);
    changeFingerValue(ui->finger31, decrement);
    changeFingerValue(ui->finger32, decrement);
    changeFingerValue(ui->finger33, decrement);
    changeFingerValue(ui->finger41, decrement);
    changeFingerValue(ui->finger42, decrement);
    changeFingerValue(ui->finger43, decrement);
}

MainWindow::~MainWindow()
{
    delete ui;
}

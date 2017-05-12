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
    setFinger(finger12, 733, 37, 10);
    setFinger(finger13, 614, 97, 20);
    setFinger(finger21, 1015, 143, 30);
    setFinger(finger22, 910, 152, 40);
    setFinger(finger23, 824, 162, 50);
    setFinger(finger31, 1030, 248, 60);
    setFinger(finger32, 934, 242, 70);
    setFinger(finger33, 844, 238, 80);
    setFinger(finger41, 997, 338, 90);
    setFinger(finger42, 902, 326, 100);
    setFinger(finger43, 812, 314, 90);
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
    int decrement = -5;
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

MainWindow::~MainWindow()
{
    delete ui;
}

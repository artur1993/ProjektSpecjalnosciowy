#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "coloredprogressbar.h"
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
}

void MainWindow::setupFingers()
{
    setFinger(ui->finger11, 848, 24, 20);
    setFinger(ui->finger12, 737, 41, 30);
    setFinger(ui->finger13, 666, 70, 40);
    setFinger(ui->finger21, 1020, 140, 50);
    setFinger(ui->finger22, 910, 148, 60);
    setFinger(ui->finger23, 805, 160, 70);
    setFinger(ui->finger31, 1033, 248, 80);
    setFinger(ui->finger32, 934, 240, 90);
    setFinger(ui->finger33, 843, 236, 0);
    setFinger(ui->finger41, 997, 338, 10);
    setFinger(ui->finger42, 910, 326, 20);
    setFinger(ui->finger43, 812, 312, 30);
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
}

void MainWindow::changeValuePlus()
{
    int increment = 5;
    int value = ui->finger11->value();
    ui->finger11->setValue(value+increment);
    ui->finger12->setValue(value+increment);
    ui->finger13->setValue(value+increment);
    ui->finger21->setValue(value+increment);
    ui->finger22->setValue(value+increment);
    ui->finger23->setValue(value+increment);
    ui->finger31->setValue(value+increment);
    ui->finger32->setValue(value+increment);
    ui->finger33->setValue(value+increment);
    ui->finger41->setValue(value+increment);
    ui->finger42->setValue(value+increment);
    ui->finger43->setValue(value+increment);
}

void MainWindow::changeValueMinus()
{
    int increment = 5;
    int value = ui->finger11->value();
    ui->finger11->setValue(value-increment);
    ui->finger12->setValue(value-increment);
    ui->finger13->setValue(value-increment);
    ui->finger21->setValue(value-increment);
    ui->finger22->setValue(value-increment);
    ui->finger23->setValue(value-increment);
    ui->finger31->setValue(value-increment);
    ui->finger32->setValue(value-increment);
    ui->finger33->setValue(value-increment);
    ui->finger41->setValue(value-increment);
    ui->finger42->setValue(value-increment);
    ui->finger43->setValue(value-increment);
}

MainWindow::~MainWindow()
{
    delete ui;
}

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QCoreApplication>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap bkgnd("../res/pobrane.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(changeValuePlus()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(changeValueMinus()));
}

void MainWindow::changeValuePlus()
{
    int value = ui->progressBar->value();
    ui->progressBar->setValue(value+10);
    ui->progressBar_2->setValue(value+10);
    ui->progressBar_3->setValue(value+10);
    ui->progressBar_4->setValue(value+10);
    ui->progressBar_5->setValue(value+10);
    ui->progressBar_6->setValue(value+10);
    ui->progressBar_7->setValue(value+10);
    ui->progressBar_8->setValue(value+10);
    ui->progressBar_9->setValue(value+10);
    ui->progressBar_10->setValue(value+10);
    ui->progressBar_11->setValue(value+10);
    ui->progressBar_12->setValue(value+10);
}

void MainWindow::changeValueMinus()
{
    int value = ui->progressBar->value();
    ui->progressBar->setValue(value-10);
    ui->progressBar_2->setValue(value-10);
    ui->progressBar_3->setValue(value-10);
    ui->progressBar_4->setValue(value-10);
    ui->progressBar_5->setValue(value-10);
    ui->progressBar_6->setValue(value-10);
    ui->progressBar_7->setValue(value-10);
    ui->progressBar_8->setValue(value-10);
    ui->progressBar_9->setValue(value-10);
    ui->progressBar_10->setValue(value-10);
    ui->progressBar_11->setValue(value-10);
    ui->progressBar_12->setValue(value-10);
}

MainWindow::~MainWindow()
{
    delete ui;
}

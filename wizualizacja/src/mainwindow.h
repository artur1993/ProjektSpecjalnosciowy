#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QProgressBar>
#include <QTimer>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QByteArray>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setupBackground();
    void setupFingers();
    void setFinger(QProgressBar *finger, int x, int y, int value);
    void setFingerValue(int value, int increment);
    void changeFingerValue(QProgressBar *finger, const int increment);

    uint16_t sensor[20];

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    QProgressBar *finger41;
    QProgressBar *finger42;
    QProgressBar *finger43;
    QProgressBar *finger31;
    QProgressBar *finger32;
    QProgressBar *finger33;
    QProgressBar *finger21;
    QProgressBar *finger22;
    QProgressBar *finger23;
    QProgressBar *finger13;
    QProgressBar *finger12;
    QProgressBar *finger11;

    QSerialPort *serialPort;
    QByteArray  readData;

private slots:
    void changeValuePlus();
    void changeValueMinus();

    void handleReadyRead();
    void portChange();
};

#endif // MAINWINDOW_H

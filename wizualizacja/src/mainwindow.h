#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QProgressBar>
#include <QTimer>

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

private slots:
    void changeValuePlus();
    void changeValueMinus();
};

#endif // MAINWINDOW_H

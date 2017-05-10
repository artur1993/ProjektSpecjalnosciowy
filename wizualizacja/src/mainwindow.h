#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QProgressBar>

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
private:
    Ui::MainWindow *ui;
    QPushButton *pushButton;

private slots:
    void changeValuePlus();
    void changeValueMinus();
};

#endif // MAINWINDOW_H

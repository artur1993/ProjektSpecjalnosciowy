
#include "coloredprogressbar.h"

#include <QPainter>
#include <QBrush>
#include <QStyle>
#include <QPen>
#include <QColor>

ColoredProgressBar::ColoredProgressBar(QWidget *parent) : QProgressBar(parent)
{

}

ColoredProgressBar::~ColoredProgressBar()
{

}

void ColoredProgressBar::paintColor(QPainter& painter, QColor color, int beginPosition, int currentPosition)
{
    painter.setPen(color);
    painter.setBrush(QBrush(color));
    painter.drawRect(beginPosition,0,currentPosition,height());
}



void ColoredProgressBar::paintEvent(QPaintEvent*)
{
    int currentValue = value();
    int currentPosition = QStyle::sliderPositionFromValue(minimum(), maximum(), currentValue, width());
    int pos0 = QStyle::sliderPositionFromValue(minimum(), maximum(), 0, width());
    int pos20 = QStyle::sliderPositionFromValue(minimum(), maximum(), 20, width());
    int pos40 = QStyle::sliderPositionFromValue(minimum(), maximum(), 40, width());
    int pos60 = QStyle::sliderPositionFromValue(minimum(), maximum(), 60, width());
    int pos80 = QStyle::sliderPositionFromValue(minimum(), maximum(), 80, width());

    QPainter painter(this);
    QColor orange = QColor(255,165,0);
    QColor lightGreen= QColor(128, 255, 0);

    if(currentValue >= 0 && currentValue <= 20)
    {
        paintColor(painter, Qt::green, pos0, currentPosition);
    }
    else if(currentValue > 20 && currentValue <= 40)
    {
        paintColor(painter, Qt::green, pos0, pos20);
        paintColor(painter, lightGreen, pos20, currentPosition);
    }
    else if(currentValue > 40 && currentValue <= 60)
    {
        paintColor(painter, Qt::green, pos0, pos20);
        paintColor(painter, lightGreen, pos20, pos40);
        paintColor(painter, Qt::yellow, pos40, currentPosition);
    }
    else if(currentValue > 60 && currentValue <= 80)
    {
        paintColor(painter, Qt::green, pos0, pos20);
        paintColor(painter, lightGreen, pos20, pos40);
        paintColor(painter, Qt::yellow, pos40, pos60);
        paintColor(painter, orange, pos60, currentPosition);
    }
    else if(currentValue > 80 && currentValue <= 100)
    {
        paintColor(painter, Qt::green, pos0, pos20);
        paintColor(painter, lightGreen, pos20, pos40);
        paintColor(painter, Qt::yellow, pos40, pos60);
        paintColor(painter, orange, pos60, pos80);
        paintColor(painter, Qt::red, pos80, currentPosition);
    }

    painter.setPen(Qt::white);
    painter.setBrush(QBrush(Qt::white));
    painter.drawRect(currentPosition, 0, width(), height());

    painter.setPen(Qt::black);
    painter.setBrush(QBrush(Qt::black));
    painter.drawText(0,0, width(), height(), Qt::AlignCenter, QString::number(currentValue) + "%");
}

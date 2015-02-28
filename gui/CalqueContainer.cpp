#include "CalqueContainer.h"
#include <QDebug>
#include <QPainter>

CalqueContainer::CalqueContainer(QImage* imageVideo, QList<QImage *> calque, DrawArea *drawArea) :
    QStackedLayout(),
    _drawArea(drawArea),
    _backgroundImage(new QImage(imageVideo->size(), QImage::Format_ARGB32))
{
    setStackingMode(QStackedLayout::StackAll);
    _background = new QLabel();
    _background->resize(imageVideo->size());
    loadFrame(imageVideo, calque);

    addWidget(_background);
    addWidget(_drawArea);
}

void CalqueContainer::loadFrame(QImage *imageVideo, QList<QImage*> calque)
{    
    QPainter painter(_backgroundImage);
    painter.drawImage(0,0,*imageVideo);

    qreal opacity(0.5);

    for(QList<QImage*>::iterator iter = calque.begin(); iter != calque.end(); ++iter)
    {
        painter.setOpacity(opacity);
        opacity -= 0.05;
        painter.drawImage(0,0,*(*iter));
    }

    _background->setPixmap(QPixmap::fromImage(*_backgroundImage));
}

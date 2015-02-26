#include "CalqueContainer.h"
#include <QPainter>
#include <QLabel>

CalqueContainer::CalqueContainer(QImage* imageVideo, DrawArea *drawArea) : QStackedLayout(), _imageVideo(imageVideo), _drawArea(drawArea)
{
    setStackingMode(QStackedLayout::StackAll);
    QLabel *widget = new QLabel();
    widget->resize(_imageVideo->size());
    widget->setPixmap(QPixmap::fromImage(*_imageVideo));

    addWidget(widget);
    addWidget(_drawArea);
}

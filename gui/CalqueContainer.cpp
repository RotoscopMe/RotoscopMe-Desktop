#include "CalqueContainer.h"

CalqueContainer::CalqueContainer(QImage* imageVideo, DrawArea *drawArea) : QStackedLayout(), _imageVideo(imageVideo), _drawArea(drawArea)
{
    setStackingMode(QStackedLayout::StackAll);
    _background = new QLabel();
    _background->setPixmap(QPixmap::fromImage(_imageVideo->scaled(_background->size())));

    addWidget(_background);
    addWidget(_drawArea);
}

void CalqueContainer::resizeUpdate()
{
    _background->setPixmap(QPixmap::fromImage(_imageVideo->scaled(_background->size())));
}

#include "CalqueContainer.h"

CalqueContainer::CalqueContainer(QImage* imageVideo, DrawArea *drawArea) : QStackedLayout(), _imageVideo(imageVideo), _drawArea(drawArea)
{
    setStackingMode(QStackedLayout::StackAll);
    _background = new QLabel();
    int newHeight = _imageVideo->height()*_background->width()/_imageVideo->width();
    _background->resize(_background->width(), newHeight);

    _background->setPixmap(QPixmap::fromImage(_imageVideo->scaled(_background->width(), newHeight)));

    addWidget(_background);
    addWidget(_drawArea);
}

void CalqueContainer::loadFrame(QImage *imageVideo)
{
    _imageVideo = imageVideo;
    int newHeight = _imageVideo->height()*_background->width()/_imageVideo->width();
    _background->resize(_background->width(), newHeight);

    _background->setPixmap(QPixmap::fromImage(_imageVideo->scaled(_background->width(), newHeight)));
}

void CalqueContainer::resizeUpdate()
{
    int newHeight = _imageVideo->height()*_background->width()/_imageVideo->width();
    _background->resize(_background->width(), newHeight);

    _background->setPixmap(QPixmap::fromImage(_imageVideo->scaled(_background->width(), newHeight)));

    _drawArea->resizeUpdate(new QSize(_background->width(), newHeight));
}

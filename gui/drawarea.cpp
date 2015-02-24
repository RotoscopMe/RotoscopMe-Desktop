#include "drawarea.h"
#include <utility>

DrawArea::DrawArea(): QWidget(), _image(new QImage(this->size(), QImage::Format_ARGB32)), _drawing(false)
{
    QPalette pal(Qt::white);
    setAutoFillBackground(true);
    setPalette(pal);
}

void DrawArea::mousePressEvent(QMouseEvent* event)
{
    _drawing = true;
    _drawingLastPosition = event->pos();
}

void DrawArea::mouseReleaseEvent(QMouseEvent* event)
{
    if(_drawing)
    {
        QPainter painter(_image);

        painter.setPen(_pen);
        painter.drawPoint(event->pos());
        _drawingLastPosition = event->pos();

    }
    _drawing = false;

    update();
}

void DrawArea::mouseMoveEvent(QMouseEvent* event)
{
    if(_drawing)
    {
        QPainter painter(_image);

        painter.setPen(_pen);
        painter.drawLine(_drawingLastPosition, event->pos());
        _drawingLastPosition = event->pos();

        update();
    }
}

void DrawArea::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    painter.setPen(_pen);
    painter.drawImage(0,0, *_image);
}

void DrawArea::resizeEvent(QResizeEvent *)
{
    QImage tmp(this->size(), QImage::Format_ARGB32);

    QPainter painter(&tmp);
    painter.setPen(_pen);
    painter.drawImage(0,0, *_image);

    std::swap(tmp, *_image); //Assure la destruction de l'ancienne _image à la sortie de la méthode
}
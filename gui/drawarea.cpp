#include "drawarea.h"
#include <utility>

DrawArea::DrawArea():
    QWidget(),
    _pen(Qt::black),
    _rubber(),
    _image(new QImage(this->size(), QImage::Format_ARGB32)),
    _drawing(false)
{
    QPalette pal(Qt::transparent);
    setAutoFillBackground(true);
    setPalette(pal);

    _image->fill(Qt::transparent);

    _pen.setWidth(1);
    _rubber.setWidth(1);
}

void DrawArea::setPenWidth(int width)
{
    _pen.setWidth(width);
}

void DrawArea::setPenColor(QColor color)
{
    _pen.setColor(color);
}

void DrawArea::setRubberWidth(int width)
{
    _rubber.setWidth(width);
}

void DrawArea::clear()
{
    _image->fill(Qt::transparent);
    update();
}

void DrawArea::load(QImage *image)
{
    delete _image;
    _image = image;
    update();
}

void DrawArea::setTool(Tool tool)
{
    _tool = tool;
}

void DrawArea::mousePressEvent(QMouseEvent* event)
{
    _drawing = true;
    _drawingLastPosition = event->pos();

    onClick();
}

void DrawArea::mouseReleaseEvent(QMouseEvent* event)
{
    if(_drawing)
    {
        QPainter painter(_image);

        if(_tool == RUBBER)
        {
            painter.setCompositionMode(QPainter::CompositionMode_Clear);
            painter.setPen(_rubber);
        }
        else
        {
            painter.setPen(_pen);
        }

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

        if(_tool == RUBBER)
        {
            painter.setCompositionMode(QPainter::CompositionMode_Clear);
            painter.setPen(_rubber);
        }
        else
        {
            painter.setPen(_pen);
        }

        painter.drawLine(_drawingLastPosition, event->pos());
        _drawingLastPosition = event->pos();

        update();
    }
}

void DrawArea::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.drawImage(0,0, *_image);
}

void DrawArea::resizeEvent(QResizeEvent *)
{
    QImage tmp(this->size(), QImage::Format_ARGB32);
    tmp.fill(Qt::transparent);

    QPainter painter(&tmp);
    painter.drawImage(0,0, *_image);

    std::swap(tmp, *_image); //Assure la destruction de l'ancienne _image à la sortie de la méthode
}

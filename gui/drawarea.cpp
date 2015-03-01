#include "drawarea.h"
#include <utility>
#include <QDebug>

DrawArea::DrawArea(QImage *image):
    QWidget(),
    _pen(Qt::black),
    _rubber(),
    _image(image),
    _imageUndo(new QImage(image->size(), QImage::Format_ARGB32)),
    _drawing(false)
{
    resize(_image->size());

    QPalette pal(Qt::transparent);
    setAutoFillBackground(true);
    setPalette(pal);

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

void DrawArea::load(QImage *image)
{
    _image = image;
    update();
}

void DrawArea::setTool(Tool tool)
{
    _tool = tool;
}

void DrawArea::undo()
{
    _image->fill(Qt::transparent);
    QPainter painter(_image);
    painter.drawImage(0,0,*_imageUndo);

    update();
}

void DrawArea::mousePressEvent(QMouseEvent* event)
{
    _drawing = true;
    _drawingLastPosition = event->pos();

    _imageUndo->fill(Qt::transparent);
    QPainter painterUndo(_imageUndo);
    painterUndo.drawImage(0,0,*_image);

    onClick();

    qDebug() << "draw";
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

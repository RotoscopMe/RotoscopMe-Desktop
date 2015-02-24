#ifndef DRAWAREA_H
#define DRAWAREA_H

#include <QWidget>
#include <QPen>
#include <QPoint>
#include <QPainter>
#include <QMouseEvent>

class DrawArea : public QWidget
{
    public:
        DrawArea();
        void paintEvent(QPaintEvent*);
        void mousePressEvent(QMouseEvent* event);
        void mouseReleaseEvent(QMouseEvent* event);
        void mouseMoveEvent(QMouseEvent* event);
        void resizeEvent(QResizeEvent *);

    private:
        QPen _pen;
        QImage* _image;

        bool _drawing;
        QPoint _drawingLastPosition;
};

#endif // DRAWAREA_H

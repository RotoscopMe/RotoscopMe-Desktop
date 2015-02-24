#ifndef DRAWAREA_H
#define DRAWAREA_H

#include <QWidget>
#include <QPen>
#include <QPoint>
#include <QPainter>
#include <QMouseEvent>

class DrawArea : public QWidget
{
    Q_OBJECT

    private:
        enum Tool {PEN, RUBBER};

    public:
        DrawArea();

        void setPenWidth(int width);
        void setPenColor(QColor &color);

    public slots:
        void switchToPen();
        void switchToRubber();

    private:
        QPen _pen;
        QImage* _image;

        bool _drawing;
        QPoint _drawingLastPosition;
        Tool _tool;


        void paintEvent(QPaintEvent*);

        void mousePressEvent(QMouseEvent* event);
        void mouseReleaseEvent(QMouseEvent* event);
        void mouseMoveEvent(QMouseEvent* event);

        void resizeEvent(QResizeEvent *);
};

#endif // DRAWAREA_H

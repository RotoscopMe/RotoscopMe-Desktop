#ifndef DRAWAREA_H
#define DRAWAREA_H

#include <QWidget>
#include <QPen>
#include <QPoint>
#include <QPainter>
#include <QMouseEvent>

enum Tool {PEN, RUBBER};

class DrawArea : public QWidget
{
    Q_OBJECT

    public:
        DrawArea(QImage *image);

        void setPenWidth(int width);
        void setPenColor(QColor color);
        void setRubberWidth(int width);

    public slots:
        void setTool(Tool tool);

        void load(QImage* image);

        void undo();
        void redo();

    signals:
        void onClick();

    private:
        QPen _pen;
        QPen _rubber;
        QImage* _image;
        QImage *_imageUndo;
        QImage *_imageRedo;

        bool _drawing;
        bool _undo;
        bool _redo;
        QPoint _drawingLastPosition;
        Tool _tool;

        void paintEvent(QPaintEvent*);

        void mousePressEvent(QMouseEvent* event);
        void mouseReleaseEvent(QMouseEvent* event);
        void mouseMoveEvent(QMouseEvent* event);
};

#endif // DRAWAREA_H

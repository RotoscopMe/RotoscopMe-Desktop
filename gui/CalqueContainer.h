#ifndef CALQUECONTAINER_H
#define CALQUECONTAINER_H

#include <QStackedLayout>
#include <QLabel>
#include "drawarea.h"
#include <QList>

class CalqueContainer : public QStackedLayout
{
    public:
        CalqueContainer(QImage *imageVideo, QList<QImage*> calque, DrawArea *drawArea);
        void loadFrame(QImage *imageVideo, QList<QImage *> calque);

    private:
        DrawArea *_drawArea;
        QLabel *_background;
        QImage *_backgroundImage;

        void drawBackground(QImage *imageVideo, QList<QImage*> calque);
};

#endif // CALQUECONTAINER_H

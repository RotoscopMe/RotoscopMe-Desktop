#ifndef CALQUECONTAINER_H
#define CALQUECONTAINER_H

#include <QStackedLayout>
#include <QLabel>
#include "drawarea.h"

class CalqueContainer : public QStackedLayout
{
    public:
        CalqueContainer(QImage *imageVideo, DrawArea *drawArea);
        void resizeUpdate();

    private:
        QImage* _imageVideo;
        DrawArea *_drawArea;
        QLabel *_background;
};

#endif // CALQUECONTAINER_H

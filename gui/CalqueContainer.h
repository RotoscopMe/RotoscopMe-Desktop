#ifndef CALQUECONTAINER_H
#define CALQUECONTAINER_H

#include <QStackedLayout>
#include "drawarea.h"

class CalqueContainer : public QStackedLayout
{
    public:
        CalqueContainer(QImage *imageVideo, DrawArea *drawArea);

    private:
        QImage* _imageVideo;
        DrawArea *_drawArea;
};

#endif // CALQUECONTAINER_H

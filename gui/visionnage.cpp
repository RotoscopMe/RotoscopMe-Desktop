#include "visionnage.h"
#include "mainwindow.h"

#include <QDebug>
#include <QException>

Visionnage::Visionnage(MainWindow *parent, Projet *projet, int nPreviousImage) :
    QThread(parent),
    _parent(parent),
    _projet(projet),
    _nPreviousImage(nPreviousImage),
    _initFrame(parent->getNbFrame()),
    _stop(false)
{
}


void Visionnage::run()
{
    int frame = _initFrame;

    while(!_stop)
    {
        _parent->loadFrame(frame);

        if(_nPreviousImage == -1)
        {
            if(frame == _projet->getNbFrameVideo())
            {
                frame = 0;
            }
            else
            {
                frame += 1;
            }
        }
        else
        {
            if(frame == _initFrame)
            {
                frame -= _nPreviousImage;

                if(frame < 0)
                    frame = 0;
            }
            else
            {
                frame += 1;
            }
        }


        msleep(100);
    }
}

void Visionnage::stop()
{
    _stop = true;
    msleep(20);
    _parent->loadFrame(_initFrame);
}

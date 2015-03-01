#include "visionnage.h"
#include "mainwindow.h"

Visionnage::Visionnage(MainWindow *parent, Projet *projet) :
    QThread(parent),
    _parent(parent),
    _projet(projet),
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

        if(frame == _projet->getNbFrameVideo())
        {
            frame = 0;
        }
        else
        {
            frame += 1;
        }

        msleep(20);
    }
}

void Visionnage::stop()
{
    _stop = true;
}

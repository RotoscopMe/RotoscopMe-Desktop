#ifndef VISIONNAGE_H
#define VISIONNAGE_H

#include <QThread>
#include "core/projet.h"

class MainWindow;

class Visionnage : public QThread
{
    Q_OBJECT
public:
    Visionnage(MainWindow *parent, Projet *projet, int nPreviousImage = -1);

signals:

public slots:
    void stop();

private:
    MainWindow *_parent;
    Projet *_projet;
    int _nPreviousImage;
    int _initFrame;

    bool _stop;

    void run();
};

#endif // VISIONNAGE_H

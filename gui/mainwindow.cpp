#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    QWidget *widget = new QWidget;
        setCentralWidget(widget);

   QMenu *menuFile = menuBar()->addMenu("&Fichier");

   QAction *actionNouveau = new QAction("&Nouveau Projet", this);
      menuFile->addAction(actionNouveau);
   QAction *actionOuvrir = new QAction("&Ouvrir un projet", this);
      menuFile->addAction(actionOuvrir);
   QAction *actionEnregistrer = new QAction("&Enregistrer", this);
      menuFile->addAction(actionEnregistrer);
   QAction *actionEnregistrerSous = new QAction("&Enregistrer sous", this);
      menuFile->addAction(actionEnregistrerSous);
   QAction *actionExporterImages = new QAction("&Exporter en images", this);
       menuFile->addAction(actionExporterImages);
   QAction *actionExporterVideo = new QAction("&Exporter en vidéo", this);
       menuFile->addAction(actionExporterVideo);
   QAction *actionFermerProjet = new QAction("&Fermer le projet", this);
       menuFile->addAction(actionFermerProjet);
   QAction *actionQuitter = new QAction("&Quitter", this);
      menuFile->addAction(actionQuitter);


    setWindowTitle(tr("Rotoscop'Me"));

}


MainWindow::~MainWindow()
{

}


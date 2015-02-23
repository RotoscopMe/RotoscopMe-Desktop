#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    QWidget *widget = new QWidget;
        setCentralWidget(widget);

     setWindowTitle(tr("Rotoscop'Me"));
     createMenu();

     // Couleur
    colorButton = new QPushButton("", this);
    connect(colorButton, SIGNAL(clicked()), this, SLOT(setcolor()));
    colorButton->setGeometry(QRect(5, 100, 20, 20));
    colorLabel =new QLabel(this);
    layout = new QVBoxLayout(this);
    layout->addWidget(colorButton);
    layout->addWidget(colorLabel);
    colorLabel->setGeometry(QRect(30, 86, 50, 50));
    setLayout(layout);

    verticalLayoutWidget = new QWidget(this);
    verticalLayoutWidget->setGeometry(QRect(700, 100, 200, 141));
    verticalLayout = new QVBoxLayout(verticalLayoutWidget);
    ImageOrigineButton = new QPushButton("Afficher l'image d'origine",this);
    verticalLayout->addWidget(ImageOrigineButton);
    PelureOignonButton = new QPushButton("Afficher les pelures d'oignons",this);
    verticalLayout->addWidget(PelureOignonButton);
    NbrPelureLabel = new QLabel("Nombres de pelures d'oignons",verticalLayoutWidget);
    verticalLayout->addWidget(NbrPelureLabel);
    NbrPelurespinBox = new QSpinBox(verticalLayoutWidget);
    NbrPelurespinBox->setMaximum(10);
    NbrPelurespinBox->setMinimum(1);
    verticalLayout->addWidget(NbrPelurespinBox);
    setLayout(verticalLayout);

    horizontalSlider = new QSlider(this);
    horizontalSlider->setGeometry(QRect(160, 500, 350, 19));
    horizontalSlider->setOrientation(Qt::Horizontal);
    graphicsView = new QGraphicsView(this);
    graphicsView->setGeometry(QRect(170, 60, 500, 400));


    verticalLayoutWidget_2 = new QWidget(this);
    verticalLayoutWidget_2->setGeometry(QRect(700, 310, 200, 111));
    verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
    VisioButton = new QPushButton("Visionner depuis le début",this);
    verticalLayout_2->addWidget(VisioButton);
    NimagecheckBox = new QCheckBox("Visionner depuis n images",verticalLayoutWidget_2);
    verticalLayout_2->addWidget(NimagecheckBox);
    Nimages = new QSpinBox(verticalLayoutWidget_2);
    Nimages->setMaximum(10);
    Nimages->setMinimum(1);
    verticalLayout_2->addWidget(Nimages);
}

void MainWindow::setcolor()
{
    QColor color = QColorDialog::getColor(Qt::black, this);
    if (color.isValid())
    {
        colorLabel->setText(color.name());
        colorLabel->setPalette(QPalette(color));
        colorLabel->setAutoFillBackground(true);
    }
}


void MainWindow::createMenu()
{
    // Création de la barre de menu
      QMenu *menuFile = menuBar()->addMenu("&Fichier");
      QMenu *menuEdition = menuBar()->addMenu("&Edition");
      QMenu *menuNavig = menuBar()->addMenu("&Navigation");
      QMenu *menuVisual = menuBar()->addMenu("&Visualisation");
      QMenu *menuPref = menuBar()->addMenu("&Preferences");
      QMenu *menuAide = menuBar()->addMenu("&Aide");

     //Création des sous-menu de Fichier
      QAction *actionNouveau = new QAction("&Nouveau Projet", this);
         menuFile->addAction(actionNouveau);
         actionNouveau->setShortcut(QKeySequence("Ctrl+N"));
         //  connect(actionEnregistrer, SIGNAL(triggered(),qApp, SLOT(new()));

      QAction *actionOuvrir = new QAction("&Ouvrir un projet", this);
         menuFile->addAction(actionOuvrir);
         actionOuvrir->setShortcut(QKeySequence("Ctrl+O"));
         //  connect(actionEnregistrer, SIGNAL(triggered(),qApp, SLOT(open()));
      menuFile->addSeparator();

      QAction *actionEnregistrer = new QAction("&Enregistrer", this);
         menuFile->addAction(actionEnregistrer);
         actionEnregistrer->setShortcut(QKeySequence("Ctrl+S"));
       //  connect(actionEnregistrer, SIGNAL(triggered(),qApp, SLOT(save()));

      QAction *actionEnregistrerSous = new QAction("&Enregistrer sous", this);
         menuFile->addAction(actionEnregistrerSous);
         actionEnregistrerSous->setShortcut(QKeySequence("Shift+Ctrl+S"));
         //  connect(actionEnregistrer, SIGNAL(triggered(),qApp, SLOT(saveas()));
      menuFile->addSeparator();

      QAction *actionExporterImages = new QAction("&Exporter en images", this);
          menuFile->addAction(actionExporterImages);
          actionExporterImages->setShortcut(QKeySequence("Ctrl+I"));
          //  connect(actionEnregistrer, SIGNAL(triggered(),qApp, SLOT(exportPicture()));

      QAction *actionExporterVideo = new QAction("&Exporter en vidéo", this);
          menuFile->addAction(actionExporterVideo);
          actionExporterVideo->setShortcut(QKeySequence("Ctrl+E"));
          //  connect(actionEnregistrer, SIGNAL(triggered(),qApp, SLOT(exportFilm()));
       menuFile->addSeparator();

       QAction *actionFermerProjet = new QAction("&Fermer le projet", this);
          menuFile->addAction(actionFermerProjet);
          //  connect(actionEnregistrer, SIGNAL(triggered(),qApp, SLOT(CloseProject()));

       QAction *actionQuitter = new QAction("&Quitter", this);
         menuFile->addAction(actionQuitter);
         actionQuitter->setShortcut(QKeySequence("Ctrl+Q"));
         connect(actionQuitter, SIGNAL(triggered()), qApp , SLOT(quit()));

         //Création des sous-menu de Edition

         QAction *actionAnnuler = new QAction("&Annuler", this);
           menuEdition->addAction(actionAnnuler);
           actionAnnuler->setShortcut(QKeySequence("Ctrl+Z"));
           //  connect(actionEnregistrer, SIGNAL(triggered(),qApp, SLOT(()));

         QAction *actionRetablir = new QAction("&Retablir", this);
            menuEdition->addAction(actionRetablir);
            actionRetablir->setShortcut(QKeySequence("Ctrl+Y"));
            menuEdition->addSeparator();
         QAction *actionInfo = new QAction("&Information sur le projet", this);
            menuEdition->addAction(actionInfo);

            //Création des sous-menu de Navigation
            QAction *actionImageSuivante = new QAction("&Image suivante", this);
              menuNavig->addAction(actionImageSuivante);
              actionImageSuivante->setShortcut(QKeySequence("Right"));
            QAction *actionImagePrec = new QAction("&Image précédente", this);
               menuNavig->addAction(actionImagePrec);
               actionImagePrec->setShortcut(QKeySequence("Left"));
            QAction *actionAllerDebut = new QAction("&Aller au début", this);
               menuNavig->addAction(actionAllerDebut);
               actionAllerDebut->setShortcut(QKeySequence("Ctrl+Left"));
            QAction *actionAllerFin = new QAction("&Aller à la fin", this);
               menuNavig->addAction(actionAllerFin);
               actionAllerFin->setShortcut(QKeySequence("Ctrl+Right"));


           //Création des sous-menu de Visualisation
           QAction *actionVisioDebut = new QAction("&Visionner depuis le début", this);
              menuVisual->addAction(actionVisioDebut);
              actionVisioDebut->setShortcut(QKeySequence("Ctrl+V"));
           QAction *actionVisioNimage = new QAction("&Visionner depuis n images", this);
              menuVisual->addAction(actionVisioNimage);
              actionVisioNimage->setShortcut(QKeySequence("Ctrl+B"));

              //Création des sous-menu de Préférence
           QAction *actionAfficherImOrig = new QAction("&Afficher les images d'origines", this);
              menuPref->addAction(actionAfficherImOrig);
              actionAfficherImOrig->setShortcut(QKeySequence("Ctrl+J"));
           QAction *actionAfficherPelures = new QAction("&Afficher les pelures d'oignons", this);
              menuPref->addAction(actionAfficherPelures);
              actionAfficherPelures->setShortcut(QKeySequence("Ctrl+K"));
           QAction *actionNbrPelures = new QAction("&Nombres de pelures d'oignons", this);
              menuPref->addAction(actionNbrPelures);
              actionNbrPelures->setShortcut(QKeySequence("Ctrl+L"));
           QAction *actionFreqPelures = new QAction("&Fréquence des pelures d'oignons", this);
              menuPref->addAction(actionFreqPelures);
              actionFreqPelures->setShortcut(QKeySequence("Ctrl+M"));

              //Création des sous-menu d'Aide
           QAction *actionAide = new QAction("&Aide", this);
              menuAide->addAction(actionAide);
              actionAide->setShortcut(QKeySequence("F1"));
           QAction *actionAPropos = new QAction("&A propos", this);
              menuAide->addAction(actionAPropos);
}


MainWindow::~MainWindow()
{

}


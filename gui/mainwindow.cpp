#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    QWidget *widget = new QWidget();
    setCentralWidget(widget);


     setWindowTitle(tr("Rotoscop'Me"));
     createMenu();

        // Outils de dessin
    // Couleur
    colorButton = new QPushButton("");
    connect(colorButton, SIGNAL(clicked()), this, SLOT(setcolor()));
    colorButton->setGeometry(QRect(5, 200, 20, 20));
    colorLabel = new QLabel();

    QVBoxLayout* drawLayout = new QVBoxLayout();
    drawLayout->addWidget(colorButton);
    drawLayout->addWidget(colorLabel);

    //Crayon
    QPixmap pen("pen.png");
    QLabel* penLabel = new QLabel();
    penLabel->setFixedSize(40, 30);
    penButton = new QPushButton("");
    penButton->setFixedSize(10, 10);

    QHBoxLayout* penLayout = new QHBoxLayout();
    penLayout->addWidget(penLabel);
    penLayout->addWidget(penButton);

    //Gomme
    QPixmap gomme("gomme.png");
    QLabel* gommeLabel = new QLabel();
    gommeLabel->setFixedSize(40, 17);
    gommeLabel->setPixmap(gomme);
    gommeButton = new QPushButton("");
    gommeButton->setFixedSize(10, 10);

    QHBoxLayout* gommeLayout = new QHBoxLayout();
    gommeLayout->addWidget(gommeLabel);
    gommeLayout->addWidget(gommeButton);

             // Undo - Redo
       redoButton = new QPushButton("");
       redoButton->setFixedSize(25, 25);
       redoButton->setIcon(QIcon("redo.png"));
       undoButton = new QPushButton("");
       undoButton->setFixedSize(25, 25);
       undoButton->setIcon(QIcon("undo.png"));

      QHBoxLayout* undoredoLayout = new QHBoxLayout();
      undoredoLayout->addWidget(undoButton);
      undoredoLayout->addWidget(redoButton);


       //Preference

    ImageOrigineButton = new QPushButton("Afficher l'image d'origine");
    PelureOignonButton = new QPushButton("Afficher les pelures d'oignons");
    NbrPelureLabel = new QLabel("Nombres de pelures d'oignons");
    NbrPelurespinBox = new QSpinBox();
    NbrPelurespinBox->setMaximum(10);
    NbrPelurespinBox->setMinimum(1);

    QVBoxLayout* preferenceLayout = new QVBoxLayout();
    preferenceLayout->addWidget(ImageOrigineButton);
    preferenceLayout->addWidget(PelureOignonButton);
    preferenceLayout->addWidget(NbrPelureLabel);
    preferenceLayout->addWidget(ImageOrigineButton);
    preferenceLayout->addWidget(NbrPelurespinBox);


    //Visualisation

    VisioButton = new QPushButton("Visionner depuis le début");
    NimagecheckBox = new QCheckBox("Visionner depuis n images");
    Nimages = new QSpinBox();
    Nimages->setMaximum(10);
    Nimages->setMinimum(1);

    QVBoxLayout* visualisationLayout = new QVBoxLayout();
    visualisationLayout->addWidget(VisioButton);
    visualisationLayout->addWidget(NimagecheckBox);
    visualisationLayout->addWidget(Nimages);


    // Mode de lecture

    debutButton = new QPushButton("");
       debutButton->setFixedSize(25, 25);
       debutButton->setIcon(QIcon("debut.png"));

    precedenteButton = new QPushButton("");
        precedenteButton->setFixedSize(25, 25);
        precedenteButton->setIcon(QIcon("precedente.png"));

        QPixmap imagePrecedente("imagePrecedente.png");
        QLabel* imagePrecedenteLabel = new QLabel();
        imagePrecedenteLabel->setFixedSize(25, 25);
        imagePrecedenteLabel->setPixmap(imagePrecedente);

        QPixmap imageEnCours("imageEnCours.png");
        QLabel* imageEnCoursLabel = new QLabel();
        imageEnCoursLabel->setFixedSize(50, 50);
        imageEnCoursLabel->setPixmap(imageEnCours);

        QPixmap imageSuivante("imageSuivante.png");
        QLabel* imageSuivanteLabel = new QLabel();
        imageSuivanteLabel->setFixedSize(25, 25);
        imageSuivanteLabel->setPixmap(imageSuivante);

    suivanteButton = new QPushButton("");
       suivanteButton->setFixedSize(25, 25);
       suivanteButton->setIcon(QIcon("suivante.png"));

    finButton = new QPushButton("");
        finButton->setFixedSize(25, 25);
        finButton->setIcon(QIcon("fin.png"));

    QHBoxLayout* playbackBarLayout = new QHBoxLayout();
    playbackBarLayout->addWidget(debutButton);
    playbackBarLayout->addWidget(precedenteButton);
    playbackBarLayout->addWidget(imagePrecedenteLabel);
    playbackBarLayout->addWidget(imageEnCoursLabel);
    playbackBarLayout->addWidget(imageSuivanteLabel);
    playbackBarLayout->addWidget(suivanteButton);
    playbackBarLayout->addWidget(finButton);


    //Left layout

    QVBoxLayout* leftLayout = new QVBoxLayout();
    leftLayout->addLayout(undoredoLayout);
    leftLayout->addLayout(drawLayout);
    leftLayout->addLayout(penLayout);
    leftLayout->addLayout(gommeLayout);


    //Right layout

    QVBoxLayout* rightLayout = new QVBoxLayout();
    rightLayout->addStretch(1);
    rightLayout->addLayout(preferenceLayout);
    rightLayout->addStretch(2);
    rightLayout->addLayout(visualisationLayout);
    rightLayout->addStretch(1);

    //Bottom layout

    horizontalSlider = new QSlider();
    horizontalSlider->setOrientation(Qt::Horizontal);

    QVBoxLayout* bottomLayout = new QVBoxLayout();
    bottomLayout->addLayout(playbackBarLayout);
    bottomLayout->addWidget(horizontalSlider);


    // Global layout

    graphicsView = new QGraphicsView();

    QGridLayout* layout = new QGridLayout();
    layout->addLayout(leftLayout, 0, 0);
    layout->addWidget(graphicsView, 0, 1);
    layout->addLayout(rightLayout, 0, 2);
    layout->addLayout(bottomLayout, 1,1);

    widget->setLayout(layout);

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


#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    QWidget *widget = new QWidget();
    setCentralWidget(widget);

    setWindowTitle(tr("Rotoscop'Me"));
    createMenu();

    // Outils de dessin

    // Couleur
    _colorButton = new QPushButton("Color");
    connect(_colorButton, SIGNAL(clicked()), this, SLOT(setcolor()));
    _colorButton->setFixedSize(50, 30);
    _colorLabel = new QLabel();
    _colorLabel->setFixedSize(50, 50);

    QVBoxLayout* drawLayout = new QVBoxLayout();
    drawLayout->addWidget(_colorButton);
    drawLayout->addWidget(_colorLabel);

    //Crayon
    _penActiveButton = new QPushButton();
    _penActiveButton->setFixedSize(50, 35);
    _penActiveButton->setIcon(QIcon("pen.png"));
    _penButton = new QPushButton("");
    _penButton->setFixedSize(10, 10);

    QHBoxLayout* penLayout = new QHBoxLayout();
    penLayout->addWidget(_penActiveButton);
    penLayout->addWidget(_penButton);

    //Gomme
    _gommeActiveButton = new QPushButton();
    _gommeActiveButton->setFixedSize(50, 35);
    _gommeActiveButton->setIcon(QIcon("gomme.png"));
    _gommeButton = new QPushButton("");
    _gommeButton->setFixedSize(10, 10);

    QHBoxLayout* gommeLayout = new QHBoxLayout();
    gommeLayout->addWidget(_gommeActiveButton);
    gommeLayout->addWidget(_gommeButton);

    // Undo - Redo
    _redoButton = new QPushButton("");
    _redoButton->setFixedSize(25, 25);
    _redoButton->setIcon(QIcon("redo.png"));
    _undoButton = new QPushButton("");
    _undoButton->setFixedSize(25, 25);
    _undoButton->setIcon(QIcon("undo.png"));

    QHBoxLayout* undoRedoLayout = new QHBoxLayout();
    undoRedoLayout->addWidget(_undoButton);
    undoRedoLayout->addWidget(_redoButton);


    //Preference

    _imageOrigineButton = new QPushButton("Afficher l'image d'origine");
    _pelureOignonButton = new QPushButton("Afficher les pelures d'oignons");
    _nbrPelureLabel = new QLabel("Nombres de pelures d'oignons");
    _nbrPelureSpinBox = new QSpinBox();
    _nbrPelureSpinBox->setMaximum(10);
    _nbrPelureSpinBox->setMinimum(1);

    QVBoxLayout* preferenceLayout = new QVBoxLayout();
    preferenceLayout->addWidget(_imageOrigineButton);
    preferenceLayout->addWidget(_pelureOignonButton);
    preferenceLayout->addWidget(_nbrPelureLabel);
    preferenceLayout->addWidget(_imageOrigineButton);
    preferenceLayout->addWidget(_nbrPelureSpinBox);


    //Visualisation

    _visioButton = new QPushButton("Visionner depuis le début");
    _nImageCheckBox = new QCheckBox("Visionner depuis n images");
    _nImages = new QSpinBox();
    _nImages->setMaximum(10);
    _nImages->setMinimum(1);

    QVBoxLayout* visualisationLayout = new QVBoxLayout();
    visualisationLayout->addWidget(_visioButton);
    visualisationLayout->addWidget(_nImageCheckBox);
    visualisationLayout->addWidget(_nImages);


    // Mode de lecture

    _debutButton = new QPushButton("");
    _debutButton->setFixedSize(25, 25);
    _debutButton->setIcon(QIcon("debut.png"));

    _precedenteButton = new QPushButton("");
    _precedenteButton->setFixedSize(25, 25);
    _precedenteButton->setIcon(QIcon("precedente.png"));

    QPixmap imagePrecedente("imagePrecedente.png");
    _imagePrecedenteLabel = new QLabel();
    _imagePrecedenteLabel->setFixedSize(25, 25);
    _imagePrecedenteLabel->setPixmap(imagePrecedente);

    QPixmap imageEnCours("imageEnCours.png");
    _imageEnCoursLabel = new QLabel();
    _imageEnCoursLabel->setFixedSize(50, 50);
    _imageEnCoursLabel->setPixmap(imageEnCours);

    QPixmap imageSuivante("imageSuivante.png");
    _imageSuivanteLabel = new QLabel();
    _imageSuivanteLabel->setFixedSize(25, 25);
    _imageSuivanteLabel->setPixmap(imageSuivante);

    _suivanteButton = new QPushButton("");
    _suivanteButton->setFixedSize(25, 25);
    _suivanteButton->setIcon(QIcon("suivante.png"));

    _finButton = new QPushButton("");
    _finButton->setFixedSize(25, 25);
    _finButton->setIcon(QIcon("fin.png"));

    QHBoxLayout* playbackBarLayout = new QHBoxLayout();
    playbackBarLayout->addWidget(_debutButton);
    playbackBarLayout->addWidget(_precedenteButton);
    playbackBarLayout->addWidget(_imagePrecedenteLabel);
    playbackBarLayout->addWidget(_imageEnCoursLabel);
    playbackBarLayout->addWidget(_imageSuivanteLabel);
    playbackBarLayout->addWidget(_suivanteButton);
    playbackBarLayout->addWidget(_finButton);


    //Left layout

    QVBoxLayout* leftLayout = new QVBoxLayout();
    leftLayout->addLayout(undoRedoLayout);
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

    _horizontalSlider = new QSlider();
    _horizontalSlider->setOrientation(Qt::Horizontal);

    QVBoxLayout* bottomLayout = new QVBoxLayout();
    bottomLayout->addLayout(playbackBarLayout);
    bottomLayout->addWidget(_horizontalSlider);


    // Global layout

    _drawArea = new DrawArea();

    QGridLayout* layout = new QGridLayout();
    layout->addLayout(leftLayout, 0, 0);
    layout->addWidget(_drawArea, 0, 1);
    layout->addLayout(rightLayout, 0, 2);
    layout->addLayout(bottomLayout, 1,1);

    widget->setLayout(layout);

    connect(_penButton, SIGNAL(clicked()), this, SLOT(switchToPen()));
    connect(_gommeButton, SIGNAL(clicked()), this, SLOT(switchToRubber()));
}

void MainWindow::switchToPen()
{
    _drawArea->setTool(PEN);
}

void MainWindow::switchToRubber()
{
    _drawArea->setTool(RUBBER);
}


void MainWindow::setcolor()
{
    QColor color = QColorDialog::getColor(Qt::black, this);
    if (color.isValid())
    {
        _colorLabel->setText(color.name());
        _colorLabel->setPalette(QPalette(color));
        _colorLabel->setAutoFillBackground(true);
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


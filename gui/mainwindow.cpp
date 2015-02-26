#include "mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    QWidget *widget = new QWidget();
    setCentralWidget(widget);

    setWindowTitle(tr("Rotoscop'Me"));
    createMenu();

    // Outils de dessin

    // Couleur

    _colorButton = new QPushButton("Color");
    _colorButton->setFixedSize(50, 30);
    _colorLabel = new QLabel();
    _colorLabel->setFixedSize(50, 50);
    connect(_colorButton, SIGNAL(clicked()), this, SLOT(optionColor()));
    

    QVBoxLayout* drawLayout = new QVBoxLayout();
    drawLayout->addWidget(_colorButton);
    drawLayout->addWidget(_colorLabel);

    //Crayon

    _selectPenButton = new QPushButton(QIcon("pen.png"), "");
    _selectPenButton->setFixedSize(50, 35);
    _selectPenButton->setCheckable(true);
    _selectPenButton->setChecked(true);
    _optionPenButton = new QPushButton();
    _optionPenButton->setFixedSize(10, 10);

    QHBoxLayout* penLayout = new QHBoxLayout();
    penLayout->addWidget(_selectPenButton);
    penLayout->addWidget(_optionPenButton);

    //Gomme
    _selectRubberButton = new QPushButton(QIcon("gomme.png"), "");
    _selectRubberButton->setFixedSize(50, 35);
    _selectRubberButton->setCheckable(true);
    _optionRubberButton = new QPushButton();
    _optionRubberButton->setFixedSize(10, 10);

    QHBoxLayout* rubberLayout = new QHBoxLayout();
    rubberLayout->addWidget(_selectRubberButton);
    rubberLayout->addWidget(_optionRubberButton);
    

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
    leftLayout->addLayout(rubberLayout);


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

    connect(_selectPenButton, SIGNAL(clicked()), this, SLOT(switchToPen()));
    connect(_selectRubberButton, SIGNAL(clicked()), this, SLOT(switchToRubber()));
    connect(_optionPenButton, SIGNAL(clicked()), this, SLOT(optionPen()));
    connect(_optionRubberButton, SIGNAL(clicked()), this, SLOT(optionRubber()));


    //Menu crayon

    QPoint *centerPenButton = new QPoint(_optionPenButton->x(), _optionPenButton->y() + menuBar()->size().height() + _optionPenButton->height()/2);

    _optionPenMenu = new ToolDialog(centerPenButton, this);
    _optionPenMenu->resize(150,40);

    QPushButton *smallPen = new QPushButton(QIcon("penPetit.png"), "");
    QPushButton *mediumPen = new QPushButton(QIcon("penMoyen.png"), "");
    QPushButton *largePen = new QPushButton(QIcon("penGrand.png"), "");

    _optionPenMenu->addWidget(smallPen, 1, 1);
    _optionPenMenu->addWidget(mediumPen, 1, 2);
    _optionPenMenu->addWidget(largePen, 1, 3);

    connect(smallPen, SIGNAL(clicked()), this, SLOT(setPenSmall()));
    connect(mediumPen, SIGNAL(clicked()), this, SLOT(setPenMedium()));
    connect(largePen, SIGNAL(clicked()), this, SLOT(setPenLarge()));

    _optionPenMenu->hide();

    connect(smallPen, SIGNAL(clicked()), _optionPenMenu, SLOT(hide()));
    connect(mediumPen, SIGNAL(clicked()), _optionPenMenu, SLOT(hide()));
    connect(largePen, SIGNAL(clicked()), _optionPenMenu, SLOT(hide()));


    //Menu gomme

    QPoint *centerRubberButton = new QPoint(_optionRubberButton->x(), _optionRubberButton->y() + menuBar()->size().height() + _optionRubberButton->height()/2);

    _optionRubberMenu = new ToolDialog(centerRubberButton, this);
    _optionRubberMenu->resize(150,40);

    QPushButton *smallRubber = new QPushButton(QIcon("rubberPetit.png"), "");
    QPushButton *mediumRubber = new QPushButton(QIcon("rubberMoyen.png"), "");
    QPushButton *largeRubber = new QPushButton(QIcon("rubberGrand.png"), "");

    _optionRubberMenu->addWidget(smallRubber, 1, 1);
    _optionRubberMenu->addWidget(mediumRubber, 1, 2);
    _optionRubberMenu->addWidget(largeRubber, 1, 3);

    connect(smallRubber, SIGNAL(clicked()), this, SLOT(setRubberSmall()));
    connect(mediumRubber, SIGNAL(clicked()), this, SLOT(setRubberMedium()));
    connect(largeRubber, SIGNAL(clicked()), this, SLOT(setRubberLarge()));

    _optionRubberMenu->hide();

    connect(smallRubber, SIGNAL(clicked()), _optionRubberMenu, SLOT(hide()));
    connect(mediumRubber, SIGNAL(clicked()), _optionRubberMenu, SLOT(hide()));
    connect(largeRubber, SIGNAL(clicked()), _optionRubberMenu, SLOT(hide()));


    //Menu color

    QPoint *centerColorButton = new QPoint(_colorButton->x(), _colorButton->y() + menuBar()->size().height() + _colorButton->height()/2);

    _colorMenu = new ToolDialog(centerColorButton, this);
    _colorMenu->resize(120,80);

    QPushButton *colorBlack = new QPushButton();
    colorBlack->setStyleSheet("background-color:black; border:none");
    QPushButton *colorRed = new QPushButton();
    colorRed->setStyleSheet("background-color:red; border:none");
    QPushButton *colorBlue = new QPushButton();
    colorBlue->setStyleSheet("background-color:blue; border:none");
    QPushButton *colorGreen = new QPushButton();
    colorGreen->setStyleSheet("background-color:green; border:none");
    QPushButton *colorYellow = new QPushButton();
    colorYellow->setStyleSheet("background-color:yellow; border:none");
    QPushButton *colorBrown = new QPushButton();
    colorBrown->setStyleSheet("background-color:#8B4513; border:none");

    _colorMenu->addWidget(colorBlack, 1, 1);
    _colorMenu->addWidget(colorRed, 1, 2);
    _colorMenu->addWidget(colorBlue, 1, 3);
    _colorMenu->addWidget(colorGreen, 2, 1);
    _colorMenu->addWidget(colorYellow, 2, 2);
    _colorMenu->addWidget(colorBrown, 2, 3);

    connect(colorBlack, SIGNAL(clicked()), this, SLOT(setColorBlack()));
    connect(colorRed, SIGNAL(clicked()), this, SLOT(setColorRed()));
    connect(colorBlue, SIGNAL(clicked()), this, SLOT(setColorBlue()));
    connect(colorGreen, SIGNAL(clicked()), this, SLOT(setColorGreen()));
    connect(colorYellow, SIGNAL(clicked()), this, SLOT(setColorYellow()));
    connect(colorBrown, SIGNAL(clicked()), this, SLOT(setColorBrown()));

    _colorMenu->hide();

    connect(colorBlack, SIGNAL(clicked()), _colorMenu, SLOT(hide()));
    connect(colorRed, SIGNAL(clicked()), _colorMenu, SLOT(hide()));
    connect(colorBlue, SIGNAL(clicked()), _colorMenu, SLOT(hide()));
    connect(colorGreen, SIGNAL(clicked()), _colorMenu, SLOT(hide()));
    connect(colorYellow, SIGNAL(clicked()), _colorMenu, SLOT(hide()));
    connect(colorBrown, SIGNAL(clicked()), _colorMenu, SLOT(hide()));


    //Connect menu

    connect(_selectPenButton, SIGNAL(clicked()), this, SLOT(hideMenu()));
    connect(_selectRubberButton, SIGNAL(clicked()), this, SLOT(hideMenu()));
    connect(_drawArea, SIGNAL(onClick()), this, SLOT(hideMenu()));
    connect(_imageOrigineButton, SIGNAL(clicked()), this, SLOT(hideMenu()));
    connect(_pelureOignonButton, SIGNAL(clicked()), this, SLOT(hideMenu()));
    connect(_nbrPelureSpinBox, SIGNAL(valueChanged(int)), this, SLOT(hideMenu()));
    connect(_horizontalSlider, SIGNAL(sliderPressed()), this, SLOT(hideMenu()));
    connect(_visioButton, SIGNAL(clicked()), this, SLOT(hideMenu()));
    connect(_nImageCheckBox, SIGNAL(clicked()), this, SLOT(hideMenu()));
    connect(_nImages, SIGNAL(valueChanged(int)), this, SLOT(hideMenu()));
    connect(_undoButton, SIGNAL(clicked()), this, SLOT(hideMenu()));
    connect(_redoButton, SIGNAL(clicked()), this, SLOT(hideMenu()));
    connect(_debutButton, SIGNAL(clicked()), this, SLOT(hideMenu()));
    connect(_finButton, SIGNAL(clicked()), this, SLOT(hideMenu()));
    connect(_precedenteButton, SIGNAL(clicked()), this, SLOT(hideMenu()));
    connect(_suivanteButton, SIGNAL(clicked()), this, SLOT(hideMenu()));

    connect(_optionPenButton, SIGNAL(clicked()), _optionRubberMenu, SLOT(hide()));
    connect(_optionPenButton, SIGNAL(clicked()), _colorMenu, SLOT(hide()));
    connect(_optionRubberButton, SIGNAL(clicked()), _optionPenMenu, SLOT(hide()));
    connect(_optionRubberButton, SIGNAL(clicked()), _colorMenu, SLOT(hide()));
    connect(_colorButton, SIGNAL(clicked()), _optionPenMenu, SLOT(hide()));
    connect(_colorButton, SIGNAL(clicked()), _optionRubberMenu, SLOT(hide()));

    setCurrentFile("");

}

void MainWindow::switchToPen()
{
    _drawArea->setTool(PEN);
    _selectPenButton->setChecked(true);
    _selectRubberButton->setChecked(false);
}

void MainWindow::switchToRubber()
{
    _drawArea->setTool(RUBBER);
    _selectPenButton->setChecked(false);
    _selectRubberButton->setChecked(true);
}

void MainWindow::optionPen()
{
    QPoint *centerPenButton = new QPoint(_optionPenButton->x(), _optionPenButton->y() + menuBar()->size().height() + _optionPenButton->height()/2);
    _optionPenMenu->update(centerPenButton);
    _optionPenMenu->show();
}

void MainWindow::optionRubber()
{
    QPoint *centerRubberButton = new QPoint(_optionRubberButton->x(), _optionRubberButton->y() + menuBar()->size().height() + _optionRubberButton->height()/2);
    _optionRubberMenu->update(centerRubberButton);
    _optionRubberMenu->show();
}

void MainWindow::optionColor()
{
    QPoint *centerColorButton = new QPoint(_colorButton->x(), _colorButton->y() + menuBar()->size().height() + _colorButton->height()/2);
    _colorMenu->update(centerColorButton);
    _colorMenu->show();
}

void MainWindow::setPenSmall()
{
    _drawArea->setPenWidth(1);
}

void MainWindow::setPenMedium()
{
    _drawArea->setPenWidth(3);
}

void MainWindow::setPenLarge()
{
    _drawArea->setPenWidth(5);
}

void MainWindow::setRubberSmall()
{
    _drawArea->setRubberWidth(1);
}

void MainWindow::setRubberMedium()
{
    _drawArea->setRubberWidth(3);
}

void MainWindow::setRubberLarge()
{
    _drawArea->setRubberWidth(5);
}

void MainWindow::setColorBlack()
{
    _drawArea->setPenColor(QColor(Qt::black));
}

void MainWindow::setColorRed()
{
    _drawArea->setPenColor(QColor(Qt::red));
}

void MainWindow::setColorBlue()
{
    _drawArea->setPenColor(QColor(Qt::blue));
}

void MainWindow::setColorGreen()
{
    _drawArea->setPenColor(QColor(Qt::green));
}

void MainWindow::setColorYellow()
{
    _drawArea->setPenColor(QColor(Qt::yellow));
}

void MainWindow::setColorBrown()
{
    _drawArea->setPenColor(QColor(139,69,19));
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

void MainWindow::hideMenu()
{
    _optionPenMenu->hide();
    _optionRubberMenu->hide();
    _colorMenu->hide();
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
    connect(actionNouveau, SIGNAL(triggered()), this, SLOT(newFile()));

      QAction *actionOuvrir = new QAction("&Ouvrir un projet", this);
         menuFile->addAction(actionOuvrir);
         actionOuvrir->setShortcut(QKeySequence("Ctrl+O"));
         connect(actionOuvrir, SIGNAL(triggered()), this, SLOT(open()));
      menuFile->addSeparator();

      QAction *actionEnregistrer = new QAction("&Enregistrer", this);
         menuFile->addAction(actionEnregistrer);
         actionEnregistrer->setShortcut(QKeySequence("Ctrl+S"));
         connect(actionEnregistrer, SIGNAL(triggered()), this, SLOT(save()));

      QAction *actionEnregistrerSous = new QAction("&Enregistrer sous", this);
         menuFile->addAction(actionEnregistrerSous);
         actionEnregistrerSous->setShortcut(QKeySequence("Shift+Ctrl+S"));
         connect(actionEnregistrerSous, SIGNAL(triggered()), this, SLOT(saveAs()));
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
              connect(actionAPropos, SIGNAL(triggered()), qApp, SLOT(aboutQt()));

}

void MainWindow::mousePressEvent(QMouseEvent *)
{
    _optionPenMenu->hide();
    _optionRubberMenu->hide();
    _colorMenu->hide();
}


void MainWindow::newFile()
{
        _drawArea->clear();
        setCurrentFile("");
}

void MainWindow::open()
{

        QString fileName = QFileDialog::getOpenFileName(this);
        if (!fileName.isEmpty())
            loadFile(fileName);

   }

bool MainWindow::save()
{
    if (curFile.isEmpty()) {
        return saveAs();
    } else {
        return saveFile(curFile);
    }
}

bool MainWindow::saveAs()
{
    QFileDialog dialog(this);
    dialog.setWindowModality(Qt::WindowModal);
    dialog.setAcceptMode(QFileDialog::AcceptSave);
    QStringList files;
    if (dialog.exec())
        files = dialog.selectedFiles();
    else
        return false;

    return saveFile(files.at(0));
}

void MainWindow::about()
{
   QMessageBox::about(this, tr("About Application"),
            tr("Rotoscop'Me est une application de rotoscopie créée par Matthieu RIOU et Manon BOBIN."));
}

void MainWindow::loadFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return;
    }

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File loaded"), 2000);
}

bool MainWindow::saveFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, tr("Application"),
                             tr("Cannot write file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return false;
    }
    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File saved"), 2000);
    return true;
}

void MainWindow::setCurrentFile(const QString &fileName)
{
    curFile = fileName;

    QString shownName = curFile;
    if (curFile.isEmpty())
        shownName = "untitled.txt";
    setWindowFilePath(shownName);
}

QString MainWindow::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}

MainWindow::~MainWindow()
{

}


#include "mainwindow.h"
#include "createprojectdialog.h"
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), projet(NULL), _nbFrame(0), _modified(false)
{
    QWidget *widget = new QWidget();
    setCentralWidget(widget);

    setWindowTitle(tr("Rotoscop'Me"));
    createMenu();

    centralWidget()->hide();

}

void MainWindow::launch()
{
    homePageOuvrir();
}

void MainWindow::homePageOuvrir()
{
    QDialog *homepage = new QDialog(this);

    homepage->setWindowTitle(tr("Rotoscop'Me - Bienvenue "));
    homepage->setFixedSize(700, 300);

    QFont policeTitle("calibri");
    policeTitle.setPointSize (60);
    QLabel *titreLabel = new QLabel("Rotoscop'Me",homepage);
    titreLabel->setGeometry(QRect(100, 50, 600, 100));
    titreLabel->setFont(policeTitle);

    QPushButton *newButton = new QPushButton("Nouveau",homepage );
    newButton->setGeometry(QRect(150, 200, 100, 50));
    connect(newButton, SIGNAL(clicked()), homepage, SLOT(close()));
    connect(newButton, SIGNAL(clicked()), this, SLOT(createProjectPageOuvrir()));
    QPushButton *openButton = new QPushButton("Ouvrir", homepage);
    openButton->setGeometry(QRect(450, 200, 100, 50));
    connect(openButton, SIGNAL(clicked()), homepage, SLOT(close()));
    connect(openButton, SIGNAL(clicked()), this, SLOT(open()));

    homepage->exec();
}

void MainWindow::createProjectPageOuvrir()
{
    CreateProjectDialog dialog(this);

    dialog.exec();

    try
    {
        QString name(dialog.getNom());
        QDir dir(dialog.getWorkspace());
        QFile file(dialog.getVideo());
        int freq(dialog.getFrequence());

        projet = Projet::create(name, dir, file, freq);
        projectPage();
        centralWidget()->show();
    }
    catch(QString e)
    {
        qDebug() << e;
    }
}

void MainWindow::projectPage()
{
    // Outils de dessin

    // Couleur

    _colorButton = new QPushButton();
    _colorButton->setStyleSheet("background-color:black");
    _colorButton->setFixedSize(40, 40);
    connect(_colorButton, SIGNAL(clicked()), this, SLOT(optionColor()));


    QHBoxLayout* drawLayout = new QHBoxLayout();
    drawLayout->addWidget(_colorButton);
    drawLayout->setAlignment(_colorButton, Qt::AlignCenter);

    //Crayon

    _selectPenButton = new QPushButton(QIcon("pen.png"), "");
    _selectPenButton->setFixedSize(50, 50);
    _selectPenButton->setCheckable(true);
    _selectPenButton->setChecked(true);
    _optionPenButton = new QPushButton(QIcon("penPetit.png"), "");
    _optionPenButton->setFixedSize(30, 30);

    QHBoxLayout* penLayout = new QHBoxLayout();
    penLayout->addWidget(_selectPenButton);
    penLayout->addWidget(_optionPenButton);

    //Gomme
    _selectRubberButton = new QPushButton(QIcon("gomme.png"), "");
    _selectRubberButton->setFixedSize(50, 50);
    _selectRubberButton->setCheckable(true);
    _optionRubberButton = new QPushButton(QIcon("rubberPetit.png"), "");
    _optionRubberButton->setFixedSize(30, 30);

    QHBoxLayout* rubberLayout = new QHBoxLayout();
    rubberLayout->addWidget(_selectRubberButton);
    rubberLayout->addWidget(_optionRubberButton);


    // Undo - Redo
    _redoButton = new QPushButton(QIcon("redo.png"), "");
    _redoButton->setFixedSize(40, 40);
    _undoButton = new QPushButton(QIcon("undo.png"), "");
    _undoButton->setFixedSize(40, 40);

    undoRedoGroupBox = new QGroupBox(tr(""));

    QHBoxLayout* undoRedoLayout = new QHBoxLayout();
    undoRedoLayout->addWidget(_undoButton);
    undoRedoLayout->addWidget(_redoButton);
    undoRedoGroupBox->setLayout(undoRedoLayout);


    //Preference

    _imageOrigineButton = new QPushButton("Afficher l'image d'origine");
    _imageOrigineButton->setCheckable(true);
    _imageOrigineButton->setChecked(true);
    _pelureOignonButton = new QPushButton("Afficher les pelures d'oignons");
    _pelureOignonButton->setCheckable(true);
    _nbrPelureLabel = new QLabel("Nombres de pelures d'oignons");
    _nbrPelureSpinBox = new QSpinBox();
    _nbrPelureSpinBox->setMaximum(10);
    _nbrPelureSpinBox->setMinimum(1);
    _nbrPelureSpinBox->setEnabled(false);

    preferenceGroupBox = new QGroupBox(tr("Préférence"));

    QVBoxLayout* preferenceLayout = new QVBoxLayout();
    preferenceLayout->addWidget(_imageOrigineButton);
    preferenceLayout->addWidget(_pelureOignonButton);
    preferenceLayout->addWidget(_nbrPelureLabel);
    preferenceLayout->addWidget(_imageOrigineButton);
    preferenceLayout->addWidget(_nbrPelureSpinBox);
    preferenceGroupBox->setLayout(preferenceLayout);

    connect(_pelureOignonButton, SIGNAL(clicked(bool)), _nbrPelureSpinBox, SLOT(setEnabled(bool)));
    connect(_imageOrigineButton, SIGNAL(clicked()), this, SLOT(reloadCurrentFrame()));
    connect(_pelureOignonButton, SIGNAL(clicked()), this, SLOT(reloadCurrentFrame()));
    connect(_nbrPelureSpinBox, SIGNAL(valueChanged(int)), this, SLOT(reloadCurrentFrame()));


    //Visualisation

    _visioButton = new QPushButton("Visionner depuis le début");
    _visioButton->setCheckable(true);
    _nImageVisioButton = new QPushButton("Visionner depuis n images");
    _nImageVisioButton->setCheckable(true);
    _nImages = new QSpinBox();
    _nImages->setMaximum(projet->getNbFrameVideo());
    _nImages->setMinimum(2);

    visualisationGroupBox = new QGroupBox(tr("Visualisation"));

    QVBoxLayout* visualisationLayout = new QVBoxLayout();
    visualisationLayout->addWidget(_visioButton);
    visualisationLayout->addWidget(_nImageVisioButton);
    visualisationLayout->addWidget(_nImages);
    visualisationGroupBox->setLayout(visualisationLayout);

    connect(_visioButton, SIGNAL(clicked()), this, SLOT(startVisionAll()));
    connect(_nImageVisioButton, SIGNAL(clicked()), this, SLOT(startVisionPrevious()));

    // Mode de lecture

    _debutButton = new QPushButton("");
    _debutButton->setFixedSize(25, 25);
    _debutButton->setIcon(QIcon("debut.png"));

    _precedenteButton = new QPushButton("");
    _precedenteButton->setFixedSize(25, 25);
    _precedenteButton->setIcon(QIcon("precedente.png"));

    QImage black(40,40, QImage::Format_ARGB32);
    black.fill(Qt::black);

    _imagePrecedenteLabel = new QLabel();
    _imagePrecedenteLabel->setFixedSize(50, 50);
    _imagePrecedenteLabel->setPixmap(QPixmap::fromImage(black));

    QPixmap imageEnCours("imageEnCours.png");
    _imageEnCoursLabel = new QLabel();
    _imageEnCoursLabel->setFixedSize(60, 60);
    _imageEnCoursLabel->setPixmap(QPixmap::fromImage(projet->getImageVideo(0)->scaled(50,50)));

    QPixmap imageSuivante("imageSuivante.png");
    _imageSuivanteLabel = new QLabel();
    _imageSuivanteLabel->setFixedSize(50, 50);
    _imageSuivanteLabel->setPixmap(QPixmap::fromImage(projet->getImageVideo(1)->scaled(40,40)));

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

    connect(_precedenteButton, SIGNAL(clicked()), this, SLOT(previousFrame()));
    connect(_suivanteButton, SIGNAL(clicked()), this, SLOT(nextFrame()));
    connect(_debutButton, SIGNAL(clicked()), this, SLOT(firstFrame()));
    connect(_finButton, SIGNAL(clicked()), this, SLOT(lastFrame()));



    //Palette
    paletteGroupBox = new QGroupBox(tr("Palette"));

    QVBoxLayout *paletteLayout = new QVBoxLayout();
    paletteLayout->addLayout(drawLayout);
    paletteLayout->addLayout(penLayout);
    paletteLayout->addLayout(rubberLayout);
    paletteGroupBox->setLayout(paletteLayout);

    //Left layout

    QVBoxLayout* leftLayout = new QVBoxLayout();
    leftLayout->addStretch(1);
    leftLayout->addWidget(undoRedoGroupBox);
    leftLayout->addStretch(2);
    leftLayout->addWidget(paletteGroupBox);
    leftLayout->addStretch(4);

    //Right layout

    QVBoxLayout* rightLayout = new QVBoxLayout();
    rightLayout->addStretch(1);
    rightLayout->addWidget(preferenceGroupBox);
    rightLayout->addStretch(2);
    rightLayout->addWidget(visualisationGroupBox);
    rightLayout->addStretch(1);

    //Bottom layout

    _horizontalSlider = new QSlider();
    _horizontalSlider->setOrientation(Qt::Horizontal);
    _horizontalSlider->setMinimum(0);
    _horizontalSlider->setMaximum(projet->getNbFrameVideo()-1);

    QVBoxLayout* bottomLayout = new QVBoxLayout();
    bottomLayout->addLayout(playbackBarLayout);
    bottomLayout->addWidget(_horizontalSlider);

    connect(_horizontalSlider, SIGNAL(sliderMoved(int)), this, SLOT(loadFrame(int)));


    // Global layout

    _drawArea = new DrawArea(projet->getImageOutput(_nbFrame));
    connect(_drawArea, SIGNAL(onClick()), this, SLOT(projectModified()));

    _calqueContainer = new CalqueContainer(projet->getImageVideo(_nbFrame), QList<QImage*>(), _drawArea);

    QGridLayout* layout = new QGridLayout();
    layout->addLayout(leftLayout, 0, 0);
    layout->addLayout(_calqueContainer, 0, 1);
    layout->addLayout(rightLayout, 0, 2);
    layout->addLayout(bottomLayout, 1,1);

    centralWidget()->setLayout(layout);

    connect(_selectPenButton, SIGNAL(clicked()), this, SLOT(switchToPen()));
    connect(_selectRubberButton, SIGNAL(clicked()), this, SLOT(switchToRubber()));
    connect(_optionPenButton, SIGNAL(clicked()), this, SLOT(optionPen()));
    connect(_optionRubberButton, SIGNAL(clicked()), this, SLOT(optionRubber()));


    //Menu crayon

    QPoint *centerPenButton = new QPoint(paletteGroupBox->x() + _optionPenButton->x(), paletteGroupBox->y() + _optionPenButton->y() + menuBar()->size().height() + _optionPenButton->height()/2);

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

    QPoint *centerRubberButton = new QPoint(paletteGroupBox->x() + _optionRubberButton->x(), paletteGroupBox->y() + _optionRubberButton->y() + menuBar()->size().height() + _optionRubberButton->height()/2);

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

    QPoint *centerColorButton = new QPoint(paletteGroupBox->x() + _colorButton->x(), paletteGroupBox->y() + _colorButton->y() + menuBar()->size().height() + _colorButton->height()/2);

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
    connect(_nImageVisioButton, SIGNAL(clicked()), this, SLOT(hideMenu()));
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


    connect(_undoButton, SIGNAL(clicked()), _drawArea, SLOT(undo()));
    connect(_redoButton, SIGNAL(clicked()), _drawArea, SLOT(redo()));

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
    QPoint *centerPenButton = new QPoint(paletteGroupBox->x() + _optionPenButton->x(), paletteGroupBox->y() + _optionPenButton->y() + menuBar()->size().height() + _optionPenButton->height()/2);
    _optionPenMenu->update(centerPenButton);
    _optionPenMenu->show();
}

void MainWindow::optionRubber()
{
    QPoint *centerRubberButton = new QPoint(paletteGroupBox->x() + _optionRubberButton->x(), paletteGroupBox->y() + _optionRubberButton->y() + menuBar()->size().height() + _optionRubberButton->height()/2);
    _optionRubberMenu->update(centerRubberButton);
    _optionRubberMenu->show();
}

void MainWindow::optionColor()
{
    QPoint *centerColorButton = new QPoint(paletteGroupBox->x() + _colorButton->x(), paletteGroupBox->y() + _colorButton->y() + menuBar()->size().height() + _colorButton->height()/2);
    _colorMenu->update(centerColorButton);
    _colorMenu->show();
}

void MainWindow::setPenSmall()
{
    _drawArea->setPenWidth(1);
    _optionPenButton->setIcon(QIcon("penPetit.png"));
}

void MainWindow::setPenMedium()
{
    _drawArea->setPenWidth(3);
    _optionPenButton->setIcon(QIcon("penMoyen.png"));
}

void MainWindow::setPenLarge()
{
    _drawArea->setPenWidth(5);
    _optionPenButton->setIcon(QIcon("penGrand.png"));
}

void MainWindow::setRubberSmall()
{
    _drawArea->setRubberWidth(1);
    _optionRubberButton->setIcon(QIcon("rubberPetit.png"));
}

void MainWindow::setRubberMedium()
{
    _drawArea->setRubberWidth(3);
    _optionRubberButton->setIcon(QIcon("rubberMoyen.png"));
}

void MainWindow::setRubberLarge()
{
    _drawArea->setRubberWidth(5);
    _optionRubberButton->setIcon(QIcon("rubberGrand.png"));
}

void MainWindow::setColorBlack()
{
    _drawArea->setPenColor(QColor(Qt::black));
    _colorButton->setStyleSheet("background-color:black;");
}

void MainWindow::setColorRed()
{
    _drawArea->setPenColor(QColor(Qt::red));
    _colorButton->setStyleSheet("background-color:red;");
}

void MainWindow::setColorBlue()
{
    _drawArea->setPenColor(QColor(Qt::blue));
    _colorButton->setStyleSheet("background-color:blue;");
}

void MainWindow::setColorGreen()
{
    _drawArea->setPenColor(QColor(Qt::green));
    _colorButton->setStyleSheet("background-color:green;");
}

void MainWindow::setColorYellow()
{
    _drawArea->setPenColor(QColor(Qt::yellow));
    _colorButton->setStyleSheet("background-color:yellow");
}

void MainWindow::setColorBrown()
{
    _drawArea->setPenColor(QColor(139,69,19));
    _colorButton->setStyleSheet("background-color:#8B4513;");
}

void MainWindow::hideMenu()
{
    _optionPenMenu->hide();
    _optionRubberMenu->hide();
    _colorMenu->hide();
}

void MainWindow::loadFrame(int nbFrame)
{
    if(nbFrame >= 0 && nbFrame < projet->getNbFrameVideo())
    {
        _nbFrame = nbFrame;

        QList<QImage*> calque;
        if(_pelureOignonButton->isChecked())
        {
            for(int i = 0; i < _nbFrame && i < _nbrPelureSpinBox->value(); i++)
            {
                calque.append(projet->getImageOutput(_nbFrame-1-i));
            }
        }

        QImage* imageVideo;
        if(_imageOrigineButton->isChecked())
        {
            imageVideo = projet->getImageVideo(_nbFrame);
        }
        else
        {
            imageVideo = new QImage(projet->sizeOutput, QImage::Format_ARGB32);
            imageVideo->fill(Qt::white);
        }

        _calqueContainer->loadFrame(imageVideo, calque);
        _drawArea->load(projet->getImageOutput(_nbFrame));

        _horizontalSlider->setValue(_nbFrame);

        QImage black(40, 40, QImage::Format_ARGB32);
        black.fill(Qt::black);

        if(nbFrame > 0)
            _imagePrecedenteLabel->setPixmap(QPixmap::fromImage(projet->getImageVideo(_nbFrame-1)->scaled(40, 40)));
        else
            _imagePrecedenteLabel->setPixmap(QPixmap::fromImage(black));

        if(nbFrame < projet->getNbFrameVideo() -1)
            _imageSuivanteLabel->setPixmap(QPixmap::fromImage(projet->getImageVideo(_nbFrame+1)->scaled(40,40)));
        else
            _imageSuivanteLabel->setPixmap(QPixmap::fromImage(black));

        _imageEnCoursLabel->setPixmap(QPixmap::fromImage(projet->getImageVideo(_nbFrame)->scaled(50,50)));
    }
}

void MainWindow::previousFrame()
{
    loadFrame(_nbFrame-1);
}

void MainWindow::nextFrame()
{
    loadFrame(_nbFrame+1);
}

void MainWindow::firstFrame()
{
    loadFrame(0);
}

void MainWindow::lastFrame()
{
    loadFrame(projet->getNbFrameVideo()-1);
}

void MainWindow::reloadCurrentFrame()
{
    loadFrame(_nbFrame);
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
    connect(actionNouveau, SIGNAL(triggered()), this, SLOT(newProject()));

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
          connect(actionExporterImages, SIGNAL(triggered()), this, SLOT(exportImage()));

      QAction *actionExporterVideo = new QAction("&Exporter en vidéo", this);
          menuFile->addAction(actionExporterVideo);
          actionExporterVideo->setShortcut(QKeySequence("Ctrl+E"));
          connect(actionExporterVideo, SIGNAL(triggered()), this, SLOT(exportVideo()));
       menuFile->addSeparator();

       QAction *actionFermerProjet = new QAction("&Fermer le projet", this);
          menuFile->addAction(actionFermerProjet);
          actionFermerProjet->setShortcut(QKeySequence("Ctrl+W"));
          connect(actionFermerProjet, SIGNAL(triggered()), this, SLOT(close()));


       QAction *actionQuitter = new QAction("&Quitter", this);
         menuFile->addAction(actionQuitter);
         actionQuitter->setShortcut(QKeySequence("Ctrl+Q"));
         connect(actionQuitter, SIGNAL(triggered()), this , SLOT(quit()));

         //Création des sous-menu de Edition

         QAction *actionAnnuler = new QAction("&Annuler", this);
           menuEdition->addAction(actionAnnuler);
           actionAnnuler->setShortcut(QKeySequence("Ctrl+Z"));
           connect(actionAnnuler, SIGNAL(triggered()), this, SLOT(undo()));
         QAction *actionRetablir = new QAction("&Retablir", this);
            menuEdition->addAction(actionRetablir);
            actionRetablir->setShortcut(QKeySequence("Ctrl+Y"));
            connect(actionRetablir, SIGNAL(triggered()), this, SLOT(redo()));
            menuEdition->addSeparator();
         QAction *actionInfo = new QAction("&Information sur le projet", this);
            menuEdition->addAction(actionInfo);
            connect(actionInfo, SIGNAL(triggered()), this, SLOT(projectInfo()));


            //Création des sous-menu de Navigation
            QAction *actionImageSuivante = new QAction("&Image suivante", this);
              menuNavig->addAction(actionImageSuivante);
              actionImageSuivante->setShortcut(QKeySequence("Right"));
              connect(actionImageSuivante, SIGNAL(triggered()), this, SLOT(nextFrame()));
            QAction *actionImagePrec = new QAction("&Image précédente", this);
               menuNavig->addAction(actionImagePrec);
               actionImagePrec->setShortcut(QKeySequence("Left"));
               connect(actionImagePrec, SIGNAL(triggered()), this, SLOT(previousFrame()));
            QAction *actionAllerDebut = new QAction("&Aller au début", this);
               menuNavig->addAction(actionAllerDebut);
               actionAllerDebut->setShortcut(QKeySequence("Ctrl+Left"));
               connect(actionAllerDebut, SIGNAL(triggered()), this, SLOT(firstFrame()));
            QAction *actionAllerFin = new QAction("&Aller à la fin", this);
               menuNavig->addAction(actionAllerFin);
               actionAllerFin->setShortcut(QKeySequence("Ctrl+Right"));
               connect(actionAllerFin, SIGNAL(triggered()), this, SLOT(lastFrame()));


           //Création des sous-menu de Visualisation
           QAction *actionVisioDebut = new QAction("&Visionner depuis le début", this);
              menuVisual->addAction(actionVisioDebut);
              actionVisioDebut->setShortcut(QKeySequence("Ctrl+V"));
              connect(actionVisioDebut, SIGNAL(triggered()), this, SLOT(startVisionAll()));
           QAction *actionVisioNimage = new QAction("&Visionner depuis n images", this);
              menuVisual->addAction(actionVisioNimage);
              actionVisioNimage->setShortcut(QKeySequence("Ctrl+B"));
              connect(actionVisioNimage, SIGNAL(triggered()), this, SLOT(startVisionPrevious()));

              //Création des sous-menu de Préférence
           QAction *actionAfficherImOrig = new QAction("&Afficher les images d'origines", this);
              menuPref->addAction(actionAfficherImOrig);
              actionAfficherImOrig->setShortcut(QKeySequence("Ctrl+J"));
              connect(actionAfficherImOrig, SIGNAL(triggered()), this, SLOT(afficherImOrig()));
           QAction *actionAfficherPelures = new QAction("&Afficher les pelures d'oignons", this);
              menuPref->addAction(actionAfficherPelures);
              actionAfficherPelures->setShortcut(QKeySequence("Ctrl+K"));
              connect(actionAfficherPelures, SIGNAL(triggered()), this, SLOT(afficherPelure()));
           QAction *actionFreqPelures = new QAction("&Fréquence des pelures d'oignons", this);
              menuPref->addAction(actionFreqPelures);
              actionFreqPelures->setShortcut(QKeySequence("Ctrl+M"));
              connect(actionFreqPelures, SIGNAL(triggered()), this, SLOT(setFrequencePelure()));

              //Création des sous-menu d'Aide
           QAction *actionAide = new QAction("&Aide", this);
              menuAide->addAction(actionAide);
              actionAide->setShortcut(QKeySequence("F1"));
              connect(actionAide, SIGNAL(triggered()), this, SLOT(help()));
           QAction *actionAPropos = new QAction("&A propos", this);
              menuAide->addAction(actionAPropos);
              connect(actionAPropos, SIGNAL(triggered()), this, SLOT(about()));

}

void MainWindow::mousePressEvent(QMouseEvent *)
{
    _optionPenMenu->hide();
    _optionRubberMenu->hide();
    _colorMenu->hide();
}


void MainWindow::newProject()
{
    if(close())
    {
        createProjectPageOuvrir();

        setWindowTitle("Rotoscop'Me - " + projet->getName());

        statusBar()->showMessage("Nouveau projet ouvert", 2000);
    }
}

void MainWindow::open()
{
    if(close())
    {
        QString dirName = QFileDialog::getExistingDirectory(this);
        if(!dirName.isEmpty())
        {
            QDir dir(dirName);

            try
            {
                projet = Projet::open(dir);
                projectPage();
                centralWidget()->show();
                statusBar()->showMessage("Projet ouvert", 2000);

                setWindowTitle("Rotoscop'Me - " + projet->getName());
            }
            catch(QString e)
            {
                close();
                centralWidget()->hide();
                setWindowTitle("Rotoscop'Me");
                statusBar()->showMessage("Erreur lors de l'ouverture du projet : " + e, 2000);
            }
       }
    }
}

bool MainWindow::close()
{
    if(projet != NULL)
    {
        if(_modified)
        {
            QMessageBox::StandardButton reply;
            reply = QMessageBox::question(this, "Projet modifié", "Ce projet a été modifié, voulez-vous le sauvegarder ?", QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

            if(reply == QMessageBox::Yes)
                projet->save();
            else if(reply == QMessageBox::Cancel)
                return false;

        }

        delete projet;
        projet = NULL;
        delete centralWidget();
        setCentralWidget(new QWidget());
        centralWidget()->hide();
        setWindowTitle("Rotoscop'Me");

        return true;
    }
    else
        return true;
}

void MainWindow::quit()
{
    if(close())
        qApp->quit();
}

bool MainWindow::save()
{
    try
    {
        projet->save();
        statusBar()->showMessage("Projet sauvegardé", 2000);
        _modified=false;
    }
    catch(QString e)
    {
        statusBar()->showMessage("Erreur lors de la sauvegarde : " + e, 2000);
        return false;
    }

    return true;
}

bool MainWindow::saveAs()
{
    QString dirPath = QFileDialog::getExistingDirectory(this);

    if(!dirPath.isEmpty())
    {
        QDir dir(dirPath);

        try
        {
            projet->saveAs(dir);
            _modified=false;
            statusBar()->showMessage("Projet sauvegardé", 2000);
        }
        catch(QString e)
        {
            statusBar()->showMessage("Erreur lors de la sauvegarde : " + e, 2000);
            return false;
        }
    }
    else
    {
        statusBar()->showMessage("Sauvegarde non effectuée", 2000);

        return false;
    }

    return true;
}

void MainWindow::exportImage()
{
    QString dirPath = QFileDialog::getExistingDirectory(this);

    if(!dirPath.isEmpty())
    {
        QDir dir(dirPath);

        try
        {
            projet->exportImage(dir);
            statusBar()->showMessage("Projet exporté", 2000);
        }
        catch(QString e)
        {
            statusBar()->showMessage("Erreur lors de l'exportation : " + e, 2000);
        }
    }
    else
    {
        statusBar()->showMessage("Exportation non effectuée", 2000);
    }
}

void MainWindow::exportVideo()
{
    QString filePath = QFileDialog::getSaveFileName(this);

    if(!filePath.isEmpty())
    {
        try
        {
            projet->exportVideo(filePath);
            statusBar()->showMessage("Projet exporté", 2000);
        }
        catch(QString e)
        {
            statusBar()->showMessage("Erreur lors de l'exportation : " + e, 2000);
        }
    }
    else
    {
        statusBar()->showMessage("Exportation non effectuée", 2000);
    }
}

void MainWindow::projectInfo()
{
   QMessageBox::about(this, tr("Information sur le projet"),
            "Projet : " + projet->getName() + "\n"
               "Workspace : " + projet->getWorkspace() + "\n"
               "Vidéo : " + projet->getVideo() + "\n"
               "Fréquence d'images : " + QString::number(projet->getFrequence()) + "\n");
}

void MainWindow::help()
{
   QMessageBox::about(this, tr("Aide"),
            tr("Bienvenue dans l'aide de Rotoscop'Me. \n"
               "Retrouver l'aide  détaillée à l'adresse :\n"
               "rotoscopme.com/aide"));
}

void MainWindow::about()
{
   QMessageBox::about(this, tr("A propos"),
            tr("Rotoscop'Me est une application de rotoscopie créée par Matthieu RIOU et Manon BOBIN."));
}

void MainWindow::undo()
{
    if(_drawArea != NULL)
        _drawArea->undo();
}

void MainWindow::redo()
{
    if(_drawArea != NULL)
        _drawArea->redo();
}

void MainWindow::projectModified()
{
    _modified = true;
}

void MainWindow::startVisionAll()
{
    if(_visionnage != NULL && _visionnage->isRunning())
    {
        _visionnage->stop();
        delete _visionnage;

        _visioButton->setChecked(false);
        _nImageVisioButton->setChecked(false);
    }

    _visioButton->setChecked(true);

    _visionnage = new Visionnage(this, projet);
    _visionnage->start();

    disconnect(_visioButton, SIGNAL(clicked()), this, SLOT(startVisionAll()));
    connect(_visioButton, SIGNAL(clicked()), this, SLOT(stopVisionAll()));
}

void MainWindow::stopVisionAll()
{
    _visionnage->stop();
    connect(_visioButton, SIGNAL(clicked()), this, SLOT(startVisionAll()));
    disconnect(_visioButton, SIGNAL(clicked()), this, SLOT(stopVisionAll()));
}

void MainWindow::startVisionPrevious()
{
    if(_visionnage != NULL && _visionnage->isRunning())
    {
        _visionnage->stop();
        delete _visionnage;

        _visioButton->setChecked(false);
        _nImageVisioButton->setChecked(false);
    }

    _nImageVisioButton->setChecked(true);

    _visionnage = new Visionnage(this, projet, _nImages->value());
    _visionnage->start();

    disconnect(_nImageVisioButton, SIGNAL(clicked()), this, SLOT(startVisionPrevious()));
    connect(_nImageVisioButton, SIGNAL(clicked()), this, SLOT(stopVisionPrevious()));
}

void MainWindow::stopVisionPrevious()
{
    _visionnage->stop();
    connect(_nImageVisioButton, SIGNAL(clicked()), this, SLOT(startVisionPrevious()));
    disconnect(_nImageVisioButton, SIGNAL(clicked()), this, SLOT(stopVisionPrevious()));
}

void MainWindow::afficherImOrig()
{
    _imageOrigineButton->click();
    reloadCurrentFrame();
}

void MainWindow::afficherPelure()
{
    _pelureOignonButton->click();
    reloadCurrentFrame();
}

void MainWindow::setFrequencePelure()
{
    QDialog *dialog = new QDialog(this);

    QLabel *label = new QLabel("Fréquence des pelures d'oignons");
    QSpinBox *frequence = new QSpinBox();

    QHBoxLayout *freqLayout = new QHBoxLayout();
    freqLayout->addWidget(label);
    freqLayout->addWidget(frequence);

    QPushButton *valider = new QPushButton("Valider");
    connect(valider, SIGNAL(clicked()), dialog, SLOT(close()));

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(valider);
    buttonLayout->setAlignment(valider, Qt::AlignRight);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addLayout(freqLayout);
    layout->addLayout(buttonLayout);

    dialog->setLayout(layout);
    dialog->exec();

}

int MainWindow::getNbFrame()
{
    return _nbFrame;
}

MainWindow::~MainWindow()
{

}


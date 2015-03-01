#include "createprojectdialog.h"

CreateProjectDialog::CreateProjectDialog(QWidget *parent) :
    QDialog(parent)
{
    setWindowTitle(tr("Rotoscop'Me - Nouveau Projet "));

    QLabel *nomLabel = new QLabel("Nom : ");
    _nomEdit = new QLineEdit();


    QLabel *workspaceLabel = new QLabel("Workspace : ");
    _workspaceEdit = new QLineEdit();

    QLabel *videoLabel = new QLabel("Vidéo : ");
    _videoEdit = new QLineEdit();

    QLabel *freqImageLabel = new QLabel("Fréquence d'images : ");
    _freqImgSpinBox = new QSpinBox();
    _freqImgSpinBox->setMinimum(1);

    QPushButton *createButton = new QPushButton("Créer");
    createButton->setGeometry(QRect(800, 450, 100, 50));
    connect(createButton, SIGNAL(clicked()), this, SLOT(close()));


    QHBoxLayout* nomLayout = new QHBoxLayout();
    nomLayout->addWidget(nomLabel);
    nomLayout->addWidget(_nomEdit);

    QHBoxLayout* workspaceLayout = new QHBoxLayout();
    workspaceLayout->addWidget(workspaceLabel);
    workspaceLayout->addWidget(_workspaceEdit);

    QHBoxLayout* videoLayout = new QHBoxLayout();
    videoLayout->addWidget(videoLabel);
    videoLayout->addWidget(_videoEdit);

    QHBoxLayout* freqImLayout = new QHBoxLayout();
    freqImLayout->addWidget(freqImageLabel);
    freqImLayout->addWidget(_freqImgSpinBox);

    QHBoxLayout* buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(createButton);
    buttonLayout->setAlignment(createButton, Qt::AlignRight);

    QVBoxLayout* homeLayout = new QVBoxLayout();
    homeLayout->addStretch(1);
    homeLayout->addLayout(nomLayout);
    homeLayout->addLayout(workspaceLayout);
    homeLayout->addLayout(videoLayout);
    homeLayout->addLayout(freqImLayout);
    homeLayout->addStretch(1);
    homeLayout->addLayout(buttonLayout);

    setLayout(homeLayout);
}

QString CreateProjectDialog::getNom()
{
    return _nomEdit->text();
}

QString CreateProjectDialog::getWorkspace()
{
    return _workspaceEdit->text();
}

QString CreateProjectDialog::getVideo()
{
    return _videoEdit->text();
}

int CreateProjectDialog::getFrequence()
{
    return _freqImgSpinBox->value();
}

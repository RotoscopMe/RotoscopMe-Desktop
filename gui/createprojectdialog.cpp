#include "createprojectdialog.h"

CreateProjectDialog::CreateProjectDialog(QWidget *parent) :
    QDialog(parent)
{
    setWindowTitle(tr("Rotoscop'Me - Nouveau Projet "));

    QLabel *nomLabel = new QLabel("Nom : ");
    _nomEdit = new QLineEdit();

    QLabel *workspaceLabel = new QLabel("Workspace : ");
    _workspaceEdit = new QLineEdit();
    QPushButton *workspaceParcourirButton = new QPushButton("...");
    connect(workspaceParcourirButton, SIGNAL(clicked()), this, SLOT(workspaceParcourir()));

    QLabel *videoLabel = new QLabel("Vidéo : ");
    _videoEdit = new QLineEdit();
    QPushButton *videoParcourirButton = new QPushButton("...");
    connect(videoParcourirButton, SIGNAL(clicked()), this, SLOT(videoParcourir()));

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
    workspaceLayout->addWidget(workspaceParcourirButton);

    QHBoxLayout* videoLayout = new QHBoxLayout();
    videoLayout->addWidget(videoLabel);
    videoLayout->addWidget(_videoEdit);
    videoLayout->addWidget(videoParcourirButton);

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

void CreateProjectDialog::workspaceParcourir()
{
    QString path = QFileDialog::getExistingDirectory();

    if(!path.isEmpty())
    {
        _workspaceEdit->setText(path);
    }
}

void CreateProjectDialog::videoParcourir()
{
    QString path = QFileDialog::getOpenFileName();

    if(!path.isEmpty())
    {
        _videoEdit->setText(path);
    }
}

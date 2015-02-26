#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QMenu>
#include <QMenuBar>
#include <QVBoxLayout>
#include <QAction>
#include <QApplication>
#include <QColorDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QString>
#include <QLineEdit>


#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>

#include "drawarea.h"
#include "ToolDialog.h"
#include "core/projet.h"


#include <QDialog>
#include <QFileDialog>
#include <QMessageBox>
#include <QGroupBox>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:

public slots:
    void createMenu();
    void setcolor();
    void projectPage();
    void homePageOuvrir();
    void createProjectPageOuvrir();

    void switchToPen();
    void switchToRubber();

    void optionPen();
    void optionRubber();
    void optionColor();

    void setPenSmall();
    void setPenMedium();
    void setPenLarge();

    void setRubberSmall();
    void setRubberMedium();
    void setRubberLarge();

    void setColorBlack();
    void setColorRed();
    void setColorBlue();
    void setColorGreen();
    void setColorYellow();
    void setColorBrown();

    void hideMenu();

private slots :
    void newFile();
    void open();
    bool save();
    bool saveAs();
    void about();
    void help();
    void projectInfo();

private:

    QDialog *homepage;
    QFont *policeTitle;
    QLabel *titreLabel;
    QPushButton * newButton;
    QPushButton * openButton;

    QDialog *createProjectPage;
    QLabel *nomLabel;
    QLabel *workspaceLabel;
    QLabel *videoLabel;
    QLabel *freqImageLabel;
    QLineEdit *nomEdit;
    QLineEdit *workspaceEdit;
    QLineEdit *videoEdit;
    QSpinBox *freqImSpinBox;
    QHBoxLayout *nomLayout;
    QHBoxLayout *workspaceLayout;
    QHBoxLayout *videoLayout;
    QHBoxLayout *freqImLayout;
    QVBoxLayout *homeLayout;
    QGridLayout *projectGrid;
    QPushButton *createButton;


    bool maybeSave();
    void loadFile(const QString &fileName);
    bool saveFile(const QString &fileName);
    void setCurrentFile(const QString &fileName);
    QString strippedName(const QString &fullFileName);
    QString curFile;

    QGroupBox *visualisationGroupBox;
    QGroupBox *preferenceGroupBox;
    QGroupBox *undoRedoGroupBox;
    QGroupBox *paletteGroupBox;

    QPushButton *_colorButton;
    QLabel *_colorLabel;

    QPushButton *_imageOrigineButton;
    QPushButton *_pelureOignonButton;
    QLabel *_nbrPelureLabel;
    QSpinBox *_nbrPelureSpinBox;

    QWidget *_verticalLayoutWidget;
    QSlider *_horizontalSlider;
    DrawArea *_drawArea;

    QPushButton *_visioButton;
    QCheckBox *_nImageCheckBox;
    QSpinBox *_nImages;

    QPushButton *_undoButton;
    QPushButton *_redoButton;
    QPushButton *_debutButton;
    QPushButton *_finButton;
    QPushButton *_precedenteButton;
    QPushButton *_suivanteButton;

    QPushButton *_selectRubberButton;
    QPushButton *_optionRubberButton;
    QPushButton *_selectPenButton;
    QPushButton *_optionPenButton;

    QLabel *_imageEnCoursLabel;
    QLabel *_imagePrecedenteLabel;
    QLabel *_imageSuivanteLabel;

    ToolDialog *_optionPenMenu;
    ToolDialog *_optionRubberMenu;
    ToolDialog *_colorMenu;

    Projet *projet;

    void mousePressEvent(QMouseEvent *);

};

#endif // MAINWINDOW_H

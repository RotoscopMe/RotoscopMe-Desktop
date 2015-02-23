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

#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>



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

private:
    QPushButton *colorButton;
    QLabel *colorLabel;

    QPushButton *ImageOrigineButton;
    QPushButton *PelureOignonButton;
    QLabel *NbrPelureLabel;
    QSpinBox *NbrPelurespinBox;

    QWidget *verticalLayoutWidget;
    QSlider *horizontalSlider;
    QGraphicsView *graphicsView;

    QPushButton *VisioButton;
    QCheckBox *NimagecheckBox;
    QSpinBox *Nimages;

    QPushButton *undoButton;
    QPushButton *redoButton;
    QPushButton *debutButton;
    QPushButton *finButton;
    QPushButton *precedenteButton;
    QPushButton *suivanteButton;

    QPixmap *gomme;
    QLabel *gommeLabel;
    QPushButton *gommeButton;
    QPixmap *pen;
    QLabel *penLabel;
    QPushButton *penButton;
    QPixmap *imageEnCours;
    QLabel *imageEnCoursLabel;
    QPixmap *imagePrecedente;
    QLabel *imagePrecedenteLabel;
    QPixmap *imageSuivante;
    QLabel *imageSuivanteLabel;

};

#endif // MAINWINDOW_H

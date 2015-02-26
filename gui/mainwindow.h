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
    QPushButton *_colorButton;
    QLabel *_colorLabel;

    QPushButton *_imageOrigineButton;
    QPushButton *_pelureOignonButton;
    QLabel *_nbrPelureLabel;
    QSpinBox *_nbrPelureSpinBox;

    QWidget *_verticalLayoutWidget;
    QSlider *_horizontalSlider;
    QGraphicsView *_graphicsView;

    QPushButton *_visioButton;
    QCheckBox *_nImageCheckBox;
    QSpinBox *_nImages;

    QPushButton *_undoButton;
    QPushButton *_redoButton;
    QPushButton *_debutButton;
    QPushButton *_finButton;
    QPushButton *_precedenteButton;
    QPushButton *_suivanteButton;

    QPushButton *_gommeActiveButton;
    QPushButton *_gommeButton;
    QPushButton *_penActiveButton;
    QPushButton *_penButton;
    QLabel *_imageEnCoursLabel;
    QLabel *_imagePrecedenteLabel;
    QLabel *_imageSuivanteLabel;

};

#endif // MAINWINDOW_H

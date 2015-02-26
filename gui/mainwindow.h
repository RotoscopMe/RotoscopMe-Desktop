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

#include "drawarea.h"
#include "ToolDialog.h"


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

    void switchToPen();
    void switchToRubber();

    void optionPen();
    void optionRubber();

    void setPenSmall();
    void setPenMedium();
    void setPenLarge();

    void setRubberSmall();
    void setRubberMedium();
    void setRubberLarge();

    void hideMenu();

private:
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


    void mousePressEvent(QMouseEvent *);

};

#endif // MAINWINDOW_H

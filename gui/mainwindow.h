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

    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QPushButton *VisioButton;
    QCheckBox *NimagecheckBox;
    QSpinBox *Nimages;


};

#endif // MAINWINDOW_H

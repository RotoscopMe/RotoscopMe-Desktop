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

#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>

#include "drawarea.h"
#include "ToolDialog.h"

#include <QDialog>
#include <QFileDialog>
#include <QMessageBox>

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
    bool maybeSave();
    void loadFile(const QString &fileName);
    bool saveFile(const QString &fileName);
    void setCurrentFile(const QString &fileName);
    QString strippedName(const QString &fullFileName);
    QString curFile;

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

    void mousePressEvent(QMouseEvent *);

};

#endif // MAINWINDOW_H

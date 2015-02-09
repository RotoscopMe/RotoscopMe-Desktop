#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QMenu>
#include <QMenuBar>
#include <QVBoxLayout>
#include <QAction>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:

public slots:

private:

};

#endif // MAINWINDOW_H

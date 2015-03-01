#ifndef CREATEPROJECTDIALOG_H
#define CREATEPROJECTDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QSpinBox>
#include <QLabel>
#include <QLayout>
#include <QPushButton>

class CreateProjectDialog : public QDialog
{
    Q_OBJECT
public:
    explicit CreateProjectDialog(QWidget *parent = 0);

    QString getNom();
    QString getWorkspace();
    QString getVideo();
    int getFrequence();

signals:

public slots:

private:
    QLineEdit *_nomEdit;
    QLineEdit *_workspaceEdit;
    QLineEdit *_videoEdit;
    QSpinBox *_freqImgSpinBox;

};

#endif // CREATEPROJECTDIALOG_H

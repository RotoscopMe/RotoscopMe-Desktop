#ifndef CREATEPROJECTDIALOG_H
#define CREATEPROJECTDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QComboBox>
#include <QLabel>
#include <QLayout>
#include <QPushButton>
#include <QFileDialog>

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
    void workspaceParcourir();
    void videoParcourir();

private:
    QLineEdit *_nomEdit;
    QLineEdit *_workspaceEdit;
    QLineEdit *_videoEdit;
    QComboBox *_freqImgComboBox;

};

#endif // CREATEPROJECTDIALOG_H

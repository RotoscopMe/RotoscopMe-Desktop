#ifndef TOOLDIALOG_H
#define TOOLDIALOG_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>

class ToolDialog : public QPushButton
{
    public:
        ToolDialog(QPoint *centerOrigin, QWidget* parent = 0);

        void addWidget(QWidget* widget, int row, int column);

    private:
        QPoint *_centerOrigin;
        QGridLayout *_layout;

        void mousePressEvent(QMouseEvent *);
        void resizeEvent(QResizeEvent *);
};

#endif // TOOLDIALOG_H

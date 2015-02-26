#include "ToolDialog.h"
#include <QLabel>
#include <QStyle>
#include <QDebug>

ToolDialog::ToolDialog(QPoint *centerOrigin, QWidget *parent) :
    QPushButton(parent),
    _centerOrigin(centerOrigin),
    _layout(new QGridLayout())
{
    move(_centerOrigin->x(), _centerOrigin->y() - height()/2);

    setLayout(_layout);
}

void ToolDialog::addWidget(QWidget *widget, int row, int column)
{
    _layout->addWidget(widget, row, column);
}

void ToolDialog::mousePressEvent(QMouseEvent*)
{}

void ToolDialog::resizeEvent(QResizeEvent *)
{
    move(_centerOrigin->x(), _centerOrigin->y() - height()/2);
}

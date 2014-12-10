#include "eigenerbutton.h"
#include <QMouseEvent>

EigenerButton::EigenerButton(int reihe, int spalte, QWidget *parent) :
    QPushButton(parent),
    reihe(reihe),
    spalte(spalte)
{
}

void EigenerButton::mousePressEvent(QMouseEvent *e)
{
    switch(e->button())
    {
    case Qt::RightButton:
        emit rightClicked();
        break;
    case Qt::LeftButton:
        emit leftClicked();
        break;
    default:
        break;
    }
    QPushButton::mousePressEvent(e);
}

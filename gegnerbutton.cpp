#include "gegnerbutton.h"

GegnerButton::GegnerButton(int reihe, int spalte, QWidget *parent) :
    QPushButton(parent)
{
    this->reihe = reihe;
    this->spalte = spalte;
}

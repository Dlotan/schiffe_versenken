#include "gegnerbutton.h"

GegnerButton::GegnerButton(int reihe, int spalte, QWidget *parent) :
    QPushButton(parent),
    reihe(reihe),
    spalte(spalte)
{
}

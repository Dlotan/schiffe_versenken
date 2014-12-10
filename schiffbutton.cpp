#include "schiffbutton.h"

SchiffButton::SchiffButton(SchiffAuswahl schiffTyp, QWidget *parent) :
    QPushButton(parent),
    schiffTyp(schiffTyp)
{
}

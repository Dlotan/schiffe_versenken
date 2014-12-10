#ifndef GEGNERBUTTON_H
#define GEGNERBUTTON_H

#include <QPushButton>
#include "schiffauswahl.h"

class GegnerButton : public QPushButton
{
    Q_OBJECT
public:
    explicit GegnerButton(int reihe, int spalte, QWidget *parent = 0);
    int reihe, spalte;
    SchiffAuswahl schiff = SchiffAuswahl::NONE;
    bool abgeschossen = false;
    int schiffId = 0;
signals:

public slots:

};

#endif // GEGNERBUTTON_H

#ifndef SCHIFFBUTTON_H
#define SCHIFFBUTTON_H

#include <QPushButton>
#include "schiffauswahl.h"

class SchiffButton : public QPushButton
{
    Q_OBJECT
public:
    explicit SchiffButton(SchiffAuswahl schiffTyp, QWidget *parent = 0);
    SchiffAuswahl schiffTyp;

signals:

public slots:

};

#endif // SCHIFFBUTTON_H

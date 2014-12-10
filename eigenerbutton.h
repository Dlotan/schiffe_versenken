#ifndef EIGENERBUTTON_H
#define EIGENERBUTTON_H

#include <QPushButton>

class EigenerButton : public QPushButton
{
    Q_OBJECT
public:
    explicit EigenerButton(int reihe, int spalte, QWidget *parent = 0);
    int reihe, spalte;
    int schiffId = 0;
    bool abgeschossen = false;
signals:
    void rightClicked();
    void leftClicked();
public slots:

private slots:
    void mousePressEvent(QMouseEvent *e);

};

#endif // EIGENERBUTTON_H

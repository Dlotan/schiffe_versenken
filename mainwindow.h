#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include <QList>
#include <QMap>
#include <QListWidget>
#include "eigenerbutton.h"
#include "gegnerbutton.h"
#include "schiffbutton.h"
#include "schiffauswahl.h"

class QLabel;

class MainWindow : public QDialog
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    const int BREITE = 10;
    const int HOEHE = 10;

    const int ANZ_SCHLACHTSCHIFF = 1;
    const int ANZ_KREUZER = 2;
    const int ANZ_ZERSTOERER = 3;
    const int ANZ_UBOOT = 4;

    const int LEN_SCHLACHTSCHIFF = 5;
    const int LEN_KREUZER = 4;
    const int LEN_ZERSTOERER = 3;
    const int LEN_UBOOT = 2;
private:
    QList<QList<EigenerButton*>> eigeneButtons;
    QList<QList<GegnerButton*>> gegnerButtons;
    QList<SchiffButton*> schiffButtons;
    QPushButton *startButton;
    QLabel *schiffAuswahlLabel;
    QLabel *restLabel;
    QListWidget *eigeneList;
    QListWidget *gegnerList;
    SchiffAuswahl schiffAuswahl = SchiffAuswahl::NONE;

    QList<SchiffAuswahl> schiffTypen;
    QMap<SchiffAuswahl, int> schiffToLaenge;
    QMap<SchiffAuswahl, int> schiffToAnzahl;
    QMap<int, SchiffAuswahl> idToSchiffAuswahl;
    QMap<SchiffAuswahl, QString> schiffToInitialie;
    QMap<SchiffAuswahl, QString> schiffToString;
    QMap<SchiffAuswahl, int> schiffUebrig;


    int currentId = 1;
public slots:
    void eigenerLeftClicked();
    void eigenerRightClicked();
    void gegnerButtonClicked();
    void schiffButtonClicked();
    void startButtonClicked();
};

#endif // MAINWINDOW_H

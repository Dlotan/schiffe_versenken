#include "mainwindow.h"
#include <QGridLayout>
#include <QDebug>
#include <QLabel>
#include <QMessageBox>
#include <QDateTime>

MainWindow::MainWindow(QWidget *parent)
    : QDialog(parent)
{
    schiffTypen << SchiffAuswahl::SCHLACHTSCHIFF
        << SchiffAuswahl::KREUZER
        << SchiffAuswahl::ZERSTOERER
        << SchiffAuswahl::UBOOT;
    schiffToLaenge[SchiffAuswahl::NONE] = 0;
    schiffToLaenge[SchiffAuswahl::SCHLACHTSCHIFF] = LEN_SCHLACHTSCHIFF;
    schiffToLaenge[SchiffAuswahl::KREUZER] = LEN_KREUZER;
    schiffToLaenge[SchiffAuswahl::ZERSTOERER] = LEN_ZERSTOERER;
    schiffToLaenge[SchiffAuswahl::UBOOT] = LEN_UBOOT;

    schiffToAnzahl[SchiffAuswahl::NONE] = 0;
    schiffToAnzahl[SchiffAuswahl::SCHLACHTSCHIFF] = ANZ_SCHLACHTSCHIFF;
    schiffToAnzahl[SchiffAuswahl::KREUZER] = ANZ_KREUZER;
    schiffToAnzahl[SchiffAuswahl::ZERSTOERER] = ANZ_ZERSTOERER;
    schiffToAnzahl[SchiffAuswahl::UBOOT] = ANZ_UBOOT;

    schiffToInitialie[SchiffAuswahl::NONE] = "N";
    schiffToInitialie[SchiffAuswahl::SCHLACHTSCHIFF] = "S";
    schiffToInitialie[SchiffAuswahl::KREUZER] = "K";
    schiffToInitialie[SchiffAuswahl::ZERSTOERER] = "Z";
    schiffToInitialie[SchiffAuswahl::UBOOT] = "U";

    schiffToString[SchiffAuswahl::NONE] = "NONE";
    schiffToString[SchiffAuswahl::SCHLACHTSCHIFF] = "SCHLACHT";
    schiffToString[SchiffAuswahl::KREUZER] = "KREUZER";
    schiffToString[SchiffAuswahl::ZERSTOERER] = "ZERSTOERER";
    schiffToString[SchiffAuswahl::UBOOT] = "UBOOT";

    schiffUebrig[SchiffAuswahl::NONE] = 0;
    schiffUebrig[SchiffAuswahl::SCHLACHTSCHIFF] = ANZ_SCHLACHTSCHIFF;
    schiffUebrig[SchiffAuswahl::KREUZER] = ANZ_KREUZER;
    schiffUebrig[SchiffAuswahl::ZERSTOERER] = ANZ_ZERSTOERER;
    schiffUebrig[SchiffAuswahl::UBOOT] = ANZ_UBOOT;

    QHBoxLayout *horizontalLayout = new QHBoxLayout();
    QGridLayout *gegnerLayout = new QGridLayout();
    for(int i = 0; i < HOEHE; ++i)
    {
        gegnerButtons.append(QList<GegnerButton*>());
        for(int j = 0; j < BREITE; ++j)
        {
            GegnerButton *gegnerButton = new GegnerButton(i, j, this);
            gegnerButton->setText("   ");
            gegnerButton->setDisabled(true);
            gegnerButtons[i].append(gegnerButton);
            gegnerButton->setMinimumHeight(1);
            gegnerButton->setMinimumWidth(1);
            connect(gegnerButton, SIGNAL(clicked()), this, SLOT(gegnerButtonClicked()));
            gegnerLayout->addWidget(gegnerButton, i, j);
        }
    }
    QGridLayout *eigenerLayout = new QGridLayout();
    for(int i = 0; i < HOEHE; ++i)
    {
        eigeneButtons.append(QList<EigenerButton*>());
        for(int j = 0; j < BREITE; ++j)
        {
            EigenerButton *eigenerButton = new EigenerButton(i, j, this);
            eigenerButton->setText("   ");
            eigeneButtons[i].append(eigenerButton);
            eigenerButton->setMinimumHeight(1);
            eigenerButton->setMinimumWidth(1);
            connect(eigenerButton, SIGNAL(leftClicked()), this, SLOT(eigenerLeftClicked()));
            connect(eigenerButton, SIGNAL(rightClicked()), this, SLOT(eigenerRightClicked()));
            eigenerLayout->addWidget(eigenerButton, i, j);
        }
    }
    QVBoxLayout *verticalLayout = new QVBoxLayout();
    verticalLayout->addItem(gegnerLayout);

    QWidget *horizontalLineWidget = new QWidget;
    horizontalLineWidget->setFixedHeight(2);
    horizontalLineWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    horizontalLineWidget->setStyleSheet(QString("background-color: #505050;"));
    verticalLayout->addWidget(horizontalLineWidget);
    verticalLayout->addItem(eigenerLayout);
    // Schiffe auswaehlen buttons.
    QVBoxLayout *schiffeAuswahlLayout = new QVBoxLayout();
    startButton = new QPushButton("START");
    startButton->setEnabled(false);
    connect(startButton, SIGNAL(clicked()), this, SLOT(startButtonClicked()));
    startButton->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    schiffeAuswahlLayout->addWidget(startButton);
    schiffAuswahlLabel = new QLabel("NONE");
    schiffAuswahlLabel->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    schiffeAuswahlLayout->addWidget(schiffAuswahlLabel);
    restLabel = new QLabel(QString::number(schiffUebrig[SchiffAuswahl::NONE]));
    restLabel->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
    schiffeAuswahlLayout->addWidget(restLabel);
    SchiffButton *schlachtSchiff = new SchiffButton(SchiffAuswahl::SCHLACHTSCHIFF, this);
    schlachtSchiff->setText("Schlachtschiff");
    SchiffButton *kreuzer = new SchiffButton(SchiffAuswahl::KREUZER, this);
    kreuzer->setText("Kreuzer");
    SchiffButton *zerstoerer = new SchiffButton(SchiffAuswahl::ZERSTOERER, this);
    zerstoerer->setText("Zerstoerer");
    SchiffButton *uBoot = new SchiffButton(SchiffAuswahl::UBOOT, this);
    uBoot->setText("UBoot");
    schiffButtons << schlachtSchiff << kreuzer << zerstoerer << uBoot;
    for(SchiffButton* button: schiffButtons)
    {
        connect(button, SIGNAL(clicked()), this, SLOT(schiffButtonClicked()));
        button->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));
        schiffeAuswahlLayout->addWidget(button);
    }
    eigeneList = new QListWidget();
    eigeneList->setMinimumWidth(50);
    eigeneList->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Expanding);
    schiffeAuswahlLayout->addWidget(eigeneList);
    gegnerList = new QListWidget();
    gegnerList->setMinimumWidth(50);
    gegnerList->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Expanding);
    schiffeAuswahlLayout->addWidget(gegnerList);
    horizontalLayout->addItem(schiffeAuswahlLayout);
    horizontalLayout->addItem(verticalLayout);
    this->setLayout(horizontalLayout);

    qsrand(QDateTime::currentMSecsSinceEpoch());
}

MainWindow::~MainWindow()
{
}

void MainWindow::eigenerLeftClicked()
{
    EigenerButton* button = qobject_cast<EigenerButton*>(sender());
    int reihe = button->reihe;
    int spalte = button->spalte;
    // Auf ein belegtes feld geklickt -> Schiff drehen.
    if(button->schiffId != 0)
    {
        int currentSchiffId = button->schiffId;
        SchiffAuswahl currentAuswahl = idToSchiffAuswahl[currentSchiffId];
        int currentLaenge = schiffToLaenge[currentAuswahl];
        int erstesReihe = -1;
        int erstesSpalte = -1;
        bool found = false;
        bool vertical = false;
        for(int i = 0; i < HOEHE; ++i)
        {
            for(int j = 0; j < BREITE; ++j)
            {
                if(eigeneButtons[i][j]->schiffId == currentSchiffId)
                {
                    erstesReihe = i;
                    erstesSpalte = j;
                    if(j < BREITE - 1 && eigeneButtons[i][j + 1]->schiffId == currentSchiffId)
                    {
                        vertical = true;
                    }
                    found = true;
                    break;
                }
            }
            if(found)
            {
                break;
            }
        }
        // Check ob das drehen passt
        // War vertikal muss jetzt horizontal.
        if(vertical)
        {
            if(!(erstesReihe + currentLaenge <= HOEHE))
            {
                return;
            }
            for(int i = erstesReihe + 1; i < erstesReihe + currentLaenge; ++i)
            {
                if(eigeneButtons[i][erstesSpalte]->schiffId != 0)
                {
                    return;
                }
            }
        }
        else
        {
            if(!(erstesSpalte + currentLaenge <= BREITE))
            {
                return;
            }
            for(int i = erstesSpalte + 1; i < erstesSpalte + currentLaenge; ++i)
            {
                if(eigeneButtons[erstesReihe][i]->schiffId != 0)
                {
                    return;
                }
            }
        }
        for(auto& lst : eigeneButtons)
        {
            for(EigenerButton* iter : lst)
            {
                if(iter->schiffId == currentSchiffId)
                {
                    iter->schiffId = 0;
                    iter->setText("   ");
                }
            }
        }
        // War vertikal muss jetzt horizontal.
        if(vertical)
        {
            for(int i = erstesReihe; i < erstesReihe + currentLaenge; ++i)
            {
                eigeneButtons[i][erstesSpalte]->schiffId = currentSchiffId;
                eigeneButtons[i][erstesSpalte]->setText(" " + schiffToInitialie[currentAuswahl] + " ");
            }
        }
        else
        {
            for(int i = erstesSpalte; i < erstesSpalte + currentLaenge; ++i)
            {
                eigeneButtons[erstesReihe][i]->schiffId = currentSchiffId;
                eigeneButtons[erstesReihe][i]->setText(" " + schiffToInitialie[currentAuswahl] + " ");
            }
        }
        return;
    }
    if(schiffAuswahl == SchiffAuswahl::NONE)
    {
        return;
    }
    if(schiffUebrig[schiffAuswahl] <= 0)
    {
        return;
    }
    // Vertikal ist moeglich.
    bool blockedVertical = true;
    if(spalte + schiffToLaenge[schiffAuswahl] <= BREITE)
    {
        blockedVertical = false;
        for(int i = spalte; i < spalte + schiffToLaenge[schiffAuswahl] ; ++i)
        {
            if(eigeneButtons[reihe][i]->schiffId != 0)
            {
                blockedVertical = true;
                break;
            }
        }
        if(!blockedVertical)
        {
            for(int i = spalte; i < spalte + schiffToLaenge[schiffAuswahl]; ++i)
            {
                eigeneButtons[reihe][i]->schiffId = currentId;
                eigeneButtons[reihe][i]->setText(" " + schiffToInitialie[schiffAuswahl] + " ");
            }
        }
    }
    // Horizontal
    bool blockedHorizontal = true;
    if(blockedVertical)
    {
        if(reihe + schiffToLaenge[schiffAuswahl] <= HOEHE)
        {
            blockedHorizontal = false;
            for(int i = reihe; i < reihe + schiffToLaenge[schiffAuswahl] ; ++i)
            {
                if(eigeneButtons[i][spalte]->schiffId != 0)
                {
                    blockedHorizontal = true;
                    break;
                }
            }
            if(!blockedHorizontal)
            {
                for(int i = reihe; i < reihe + schiffToLaenge[schiffAuswahl]; ++i)
                {
                    eigeneButtons[i][spalte]->schiffId = currentId;
                    eigeneButtons[i][spalte]->setText(" " + schiffToInitialie[schiffAuswahl] + " ");
                }
            }
        }
    }
    if(blockedHorizontal ^ blockedVertical)
    {
        idToSchiffAuswahl[currentId] = schiffAuswahl;
        schiffUebrig[schiffAuswahl]--;
        restLabel->setText(QString::number(schiffUebrig[schiffAuswahl]));
        currentId++;
        bool alleGesetzt = true;
        for(auto zahl : schiffUebrig.values())
        {
            if(zahl > 0)
            {
                alleGesetzt = false;
                break;
            }
        }
        if(alleGesetzt)
        {
            startButton->setEnabled(true);
        }
    }
}

void MainWindow::eigenerRightClicked()
{
    EigenerButton* button = qobject_cast<EigenerButton*>(sender());
    int schiffId = button->schiffId;
    schiffUebrig[idToSchiffAuswahl[schiffId]]++;
    if(schiffAuswahl == idToSchiffAuswahl[schiffId])
    {
        restLabel->setText(QString::number(schiffUebrig[idToSchiffAuswahl[schiffId]]));
    }
    for(auto& lst : eigeneButtons)
    {
        for(EigenerButton* eigener : lst)
        {
            if(eigener->schiffId == schiffId)
            {
                eigener->schiffId = 0;
                eigener->setText("   ");
            }
        }
    }
    idToSchiffAuswahl[schiffId] = SchiffAuswahl::NONE;
}

void MainWindow::gegnerButtonClicked()
{
    GegnerButton *gegner = qobject_cast<GegnerButton*>(sender());
    gegner->abgeschossen = true;

    gegner->setAutoFillBackground(true);
    bool getroffen = false;
    // Getroffen.
    if(gegner->schiff != SchiffAuswahl::NONE)
    {
        gegner->setStyleSheet("background-color: rgb(170, 1, 20); color: rgb(255, 255, 255)");
        getroffen = true;
        gegner->setText(" " + schiffToInitialie[gegner->schiff] + " ");
        bool versenkt = true;
        for(auto& lst : gegnerButtons)
        {
            for(GegnerButton* gegnerButton : lst)
            {
                if(gegnerButton->schiffId == gegner->schiffId)
                {
                    if(gegnerButton->abgeschossen == false)
                    {
                        versenkt = false;
                        break;
                    }
                }
            }
            if(!versenkt)
            {
                break;
            }
        }
        if(versenkt)
        {
            new QListWidgetItem(schiffToString[gegner->schiff] + " Versenkt", eigeneList);
            eigeneList->scrollToBottom();
        }
        else
        {
            new QListWidgetItem(schiffToString[gegner->schiff] + " Getroffen", eigeneList);
            eigeneList->scrollToBottom();
        }
    }
    // Nicht getroffen.
    else
    {
        gegner->setStyleSheet("background-color: rgb(7, 115, 122); color: rgb(255, 255, 255)");
        new QListWidgetItem("Wasser", eigeneList);
        eigeneList->scrollToBottom();
    }
    gegner->update();
    gegner->setDisabled(true);
    bool alleAbgeschossen = true;
    for(auto& lst : gegnerButtons)
    {
        for(GegnerButton* gegner : lst)
        {
            if(gegner->schiff != SchiffAuswahl::NONE)
            {
                if(gegner->abgeschossen == false)
                {
                    alleAbgeschossen = false;
                    break;
                }
            }
        }
        if(!alleAbgeschossen)
        {
            break;
        }
    }
    // Sieg.
    if(alleAbgeschossen)
    {
        QMessageBox siegBox;
        siegBox.setText("SIEG!");
        siegBox.exec();
        return;
    }
    // Gegner Zug.
    if(!getroffen)
    {
        getroffen = true;
        alleAbgeschossen = true;
        do
        {
            int reihe = qrand() % HOEHE;
            int spalte = qrand() % BREITE;
            if(eigeneButtons[reihe][spalte]->abgeschossen == true)
            {
                continue;
            }
            eigeneButtons[reihe][spalte]->abgeschossen = true;
            eigeneButtons[reihe][spalte]->setAutoFillBackground(true);
            // Getroffen.
            if(eigeneButtons[reihe][spalte]->schiffId != 0)
            {
                eigeneButtons[reihe][spalte]->setStyleSheet("background-color: rgb(170, 1, 20); color: rgb(255, 255, 255)");
                eigeneButtons[reihe][spalte]->update();
                bool versenkt = true;
                for(auto& lst : eigeneButtons)
                {
                    for(EigenerButton* eigener : lst)
                    {
                        if(eigener->schiffId == eigeneButtons[reihe][spalte]->schiffId)
                        {
                            if(eigener->abgeschossen == false)
                            {
                                versenkt = false;
                                break;
                            }
                        }
                    }
                    if(!versenkt)
                    {
                        break;
                    }
                }
                if(versenkt)
                {
                    new QListWidgetItem(schiffToString[idToSchiffAuswahl[eigeneButtons[reihe][spalte]->schiffId]] + " Versenkt", gegnerList);
                    gegnerList->scrollToBottom();
                }
                else
                {
                    new QListWidgetItem(schiffToString[idToSchiffAuswahl[eigeneButtons[reihe][spalte]->schiffId]] + " Getroffen", gegnerList);
                    gegnerList->scrollToBottom();
                }
                getroffen = true;
                for(auto& lst : eigeneButtons)
                {
                    for(EigenerButton* eigener : lst)
                    {
                        if(eigener->schiffId != 0)
                        {
                            if(eigener->abgeschossen == false)
                            {
                                alleAbgeschossen = false;
                                break;
                            }
                        }
                    }
                    if(!alleAbgeschossen)
                    {
                        break;
                    }
                }
                if(alleAbgeschossen)
                {
                    QMessageBox verlustBox;
                    verlustBox.setText("Verloren!");
                    verlustBox.exec();
                }

            }
            // Nicht getroffen.
            else
            {
                eigeneButtons[reihe][spalte]->setStyleSheet("background-color: rgb(7, 115, 122); color: rgb(255, 255, 255)");
                eigeneButtons[reihe][spalte]->update();
                getroffen = false;
                new QListWidgetItem("Wasser", gegnerList);
                gegnerList->scrollToBottom();
            }
        }while(getroffen);
    }
}

void MainWindow::schiffButtonClicked()
{
    SchiffButton* sending = qobject_cast<SchiffButton*>(sender());
    schiffAuswahl = sending->schiffTyp;
    schiffAuswahlLabel->setText(schiffToString[sending->schiffTyp]);
    restLabel->setText(QString::number(schiffUebrig[schiffAuswahl]));
}

void MainWindow::startButtonClicked()
{
    for(auto schiffAnzahl : schiffUebrig.values())
    {
        if(schiffAnzahl > 0)
        {
            return;
        }
    }
    for(auto& lst : eigeneButtons)
    {
        for(EigenerButton* eigener : lst)
        {
            eigener->setDisabled(true);
        }
    }

    for(auto& lst : gegnerButtons)
    {
        for(GegnerButton* gegner : lst)
        {
            gegner->setDisabled(false);
        }
    }
    // Gegner Schiffe setzen.
    int gegnerId = 1;
    int vertikale = 0;
    int horizontale = 0;
    for(SchiffAuswahl schiff : schiffTypen)
    {
        for(int i = 0; i < schiffToAnzahl[schiff]; ++i)
        {
            int reihe = qrand() % HOEHE;
            int spalte = qrand() % BREITE;
            bool vertikal = qrand() % 2;
            int laenge = schiffToLaenge[schiff];
            if(vertikal)
            {
                if(!(spalte + laenge - 1 < BREITE))
                {
                    i--;
                    continue;
                }
                bool kolision = false;
                for(int j = spalte; j < spalte + laenge; ++j)
                {
                    if(gegnerButtons[reihe][j]->schiff != SchiffAuswahl::NONE)
                    {
                        kolision = true;
                        break;
                    }
                }
                if(kolision)
                {
                    i--;
                    continue;
                }
                vertikale++;
                for(int j = spalte; j < spalte + laenge; ++j)
                {
                    gegnerButtons[reihe][j]->schiff = schiff;
                    gegnerButtons[reihe][j]->schiffId = gegnerId;
                }
                gegnerId++;
            }
            else
            {
                if(!(reihe + laenge - 1 < HOEHE))
                {
                    i--;
                    continue;
                }
                bool kolision = false;
                for(int j = reihe; j < reihe + laenge; ++j)
                {
                    if(gegnerButtons[j][spalte]->schiff != SchiffAuswahl::NONE)
                    {
                        kolision = true;
                        break;
                    }
                }
                if(kolision)
                {
                    i--;
                    continue;
                }
                horizontale++;
                for(int j = reihe; j < reihe + laenge; ++j)
                {
                    gegnerButtons[j][spalte]->schiff = schiff;
                    gegnerButtons[j][spalte]->schiffId = gegnerId;
                }
                gegnerId++;
            }
        }
    }
    startButton->setEnabled(false);
    for(SchiffButton* button: schiffButtons)
    {
        button->setEnabled(false);
    }
}

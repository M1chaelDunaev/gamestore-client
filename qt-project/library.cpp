#include "library.h"
#include "ui_library.h"
#include <QDebug>
#include "mainwindow.h"
#include "useraccount.h"
#include "itemeldenring.h"
#include "itemgodofwar.h"
#include "itemstray.h"
#include "itemhorizon.h"
#include "itemplaguetale.h"
#include "itemlastofus.h"
#include "itemcuphead.h"
#include "itemdyinglight.h"
#include "itemwarhammer.h"

Library::Library(MainWindow* _mainWindow, UserAccount* _currentAccount) :
    QWidget(nullptr), ui(new Ui::Library),
    mainWindow(_mainWindow), currentAccount(_currentAccount)
{
    ui->setupUi(this);

    initWindows();
    setIcons();
    setGameList();

    centralLayout = new QStackedLayout;
    centralLayout->addWidget(ui->NoGames_widget);
    ui->Central_widget->setLayout(centralLayout);    
    init();
}

Library::~Library()
{
    delete ui;
    deleteWindows();
}

void Library::showEvent(QShowEvent *event)
{
    setGameList();
}

void Library::initWindows()
{
    eldenRing = nullptr;
    godOfWar = nullptr;
    stray = nullptr;
    horizon = nullptr;
    plagueTale = nullptr;
    lastOfUs = nullptr;
    cuphead = nullptr;
    dyingLight = nullptr;
    warhammer = nullptr;
}

void Library::deleteWindows()
{
    delete eldenRing;
    delete godOfWar;
    delete stray;
    delete horizon;
    delete plagueTale;
    delete lastOfUs;
    delete cuphead;
    delete dyingLight;
    delete warhammer;
}

void Library::init()
{
    for(int i = 0; i < 9; ++i)
    {
        if(currentAccount->library.bought[i])
        {
            setCurrentGame((Games)(i));
            return;
        }
    }

    centralLayout->setCurrentWidget(ui->NoGames_widget);
}

void Library::setGameList()
{

    if(currentAccount->library.bought[(int)Games::ELDEN_RING])
        ui->ER_widget->show();
    else
        ui->ER_widget->hide();


    if(currentAccount->library.bought[(int)Games::GOD_OF_WAR])
        ui->GOW_widget->show();
    else
        ui->GOW_widget->hide();


    if(currentAccount->library.bought[(int)Games::STRAY])
        ui->Str_widget->show();
    else
        ui->Str_widget->hide();


    if(currentAccount->library.bought[(int)Games::PLAGUE_TALE])
        ui->PT_widget->show();
    else
        ui->PT_widget->hide();


    if(currentAccount->library.bought[(int)Games::HORIZON])
        ui->HFW_widget->show();
    else
        ui->HFW_widget->hide();


    if(currentAccount->library.bought[(int)Games::LAST_OF_US])
        ui->LOU_widget->show();
    else
        ui->LOU_widget->hide();


    if(currentAccount->library.bought[(int)Games::CUPHEAD])
        ui->Cup_widget->show();
    else
        ui->Cup_widget->hide();


    if(currentAccount->library.bought[(int)Games::DYING_LIGHT])
        ui->DL_widget->show();
    else
        ui->DL_widget->hide();


    if(currentAccount->library.bought[(int)Games::WARHAMMER])
        ui->War_widget->show();
    else
        ui->War_widget->hide();

}

void Library::setIcons()
{    
    ui->ER_icon->setPixmap(QPixmap("GameIcons/EldenRing.png"));
    ui->GOW_icon->setPixmap(QPixmap("GameIcons/GodOfWar.png"));
    ui->Str_icon->setPixmap(QPixmap("GameIcons/Stray.png"));
    ui->HFW_icon->setPixmap(QPixmap("GameIcons/Horizon.png"));
    ui->PT_icon->setPixmap(QPixmap("GameIcons/PlagueTale.png"));
    ui->LOU_icon->setPixmap(QPixmap("GameIcons/LastOfUs.png"));
    ui->Cup_icon->setPixmap(QPixmap("GameIcons/Cuphead.png"));
    ui->DL_icon->setPixmap(QPixmap("GameIcons/DyingLight.png"));
    ui->War_icon->setPixmap(QPixmap("GameIcons/Warhammer.png"));
}

void Library::setCurrentGame(Games _game)
{
    if(_game == Games::ELDEN_RING)
    {
        if(!eldenRing)
        {
            eldenRing = new ItemEldenRing(mainWindow, currentAccount);
            centralLayout->addWidget(eldenRing);
        }

        centralLayout->setCurrentWidget(eldenRing);
        ui->ER_widget->setStyleSheet(currentGame_styleSheet());
    }
    else
    {
        ui->ER_widget->setStyleSheet(baseGame_styleSheet());
    }

    if(_game == Games::GOD_OF_WAR)
    {
        if(!godOfWar)
        {
            godOfWar = new ItemGodOfWar(mainWindow, currentAccount);
            centralLayout->addWidget(godOfWar);
        }

        centralLayout->setCurrentWidget(godOfWar);
        ui->GOW_widget->setStyleSheet(currentGame_styleSheet());
    }
    else
    {
        ui->GOW_widget->setStyleSheet(baseGame_styleSheet());
    }

    if(_game == Games::STRAY)
    {
        if(!stray)
        {
            stray = new ItemStray(mainWindow, currentAccount);
            centralLayout->addWidget(stray);
        }

        centralLayout->setCurrentWidget(stray);
        ui->Str_widget->setStyleSheet(currentGame_styleSheet());
    }
    else
    {
        ui->Str_widget->setStyleSheet(baseGame_styleSheet());
    }

    if(_game == Games::HORIZON)
    {
        if(!horizon)
        {
            horizon = new ItemHorizon(mainWindow, currentAccount);
            centralLayout->addWidget(horizon);
        }

        centralLayout->setCurrentWidget(horizon);
        ui->HFW_widget->setStyleSheet(currentGame_styleSheet());
    }
    else
    {
        ui->HFW_widget->setStyleSheet(baseGame_styleSheet());
    }

    if(_game == Games::PLAGUE_TALE)
    {
        if(!plagueTale)
        {
            plagueTale = new ItemPlagueTale(mainWindow, currentAccount);
            centralLayout->addWidget(plagueTale);
        }

        centralLayout->setCurrentWidget(plagueTale);
        ui->PT_widget->setStyleSheet(currentGame_styleSheet());
    }
    else
    {
        ui->PT_widget->setStyleSheet(baseGame_styleSheet());
    }

    if(_game == Games::LAST_OF_US)
    {
        if(!lastOfUs)
        {
            lastOfUs = new ItemLastOfUs(mainWindow, currentAccount);
            centralLayout->addWidget(lastOfUs);
        }

        centralLayout->setCurrentWidget(lastOfUs);
        ui->LOU_widget->setStyleSheet(currentGame_styleSheet());
    }
    else
    {
        ui->LOU_widget->setStyleSheet(baseGame_styleSheet());
    }

    if(_game == Games::CUPHEAD)
    {
        if(!cuphead)
        {
            cuphead = new ItemCuphead(mainWindow, currentAccount);
            centralLayout->addWidget(cuphead);
        }

        centralLayout->setCurrentWidget(cuphead);
        ui->Cup_widget->setStyleSheet(currentGame_styleSheet());
    }
    else
    {
        ui->Cup_widget->setStyleSheet(baseGame_styleSheet());
    }

    if(_game == Games::DYING_LIGHT)
    {
        if(!dyingLight)
        {
            dyingLight = new ItemDyingLight(mainWindow, currentAccount);
            centralLayout->addWidget(dyingLight);
        }

        centralLayout->setCurrentWidget(dyingLight);
        ui->DL_widget->setStyleSheet(currentGame_styleSheet());
    }
    else
    {
        ui->DL_widget->setStyleSheet(baseGame_styleSheet());
    }

    if(_game == Games::WARHAMMER)
    {
        if(!warhammer)
        {
            warhammer = new ItemWarhammer(mainWindow, currentAccount);
            centralLayout->addWidget(warhammer);
        }

        centralLayout->setCurrentWidget(warhammer);
        ui->War_widget->setStyleSheet(currentGame_styleSheet());
    }
    else
    {
        ui->War_widget->setStyleSheet(baseGame_styleSheet());
    }
}

QString Library::currentGame_styleSheet()
{
    return "background-color: rgb(161, 171, 195); ";
}

QString Library::baseGame_styleSheet()
{
    return "QWidget{background-color: none;} QWidget:hover{background-color: rgb(161, 171, 195);}";
}

void Library::on_ER_pushButton_clicked()
{
    setCurrentGame(Games::ELDEN_RING);
}


void Library::on_GOW_button_clicked()
{
    setCurrentGame(Games::GOD_OF_WAR);
}

void Library::on_Str_button_clicked()
{
    setCurrentGame(Games::STRAY);
}

void Library::on_PT_button_clicked()
{
    setCurrentGame(Games::PLAGUE_TALE);
}


void Library::on_HWF_button_clicked()
{
    setCurrentGame(Games::HORIZON);
}

void Library::on_LOU_button_clicked()
{
    setCurrentGame(Games::LAST_OF_US);
}

void Library::on_Cup_button_clicked()
{
    setCurrentGame(Games::CUPHEAD);
}

void Library::on_DL_button_clicked()
{
    setCurrentGame(Games::DYING_LIGHT);
}


void Library::on_War_button_clicked()
{
    setCurrentGame(Games::WARHAMMER);
}


void Library::on_toStore_pushButton_clicked()
{
    mainWindow->showStore();
}


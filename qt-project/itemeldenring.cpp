#include "itemeldenring.h"
#include <QMessageBox>

#include "useraccount.h"
#include "mainwindow.h"

ItemEldenRing::ItemEldenRing(MainWindow* _mainWindow, UserAccount* _currentAccount) :
    StoreItem(_mainWindow, _currentAccount)
{
    this->loadScreens("GameImages/EldenRing_s1.png", "GameImages/EldenRing_s2.png", "GameImages/EldenRing_s3.png",
                      "GameImages/EldenRing_s4.png", "GameImages/EldenRing_s5.png");
    this->setScreens();
    this->setCover("GameImages/EldenRing_cover.png");
    this->setName("ELDEN RING");
    this->setPrice("59.99$");
    this->setMainDescription("THE NEW FANTASY ACTION RPG. Rise, Tarnished, and be guided by grace to brandish the "
                             "power of the Elden Ring and become an Elden Lord in the Lands Between.");
    this->setSmallDescriptions("Very Positive (10,104)", "Very Positive (542,245)", "25 Feb, 2022",
                               "FromSoftware Inc.", "FromSoftware Inc.");
    this->setLanguages("111-101-101-101-101");
    this->setMinSR("INTEL CORE I5-8400", "12 GB RAM", "NVIDIA GEFORCE GTX 1060",
                   "Version 12", "60 GB available space");
    this->setRecSR("INTEL CORE I7-8700K", "16 GB RAM", "NVIDIA GEFORCE GTX 1070",
                   "Version 12", "60 GB available space");

    this->updateWidget();
}

ItemEldenRing::~ItemEldenRing()
{

}

void ItemEldenRing::setStatus()
{
    this->bought = this->currentAccount->library.bought[(int)Games::ELDEN_RING];
    this->installed = this->currentAccount->library.installed[(int)Games::ELDEN_RING];
    this->inCart = this->currentAccount->cart.list[(int)Games::ELDEN_RING];
}

void ItemEldenRing::pressAddToCart()
{
    currentAccount->cart.list[(int)Games::ELDEN_RING] = true;
}

void ItemEldenRing::pressInstall()
{
    mainWindow->startDownload(Games::ELDEN_RING);
}

void ItemEldenRing::pressPlay()
{
    mainWindow->showPlayWindow(Games::ELDEN_RING, "GameIcons/EldenRing.png");
}

void ItemEldenRing::pressUninstall()
{
    currentAccount->library.installed[(int)Games::ELDEN_RING] = false;
    mainWindow->showInformationalWindow("Uninstall comleted", "Game ELDEN RING\nhas been successfully uninstalled");
    updateWidget();
}



#include "itemstray.h"
#include "useraccount.h"
#include "mainwindow.h"

ItemStray::ItemStray(MainWindow* _mainWindow, UserAccount* _currentAccount) :
    StoreItem(_mainWindow, _currentAccount)
{
    this->loadScreens("GameImages/Stray_s1.png", "GameImages/Stray_s2.png", "GameImages/Stray_s3.png",
                      "GameImages/Stray_s4.png", "GameImages/Stray_s5.png");
    this->setScreens();
    this->setCover("GameImages/Stray_cover.png");
    this->setName("Stray");
    this->setPrice("29.99$");
    this->setMainDescription("Lost, alone and separated from family, "
                             "a stray cat must untangle an ancient mystery to escape"
                             " a long-forgotten cybercity and find their way home.");
    this->setSmallDescriptions("Overwhelmingly Positive (1,355)", "Overwhelmingly Positive (113,792)", "19 Jul, 2022",
                               "BlueTwelve Studio", "Annapurna Interactive");
    this->setLanguages("101-101-101-101-101");
    this->setMinSR("Intel Core i5-2300", "8 GB RAM", "NVIDIA GeForce GTX 650 Ti",
                   "Version 12", "10 GB available space");
    this->setRecSR("Intel Core i5-8400", "8 GB RAM", "NVIDIA GeForce GTX 780",
                   "Version 12", "10 GB available space");

    this->updateWidget();
}

ItemStray::~ItemStray()
{

}

void ItemStray::setStatus()
{
    bought = currentAccount->library.bought[(int)Games::STRAY];
    installed = currentAccount->library.installed[(int)Games::STRAY];
    inCart = this->currentAccount->cart.list[(int)Games::STRAY];
}

void ItemStray::pressAddToCart()
{
    currentAccount->cart.list[(int)Games::STRAY] = true;
}

void ItemStray::pressInstall()
{
    mainWindow->startDownload(Games::STRAY);
}

void ItemStray::pressPlay()
{
    mainWindow->showPlayWindow(Games::STRAY, "GameIcons/Stray.png");
}

void ItemStray::pressUninstall()
{
    currentAccount->library.installed[(int)Games::STRAY] = false;
    mainWindow->showInformationalWindow("Uninstall comleted", "Game Stray\nhas been successfully uninstalled");
    updateWidget();
}

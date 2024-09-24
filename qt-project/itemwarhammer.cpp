#include "itemwarhammer.h"
#include "useraccount.h"
#include "mainwindow.h"

ItemWarhammer::ItemWarhammer(MainWindow* _mainWindow, UserAccount* _currentAccount) :
    StoreItem(_mainWindow, _currentAccount)
{
    this->loadScreens("GameImages/Warhammer_s1.png", "GameImages/Warhammer_s2.png", "GameImages/Warhammer_s3.png",
                      "GameImages/Warhammer_s4.png", "GameImages/Warhammer_s5.png");
    this->setScreens();
    this->setCover("GameImages/Warhammer_cover.png");
    this->setName("Warhammer 40,000: Darktide");
    this->setPrice("25.99$");
    this->setMainDescription("Take back the city of Tertium from hordes of bloodthirsty foes in this intense and brutal action shooter. "
                             "Warhammer 40,000: Darktide is the new co-op focused experience from the award-winning team behind the Vermintide series. "
                             "As Tertium falls, Rejects Will Rise.");
    this->setSmallDescriptions("Very Positive (3,612)", "Mixed (65,900)", "30 Nov, 2022", "Fatshark", "Fatshark");
    this->setLanguages("111-101-101-101-101");
    this->setMinSR("Intel i5-6600", "8 GB RAM", "NVIDIA GTX 970",
                   "Version 12", "50 GB available space");
    this->setRecSR("Intel i7-9700K", "16 GB RAM", "NVIDIA RTX 3060",
                   "Version 12", "50 GB available space");

    this->updateWidget();
}

ItemWarhammer::~ItemWarhammer()
{

}

void ItemWarhammer::setStatus()
{
    bought = currentAccount->library.bought[(int)Games::WARHAMMER];
    installed = currentAccount->library.installed[(int)Games::WARHAMMER];
    inCart = this->currentAccount->cart.list[(int)Games::WARHAMMER];
}

void ItemWarhammer::pressAddToCart()
{
    currentAccount->cart.list[(int)Games::WARHAMMER] = true;
}

void ItemWarhammer::pressInstall()
{
    mainWindow->startDownload(Games::WARHAMMER);
}

void ItemWarhammer::pressPlay()
{
    mainWindow->showPlayWindow(Games::WARHAMMER, "GameIcons/Warhammer.png");
}

void ItemWarhammer::pressUninstall()
{
    currentAccount->library.installed[(int)Games::WARHAMMER] = false;
    mainWindow->showInformationalWindow("Uninstall comleted", "Game Warhammer 40,000: Darktide\nhas been successfully uninstalled");
    updateWidget();
}

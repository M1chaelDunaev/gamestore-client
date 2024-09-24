#include "itemcuphead.h"
#include "useraccount.h"
#include "mainwindow.h"

ItemCuphead::ItemCuphead(MainWindow* _mainWindow, UserAccount* _currentAccount) :
    StoreItem(_mainWindow, _currentAccount)
{
    this->loadScreens("GameImages/Cuphead_s1.png", "GameImages/Cuphead_s2.png", "GameImages/Cuphead_s3.png",
                      "GameImages/Cuphead_s4.png", "GameImages/Cuphead_s5.png");
    this->setScreens();
    this->setCover("GameImages/Cuphead_cover.png");
    this->setName("Cuphead: The Delicious Last Course");
    this->setPrice("7.99$");
    this->setMainDescription("Cuphead is a classic run and gun action game heavily focused on boss battles. "
                             "Inspired by cartoons of the 1930s, the visuals and audio are painstakingly created with "
                             "the same techniques of the era, i.e. traditional hand drawn cel animation, watercolor backgrounds, "
                             "and original jazz recordings.");
    this->setSmallDescriptions("Very Positive (27)", "Overwhelmingly Positive (3,828)", "30 Jun, 2022", "Studio MDHR", "Studio MDHR");
    this->setLanguages("100-100-100-100-100");
    this->setMinSR("Intel Core2 Duo E8400", "4 GB RAM", "2GB VRAM or higher", "Version 11", "2 GB available space");
    this->setRecSR("Intel Core2 Duo E8400", "4 GB RAM", "2GB VRAM or higher", "Version 11", "2 GB available space");

    this->updateWidget();
}

ItemCuphead::~ItemCuphead()
{

}

void ItemCuphead::setStatus()
{
    bought = this->currentAccount->library.bought[(int)Games::CUPHEAD];
    installed = this->currentAccount->library.installed[(int)Games::CUPHEAD];
    inCart = this->currentAccount->cart.list[(int)Games::CUPHEAD];
}

void ItemCuphead::pressAddToCart()
{
    currentAccount->cart.list[(int)Games::CUPHEAD] = true;
}

void ItemCuphead::pressInstall()
{
    mainWindow->startDownload(Games::CUPHEAD);
}

void ItemCuphead::pressPlay()
{
    mainWindow->showPlayWindow(Games::CUPHEAD, "GameIcons/Cuphead.png");
}

void ItemCuphead::pressUninstall()
{
    currentAccount->library.installed[(int)Games::CUPHEAD] = false;
    mainWindow->showInformationalWindow("Uninstall comleted", "Game Cuphead: The Delicious Last Course\nhas been"
                                                              "successfully uninstalled");
    updateWidget();
}


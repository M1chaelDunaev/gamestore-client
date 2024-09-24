#include "itemhorizon.h"
#include "useraccount.h"
#include "mainwindow.h"

ItemHorizon::ItemHorizon(MainWindow* _mainWindow, UserAccount* _currentAccount) :
    StoreItem(_mainWindow, _currentAccount)
{
    this->loadScreens("GameImages/Horizon_s1.png", "GameImages/Horizon_s2.png", "GameImages/Horizon_s3.png",
                      "GameImages/Horizon_s4.png", "GameImages/Horizon_s5.png");
    this->setScreens();
    this->setCover("GameImages/Horizon_cover.png");
    this->setName("Horizon Forbidden West");
    this->setPrice("59.99$");
    this->setMainDescription("This Complete Edition allows you to enjoy the critically acclaimed Horizon Forbidden West "
                             "in its entirety with bonus content, including the Burning Shores "
                             "story expansion that picks up after the main game.");
    this->setSmallDescriptions("Very Positive (343)", "Very Positive (9,898)", "18 Feb, 2022",
                               "Nixxes Software", "PlayStation PC LLC");
    this->setLanguages("111-111-111-111-111");
    this->setMinSR("Intel Core i7-4790K", "16 GB RAM", "NVIDIA GTX 970",
                   "Version 12", "90 GB available space");
    this->setRecSR("Intel Core i7-8700", "16 GB RAM", "NVIDIA RTX 2080",
                   "Version 12", "90 GB available space");

    this->updateWidget();
}

ItemHorizon::~ItemHorizon()
{

}

void ItemHorizon::setStatus()
{
    bought = currentAccount->library.bought[(int)Games::HORIZON];
    installed = currentAccount->library.installed[(int)Games::HORIZON];
    inCart = this->currentAccount->cart.list[(int)Games::HORIZON];
}

void ItemHorizon::pressAddToCart()
{
    currentAccount->cart.list[(int)Games::HORIZON] = true;
}

void ItemHorizon::pressInstall()
{
    mainWindow->startDownload(Games::HORIZON);
}

void ItemHorizon::pressPlay()
{
    mainWindow->showPlayWindow(Games::HORIZON, "GameIcons/Horizon.png");
}

void ItemHorizon::pressUninstall()
{
    currentAccount->library.installed[(int)Games::HORIZON] = false;
    mainWindow->showInformationalWindow("Uninstall comleted", "Game Horizon Forbidden West\nhas been successfully uninstalled");
    updateWidget();
}

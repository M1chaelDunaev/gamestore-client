#include "itemlastofus.h"
#include "useraccount.h"
#include "mainwindow.h"

ItemLastOfUs::ItemLastOfUs(MainWindow* _mainWindow, UserAccount* _currentAccount) :
    StoreItem(_mainWindow, _currentAccount)
{
    this->loadScreens("GameImages/LastOfUs_s1.png", "GameImages/LastOfUs_s2.png", "GameImages/LastOfUs_s3.png",
                      "GameImages/LastOfUs_s4.png", "GameImages/LastOfUs_s5.png");
    this->setScreens();
    this->setCover("GameImages/LastOfUs_cover.png");
    this->setName("The Last of Us: Part I");
    this->setPrice("59.99$");
    this->setMainDescription("Experience the emotional storytelling and unforgettable characters in The Last of Us™, "
                             "winner of over 200 Game of the Year awards.");
    this->setSmallDescriptions("Very Positive (804)", "Mixed (23,237)", "28 Mar, 2022",
                               "Naughty Dog LLC", "PlayStation PC LLC");
    this->setLanguages("111-111-111-101-101");
    this->setMinSR("Intel Core i7-4770K", "16 GB RAM", "NVIDIA GTX 970",
                   "Version 12", "100 GB available space");
    this->setRecSR("Intel Core i7-8700", "16 GB RAM", "NVIDIA RTX 2070 SUPER",
                   "Version 12", "100 GB available space");

    this->updateWidget();
}

ItemLastOfUs::~ItemLastOfUs()
{

}

void ItemLastOfUs::setStatus()
{
    bought = currentAccount->library.bought[(int)Games::LAST_OF_US];
    installed = currentAccount->library.installed[(int)Games::LAST_OF_US];
    inCart = this->currentAccount->cart.list[(int)Games::LAST_OF_US];
}

void ItemLastOfUs::pressAddToCart()
{
    currentAccount->cart.list[(int)Games::LAST_OF_US] = true;
}

void ItemLastOfUs::pressInstall()
{
    mainWindow->startDownload(Games::LAST_OF_US);
}

void ItemLastOfUs::pressPlay()
{
    mainWindow->showPlayWindow(Games::LAST_OF_US, "GameIcons/LastOfUs.png");
}

void ItemLastOfUs::pressUninstall()
{
    currentAccount->library.installed[(int)Games::LAST_OF_US] = false;
    mainWindow->showInformationalWindow("Uninstall comleted", "Game The Last of Us: Part I\nhas been successfully uninstalled");
    updateWidget();
}

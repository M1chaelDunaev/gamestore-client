#include "itemplaguetale.h"
#include "useraccount.h"
#include "mainwindow.h"

ItemPlagueTale::ItemPlagueTale(MainWindow* _mainWindow, UserAccount* _currentAccount) :
    StoreItem(_mainWindow, _currentAccount)
{
    this->loadScreens("GameImages/PlagueTale_s1.png", "GameImages/PlagueTale_s2.png", "GameImages/PlagueTale_s3.png",
                      "GameImages/PlagueTale_s4.png", "GameImages/PlagueTale_s5.png");
    this->setScreens();
    this->setCover("GameImages/PlagueTale_cover.png");
    this->setName("A Plague Tale: Requiem");
    this->setPrice("59.99$");
    this->setMainDescription("Embark on a heartrending journey into a brutal, breathtaking world, "
                             "and discover the cost of saving those you love in a desperate struggle for survival. "
                             "Strike from the shadows or unleash hell with a variety of weapons, tools and unearthly powers.");
    this->setSmallDescriptions("Very Positive (343)", "Very Positive (9,898)", "17 Oct, 2022",
                               "Asobo Studio", "Focus Entertainment");
    this->setLanguages("111-111-111-111-111");
    this->setMinSR("Intel Core i5-4690K", "16 GB RAM", "GeForce GTX 970",
                   "Version 12", "55 GB available space");
    this->setRecSR("Intel Core i7-8700K", "16 GB RAM", "GeForce RTX 3070",
                   "Version 12", "55 GB available space");

    this->updateWidget();
}

ItemPlagueTale::~ItemPlagueTale()
{

}

void ItemPlagueTale::setStatus()
{
    bought = currentAccount->library.bought[(int)Games::PLAGUE_TALE];
    installed = currentAccount->library.installed[(int)Games::PLAGUE_TALE];
    inCart = this->currentAccount->cart.list[(int)Games::PLAGUE_TALE];
}

void ItemPlagueTale::pressAddToCart()
{
    currentAccount->cart.list[(int)Games::PLAGUE_TALE] = true;
}

void ItemPlagueTale::pressInstall()
{
    mainWindow->startDownload(Games::PLAGUE_TALE);
}

void ItemPlagueTale::pressPlay()
{
    mainWindow->showPlayWindow(Games::PLAGUE_TALE, "GameIcons/PlagueTale.png");
}

void ItemPlagueTale::pressUninstall()
{
    currentAccount->library.installed[(int)Games::PLAGUE_TALE] = false;
    mainWindow->showInformationalWindow("Uninstall comleted", "Game A Plague Tale: Requiem\nhas been successfully uninstalled");
    updateWidget();
}



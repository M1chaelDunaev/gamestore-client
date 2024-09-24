#include "itemdyinglight.h"
#include "useraccount.h"
#include "mainwindow.h"

ItemDyingLight::ItemDyingLight(MainWindow* _mainWindow, UserAccount* _currentAccount) :
    StoreItem(_mainWindow, _currentAccount)
{
    this->loadScreens("GameImages/DyingLight_s1.png", "GameImages/DyingLight_s2.png", "GameImages/DyingLight_s3.png",
                      "GameImages/DyingLight_s4.png", "GameImages/DyingLight_s5.png");
    this->setScreens();
    this->setCover("GameImages/DyingLight_cover.png");
    this->setName("Dying Light II");
    this->setPrice("59.99$");
    this->setMainDescription("Humanity is fighting a losing battle against the virus. Experience a post-apocalyptic open "
                             "world overrun by hordes of zombies, where your parkour and combat skills are key to survival. "
                             "Traverse the City freely during the day, but watch the monsters take over during the night.");
    this->setSmallDescriptions("Very Positive (1,261)", "Mostly Positive (116,279)", "4 Feb, 2022", "Techland", "Techland");
    this->setLanguages("111-111-111-111-111");
    this->setMinSR("Intel Core i3-9100", "8 GB RAM", "NVIDIA GTX 1050 Ti", "Version 11", "60 GB available space");
    this->setRecSR("Intel Core i5-8600K", "16 GB RAM", "NVIDIA RTX 2060", "Version 11", "60 GB available space");

    this->updateWidget();
}

ItemDyingLight::~ItemDyingLight()
{

}

void ItemDyingLight::setStatus()
{
    bought = this->currentAccount->library.bought[(int)Games::DYING_LIGHT];
    installed = this->currentAccount->library.installed[(int)Games::DYING_LIGHT];
    inCart = this->currentAccount->cart.list[(int)Games::DYING_LIGHT];
}

void ItemDyingLight::pressAddToCart()
{
    currentAccount->cart.list[(int)Games::DYING_LIGHT] = true;
}

void ItemDyingLight::pressInstall()
{
    mainWindow->startDownload(Games::DYING_LIGHT);
}

void ItemDyingLight::pressPlay()
{
    mainWindow->showPlayWindow(Games::DYING_LIGHT, "GameIcons/DyingLight.png");
}

void ItemDyingLight::pressUninstall()
{
    currentAccount->library.installed[(int)Games::DYING_LIGHT] = false;
    mainWindow->showInformationalWindow("Uninstall comleted", "Game Dying Light II\nhas been successfully uninstalled");
    updateWidget();
}

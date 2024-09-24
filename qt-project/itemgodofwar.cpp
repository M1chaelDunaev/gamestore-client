#include "itemgodofwar.h"
#include "useraccount.h"
#include "mainwindow.h"

ItemGodOfWar::ItemGodOfWar(MainWindow* _mainWindow, UserAccount* _currentAccount) :
    StoreItem(_mainWindow, _currentAccount)
{
    this->loadScreens("GameImages/GodOfWar_s1.png", "GameImages/GodOfWar_s2.png", "GameImages/GodOfWar_s3.png",
                      "GameImages/GodOfWar_s4.png", "GameImages/GodOfWar_s5.png");
    this->setScreens();
    this->setCover("GameImages/GodOfWar_cover.png");
    this->setName("God of War: Ragnarok");
    this->setPrice("59.99$");
    this->setMainDescription("His vengeance against the Gods of Olympus years behind him, "
                             "Kratos now lives as a man in the realm of Norse Gods and monsters. "
                             "It is in this harsh, unforgiving world that he must fight to survive… and teach his son to do the same.");
    this->setSmallDescriptions("Overwhelmingly Positive (929)", "Overwhelmingly Positive (78,970)", "14 Jan, 2022",
                               "Santa Monica Studio", "PlayStation PC LLC");
    this->setLanguages("111-111-111-111-111");
    this->setMinSR("Intel i5-2500k", "8 GB RAM", "NVIDIA GTX 960",
                   "Version 11", "70 GB available space");
    this->setRecSR("Intel i5-6600k", "8 GB RAM", "NVIDIA GTX 1060",
                   "Version 11", "70 GB available space");

    this->updateWidget();
}

ItemGodOfWar::~ItemGodOfWar()
{

}

void ItemGodOfWar::setStatus()
{
    bought = currentAccount->library.bought[(int)Games::GOD_OF_WAR];
    installed = currentAccount->library.installed[(int)Games::GOD_OF_WAR];
    inCart = this->currentAccount->cart.list[(int)Games::GOD_OF_WAR];
}

void ItemGodOfWar::pressAddToCart()
{
    currentAccount->cart.list[(int)Games::GOD_OF_WAR] = true;
}

void ItemGodOfWar::pressInstall()
{
    mainWindow->startDownload(Games::GOD_OF_WAR);
}

void ItemGodOfWar::pressPlay()
{
    mainWindow->showPlayWindow(Games::GOD_OF_WAR, "GameIcons/GodOfWar.png");
}

void ItemGodOfWar::pressUninstall()
{
    currentAccount->library.installed[(int)Games::GOD_OF_WAR] = false;
    mainWindow->showInformationalWindow("Uninstall comleted", "Game God of War: Ragnarok\nhas been successfully uninstalled");
    updateWidget();
}

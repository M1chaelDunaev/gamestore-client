#include "store.h"
#include "ui_store.h"
#include "mainwindow.h"
#include "useraccount.h"
#include "searchlineedit.h"

#include <QPixmap>

Store::Store(MainWindow* _mainWindow, UserAccount* _currentAccount) :
    QWidget(nullptr), ui(new Ui::Store), mainWindow(_mainWindow), currentAccount(_currentAccount)
{
    ui->setupUi(this);

    ui->ER_pushButton->setIcon(QPixmap("GameIcons/EldenRing.png"));
    ui->GOW_pushButton->setIcon(QPixmap("GameIcons/GodOfWar.png"));
    ui->Str_pushButton->setIcon(QPixmap("GameIcons/Stray.png"));
    ui->HFW_pushButton->setIcon(QPixmap("GameIcons/Horizon.png"));
    ui->PT_pushButton->setIcon(QPixmap("GameIcons/PlagueTale.png"));
    ui->LOU_pushButton->setIcon(QPixmap("GameIcons/LastOfUs.png"));
    ui->Cup_pushButton->setIcon(QPixmap("GameIcons/Cuphead.png"));
    ui->DL_pushButton->setIcon(QPixmap("GameIcons/DyingLight.png"));
    ui->War_pushButton->setIcon(QPixmap("GameIcons/Warhammer.png"));
    ui->Search_pushButton->setIcon(QPixmap("ApplicationIcons/Magnifyer.png"));

    SearchLineEdit* sl = new SearchLineEdit(ui->BottomPanel_widget);
    sl->setGeometry(727, 10, 210, 30);
    sl->show();
}

Store::~Store()
{
    delete ui;
}

void Store::showEvent(QShowEvent *event)
{
    updateWidget();
}

void Store::updateCartButton()
{
    int count = currentAccount->cart.countOfItems();
    ui->Cart_pushButton->setText("CART(" + QString::number(count) + ")" );
}

void Store::updateWidget()
{
    updateCartButton();

    if(currentAccount->cart.list[(int)Games::ELDEN_RING])
    {
        ui->ERBUY_pushButton->setIcon(QPixmap("ApplicationIcons/InCart.png"));
        ui->ERBUY_pushButton->setStyleSheet("background-color: rgb(119, 125, 145);");
    }
    else
    {
        ui->ERBUY_pushButton->setIcon(QPixmap("ApplicationIcons/AddToCart.png"));
        ui->ERBUY_pushButton->setStyleSheet("background-color: rgb(160, 200, 24);");
    }

    if(currentAccount->cart.list[(int)Games::GOD_OF_WAR])
    {
        ui->GOWBUY_pushButton->setIcon(QPixmap("ApplicationIcons/InCart.png"));
        ui->GOWBUY_pushButton->setStyleSheet("background-color: rgb(119, 125, 145);");
    }
    else
    {
        ui->GOWBUY_pushButton->setIcon(QPixmap("ApplicationIcons/AddToCart.png"));
        ui->GOWBUY_pushButton->setStyleSheet("background-color: rgb(160, 200, 24);");
    }

    if(currentAccount->cart.list[(int)Games::STRAY])
    {
        ui->StrBUY_pushButton->setIcon(QPixmap("ApplicationIcons/InCart.png"));
        ui->StrBUY_pushButton->setStyleSheet("background-color: rgb(119, 125, 145);");
    }
    else
    {
        ui->StrBUY_pushButton->setIcon(QPixmap("ApplicationIcons/AddToCart.png"));
        ui->StrBUY_pushButton->setStyleSheet("background-color: rgb(160, 200, 24);");
    }

    if(currentAccount->cart.list[(int)Games::HORIZON])
    {
        ui->HFWBUY_pushButton->setIcon(QPixmap("ApplicationIcons/InCart.png"));
        ui->HFWBUY_pushButton->setStyleSheet("background-color: rgb(119, 125, 145);");
    }
    else
    {
        ui->HFWBUY_pushButton->setIcon(QPixmap("ApplicationIcons/AddToCart.png"));
        ui->HFWBUY_pushButton->setStyleSheet("background-color: rgb(160, 200, 24);");
    }

    if(currentAccount->cart.list[(int)Games::PLAGUE_TALE])
    {
        ui->PTBUY_pushButton->setIcon(QPixmap("ApplicationIcons/InCart.png"));
        ui->PTBUY_pushButton->setStyleSheet("background-color: rgb(119, 125, 145);");
    }
    else
    {
        ui->PTBUY_pushButton->setIcon(QPixmap("ApplicationIcons/AddToCart.png"));
        ui->PTBUY_pushButton->setStyleSheet("background-color: rgb(160, 200, 24);");
    }

    if(currentAccount->cart.list[(int)Games::LAST_OF_US])
    {
        ui->LOUBUY_pushButton->setIcon(QPixmap("ApplicationIcons/InCart.png"));
        ui->LOUBUY_pushButton->setStyleSheet("background-color: rgb(119, 125, 145);");
    }
    else
    {
        ui->LOUBUY_pushButton->setIcon(QPixmap("ApplicationIcons/AddToCart.png"));
        ui->LOUBUY_pushButton->setStyleSheet("background-color: rgb(160, 200, 24);");
    }

    if(currentAccount->cart.list[(int)Games::CUPHEAD])
    {
        ui->CupBUY_pushButton->setIcon(QPixmap("ApplicationIcons/InCart.png"));
        ui->CupBUY_pushButton->setStyleSheet("background-color: rgb(119, 125, 145);");
    }
    else
    {
        ui->CupBUY_pushButton->setIcon(QPixmap("ApplicationIcons/AddToCart.png"));
        ui->CupBUY_pushButton->setStyleSheet("background-color: rgb(160, 200, 24);");
    }

    if(currentAccount->cart.list[(int)Games::DYING_LIGHT])
    {
        ui->DLBUY_pushButton->setIcon(QPixmap("ApplicationIcons/InCart.png"));
        ui->DLBUY_pushButton->setStyleSheet("background-color: rgb(119, 125, 145);");
    }
    else
    {
        ui->DLBUY_pushButton->setIcon(QPixmap("ApplicationIcons/AddToCart.png"));
        ui->DLBUY_pushButton->setStyleSheet("background-color: rgb(160, 200, 24);");
    }

    if(currentAccount->cart.list[(int)Games::WARHAMMER])
    {
        ui->WarBUY_pushButton->setIcon(QPixmap("ApplicationIcons/InCart.png"));
        ui->WarBUY_pushButton->setStyleSheet("background-color: rgb(119, 125, 145);");
    }
    else
    {
        ui->WarBUY_pushButton->setIcon(QPixmap("ApplicationIcons/AddToCart.png"));
        ui->WarBUY_pushButton->setStyleSheet("background-color: rgb(160, 200, 24);");
    }
}

void Store::showCategoriesErrorMessage()
{
    mainWindow->showInformationalWindow("Error", "Categories are not available in this version");
}

void Store::on_ER_pushButton_clicked()
{
    mainWindow->showGame(Games::ELDEN_RING);
}

void Store::on_GOW_pushButton_clicked()
{
    mainWindow->showGame(Games::GOD_OF_WAR);
}

void Store::on_Str_pushButton_clicked()
{
    mainWindow->showGame(Games::STRAY);
}

void Store::on_PT_pushButton_clicked()
{
    mainWindow->showGame(Games::PLAGUE_TALE);
}

void Store::on_HFW_pushButton_clicked()
{
    mainWindow->showGame(Games::HORIZON);
}

void Store::on_LOU_pushButton_clicked()
{
   mainWindow->showGame(Games::LAST_OF_US);
}

void Store::on_Cup_pushButton_clicked()
{
    mainWindow->showGame(Games::CUPHEAD);
}

void Store::on_DL_pushButton_clicked()
{
    mainWindow->showGame(Games::DYING_LIGHT);
}

void Store::on_War_pushButton_clicked()
{
   mainWindow->showGame(Games::WARHAMMER);
}

void Store::on_Cart_pushButton_clicked()
{
   mainWindow->showCart();
}

void Store::on_ERBUY_pushButton_clicked()
{
   if(currentAccount->cart.list[int(Games::ELDEN_RING)])
        return;

    currentAccount->cart.list[int(Games::ELDEN_RING)] = true;
    updateWidget();
}

void Store::on_GOWBUY_pushButton_clicked()
{
    if(currentAccount->cart.list[(int)Games::GOD_OF_WAR])
        return;
    currentAccount->cart.list[(int)Games::GOD_OF_WAR] = true;
    updateWidget();
}

void Store::on_StrBUY_pushButton_clicked()
{
    if(currentAccount->cart.list[(int)Games::STRAY])
        return;
    currentAccount->cart.list[(int)Games::STRAY] = true;
    updateWidget();
}

void Store::on_PTBUY_pushButton_clicked()
{
    if(currentAccount->cart.list[(int)Games::PLAGUE_TALE])
        return;
    currentAccount->cart.list[(int)Games::PLAGUE_TALE] = true;
    updateWidget();
}

void Store::on_HFWBUY_pushButton_clicked()
{
    if(currentAccount->cart.list[(int)Games::HORIZON])
        return;
    currentAccount->cart.list[(int)Games::HORIZON] = true;
    updateWidget();
}

void Store::on_LOUBUY_pushButton_clicked()
{
    if(currentAccount->cart.list[(int)Games::LAST_OF_US])
        return;
    currentAccount->cart.list[(int)Games::LAST_OF_US] = true;
    updateWidget();
}

void Store::on_CupBUY_pushButton_clicked()
{
    if(currentAccount->cart.list[(int)Games::CUPHEAD])
        return;
    currentAccount->cart.list[(int)Games::CUPHEAD] = true;
    updateWidget();
}

void Store::on_DLBUY_pushButton_clicked()
{
    if(currentAccount->cart.list[(int)Games::DYING_LIGHT])
        return;
    currentAccount->cart.list[(int)Games::DYING_LIGHT] = true;
    updateWidget();
}

void Store::on_WarBUY_pushButton_clicked()
{
    if(currentAccount->cart.list[(int)Games::WARHAMMER])
        return;
    currentAccount->cart.list[(int)Games::WARHAMMER] = true;
    updateWidget();
}



void Store::on_Gifts_pushButton_clicked()
{
    mainWindow->showGiftsWindow();
}


void Store::on_TopUpBalance_pushButton_clicked()
{
    mainWindow->topUpBalance();
}


void Store::on_FriendsGames_pushButton_clicked()
{
    mainWindow->showCommunity();
}


void Store::on_YourGames_pushButton_clicked()
{
    mainWindow->showLibrary();
}


void Store::on_pushButton_clicked()
{
    showCategoriesErrorMessage();
}


void Store::on_pushButton_2_clicked()
{
    showCategoriesErrorMessage();
}


void Store::on_pushButton_3_clicked()
{
    showCategoriesErrorMessage();
}


void Store::on_pushButton_4_clicked()
{
    showCategoriesErrorMessage();
}


void Store::on_pushButton_5_clicked()
{
    showCategoriesErrorMessage();
}


void Store::on_pushButton_6_clicked()
{
    showCategoriesErrorMessage();
}


void Store::on_pushButton_7_clicked()
{
    showCategoriesErrorMessage();
}


void Store::on_pushButton_8_clicked()
{
    showCategoriesErrorMessage();
}


void Store::on_pushButton_9_clicked()
{
    showCategoriesErrorMessage();
}


void Store::on_pushButton_10_clicked()
{
    showCategoriesErrorMessage();
}


void Store::on_Search_pushButton_clicked()
{
    mainWindow->showInformationalWindow("Error", "Search is not available in this version");
}


void Store::on_Wishlist_pushButton_clicked()
{
    mainWindow->showInformationalWindow("Error", "Wishlist is not available in this version");
}


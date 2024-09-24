#include "cart.h"
#include "ui_cart.h"
#include <QImage>
#include <QPixmap>
#include <QMessageBox>
#include "useraccount.h"
#include "mainwindow.h"
#include "promocodeslist.h"
#include "functions.h"

Cart::Cart(MainWindow* _mainWindow, UserAccount* _currentAccount) :
    QWidget(nullptr), ui(new Ui::Cart), mainWindow(_mainWindow), currentAccount(_currentAccount)
{
    ui->setupUi(this);
    setIcons();
    update();
}

Cart::~Cart()
{
    delete ui;
}

void Cart::setIcons()
{
    QImage tempImage;

    tempImage.load("GameImages/EldenRing_cover.png");
    ui->ER_icon->setPixmap( QPixmap::fromImage( tempImage.scaled(ui->ER_icon->size()) ) );

    tempImage.load("GameImages/GodOfWar_cover.png");
    ui->GOW_icon->setPixmap( QPixmap::fromImage( tempImage.scaled(ui->GOW_icon->size()) ) );

    tempImage.load("GameImages/Stray_cover.png");
    ui->Str_icon->setPixmap( QPixmap::fromImage( tempImage.scaled(ui->Str_icon->size()) ) );

    tempImage.load("GameImages/Horizon_cover.png");
    ui->HFW_icon->setPixmap( QPixmap::fromImage( tempImage.scaled(ui->HFW_icon->size()) ) );

    tempImage.load("GameImages/PlagueTale_cover.png");
    ui->PT_icon->setPixmap( QPixmap::fromImage( tempImage.scaled(ui->PT_icon->size()) ) );

    tempImage.load("GameImages/LastOfUs_cover.png");
    ui->LOU_icon->setPixmap( QPixmap::fromImage( tempImage.scaled(ui->LOU_icon->size()) ) );

    tempImage.load("GameImages/Cuphead_cover.png");
    ui->Cup_icon->setPixmap( QPixmap::fromImage( tempImage.scaled(ui->Cup_icon->size()) ) );

    tempImage.load("GameImages/DyingLight_cover.png");
    ui->DL_icon->setPixmap( QPixmap::fromImage( tempImage.scaled(ui->DL_icon->size()) ) );

    tempImage.load("GameImages/Warhammer_cover.png");
    ui->War_icon->setPixmap( QPixmap::fromImage( tempImage.scaled(ui->War_icon->size()) ) );


    ui->ER_win->setPixmap(QPixmap("ApplicationIcons/WindowsSign.png"));
    ui->GOW_win->setPixmap(QPixmap("ApplicationIcons/WindowsSign.png"));
    ui->Str_win->setPixmap(QPixmap("ApplicationIcons/WindowsSign.png"));
    ui->HFW_win->setPixmap(QPixmap("ApplicationIcons/WindowsSign.png"));
    ui->PT_win->setPixmap(QPixmap("ApplicationIcons/WindowsSign.png"));
    ui->LOU_win->setPixmap(QPixmap("ApplicationIcons/WindowsSign.png"));
    ui->Cup_win->setPixmap(QPixmap("ApplicationIcons/WindowsSign.png"));
    ui->DL_win->setPixmap(QPixmap("ApplicationIcons/WindowsSign.png"));
    ui->War_win->setPixmap(QPixmap("ApplicationIcons/WindowsSign.png"));
}

void Cart::update()
{
    double totalSum = 0.0;
    QString temp = "";
    ui->Total_widget->show();

    if(currentAccount->cart.list[(int)Games::ELDEN_RING])
    {
        ui->ER_widget->show();
        temp = ui->ER_price->text();
        temp.removeLast();
        totalSum += temp.toDouble();
    }
    else
    {
        ui->ER_widget->hide();
    }

    if(currentAccount->cart.list[(int)Games::GOD_OF_WAR])
    {
        ui->GOW_widget->show();
        temp = ui->GOW_price->text();
        temp.removeLast();
        totalSum += temp.toDouble();
    }
    else
    {
        ui->GOW_widget->hide();
    }

    if(currentAccount->cart.list[(int)Games::STRAY])
    {
        ui->Str_widget->show();
        temp = ui->Str_price->text();
        temp.removeLast();
        totalSum += temp.toDouble();
    }
    else
    {
        ui->Str_widget->hide();
    }

    if(currentAccount->cart.list[(int)Games::HORIZON])
    {
        ui->HFW_widget->show();
        temp = ui->HFW_price->text();
        temp.removeLast();
        totalSum += temp.toDouble();
    }
    else
    {
        ui->HFW_widget->hide();
    }

    if(currentAccount->cart.list[(int)Games::PLAGUE_TALE])
    {
        ui->PT_widget->show();
        temp = ui->PT_price->text();
        temp.removeLast();
        totalSum += temp.toDouble();
    }
    else
    {
        ui->PT_widget->hide();
    }

    if(currentAccount->cart.list[(int)Games::LAST_OF_US])
    {
        ui->LOU_widget->show();
        temp = ui->LOU_price->text();
        temp.removeLast();
        totalSum += temp.toDouble();
    }
    else
    {
        ui->LOU_widget->hide();
    }

    if(currentAccount->cart.list[(int)Games::CUPHEAD])
    {
        ui->Cup_widget->show();
        temp = ui->Cup_price->text();
        temp.removeLast();
        totalSum += temp.toDouble();
    }
    else
    {
        ui->Cup_widget->hide();
    }

    if(currentAccount->cart.list[(int)Games::DYING_LIGHT])
    {
        ui->DL_widget->show();
        temp = ui->DL_price->text();
        temp.removeLast();
        totalSum += temp.toDouble();
    }
    else
    {
        ui->DL_widget->hide();
    }

    if(currentAccount->cart.list[(int)Games::WARHAMMER])
    {
        ui->War_widget->show();
        temp = ui->War_price->text();
        temp.removeLast();
        totalSum += temp.toDouble();
    }
    else
    {
        ui->War_widget->hide();
    }

    if(totalSum < 1.0)
    {
        ui->Total_widget->hide();
        return;
    }


    QString finalPrice = roundTheDouble(totalSum);
    finalPrice.push_back('$');

    ui->TotalPrice->setText(finalPrice);
}

void Cart::on_AllProducts_pushButton_clicked()
{
    mainWindow->showStore();
}

void Cart::on_ER_remove_clicked()
{
    currentAccount->cart.list[(int)Games::ELDEN_RING] = false;
    update();
}


void Cart::on_GOW_remove_clicked()
{
    currentAccount->cart.list[(int)Games::GOD_OF_WAR] = false;
    update();
}


void Cart::on_Str_remove_clicked()
{
    currentAccount->cart.list[(int)Games::STRAY] = false;
    update();
}


void Cart::on_HFW_remove_clicked()
{
    currentAccount->cart.list[(int)Games::HORIZON] = false;
    update();
}


void Cart::on_PT_remove_clicked()
{
    currentAccount->cart.list[(int)Games::PLAGUE_TALE] = false;
    update();
}


void Cart::on_LOU_remove_clicked()
{
    currentAccount->cart.list[(int)Games::LAST_OF_US] = false;
    update();
}


void Cart::on_Cup_remove_clicked()
{
    currentAccount->cart.list[(int)Games::CUPHEAD] = false;
    update();
}


void Cart::on_DL_remove_clicked()
{
    currentAccount->cart.list[(int)Games::DYING_LIGHT] = false;
    update();
}


void Cart::on_War_remove_clicked()
{
    currentAccount->cart.list[(int)Games::WARHAMMER] = false;
    update();
}

void Cart::showEvent(QShowEvent *event)
{
    update();
}


void Cart::on_PurchaseForMyself_clicked()
{
    auto sum = ui->TotalPrice->text();
    sum.removeLast();

    if(sum.toDouble() > currentAccount->balance)
    {
        mainWindow->showInformationalWindow("Failure", "There are not enough funds in your wallet");
        return;
    }

    for(int i = 0; i < 9; ++i)
    {
        if(currentAccount->cart.list[i] && currentAccount->library.bought[i])
        {
            mainWindow->showInformationalWindow("Failure", "Some games are already in your Library");
            return;
        }
    }

    currentAccount->balance -= sum.toDouble();
    mainWindow->updateUserBalance();

    if(currentAccount->cart.list[(int)Games::ELDEN_RING])
    {
        currentAccount->library.bought[(int)Games::ELDEN_RING] = true;
        currentAccount->cart.list[(int)Games::ELDEN_RING] = false;
        currentAccount->activity.addNewActivity(ActivitiesList::ELDEN_RING_BOUGHT);
    }

    if(currentAccount->cart.list[(int)Games::GOD_OF_WAR])
    {
        currentAccount->library.bought[(int)Games::GOD_OF_WAR] = true;
        currentAccount->cart.list[(int)Games::GOD_OF_WAR] = false;
        currentAccount->activity.addNewActivity(ActivitiesList::GOD_OF_WAR_BOUGHT);
    }

    if(currentAccount->cart.list[(int)Games::STRAY])
    {
        currentAccount->library.bought[(int)Games::STRAY] = true;
        currentAccount->cart.list[(int)Games::STRAY] = false;
        currentAccount->activity.addNewActivity(ActivitiesList::STRAY_BOUGHT);
    }

    if(currentAccount->cart.list[(int)Games::HORIZON])
    {
        currentAccount->library.bought[(int)Games::HORIZON] = true;
        currentAccount->cart.list[(int)Games::HORIZON] = false;
        currentAccount->activity.addNewActivity(ActivitiesList::HORIZON_BOUGHT);
    }

    if(currentAccount->cart.list[(int)Games::PLAGUE_TALE])
    {
        currentAccount->library.bought[(int)Games::PLAGUE_TALE] = true;
        currentAccount->cart.list[(int)Games::PLAGUE_TALE] = false;
        currentAccount->activity.addNewActivity(ActivitiesList::PLAGUE_TALE_BOUGHT);
    }

    if(currentAccount->cart.list[(int)Games::LAST_OF_US])
    {
        currentAccount->library.bought[(int)Games::LAST_OF_US] = true;
        currentAccount->cart.list[(int)Games::LAST_OF_US] = false;
        currentAccount->activity.addNewActivity(ActivitiesList::LAST_OF_US_BOUGHT);
    }

    if(currentAccount->cart.list[(int)Games::CUPHEAD])
    {
        currentAccount->library.bought[(int)Games::CUPHEAD] = true;
        currentAccount->cart.list[(int)Games::CUPHEAD] = false;
        currentAccount->activity.addNewActivity(ActivitiesList::CUPHEAD_BOUGHT);
    }

    if(currentAccount->cart.list[(int)Games::DYING_LIGHT])
    {
        currentAccount->library.bought[(int)Games::DYING_LIGHT] = true;
        currentAccount->cart.list[(int)Games::DYING_LIGHT] = false;
        currentAccount->activity.addNewActivity(ActivitiesList::DYING_LIGHT_BOUGHT);
    }

    if(currentAccount->cart.list[(int)Games::WARHAMMER])
    {
        currentAccount->library.bought[(int)Games::WARHAMMER] = true;
        currentAccount->cart.list[(int)Games::WARHAMMER] = false;
        currentAccount->activity.addNewActivity(ActivitiesList::WARHAMMER_BOUGHT);
    }

    update();
    mainWindow->updateUserLibrary();
    mainWindow->updateUserActivity();

    mainWindow->showInformationalWindow("Success", "Games have been successfully added\nto your Library");
}


void Cart::on_PurchaseAsAGift_clicked()
{
    auto sum = ui->TotalPrice->text();
    sum.removeLast();

    if(sum.toDouble() > currentAccount->balance)
    {
        mainWindow->showInformationalWindow("Failure", "There are not enough funds in your wallet");
        return;
    }

    QString value = "";

    if(currentAccount->cart.list[(int)Games::ELDEN_RING])
    {
        value.push_back(QString::number((int)Games::ELDEN_RING));
        currentAccount->cart.list[(int)Games::ELDEN_RING] = false;
    }

    if(currentAccount->cart.list[(int)Games::GOD_OF_WAR])
    {
        value.push_back(QString::number((int)Games::GOD_OF_WAR));
        currentAccount->cart.list[(int)Games::GOD_OF_WAR] = false;
    }

    if(currentAccount->cart.list[(int)Games::STRAY])
    {
        value.push_back(QString::number((int)Games::STRAY));
        currentAccount->cart.list[(int)Games::STRAY] = false;
    }

    if(currentAccount->cart.list[(int)Games::HORIZON])
    {
        value.push_back(QString::number((int)Games::HORIZON));
        currentAccount->cart.list[(int)Games::HORIZON] = false;
    }

    if(currentAccount->cart.list[(int)Games::PLAGUE_TALE])
    {
        value.push_back(QString::number((int)Games::PLAGUE_TALE));
        currentAccount->cart.list[(int)Games::PLAGUE_TALE] = false;
    }

    if(currentAccount->cart.list[(int)Games::LAST_OF_US])
    {
        value.push_back(QString::number((int)Games::LAST_OF_US));
        currentAccount->cart.list[(int)Games::LAST_OF_US] = false;
    }

    if(currentAccount->cart.list[(int)Games::CUPHEAD])
    {
        value.push_back(QString::number((int)Games::CUPHEAD));
        currentAccount->cart.list[(int)Games::CUPHEAD] = false;
    }

    if(currentAccount->cart.list[(int)Games::DYING_LIGHT])
    {
        value.push_back(QString::number((int)Games::DYING_LIGHT));
        currentAccount->cart.list[(int)Games::DYING_LIGHT] = false;
    }

    if(currentAccount->cart.list[(int)Games::WARHAMMER])
    {
        value.push_back(QString::number((int)Games::WARHAMMER));
        currentAccount->cart.list[(int)Games::WARHAMMER] = false;
    }

    QString code = mainWindow->createPromocode(PromocodeTypes::GAME, value);
    update();

    mainWindow->showPromocodeWindow(code);
}


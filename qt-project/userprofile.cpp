#include "userprofile.h"
#include "ui_userprofile.h"
#include <QPixmap>
#include <QFile>
#include <QImage>
#include "useraccount.h"
#include "functions.h"
#include "mainwindow.h"

UserProfile::UserProfile(MainWindow *_mainWindow, UserAccount* _currentAccount) :
    QWidget(nullptr), ui(new Ui::UserProfile), mainWindow(_mainWindow), currentAccount(_currentAccount)
{
    ui->setupUi(this);
    ui->LevelDisplay->setPixmap(QPixmap("ApplicationIcons/Level.png"));
    ui->RegBage->setPixmap(QPixmap("ApplicationIcons/RegistrationBage.png"));
    ui->MouseBage->setPixmap(QPixmap("ApplicationIcons/MouseBage.png"));
    ui->TenYearsBage->setPixmap(QPixmap("ApplicationIcons/TenYearsBage.png"));
    updateWidget();

}

UserProfile::~UserProfile()
{
    delete ui;
}

void UserProfile::updateWidget()
{
    setUserName();
    setUserStatus();
    setUserAvatar();
    setUserActivity();
}

void UserProfile::setUserName()
{
    if(currentAccount->userName.size() > 20)
    {
        QString login = "";
        for(int i = 0; i < 20; ++i)
        {
            login.push_back(currentAccount->userName[i]);
        }
        login += "...";

        ui->Login_label->setText(login);
    }
    else
    {
        ui->Login_label->setText(currentAccount->userName);
    }
}

//Доделать
void UserProfile::setUserStatus()
{
    QString status = transformByLength(currentAccount->status, ui->Infornation_label->size(), ui->Infornation_label->font());
    ui->Infornation_label->setText(status);
}

void UserProfile::setUserAvatar()
{
    QString fileName = "";
    fileName += "Avatars/Avatar_" + QString::number(currentAccount->id);
    fileName += ".png";

    QPixmap avatar(fileName);
    if(avatar.isNull())
    {
        ui->Avatar_label->setPixmap(QPixmap("Avatars/BasicAvatar.png"));
        return;
    }

    ui->Avatar_label->setPixmap(avatar);
}

void UserProfile::setUserActivity()
{
    auto first = currentAccount->activity.first;
    auto second = currentAccount->activity.second;
    auto third = currentAccount->activity.third;

    if(first != ActivitiesList::NONE)
    {
        if(first == ActivitiesList::REGISTRATION)
        {
            setRegActivity(ui->RA1_icon_label, ui->RA1_name_label, ui->RA1_info_label);
        }
        if(first == ActivitiesList::ELDEN_RING_BOUGHT)
        {
            setBuyingActivity(ui->RA1_icon_label, ui->RA1_name_label, ui->RA1_info_label, "EldenRing", Games::ELDEN_RING);
        }
        if(first == ActivitiesList::GOD_OF_WAR_BOUGHT)
        {
            setBuyingActivity(ui->RA1_icon_label, ui->RA1_name_label, ui->RA1_info_label, "GodOfWar", Games::GOD_OF_WAR);
        }
        if(first == ActivitiesList::STRAY_BOUGHT)
        {
            setBuyingActivity(ui->RA1_icon_label, ui->RA1_name_label, ui->RA1_info_label, "Stray", Games::STRAY);
        }
        if(first == ActivitiesList::PLAGUE_TALE_BOUGHT)
        {
            setBuyingActivity(ui->RA1_icon_label, ui->RA1_name_label, ui->RA1_info_label, "PlagueTale", Games::PLAGUE_TALE);
        }
        if(first == ActivitiesList::HORIZON_BOUGHT)
        {
            setBuyingActivity(ui->RA1_icon_label, ui->RA1_name_label, ui->RA1_info_label, "Horizon", Games::HORIZON);
        }
        if(first == ActivitiesList::LAST_OF_US_BOUGHT)
        {
            setBuyingActivity(ui->RA1_icon_label, ui->RA1_name_label, ui->RA1_info_label, "LastOfUs", Games::LAST_OF_US);
        }
        if(first == ActivitiesList::CUPHEAD_BOUGHT)
        {
            setBuyingActivity(ui->RA1_icon_label, ui->RA1_name_label, ui->RA1_info_label, "Cuphead", Games::CUPHEAD);
        }
        if(first == ActivitiesList::DYING_LIGHT_BOUGHT)
        {
            setBuyingActivity(ui->RA1_icon_label, ui->RA1_name_label, ui->RA1_info_label, "DyingLight", Games::DYING_LIGHT);
        }
        if(first == ActivitiesList::WARHAMMER_BOUGHT)
        {
            setBuyingActivity(ui->RA1_icon_label, ui->RA1_name_label, ui->RA1_info_label, "Warhammer", Games::WARHAMMER);
        }

        ui->RA1_groupBox->show();
    }
    else
    {
        ui->RA1_groupBox->hide();
    }


    if(second != ActivitiesList::NONE)
    {
        if(second == ActivitiesList::REGISTRATION)
        {
            setRegActivity(ui->RA2_icon_label, ui->RA2_name_label, ui->RA2_info_label);
        }
        if(second == ActivitiesList::ELDEN_RING_BOUGHT)
        {
            setBuyingActivity(ui->RA2_icon_label, ui->RA2_name_label, ui->RA2_info_label, "EldenRing", Games::ELDEN_RING);
        }
        if(second == ActivitiesList::GOD_OF_WAR_BOUGHT)
        {
            setBuyingActivity(ui->RA2_icon_label, ui->RA2_name_label, ui->RA2_info_label, "GodOfWar", Games::GOD_OF_WAR);
        }
        if(second == ActivitiesList::STRAY_BOUGHT)
        {
            setBuyingActivity(ui->RA2_icon_label, ui->RA2_name_label, ui->RA2_info_label, "Stray", Games::STRAY);
        }
        if(second == ActivitiesList::PLAGUE_TALE_BOUGHT)
        {
            setBuyingActivity(ui->RA2_icon_label, ui->RA2_name_label, ui->RA2_info_label, "PlagueTale", Games::PLAGUE_TALE);
        }
        if(second == ActivitiesList::HORIZON_BOUGHT)
        {
            setBuyingActivity(ui->RA2_icon_label, ui->RA2_name_label, ui->RA2_info_label, "Horizon", Games::HORIZON);
        }
        if(second == ActivitiesList::LAST_OF_US_BOUGHT)
        {
            setBuyingActivity(ui->RA2_icon_label, ui->RA2_name_label, ui->RA2_info_label, "LastOfUs", Games::LAST_OF_US);
        }
        if(second == ActivitiesList::CUPHEAD_BOUGHT)
        {
            setBuyingActivity(ui->RA2_icon_label, ui->RA2_name_label, ui->RA2_info_label, "Cuphead", Games::CUPHEAD);
        }
        if(second == ActivitiesList::DYING_LIGHT_BOUGHT)
        {
            setBuyingActivity(ui->RA2_icon_label, ui->RA2_name_label, ui->RA2_info_label, "DyingLight", Games::DYING_LIGHT);
        }
        if(second == ActivitiesList::WARHAMMER_BOUGHT)
        {
            setBuyingActivity(ui->RA2_icon_label, ui->RA2_name_label, ui->RA2_info_label, "Warhammer", Games::WARHAMMER);
        }

        ui->RA2_groupBox->show();
    }
    else
    {
        ui->RA2_groupBox->hide();
    }


    if(third != ActivitiesList::NONE)
    {
        if(third == ActivitiesList::REGISTRATION)
        {
            setRegActivity(ui->RA3_icon_label, ui->RA3_name_label, ui->RA3_info_label);
        }
        if(third == ActivitiesList::ELDEN_RING_BOUGHT)
        {
            setBuyingActivity(ui->RA3_icon_label, ui->RA3_name_label, ui->RA3_info_label, "EldenRing", Games::ELDEN_RING);
        }
        if(third == ActivitiesList::GOD_OF_WAR_BOUGHT)
        {
            setBuyingActivity(ui->RA3_icon_label, ui->RA3_name_label, ui->RA3_info_label, "GodOfWar", Games::GOD_OF_WAR);
        }
        if(third == ActivitiesList::STRAY_BOUGHT)
        {
            setBuyingActivity(ui->RA3_icon_label, ui->RA3_name_label, ui->RA3_info_label, "Stray", Games::STRAY);
        }
        if(third == ActivitiesList::PLAGUE_TALE_BOUGHT)
        {
            setBuyingActivity(ui->RA3_icon_label, ui->RA3_name_label, ui->RA3_info_label, "PlagueTale", Games::PLAGUE_TALE);
        }
        if(third == ActivitiesList::HORIZON_BOUGHT)
        {
            setBuyingActivity(ui->RA3_icon_label, ui->RA3_name_label, ui->RA3_info_label, "Horizon", Games::HORIZON);
        }
        if(third == ActivitiesList::LAST_OF_US_BOUGHT)
        {
            setBuyingActivity(ui->RA3_icon_label, ui->RA3_name_label, ui->RA3_info_label, "LastOfUs", Games::LAST_OF_US);
        }
        if(third == ActivitiesList::CUPHEAD_BOUGHT)
        {
            setBuyingActivity(ui->RA3_icon_label, ui->RA3_name_label, ui->RA3_info_label, "Cuphead", Games::CUPHEAD);
        }
        if(third == ActivitiesList::DYING_LIGHT_BOUGHT)
        {
            setBuyingActivity(ui->RA3_icon_label, ui->RA3_name_label, ui->RA3_info_label, "DyingLight", Games::DYING_LIGHT);
        }
        if(third == ActivitiesList::WARHAMMER_BOUGHT)
        {
            setBuyingActivity(ui->RA3_icon_label, ui->RA3_name_label, ui->RA3_info_label, "Warhammer", Games::WARHAMMER);
        }

        ui->RA3_groupBox->show();
    }
    else
    {
        ui->RA3_groupBox->hide();
    }

}

void UserProfile::setRegActivity(QLabel *_icon, QLabel *_name, QLabel *_info)
{
    _icon->setPixmap(QPixmap("ApplicationIcons/Registration.png"));
    _name->setText("Registration comleted.");
    _info->setText("You have been succesfully registered\nin our store.");
}

void UserProfile::setBuyingActivity(QLabel *_icon, QLabel *_name, QLabel *_info, const QString &_iconName, Games _game)
{
    QString imageName = "GameIcons/" + _iconName + ".png";
    QImage image(imageName);
    _icon->setPixmap(QPixmap::fromImage( image.scaled(_icon->size()) ));

    _name->setText("Buying a new game.");
    _info->setText("You bought game\n" + getFullGameName(_game));
}


void UserProfile::on_EditProfile_pushButton_clicked()
{
    mainWindow->showEditProfile();
}

void UserProfile::on_MyGames_pushButton_clicked()
{
    mainWindow->showLibrary();
}

void UserProfile::on_Inventory_pushButton_clicked()
{
    mainWindow->showCommunity();
    mainWindow->setCurrentMenu(nullptr);
}

void UserProfile::on_Screenshots_pushButton_clicked()
{
    mainWindow->showCommunity();
    mainWindow->setCurrentMenu(nullptr);
}

void UserProfile::on_Video_pushButton_clicked()
{
    mainWindow->showCommunity();
    mainWindow->setCurrentMenu(nullptr);
}

void UserProfile::on_Reviews_pushButton_clicked()
{
    mainWindow->showCommunity();
    mainWindow->setCurrentMenu(nullptr);
}

void UserProfile::on_Manuals_pushButton_clicked()
{
    mainWindow->showCommunity();
    mainWindow->setCurrentMenu(nullptr);
}

void UserProfile::on_Illustrations_pushButton_clicked()
{
    mainWindow->showCommunity();
    mainWindow->setCurrentMenu(nullptr);
}

void UserProfile::showEvent(QShowEvent *event)
{
    updateWidget();
}

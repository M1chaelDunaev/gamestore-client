#include "gifts.h"
#include "ui_gifts.h"
#include "mainwindow.h"
#include "promocodeslist.h"
#include "useraccount.h"


Gifts::Gifts(MainWindow *_mainWindow, UserAccount *_currentAccount, PromocodesList *_promocodesList) :
    QDialog(nullptr), ui(new Ui::Gifts), mainWindow(_mainWindow), currentAccount(_currentAccount),
    promocodesList(_promocodesList)
{
    setWindowFlag(Qt::FramelessWindowHint);
    ui->setupUi(this);
    ui->lineEdit->setStyleSheet(lineEditBase_styleSheet());
    ui->Close_button->setIcon(QPixmap("ApplicationIcons/CloseCross.png"));
}

Gifts::~Gifts()
{
    delete ui;
}

QString Gifts::lineEditBase_styleSheet()
{
    QString str = "";
    str += "background-color: rgb(13, 19, 27);"
           "color: rgb(255, 255, 255);"
           "font: 700 11pt Arial;"
           "border: none;";

    return str;
}

QString Gifts::lineEditError_styleSheet()
{
    return (lineEditBase_styleSheet() + "border: 1px solid rgb(220, 0, 0);");
}

void Gifts::on_Activate_clicked()
{
    ui->lineEdit->setStyleSheet(lineEditBase_styleSheet());
    ui->Info->setText("");

    QString code = ui->lineEdit->text();

    PromocodeTypes type;
    QString value;
    if(!promocodesList->find(code, type, value))
    {
        ui->lineEdit->setStyleSheet(lineEditError_styleSheet());
        ui->Info->setText("This promocode was not found");
        return;
    }

    if(type == PromocodeTypes::GAME)
    {
        for(auto elem : value)
        {
            if(currentAccount->library.bought[elem.digitValue()])
            {
                mainWindow->showInformationalWindow("Activation failure", "Some games are already in your Library");
                return;
            }
        }

        for(auto elem : value)
        {
            currentAccount->library.bought[elem.digitValue()] = true;
            currentAccount->activity.addNewActivity( (ActivitiesList)(QString(elem) + "0").toInt() );
        }
        mainWindow->updateUserLibrary();
        mainWindow->updateUserActivity();

        mainWindow->deletePromocode(code);
        mainWindow->showInformationalWindow("Successfully activation", "Games have been added\nto your Library");
        close();
    }
    else
    {
        double sum = value.toDouble();

        if(currentAccount->balance + sum > 10000.0)
        {
            mainWindow->showInformationalWindow("Activation failure", "You can not use this promocode\nSum in your wallet must be less than 10000$");
            return;
        }

        currentAccount->balance += sum;
        mainWindow->updateUserBalance();

        mainWindow->deletePromocode(code);
        mainWindow->showInformationalWindow("Successfully activation", "Your balance has been top upped\nby " +
                                                                           value + "$");
        close();
    }

}


void Gifts::on_Close_button_clicked()
{
    close();
}


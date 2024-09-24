#include "editprofile.h"
#include "ui_editprofile.h"

#include <QFileDialog>
#include <QImage>
#include "mainwindow.h"
#include "useraccount.h"
#include "functions.h"
#include "imagecropper.h"

EditProfile::EditProfile(MainWindow* _mainWindow, UserAccount* _currentAccount) :
    QWidget(nullptr), ui(new Ui::EditProfile), mainWindow(_mainWindow), currentAccount(_currentAccount)
{
    ui->setupUi(this);
    updateWindow();
}

EditProfile::~EditProfile()
{
    delete ui;
}

void EditProfile::setLineEdits()
{
    ui->ProfileName_lineEdit->setText(currentAccount->userName);
    ui->RealName_lineEdit->setText(currentAccount->realName);
    ui->Status_lineEdit->setText(currentAccount->status);
}

bool EditProfile::isCorrectProfileName(const QString &_profileName)
{
    for(QChar elem : _profileName)
    {
        if(!elem.isLetterOrNumber() && elem != '_' && elem != '-' && elem != '@' && elem != '.')
            return false;
    }

    return true;
}

bool EditProfile::isCorrectName(const QString &_name)
{
    QString firstName = "";
    QString secondName = "";
    char countOfSpaces = 0;

    for (QChar elem : _name)
    {
        if(elem.isSpace())
        {
            ++countOfSpaces;
            continue;
        }

        if(countOfSpaces == 0)
            firstName.push_back(elem);
        if(countOfSpaces == 1)
            secondName.push_back(elem);
    }

    if(countOfSpaces != 1)
        return false;

    return (checkCorrect_name(firstName) && checkCorrect_name(secondName));
}

void EditProfile::restoreLineEdits()
{
    ui->ProfileName_lineEdit->setStyleSheet(lineEdit_StyleSheet());
    ui->RealName_lineEdit->setStyleSheet(lineEdit_StyleSheet());
}

void EditProfile::updateWindow()
{
    restoreLineEdits();
    setLineEdits();
}

QString EditProfile::lineEdit_StyleSheet()
{
    QString styleSheet = "";
    styleSheet += "color: rgb(255, 255, 255);"
                  "background-color: rgb(39, 41, 47);"
                  "border: 0px;";


    return styleSheet;
}

QString EditProfile::lineEditError_StyleSheet()
{
    QString styleSheet = lineEdit_StyleSheet();
    styleSheet += "border-color: rgb(255, 0, 0);"
                  "border-style: solid;"
                  "border-width: 1px;";

    return styleSheet;
}

void EditProfile::on_UploadAvatar_pushButton_clicked()
{   
    auto fileName = QFileDialog::getOpenFileName(this, "Open Image", "/home", "Images (*.png *.jpg *.jpeg *.bmp)");
    if(fileName == "")
        return;

    ImageCropper* ic = new ImageCropper(mainWindow, fileName);
    ic->exec();
    delete ic;
}


void EditProfile::on_Save_pushButton_clicked()
{
    restoreLineEdits();
    ui->Error_label->setText("");

    QString profileName = ui->ProfileName_lineEdit->text();
    QString name = ui->RealName_lineEdit->text();
    QString status = ui->Status_lineEdit->text();

    if(!isCorrectProfileName(profileName))
    {
        ui->Error_label->setText("Incorrect profile name");
        ui->ProfileName_lineEdit->setStyleSheet(lineEditError_StyleSheet());
        return;
    }

    if(!isCorrectName(name))
    {
        ui->Error_label->setText("Incorrect real name");
        ui->RealName_lineEdit->setStyleSheet(lineEditError_StyleSheet());
        return;
    }

    if(status.size() > 256)
    {
        ui->Error_label->setText("Status is too long\nMax length is 160 characters");
        ui->Status_lineEdit->setStyleSheet(lineEditError_StyleSheet());
        return;
    }

    if(profileName != currentAccount->userName)
    {
        currentAccount->userName = ui->ProfileName_lineEdit->text();
        mainWindow->updateUserAccount("UserName", ui->ProfileName_lineEdit->text());
    }

    if(name != currentAccount->realName)
    {
        currentAccount->realName = name;
        mainWindow->updateUserAccount("RealName", name);
    }

    if(status != currentAccount->status)
    {
        currentAccount->status = status;
        mainWindow->updateUserAccount("Status", status);
    }

    mainWindow->showInformationalWindow("Success", "Profile has been successfully changed");
}

void EditProfile::on_Account_pushButton_clicked()
{
    mainWindow->showProfile();
}


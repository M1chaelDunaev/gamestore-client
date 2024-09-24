#include "restorepassword.h"
#include "ui_restorepassword.h"
#include "mainapplication.h"
#include "functions.h"
#include "support.h"
#include "phonenumberlineedit.h"
#include <QMouseEvent>

RestorePassword::RestorePassword(Support* _support) :
    QDialog(nullptr), ui(new Ui::RestorePassword), support(_support)
{
    ui->setupUi(this);
    setWindowFlag(Qt::FramelessWindowHint);
    code = "Code_not_defined";
    ui->Close_button->setIcon(QPixmap("ApplicationIcons/CloseCross.png"));
    screenInfo = QApplication::primaryScreen();

    phoneNumberForm = new PhoneNumberLineEdit(this);
    phoneNumberForm->setStyleSheet(MainApplication::lineEdit_StyleSheet());
    phoneNumberForm->setGeometry(110, 340, 561, 35);
    phoneNumberForm->show();

    connect(ui->Countries_comboBox, &QComboBox::currentTextChanged, this, &RestorePassword::setPhoneCode);
}

RestorePassword::~RestorePassword()
{
    delete ui;
}

void RestorePassword::restoreEnterWidgets()
{
    ui->Email_lineEdit->setStyleSheet(MainApplication::lineEdit_StyleSheet());
    phoneNumberForm->setStyleSheet(MainApplication::lineEdit_StyleSheet());
    ui->Countries_comboBox->setStyleSheet(MainApplication::lineEdit_StyleSheet());
    ui->PhoneCode_lineEdit->setStyleSheet(MainApplication::lineEdit_StyleSheet());
    ui->Code_lineEdit->setStyleSheet(MainApplication::lineEdit_StyleSheet());
    ui->NewPassword_lineEdit->setStyleSheet(MainApplication::lineEdit_StyleSheet());
}

void RestorePassword::on_GetCode_button_clicked()
{
    ui->CodeError->setText("");
    restoreEnterWidgets();

    QString email = ui->Email_lineEdit->text();
    QString phoneCode = ui->PhoneCode_lineEdit->text();

    if(!phoneCode.isEmpty() && !phoneCode.back().isSpace())
        phoneCode.push_back(' ');

    QString phoneNumber = phoneCode + getStandardNumber(phoneNumberForm->getStandardNumber());

    if(email.isEmpty())
    {        
        if(phoneNumber.isEmpty())
        {
            ui->CodeError->setText("Both fields are not filled");
            ui->Email_lineEdit->setStyleSheet(MainApplication::lineEditError_StyleSheet());
            phoneNumberForm->setStyleSheet(MainApplication::lineEditError_StyleSheet());
            ui->PhoneCode_lineEdit->setStyleSheet(MainApplication::lineEditError_StyleSheet());
            return;
        }

        if(ui->Countries_comboBox->currentText() == "None")
        {
            ui->CodeError->setText("You have not chosen your country");
            ui->Countries_comboBox->setStyleSheet(MainApplication::lineEditError_StyleSheet());
            return;
        }

        //find phone number
        id = support->getIdByPhoneNumber(phoneNumber);
        if(id != (-1))
        {
            code = generateCode();
            support->showStoreMessage(code, "To change the password");
            return;
        }
        else
        {
            ui->CodeError->setText("User with this phone number does not exist");
            phoneNumberForm->setStyleSheet(MainApplication::lineEditError_StyleSheet());
            ui->PhoneCode_lineEdit->setStyleSheet(MainApplication::lineEditError_StyleSheet());
            return;
        }
    }
    else
    {
        id = support->getIdByEmail(email);
        if(id != (-1))
        {
           code = generateCode();
           support->showStoreMessage(code, "To change the password");
        }
        else
        {
            ui->CodeError->setText("User with this email does not exist");
            ui->Email_lineEdit->setStyleSheet(MainApplication::lineEditError_StyleSheet());
            return;
        }
    }
}


void RestorePassword::on_ChangePassword_button_clicked()
{
    restoreEnterWidgets();
    ui->Error_window_label->setText("");

    QString EnteredCode = ui->Code_lineEdit->text();
    QString newPassword = ui->NewPassword_lineEdit->text();

    if(EnteredCode != code)
    {
        ui->Error_window_label->setText("Wrong code");
        ui->Code_lineEdit->setStyleSheet(MainApplication::lineEditError_StyleSheet());
        return;
    }

    if(newPassword.isEmpty())
    {
        ui->Error_window_label->setText("Field 'New password' is not filled");
        ui->NewPassword_lineEdit->setStyleSheet(MainApplication::lineEditError_StyleSheet());
        return;
    }

    if(!checkCorrect_password(newPassword))
    {
        ui->Error_window_label->setText("Incorrect password\nIt must be longer than 8 and contains letters and digits");
        ui->NewPassword_lineEdit->setStyleSheet(MainApplication::lineEditError_StyleSheet());
        return;
    }

    support->setNewPassword(id, newPassword);
    close();
}


void RestorePassword::on_Close_button_clicked()
{
    close();
}

void RestorePassword::setPhoneCode(const QString &_text)
{
    ui->PhoneCode_lineEdit->setText(getPhoneCode(_text) + " ");
}




void RestorePassword::mousePressEvent(QMouseEvent *event)
{
    lastPressedMouseButton = event->button();

    if(lastPressedMouseButton == Qt::LeftButton)
    {
        prevMousePos = event->globalPosition();
    }

    QDialog::mousePressEvent(event);
}

void RestorePassword::mouseMoveEvent(QMouseEvent *event)
{
    if(lastPressedMouseButton != Qt::LeftButton)
        return;

    QPointF delta = event->globalPosition() - prevMousePos;

    if(event->globalPosition().x() <= 0 || event->globalPosition().y() <= 0)
        return;

    if(event->globalPosition().y() >= screenInfo->size().height() - 40 ||
        event->globalPosition().x() >= screenInfo->size().width())
        return;

    move(this->pos() + delta.toPoint());
    prevMousePos = event->globalPosition();

    QDialog::mousePressEvent(event);
}


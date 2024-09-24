#include "restorephonenumber.h"
#include "ui_restorephonenumber.h"
#include "support.h"
#include "mainapplication.h"
#include "functions.h"
#include "useraccount.h"
#include <QMouseEvent>

RestorePhoneNumber::RestorePhoneNumber(Support* _support) :
    QDialog(nullptr), ui(new Ui::RestorePhoneNumber), support(_support)
{
    ui->setupUi(this);
    setWindowFlag(Qt::FramelessWindowHint);
    code = "Code_not_defined";
    ui->Close_button->setIcon(QPixmap("ApplicationIcons/CloseCross.png"));
    screenInfo = QApplication::primaryScreen();
}

RestorePhoneNumber::~RestorePhoneNumber()
{
    delete ui;
}

void RestorePhoneNumber::restoreEnterWidgets()
{
    ui->Email_lineEdit->setStyleSheet(MainApplication::lineEdit_StyleSheet());
    ui->Code_lineEdit->setStyleSheet(MainApplication::lineEdit_StyleSheet());
    ui->SecretQuestion_comboBox->setStyleSheet(MainApplication::lineEdit_StyleSheet());
    ui->Answer_lineEdit->setStyleSheet(MainApplication::lineEdit_StyleSheet());
    ui->PhoneNumber_lineEdit->setStyleSheet(MainApplication::lineEdit_StyleSheet());
    ui->PhoneCode_label->setStyleSheet(MainApplication::lineEdit_StyleSheet());
}

void RestorePhoneNumber::on_GetCode_button_clicked()
{
    restoreEnterWidgets();
    ui->CodeError->setText("");

    QString email = ui->Email_lineEdit->text();
    id = support->getIdByEmail(email);

    if(id != (-1))
    {
        code = generateCode();
        support->showStoreMessage(code, "To change the phone number");

        support->getCountryAndSQ(id, sqType, sqAnswer, country);
        ui->PhoneCode_label->setText(getPhoneCode(country));
        return;
    }
    else
    {
        ui->CodeError->setText("User with this email does not exist");
        ui->Email_lineEdit->setStyleSheet(MainApplication::lineEditError_StyleSheet());
    }
}


void RestorePhoneNumber::on_ChangePhoneNumber_button_clicked()
{
    restoreEnterWidgets();
    ui->Error_window_label->setText("");

    QString enteredCode = ui->Code_lineEdit->text();
    SecretQuestionTypes enteredSQType = getQuestionType(ui->SecretQuestion_comboBox->currentText());
    QString enteredSQAnswer = ui->Answer_lineEdit->text();
    QString enteredPhoneNumber = ui->PhoneNumber_lineEdit->text();

    if(enteredCode != code)
    {
        ui->Error_window_label->setText("Wrong code");
        ui->Code_lineEdit->setStyleSheet(MainApplication::lineEditError_StyleSheet());
        return;
    }

    if(enteredSQType != sqType)
    {
        ui->Error_window_label->setText("Wrong secret question");
        ui->SecretQuestion_comboBox->setStyleSheet(MainApplication::lineEditError_StyleSheet());
        return;
    }

    if(enteredSQAnswer != sqAnswer)
    {
        ui->Error_window_label->setText("Wrong answer");
        ui->Answer_lineEdit->setStyleSheet(MainApplication::lineEditError_StyleSheet());
        return;
    }

    if(enteredPhoneNumber.isEmpty())
    {
        ui->Error_window_label->setText("Field 'New phone number' is not filled");
        ui->PhoneNumber_lineEdit->setStyleSheet(MainApplication::lineEditError_StyleSheet());
        return;
    }

    if(!checkCorrect_phoneNumber(enteredPhoneNumber))
    {
        ui->Error_window_label->setText("Incorrect phone number");
        ui->PhoneNumber_lineEdit->setStyleSheet(MainApplication::lineEditError_StyleSheet());
        return;
    }

    QString newPhoneNumber = ui->PhoneCode_label->text() + " " + getStandardNumber(enteredPhoneNumber);
    support->setNewPhoneNumber(id, newPhoneNumber);

    close();
}


void RestorePhoneNumber::on_Close_button_clicked()
{
    close();
}

void RestorePhoneNumber::mousePressEvent(QMouseEvent *event)
{
    lastPressedMouseButton = event->button();

    if(lastPressedMouseButton == Qt::LeftButton)
    {
        prevMousePos = event->globalPosition();
    }

    QDialog::mousePressEvent(event);
}

void RestorePhoneNumber::mouseMoveEvent(QMouseEvent *event)
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


#include "restoreemail.h"
#include "ui_restoreemail.h"
#include "support.h"
#include "functions.h"
#include "mainapplication.h"
#include <QMouseEvent>
#include "phonenumberlineedit.h"

RestoreEmail::RestoreEmail(Support* _support) :
    QDialog(nullptr), ui(new Ui::RestoreEmail), support(_support)
{
    ui->setupUi(this);
    setWindowFlag(Qt::FramelessWindowHint);
    code = "Code_not_defined";
    ui->Close_button->setIcon(QPixmap("ApplicationIcons/CloseCross.png"));
    screenInfo = QApplication::primaryScreen();

    phoneNumberForm = new PhoneNumberLineEdit(this);
    phoneNumberForm->setStyleSheet(MainApplication::lineEdit_StyleSheet());
    phoneNumberForm->setGeometry(110, 270, 560, 35);
    phoneNumberForm->show();

    connect(ui->Countries_comboBox, &QComboBox::currentTextChanged, this, &RestoreEmail::setPhoneCode);
}

RestoreEmail::~RestoreEmail()
{
    delete ui;
}

void RestoreEmail::restoreEnterWidgets()
{
    phoneNumberForm->setStyleSheet(MainApplication::lineEdit_StyleSheet());
    ui->PhoneCode_lineEdit->setStyleSheet(MainApplication::lineEdit_StyleSheet());
    ui->Code_lineEdit->setStyleSheet(MainApplication::lineEdit_StyleSheet());
    ui->NewEmail_lineEdit->setStyleSheet(MainApplication::lineEdit_StyleSheet());
}

void RestoreEmail::on_GetCode_button_clicked()
{
    restoreEnterWidgets();
    ui->CodeError->setText("");
    QString phoneCode = ui->PhoneCode_lineEdit->text();

    if(!phoneCode.isEmpty() && !phoneCode.back().isSpace())
        phoneCode.push_back(' ');

    QString phoneNumber = phoneCode + getStandardNumber(phoneNumberForm->getStandardNumber());

    if(phoneNumber.isEmpty())
    {
        phoneNumberForm->setStyleSheet(MainApplication::lineEditError_StyleSheet());
        ui->PhoneCode_lineEdit->setStyleSheet(MainApplication::lineEditError_StyleSheet());
        ui->CodeError->setText("Field 'Phone number' is not filled");
        return;
    }

    id = support->getIdByPhoneNumber(phoneNumber);

    if(id != (-1))
    {
        code = generateCode();
        support->showStoreMessage(code, "To change the email");
        return;
    }
    else
    {
        ui->CodeError->setText("User with this phone number does not exist");
        phoneNumberForm->setStyleSheet(MainApplication::lineEditError_StyleSheet());
        ui->PhoneCode_lineEdit->setStyleSheet(MainApplication::lineEditError_StyleSheet());
    }
}


void RestoreEmail::on_ChangeEmail_button_clicked()
{
    restoreEnterWidgets();
    ui->Error_window_label->setText("");

    QString enteredCode = ui->Code_lineEdit->text();
    QString newEmail = ui->NewEmail_lineEdit->text();

    if(enteredCode != code)
    {
        ui->Error_window_label->setText("Wrong code");
        ui->Code_lineEdit->setStyleSheet(MainApplication::lineEditError_StyleSheet());
        return;
    }

    if(newEmail.isEmpty())
    {
        ui->Error_window_label->setText("Field New Email is not filled");
        ui->NewEmail_lineEdit->setStyleSheet(MainApplication::lineEditError_StyleSheet());
        return;
    }

    if(!checkCorrect_email(newEmail))
    {
        ui->Error_window_label->setText("Incorrect email");
        ui->NewEmail_lineEdit->setStyleSheet(MainApplication::lineEditError_StyleSheet());
        return;
    }

    support->setNewEmail(id, newEmail);
    close();
}


void RestoreEmail::on_Close_button_clicked()
{
    close();
}

void RestoreEmail::setPhoneCode(const QString &_text)
{
    ui->PhoneCode_lineEdit->setText(getPhoneCode(_text) + " ");
}

void RestoreEmail::mousePressEvent(QMouseEvent *event)
{
    lastPressedMouseButton = event->button();

    if(lastPressedMouseButton == Qt::LeftButton)
    {
        prevMousePos = event->globalPosition();
    }

    QDialog::mousePressEvent(event);
}

void RestoreEmail::mouseMoveEvent(QMouseEvent *event)
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


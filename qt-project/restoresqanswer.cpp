#include "restoresqanswer.h"
#include "ui_restoresqanswer.h"
#include "mainapplication.h"
#include "functions.h"
#include "useraccount.h"
#include "support.h"
#include <QMouseEvent>
#include "phonenumberlineedit.h"

RestoreSQAnswer::RestoreSQAnswer(Support* _support) :
    QDialog(nullptr), ui(new Ui::RestoreSQAnswer), support(_support)
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

    connect(ui->Countries_comboBox, &QComboBox::currentTextChanged, this, &RestoreSQAnswer::setPhoneCode);
}

RestoreSQAnswer::~RestoreSQAnswer()
{
    delete ui;
    delete phoneNumberForm;
}

void RestoreSQAnswer::restoreEnterWidgets()
{
    phoneNumberForm->setStyleSheet(MainApplication::lineEdit_StyleSheet());
    ui->PhoneCode_lineEdit->setStyleSheet(MainApplication::lineEdit_StyleSheet());
    ui->Code_lineEdit->setStyleSheet(MainApplication::lineEdit_StyleSheet());
    ui->SecretQuestion_comboBox->setStyleSheet(MainApplication::lineEdit_StyleSheet());
    ui->Answer_lineEdit->setStyleSheet(MainApplication::lineEdit_StyleSheet());
}


void RestoreSQAnswer::on_GetCode_button_clicked()
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
        support->showStoreMessage(code, "To change the secret question");
        return;
    }
    else
    {
        ui->CodeError->setText("User with this phone number does not exist");
        phoneNumberForm->setStyleSheet(MainApplication::lineEditError_StyleSheet());
        ui->PhoneCode_lineEdit->setStyleSheet(MainApplication::lineEditError_StyleSheet());
    }
}

void RestoreSQAnswer::on_ChangeSQ_button_clicked()
{
    restoreEnterWidgets();
    ui->Error_window_label->setText("");

    QString enteredCode = ui->Code_lineEdit->text();
    SecretQuestionTypes sqType = getQuestionType(ui->SecretQuestion_comboBox->currentText());
    QString sqAnswer = ui->Answer_lineEdit->text();

    if(enteredCode != code)
    {
        ui->Error_window_label->setText("Wrong code");
        ui->Code_lineEdit->setStyleSheet(MainApplication::lineEditError_StyleSheet());
        return;
    }

    if(sqType == SecretQuestionTypes::NONE)
    {
        ui->Error_window_label->setText("You have not chosen the secret question");
        ui->SecretQuestion_comboBox->setStyleSheet(MainApplication::lineEditError_StyleSheet());
        return;
    }

    if(sqAnswer.isEmpty())
    {
        ui->Error_window_label->setText("Field 'Answer' is not filled");
        ui->Answer_lineEdit->setStyleSheet(MainApplication::lineEditError_StyleSheet());
        return;
    }

    support->setNewSecretQuestion(id, sqType, sqAnswer);
    close();
}


void RestoreSQAnswer::on_Close_button_clicked()
{
    close();
}

void RestoreSQAnswer::setPhoneCode(const QString &_text)
{
    ui->PhoneCode_lineEdit->setText(getPhoneCode(_text) + " ");
}

void RestoreSQAnswer::mousePressEvent(QMouseEvent *event)
{
    lastPressedMouseButton = event->button();

    if(lastPressedMouseButton == Qt::LeftButton)
    {
        prevMousePos = event->globalPosition();
    }

    QDialog::mousePressEvent(event);
}

void RestoreSQAnswer::mouseMoveEvent(QMouseEvent *event)
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


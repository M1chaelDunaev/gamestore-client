#include "registrationwindowfinal.h"
#include "ui_registrationwindowfinal.h"
#include "useraccount.h"
#include "mainapplication.h"
#include "functions.h"
#include "phonenumberlineedit.h"
#include <QMouseEvent>

RegistrationWindowFinal::RegistrationWindowFinal(MainApplication* _app, UserAccount* _buffer) :
    QWidget(nullptr), ui(new Ui::RegistrationWindowFinal), mainApp(_app), buffer(_buffer)
{
    ui->setupUi(this);
    setWindowFlag(Qt::FramelessWindowHint);
    setWindowIcon(QPixmap("ApplicationIcons/Logotype.png"));
    setWindowTitle("Registration");
    screenInfo = QApplication::primaryScreen();

    ui->Close_button->setIcon(QIcon("ApplicationIcons/CloseCross.png"));
    phoneNumberForm = new PhoneNumberLineEdit(this);
    phoneNumberForm->setStyleSheet(mainApp->lineEdit_StyleSheet());
    phoneNumberForm->setGeometry(110, 325, 560, 35);
    phoneNumberForm->show();
}

RegistrationWindowFinal::~RegistrationWindowFinal()
{
    delete ui;
    delete phoneNumberForm;
}

void RegistrationWindowFinal::restoreEnterWidgets()
{
    ui->FirstName_lineEdit->setStyleSheet(mainApp->lineEdit_StyleSheet());
    ui->SecondName_lineEdit->setStyleSheet(mainApp->lineEdit_StyleSheet());
    phoneNumberForm->setStyleSheet(mainApp->lineEdit_StyleSheet());
    ui->dateEdit->setStyleSheet(mainApp->lineEdit_StyleSheet() + "border: 0px;");
    ui->SecretQuestion_comboBox->setStyleSheet(mainApp->lineEdit_StyleSheet() + "border: 0px;");
    ui->Answer_lineEdit->setStyleSheet(mainApp->lineEdit_StyleSheet());
}

void RegistrationWindowFinal::restoreWindow()
{
    restoreEnterWidgets();
    ui->FirstName_lineEdit->clear();
    ui->SecondName_lineEdit->clear();
    phoneNumberForm->clear();
    ui->dateEdit->setDate(QDate(2000, 01, 01));
    ui->SecretQuestion_comboBox->setCurrentIndex(0);
    ui->Answer_lineEdit->clear();
}

void RegistrationWindowFinal::on_GoBack_button_clicked()
{
    hide();
    mainApp->showRegistrationWindow();
}

void RegistrationWindowFinal::setPhoneCode()
{
    QString country = buffer->country;
    ui->PhoneCode_label->setText(getPhoneCode(country) + " ");
}

void RegistrationWindowFinal::on_CompleteRegistration_button_clicked()
{
    restoreEnterWidgets();

    QString firstName = ui->FirstName_lineEdit->text();
    QString secondName = ui->SecondName_lineEdit->text();
    QString phoneNumber = phoneNumberForm->getStandardNumber();
    QString birthDate = ui->dateEdit->text();
    QString question = ui->SecretQuestion_comboBox->currentText();
    QString answer = ui->Answer_lineEdit->text();

    if(firstName.isEmpty())
    {
        ui->Error_window_label->setText("Field 'First Name' is not filled");
        ui->FirstName_lineEdit->setStyleSheet(mainApp->lineEditError_StyleSheet());
        return;
    }

    if(secondName.isEmpty())
    {
        ui->Error_window_label->setText("Field 'Second Name' is not filled");
        ui->SecondName_lineEdit->setStyleSheet(mainApp->lineEditError_StyleSheet());
        return;
    }

    if(!phoneNumberForm->isValid())
    {
        ui->Error_window_label->setText("Field 'Phone number' is not filled");
        phoneNumberForm->setStyleSheet(mainApp->lineEditError_StyleSheet());
        return;
    }

    if(birthDate.isEmpty())
    {
        ui->Error_window_label->setText("Field 'Date of Birth' is not filled");
        ui->dateEdit->setStyleSheet(mainApp->lineEditError_StyleSheet());
        return;
    }

    if(answer.isEmpty())
    {
        ui->Error_window_label->setText("Field 'Answer' is not filled");
        ui->Answer_lineEdit->setStyleSheet(mainApp->lineEditError_StyleSheet());
        return;
    }

    if(question == "None")
    {
        ui->Error_window_label->setText("You have not chosen the secret question");
        ui->SecretQuestion_comboBox->setStyleSheet(mainApp->lineEditError_StyleSheet());
        return;
    }

    if(!checkCorrect_name(firstName))
    {
        ui->Error_window_label->setText("Incorect First Name\nThis field can contain only letters");
        ui->FirstName_lineEdit->setStyleSheet(mainApp->lineEditError_StyleSheet());
        return;
    }

    if(!checkCorrect_name(secondName))
    {
        ui->Error_window_label->setText("Incorect Second Name\nThis field can contain only letters");
        ui->SecondName_lineEdit->setStyleSheet(mainApp->lineEditError_StyleSheet());
        return;
    }

    if(!checkCorrect_phoneNumber(phoneNumber))
    {
        ui->Error_window_label->setText("Incorect phone number\nThis field can contain digits, spaces and symbols '-'");
        phoneNumberForm->setStyleSheet(mainApp->lineEditError_StyleSheet());
        return;
    }

    if(!checkCorrect_date(birthDate))
    {
        ui->Error_window_label->setText("Incorrect date of Birth\nYou must be older than 13");
        ui->dateEdit->setStyleSheet(mainApp->lineEditError_StyleSheet());
        return;
    }

    QString standardNumber = (ui->PhoneCode_label->text() + phoneNumber);
    SecretQuestionTypes sqType = getQuestionType(question);\

    if(mainApp->getIdByPhoneNumber(standardNumber) != (-1))
    {
        ui->Error_window_label->setText("User with same phone number is already exists");
        phoneNumberForm->setStyleSheet(mainApp->lineEditError_StyleSheet());
        return;
    }

    buffer->realName = firstName + " " + secondName;
    buffer->phoneNumber = standardNumber;
    buffer->birthDate = birthDate;
    buffer->sq_type = sqType;
    buffer->sq_answer = answer;
    buffer->balance = 0.0;

    mainApp->addAccount();

    hide();
    mainApp->showLoginWindow();
}

void RegistrationWindowFinal::mousePressEvent(QMouseEvent *event)
{
    lastPressedMouseButton = event->button();

    if(lastPressedMouseButton == Qt::LeftButton)
    {
        prevMousePos = event->globalPosition();
    }

    QWidget::mousePressEvent(event);
}

void RegistrationWindowFinal::mouseMoveEvent(QMouseEvent *event)
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

    QWidget::mousePressEvent(event);
}

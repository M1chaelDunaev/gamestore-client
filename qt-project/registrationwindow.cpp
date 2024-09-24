#include "registrationwindow.h"
#include "ui_registrationwindow.h"
#include "mainapplication.h"
#include "useraccount.h"
#include "functions.h"
#include <QMouseEvent>

RegistrationWindow::RegistrationWindow(MainApplication* _app, UserAccount* _buffer) :
    QWidget(nullptr), ui(new Ui::RegistrationWindow), mainApp(_app), buffer(_buffer), agreement(false)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    setWindowIcon(QPixmap("ApplicationIcons/Logotype.png"));
    setWindowTitle("Registration");
    screenInfo = QApplication::primaryScreen();

    ui->Close_button->setIcon(QIcon("ApplicationIcons/CloseCross.png"));
    ui->Agree_button->setIcon(QIcon("ApplicationIcons/without_gal.png"));
}

RegistrationWindow::~RegistrationWindow()
{
    delete ui;
}

void RegistrationWindow::restoreEnterWidgets()
{
    ui->Email_lineEdit->setStyleSheet(mainApp->lineEdit_StyleSheet());
    ui->Password_lineEdit->setStyleSheet(mainApp->lineEdit_StyleSheet());
    ui->Countries_comboBox->setStyleSheet(mainApp->lineEdit_StyleSheet() + "border: 0px;");
}

void RegistrationWindow::restoreWindow()
{
    restoreEnterWidgets();
    ui->Email_lineEdit->clear();
    ui->Password_lineEdit->clear();
    ui->Countries_comboBox->setCurrentIndex(0);
    agreement = true;
    on_Agree_button_clicked();
}

void RegistrationWindow::on_Agree_button_clicked()
{
    if(!agreement)
        ui->Agree_button->setIcon(QIcon("ApplicationIcons/gal.png"));
    else
        ui->Agree_button->setIcon(QIcon("ApplicationIcons/without_gal.png"));

    agreement = !agreement;
}

void RegistrationWindow::on_Registration_button_clicked()
{
    restoreEnterWidgets();

    QString email = ui->Email_lineEdit->text();
    QString password = ui->Password_lineEdit->text();

    if(email.isEmpty())
    {
        ui->Error_window_label->setText("Field 'Email' is not filled");
        ui->Email_lineEdit->setStyleSheet(mainApp->lineEditError_StyleSheet());
        return;
    }

    if(password.isEmpty())
    {
        ui->Error_window_label->setText("Field 'Password' is not filled");
        ui->Password_lineEdit->setStyleSheet(mainApp->lineEditError_StyleSheet());
        return;
    }

    if(ui->Countries_comboBox->currentText() == "None")
    {
        ui->Error_window_label->setText("You have not chosen your country");
        ui->Countries_comboBox->setStyleSheet(mainApp->lineEditError_StyleSheet());
        return;
    }

    if(!agreement)
    {
        ui->Error_window_label->setText("You have not confirmed your agreement");
        return;
    }

    if(!checkCorrect_email(email))
    {
        ui->Error_window_label->setText("Incorrect email");
        ui->Email_lineEdit->setStyleSheet(mainApp->lineEditError_StyleSheet());
        return;
    }

    if(!checkCorrect_password(password))
    {
        ui->Error_window_label->setText("Incorrect password\nIt must be longer than 8 and contains letters and digits");
        ui->Password_lineEdit->setStyleSheet(mainApp->lineEditError_StyleSheet());
        return;
    }

    if(mainApp->getIdByEmail(email) != (-1))
    {
        ui->Error_window_label->setText("User with the same email is already exists");
        ui->Email_lineEdit->setStyleSheet(mainApp->lineEditError_StyleSheet());
        return;
    }

    buffer->email = email;
    buffer->password = password;
    buffer->country = ui->Countries_comboBox->currentText();

    hide();
    mainApp->showFinalRegistrationWindow();
}


void RegistrationWindow::on_GoBack_button_clicked()
{
    hide();
    mainApp->showLoginWindow();
}

void RegistrationWindow::mousePressEvent(QMouseEvent *event)
{
    lastPressedMouseButton = event->button();

    if(lastPressedMouseButton == Qt::LeftButton)
    {
        prevMousePos = event->globalPosition();
    }

    QWidget::mousePressEvent(event);
}

void RegistrationWindow::mouseMoveEvent(QMouseEvent *event)
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


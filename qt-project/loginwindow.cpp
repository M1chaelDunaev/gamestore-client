#include "loginwindow.h"
#include "ui_loginwindow.h"
#include "mainapplication.h"
#include <QMouseEvent>

LoginWindow::LoginWindow(MainApplication *app) :
    QWidget(nullptr), ui(new Ui::LoginWindow), mainApp(app), rememberMe(false)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    setWindowIcon(QPixmap("ApplicationIcons/Logotype.png"));
    setWindowTitle("Authorization");
    screenInfo = QApplication::primaryScreen();
    restoreLineEdits();

    ui->Logo_label->setPixmap(QPixmap("ApplicationIcons/Logotype.png"));
    ui->Close_button->setIcon(QIcon("ApplicationIcons/CloseCross.png"));
    ui->Remember_me_button->setIcon(QIcon("ApplicationIcons/without_gal.png"));
    ui->Qrcode_label->setPixmap(QPixmap("ApplicationIcons/qr.png"));
}

LoginWindow::~LoginWindow()
{
    delete ui;
}

void LoginWindow::on_Remember_me_button_clicked()
{
    if(!rememberMe)
        ui->Remember_me_button->setIcon(QIcon("ApplicationIcons/gal.png"));
    else
        ui->Remember_me_button->setIcon(QIcon("ApplicationIcons/without_gal.png"));

    rememberMe = !rememberMe;
}

void LoginWindow::on_Sign_in_button_clicked()
{
    restoreLineEdits();

    QString email, password;
    email = ui->Email_lineEdit->text();
    password = ui->Password_lineEdit->text();

    if(email.isEmpty())
    {
        ui->Error_window_label->setText("Field 'Email' is not filled");
        ui->Email_lineEdit->setStyleSheet(mainApp->lineEditError_StyleSheet());
        ui->Password_lineEdit->clear();
        return;
    }

    if(password.isEmpty())
    {
        ui->Error_window_label->setText("Field 'Password' is not filled");
        ui->Password_lineEdit->setStyleSheet(mainApp->lineEditError_StyleSheet() + "font: 12px;");
        return;
    }

    int id = -1;
    auto res = mainApp->findAccount(id, email, password);

    switch (res)
    {
    case SearchResult::EMAIL_NOT_FOUND:
    {
        ui->Error_window_label->setText("Account not found");
        ui->Email_lineEdit->setStyleSheet(mainApp->lineEditError_StyleSheet());
        ui->Password_lineEdit->clear();
        return;
    }
    case SearchResult::EMAIL_FOUND_WRONG_PASSWORD:
    {
        ui->Error_window_label->setText("Wrong password");
        ui->Password_lineEdit->setStyleSheet(mainApp->lineEditError_StyleSheet() + "font: 12px;");
        ui->Password_lineEdit->clear();
        return;
    }
    case SearchResult::EMAIL_FOUND_RIGHT_PASSWORD:
    {
        ui->Error_window_label->setText("Success!");
        ui->Password_lineEdit->clear();
        restoreLineEdits();

        if(rememberMe)
            mainApp->setRemembrance(id);

        hide();
        mainApp->setMainWindow(id);
        return;
    }
    };
}

void LoginWindow::restoreLineEdits()
{
    ui->Email_lineEdit->setStyleSheet(mainApp->lineEdit_StyleSheet());
    ui->Password_lineEdit->setStyleSheet(mainApp->lineEdit_StyleSheet() + "font: 12px;");
}

void LoginWindow::on_Registration_button_clicked()
{
    hide();
    mainApp->showRegistrationWindow();
}


void LoginWindow::on_Recover_button_clicked()
{
    mainApp->showSupportWindow();
}

void LoginWindow::mousePressEvent(QMouseEvent *event)
{
    lastPressedMouseButton = event->button();

    if(lastPressedMouseButton == Qt::LeftButton)
    {
        prevMousePos = event->globalPosition();
    }

    QWidget::mousePressEvent(event);
}

void LoginWindow::mouseMoveEvent(QMouseEvent *event)
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


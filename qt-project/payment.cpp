#include "payment.h"
#include "ui_payment.h"
#include "useraccount.h"
#include "mainwindow.h"
#include "promocodeslist.h"
#include "functions.h"
#include <QMessageBox>
#include <QMouseEvent>
#include <chrono>
#include <random>
#include <thread>


Payment::Payment(MainWindow* _mainWindow, UserAccount* _currentAccount, PurchaseTypes _purchaseType) :
    QDialog(nullptr), ui(new Ui::Payment),
    mainWindow(_mainWindow), currentAccount(_currentAccount), purchaseType(_purchaseType)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint);
    screenInfo = QApplication::primaryScreen();
    ui->Close_button->setIcon(QPixmap("ApplicationIcons/CloseCross.png"));
    calcMax();
    ui->MakePayment->setDefault(true);

    code = "Code_not_generated";
}

Payment::~Payment()
{
    delete ui;
}

void Payment::on_Close_button_clicked()
{
    close();
}

void Payment::calcMax()
{
    if(purchaseType == PurchaseTypes::FOR_PROMOCODE)
    {
        ui->Max_label->setText("10000$");
        return;
    }

    double max = 10000.00 - currentAccount->balance;

    QString res = roundTheDouble(max);
    res.push_back('$');

    ui->Max_label->setText(res);
}

bool Payment::isOnlyDigits(const QString& _str)
{
    for(QChar elem : _str)
    {
        if(!elem.isDigit())
            return false;
    }
    return true;
}

bool Payment::isCorrectName(const QString &_str)
{
    if(_str.size() < 2)
        return false;

    for(QChar elem : _str)
    {
        if(!elem.isLetter() && !elem.isSpace())
            return false;
    }

    return true;
}

bool Payment::isCorrecDate(const QString &_month, const QString &_year)
{
    if(!isOnlyDigits(_month))
        return false;

    if(_month.toInt() > 12 || _month.toInt() < 1)
        return false;

    if(!isOnlyDigits(_year))
        return false;

    if(_year.toInt() > 2038 || _year.toInt() < 2023)
        return false;

    return true;
}

void Payment::on_GetSmsCode_clicked()
{
    ui->Error_label_1->setText("");
    ui->Error_label_2->setText("");
    auto number = (ui->CN1->text() + ui->CN2->text() + ui->CN3->text() + ui->CN4->text());

    bool correctCardNumber = (number.size() == 16 && isOnlyDigits(number));
    bool correctDate = isCorrecDate(ui->DateM->text(), ui->DateY->text());
    bool correctName = isCorrectName(ui->Owner->text());
    bool correctCVC = (ui->CVC->text().size() == 3 && isOnlyDigits(ui->CVC->text()));

    if(!correctCardNumber)
    {
        ui->Error_label_1->setText("Incorrect card number");
        return;
    }

    if(!correctDate)
    {
        ui->Error_label_1->setText("Incorrect date");
        return;
    }

    if(!correctName)
    {
        ui->Error_label_1->setText("Incorrect owner name");
        return;
    }

    if(!correctCVC)
    {
        ui->Error_label_1->setText("Incorrect CVC code");
        return;
    }

    QString sum = ui->Sum->text();

    if(purchaseType == PurchaseTypes::FOR_MYSELF)
    {
        auto max = ui->Max_label->text();
        max.removeLast();

        if(sum.size() < 1 || !isOnlyDigits(sum) || sum.toDouble() > max.toDouble() || sum.toDouble() < 1.0)
        {
            ui->Error_label_1->setText("Incorrect sum. \nIt must be an integral and be less than " + max);
            return;
        }
    }

    code = generateCode();
    mainWindow->showBankMessage(code, sum);
    paymentSum = sum.toDouble();
}



void Payment::on_MakePayment_clicked()
{
    ui->Error_label_2->setText("");

    if(ui->SMSCode->text() != code)
    {
        ui->Error_label_2->setText("Wrong code");
        return;
    }

    if(purchaseType == PurchaseTypes::FOR_MYSELF)
    {
        currentAccount->balance += paymentSum;
        mainWindow->updateUserBalance();

        mainWindow->showInformationalWindow("Successfuly operation", "Your balance has been top upped\nby "
                                            + QString::number(paymentSum) + "$");
        close();
    }
    else
    {
        QString code = mainWindow->createPromocode( PromocodeTypes::MONEY, QString::number(paymentSum) );

        hide();
        mainWindow->showPromocodeWindow(code);
        close();
    }

}

void Payment::mousePressEvent(QMouseEvent *event)
{
    lastPressedMouseButton = event->button();

    if(lastPressedMouseButton == Qt::LeftButton)
    {
        prevMousePos = event->globalPosition();
    }

    QDialog::mousePressEvent(event);
}

void Payment::mouseMoveEvent(QMouseEvent *event)
{
    if(lastPressedMouseButton != Qt::LeftButton)
        return;

    if(!containsPoint(ui->UpperFrame, event->pos()))
        return;

    if(event->globalPosition().x() <= 0 || event->globalPosition().y() <= 0)
        return;

    if(event->globalPosition().y() >= screenInfo->size().height() - 40 ||
        event->globalPosition().x() >= screenInfo->size().width())
        return;

    QPointF delta = event->globalPosition() - prevMousePos;

    move(this->pos() + delta.toPoint());
    prevMousePos = event->globalPosition();

    QDialog::mousePressEvent(event);
}


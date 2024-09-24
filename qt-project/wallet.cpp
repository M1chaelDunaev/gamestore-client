#include "wallet.h"
#include "ui_wallet.h"
#include "useraccount.h"
#include "payment.h"

Wallet::Wallet(MainWindow* _mainWindow, UserAccount* _currentAccount) :
    QWidget(nullptr), ui(new Ui::Wallet),
    mainWindow(_mainWindow), currentAccount(_currentAccount)
{
    ui->setupUi(this);
    setBalance();
}

Wallet::~Wallet()
{
    delete ui;
}

void Wallet::setBalance()
{
    ui->BalanceDisplay_label->setText(QString::number(currentAccount->balance) + '$');
}

void Wallet::on_TopUpBalance_pushButton_clicked()
{
    Payment* p = new Payment(mainWindow, currentAccount, PurchaseTypes::FOR_MYSELF);
    p->exec();
    delete p;
}

void Wallet::showEvent(QShowEvent *event)
{
    setBalance();
}


void Wallet::on_MakePromocode_pushButton_clicked()
{
    Payment* p = new Payment(mainWindow, currentAccount, PurchaseTypes::FOR_PROMOCODE);
    p->exec();
    delete p;
}


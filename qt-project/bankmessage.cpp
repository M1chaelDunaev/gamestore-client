#include "bankmessage.h"
#include "ui_bankmessage.h"

BankMessage::BankMessage(const QString& _code, const QString& _sum) :
    QDialog(nullptr), ui(new Ui::BankMessage)
{
    setWindowIcon(QIcon("ApplicationIcons/MessageIcon.png"));
    setWindowTitle("New message");

    ui->setupUi(this);
    ui->Code->setReadOnly(true);

    ui->PaymentSum->setText(_sum + " USD");
    ui->Code->setText(_code);
}

BankMessage::~BankMessage()
{
    delete ui;
}

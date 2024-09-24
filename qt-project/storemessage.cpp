#include "storemessage.h"
#include "ui_storemessage.h"

StoreMessage::StoreMessage(const QString& _code, const QString& _action) :
     QDialog(nullptr), ui(new Ui::StoreMessage)
{
    ui->setupUi(this);
    ui->Code->setText(_code);
    ui->Action->setText(_action);
}

StoreMessage::~StoreMessage()
{
    delete ui;
}

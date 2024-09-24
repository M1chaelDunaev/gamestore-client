#ifndef BANKMESSAGE_H
#define BANKMESSAGE_H

#include <QDialog>

namespace Ui {
class BankMessage;
}

class BankMessage : public QDialog
{
    Q_OBJECT

public:
    explicit BankMessage(const QString& _code, const QString& _sum);
    ~BankMessage();

private:
    Ui::BankMessage *ui;
};

#endif // BANKMESSAGE_H

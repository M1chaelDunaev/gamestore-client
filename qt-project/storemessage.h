#ifndef STOREMESSAGE_H
#define STOREMESSAGE_H

#include <QDialog>

namespace Ui {
class StoreMessage;
}

class StoreMessage : public QDialog
{
    Q_OBJECT

public:
    explicit StoreMessage(const QString &_code, const QString &_action);
    ~StoreMessage();

private:
    Ui::StoreMessage *ui;
};

#endif // STOREMESSAGE_H

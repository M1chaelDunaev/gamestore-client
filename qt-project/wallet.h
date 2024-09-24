#ifndef WALLET_H
#define WALLET_H

#include <QWidget>

class MainWindow;
class UserAccount;

namespace Ui {
class Wallet;
}

class Wallet : public QWidget
{
    Q_OBJECT

    Ui::Wallet *ui;
    MainWindow* mainWindow;
    UserAccount* currentAccount;


public:
    explicit Wallet(MainWindow* _mainWindow, UserAccount* _currentAccount);
    ~Wallet();
    void setBalance();

public slots:
    void on_TopUpBalance_pushButton_clicked();
    void on_MakePromocode_pushButton_clicked();

protected:
    virtual void showEvent(QShowEvent *event) override;
};

#endif // WALLET_H

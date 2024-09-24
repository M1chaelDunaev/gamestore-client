#ifndef CART_H
#define CART_H

#include <QWidget>
class UserAccount;
class MainWindow;

namespace Ui
{
class Cart;
}


class Cart : public QWidget
{
    Q_OBJECT

    Ui::Cart *ui;
    UserAccount* currentAccount;
    MainWindow* mainWindow;

    void setIcons();

public:
    explicit Cart(MainWindow* _mainWindow, UserAccount* _currentAccount);
    ~Cart();

    void update();
private slots:
    void on_AllProducts_pushButton_clicked();
    void on_ER_remove_clicked();
    void on_GOW_remove_clicked();
    void on_Str_remove_clicked();
    void on_HFW_remove_clicked();
    void on_PT_remove_clicked();
    void on_LOU_remove_clicked();
    void on_Cup_remove_clicked();
    void on_DL_remove_clicked();
    void on_War_remove_clicked();
    void on_PurchaseForMyself_clicked();
    void on_PurchaseAsAGift_clicked();

protected:
    virtual void showEvent(QShowEvent *event) override;
};

#endif // CART_H

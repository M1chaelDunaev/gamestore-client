#ifndef STORE_H
#define STORE_H

#include <QWidget>


namespace Ui {
class Store;
}

class MainWindow;
class UserAccount;

class Store : public QWidget
{
    Q_OBJECT

    Ui::Store *ui;
    MainWindow* mainWindow;
    UserAccount* currentAccount;

public:
    explicit Store(MainWindow* _mainWindow, UserAccount* _currentAccount);
    ~Store();

    void updateCartButton();
    void updateWidget();
    void showCategoriesErrorMessage();

private slots:
    void on_ER_pushButton_clicked();

    void on_GOW_pushButton_clicked();
    void on_Str_pushButton_clicked();
    void on_PT_pushButton_clicked();
    void on_HFW_pushButton_clicked();
    void on_LOU_pushButton_clicked();
    void on_Cup_pushButton_clicked();
    void on_DL_pushButton_clicked();
    void on_War_pushButton_clicked();
    void on_ERBUY_pushButton_clicked();
    void on_Cart_pushButton_clicked();
    void on_GOWBUY_pushButton_clicked();
    void on_StrBUY_pushButton_clicked();
    void on_PTBUY_pushButton_clicked();
    void on_HFWBUY_pushButton_clicked();
    void on_LOUBUY_pushButton_clicked();
    void on_CupBUY_pushButton_clicked();
    void on_DLBUY_pushButton_clicked();
    void on_WarBUY_pushButton_clicked();

    // QWidget interface
    void on_Gifts_pushButton_clicked();

    void on_TopUpBalance_pushButton_clicked();

    void on_FriendsGames_pushButton_clicked();

    void on_YourGames_pushButton_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_Search_pushButton_clicked();

    void on_Wishlist_pushButton_clicked();

protected:
    virtual void showEvent(QShowEvent *event) override;
};


#endif // STORE_H

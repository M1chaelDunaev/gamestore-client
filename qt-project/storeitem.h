#ifndef STOREITEM_H
#define STOREITEM_H

#include <QWidget>
#include <QPixmap>
#include <QImage>


class MainWindow;
class UserAccount;

namespace Ui {
class StoreItem;
}

class StoreItem : public QWidget
{
    Q_OBJECT

protected:
    Ui::StoreItem *ui;
    UserAccount* currentAccount;
    MainWindow* mainWindow;

    QImage* screen_1;
    QImage* screen_2;
    QImage* screen_3;
    QImage* screen_4;
    QImage* screen_5;

    QString shortName;

    bool bought;
    bool installed;
    bool inCart;

    void loadScreens(const QString& _scr1, const QString& _scr2, const QString& _scr3,
                     const QString& _scr4, const QString& _scr5);
    void setScreens();

    void setCover(const QString& _cover);

    void setCurrentScreenshot(int _number);

    void setName(const QString& _name);
    void setPrice(const QString& _price);
    void setMainDescription(const QString& _description);
    void setSmallDescriptions(const QString& _first, const QString& _second, const QString& _third,
                              const QString& _fourth, const QString& _fifth);
    void setLanguages(const QString& _lang);
    void setMinSR(const QString& _first, const QString& _second, const QString& _third,
                  const QString& _fourth, const QString& _fifth);
    void setRecSR(const QString& _first, const QString& _second, const QString& _third,
                  const QString& _fourth, const QString& _fifth);

    QString inCartButton_styleSheet();
    QString baseButton_styleSheet();

    virtual void setStatus() = 0;
    virtual void pressAddToCart() = 0;
    virtual void pressInstall() = 0;
    virtual void pressPlay() = 0;
    virtual void pressUninstall() = 0;

public:
    explicit StoreItem(MainWindow* _mainWindow, UserAccount* _currentAccount);
    virtual ~StoreItem();

    void updateWidget();

private slots:

    void on_addToCart_Play_Install_clicked();
    void on_Screen1_pushButton_clicked();
    void on_Screen2_pushButton_clicked();
    void on_Screen3_pushButton_clicked();
    void on_Screen4_pushButton_clicked();
    void on_Screen5_pushButton_clicked();

    // QWidget interface
    void on_Cart_pushButton_clicked();

    void on_Uninstall_clicked();

    void on_RR_pushButton_clicked();

    void on_AR_pushButton_clicked();

    void on_DEV_pushButton_clicked();

    void on_PUB_pushButton_clicked();

protected:
    virtual void showEvent(QShowEvent *event) override;
};

#endif // STOREITEM_H

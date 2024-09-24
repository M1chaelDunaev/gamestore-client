#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QWidget>
#include <QStackedLayout>
#include <QPushButton>

class MainApplication;
class PromocodesList;
class UserAccount;
class Store;
class Library;
class Community;
class UserProfile;
class EditProfile;
class Wallet;
class Cart;
class Downloader;
class Support;

class ItemEldenRing;
class ItemGodOfWar;
class ItemStray;
class ItemHorizon;
class ItemPlagueTale;
class ItemLastOfUs;
class ItemCuphead;
class ItemDyingLight;
class ItemWarhammer;

enum class Games;
enum class PromocodeTypes;


namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT
    Ui::MainWindow *ui;
    QPointF prevMousePos;
    Qt::MouseButton lastPressedMouseButton;
    QScreen* screenInfo;
    bool sizeGripActivated;

    MainApplication* mainApp;//MainApplication pointer
    QStackedLayout* centralLayout;//MainWindow layout pointer

    //Conditions of small buttons
    bool sounds = true;
    bool notifications = true;
    bool userMenuActivated = false;

    //Big windows
    Store* store;
    Library* library;
    Community* community;
    UserProfile* profile;

    //Other windows
    EditProfile* editProfile;
    Wallet* wallet;
    Support* support;
    Cart* cart;
    Downloader* downloader;

    //Store windows
    ItemEldenRing* eldenRing;
    ItemGodOfWar* godOfWar;
    ItemStray* stray;
    ItemHorizon* horizon;
    ItemPlagueTale* plagueTale;
    ItemLastOfUs* lastOfUs;
    ItemCuphead* cuphead;
    ItemDyingLight* dyingLight;
    ItemWarhammer* warhammer;

    UserAccount* currentAccount;
    PromocodesList* promocodesList;

    //initialization methods
    void createWindows();
    void deleteWindows();
    void makeCentralLayout();
    void setIcons();

    //StyleSheets
    QString bigMenuBase_styleSheet();
    QString smallMenuBase_styleSheet();
    QString bigMenuActive_styleSheet();
    QString smallMenuActive_styleSheet();
    QString userMenuBase_styleSheet();
    QString userMenuActive_styleSheet();

public:
    explicit MainWindow(MainApplication* _app, int _id);
    ~MainWindow();

    //Database methods
    void updateUserAccount(const QString& _field, const QString& _value);
    void updateUserBalance();
    void updateUserLibrary();
    void updateUserActivity();
    void setAvatar(const QPixmap& _avatar);

    QString createPromocode(PromocodeTypes _type, const QString& _value);
    void deletePromocode(const QString& _code);

    //Show Dialogs windows
    void showInformationalWindow(const QString& _title, const QString& _text);
    void showBankMessage(const QString& _code, const QString& _sum);
    void showPromocodeWindow(const QString& _code);
    void showGiftsWindow();

    //Windows methods
    void showStore();
    void showLibrary();
    void showCommunity();
    void showProfile();
    void showEditProfile();
    void showWallet();
    void showCart();
    void showDownloader();
    void showGame(Games _game);
    void showPlayWindow(Games _game, const QString& _iconPath);

    //
    void startDownload(Games _game); //Starting download the given game
    void topUpBalance(); //Show top up balance window
    void setCurrentMenu(QPushButton* _button); //Set current menu style

signals:
    void showBankMessageSignal(const QString& _code, const QString& _sum);
    void logOutSignal();

private slots:
    void on_Store_pushButton_clicked();
    void on_Library_pushButton_clicked();
    void on_Community_pushButton_clicked();
    void on_Account_pushButton_clicked();
    void on_Settings_pushButton_clicked();
    void on_Support_pushButton_clicked();
    void on_Friends_pushButton_clicked();
    void on_Wallet_pushButton_clicked();
    void on_UserMenu_pushButton_clicked();
    void on_Notifications_clicked();
    void on_Sounds_clicked();
    void on_EnterThePromocode_clicked();
    void on_ManageDownloads_clicked();
    void on_FriendsAndChat_clicked();
    void on_MaximizedNormal_pushButton_clicked();
    void on_Minimized_pushButton_clicked();
    void on_Close_pushButton_clicked();
    void on_LogOut_clicked();

protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void resizeEvent(QResizeEvent *event) override;
};


#endif // MAINWINDOW_H

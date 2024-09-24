#ifndef MAINAPPLICATION_H
#define MAINAPPLICATION_H

#include <QSqlDatabase>
#include <QWidget>

class LoginWindow;
class RegistrationWindow;
class RegistrationWindowFinal;
class MainWindow;
class SupportHolder;
class UserAccount;
class PromocodesList;

enum class SecretQuestionTypes;

enum class SearchResult
{
    EMAIL_NOT_FOUND,
    EMAIL_FOUND_WRONG_PASSWORD,
    EMAIL_FOUND_RIGHT_PASSWORD
};

class MainApplication : public QObject
{
    Q_OBJECT

    QSqlDatabase* dataBase;
    UserAccount* buffer;

    //Windows
    LoginWindow* logWindow;
    RegistrationWindow* regWindow;
    RegistrationWindowFinal* finregWindow;
    MainWindow* mainWindow;
    SupportHolder* support;

    //Initialization methods
    void init();
    bool getInitStatus();

    //additional methods for initCurrentAccount(int)
    void setAccountFields(UserAccount* _account, int _id);
    void setLibrary(UserAccount* _account, int _id);
    void setActivity(UserAccount* _account, int _id);

public:
    MainApplication();
    ~MainApplication();

    void exec(); //To launch application

    void setMainWindow(int _id); //To create main window for user with _id

    void setRemembrance(int _id); //To set remembered user id
    int getRemembrance();//To get remembered user id

    void incrementCountOfUsers();//To increment total count of users
    int getCountOfUsers();//To get current count of users

    UserAccount* initCurrentAccount(int _id);//To get UserAccount pointer for given id
    PromocodesList* initPromocodesList();//To get PromocodeList pointer

    SearchResult findAccount(int& result_id, QString _email, QString _password);//To verification given email and password
    int getIdByEmail(const QString& _email);
    int getIdByPhoneNumber(const QString& _phoneNumber);
    void getCountryAndSQ(int _id, SecretQuestionTypes& _type, QString& _answer, QString& _country);

    void addAccount();//To add buffer to the database

    //Methods to update database
    void updateUserAccount(int _id, const QString& _field, const QString& _value);
    void updateUserBalance(int _id, double _balance);
    void updateUserLibrary(int _id, const QString& _bought, const QString& _installed);
    void updateUserActivity(int _id, const QString& _list);

    void addPromocode(const QString& _code, const QString _value);//To add new promocode to the database
    void deletePromocode(const QString& _code);//To delete given promocode from database

    //Strings
    QString getHash(const QString& _pass);
    static QString lineEdit_StyleSheet();
    static QString lineEditError_StyleSheet();

    //Windows methods
    void showMainWindow();
    void hideMainWindow();
    void showLoginWindow();
    void hideLoginWindow();
    void showRegistrationWindow();
    void hideRegistrationWindow();
    void showFinalRegistrationWindow();
    void hideFinalRegistrationWindow();
    void showSupportWindow();

private slots:

    void showBankMessageSlot(const QString& _code, const QString& _sum);
    void showStoreMessageSlot(const QString& _code, const QString& _action);

    void logOutSlot();
};
#endif // MAINAPPLICATION_H

#include <QWidget>
#include <QFile>
#include <QTextStream>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QCryptographicHash>

#include "mainapplication.h"
#include "loginwindow.h"
#include "registrationwindow.h"
#include "registrationwindowfinal.h"
#include "supportholder.h"
#include "mainwindow.h"
#include "useraccount.h"
#include "promocodeslist.h"
#include "storemessage.h"
#include "bankmessage.h"

MainApplication::MainApplication()
{
    dataBase = new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"));
    buffer = new UserAccount();

    logWindow = new LoginWindow(this);
    regWindow = new RegistrationWindow(this, buffer);
    finregWindow = new RegistrationWindowFinal(this, buffer);
    support = new SupportHolder(this);
    mainWindow = nullptr;

    if(!getInitStatus())
        init();

    dataBase->setDatabaseName("users.db");
}

MainApplication::~MainApplication()
{
    delete dataBase;
    delete logWindow;
    delete regWindow;
    delete finregWindow;
    delete mainWindow;
    delete buffer;
    delete support;
}

void MainApplication::exec()
{
    int remembrance = getRemembrance();

    if(remembrance == (-1))
    {
        logWindow->show();
    }
    else
    {
        setMainWindow(remembrance);
    }
}

void MainApplication::setMainWindow(int _id)
{
    mainWindow = new MainWindow(this, _id);
    connect(mainWindow, SIGNAL(logOutSignal()), this, SLOT(logOutSlot()));
    mainWindow->showMaximized();
}

void MainApplication::init()
{
    QFile file("remembrance.txt");
    file.open(QIODevice::ReadWrite);
    QTextStream stream(&file);

    stream << -1;
    file.close();

    file.setFileName("count_of_users.txt");
    file.open(QIODevice::ReadWrite);
    QTextStream stream2(&file);
    stream2 << 0;
    file.close();

    file.setFileName("users.db");
    file.open(QIODevice::ReadWrite);
    file.close();

    dataBase->setDatabaseName("users.db");
    dataBase->open();

    QSqlQuery query(*dataBase);
    QString q = "";

    //Create first table
    q += "CREATE TABLE 'ListOfUsers'("
         " 'ID' INT PRIMARY_KEY, "
         " 'RealName' VARCHAR(60), "
         " 'DateOfBirth' VARCHAR(10), "
         " 'Email' VARCHAR(50), "
         " 'Password' VARCHAR(64), "
         " 'UserName' VARCHAR(30), "
         " 'PhoneNumber' VARCHAR(13), "
         " 'Country' VARCHAR(25), "
         " 'Balance' FLOAT, "
         " 'SecretQuestionType' INT(2), "
         " 'SecretQuestionAnswer' VARCHAR(50), "
         " 'Status' VARCHAR"
         ");";
    query.exec(q);
    q.clear();
    query.clear();

    //Create second table
    q += "CREATE TABLE 'UserLibraries'("
         "'ID' INT PRIMARY_KEY, "
         "'Bought' VARCHAR(9),"
         "'Installed' VARCHAR(9));";
    query.exec(q);
    q.clear();
    query.clear();

    //Create third table
    q += "CREATE TABLE 'UserActivities'("
         "'ID' INT PRIMARY_KEY,"
         "'List' VARCHAR(9));";
    query.exec(q);

    q.clear();
    query.clear();

    //Create fourth table
    q += "CREATE TABLE 'Promocodes'("
         "'Code' VARCHAR(32), "
         "'Value' VARCHAR(11));";
    query.exec(q);

    dataBase->close();

    //set init status
    file.setFileName("init_status.txt");
    file.open(QIODevice::ReadWrite | QIODevice::Truncate);
    QTextStream stream3(&file);
    stream3 << 1;
}

bool MainApplication::getInitStatus()
{
    QFile file("init_status.txt");
    file.open(QIODevice::ReadWrite);
    QTextStream stream(&file);

    int status;
    stream >> status;

    if(status == 1)
        return true;
    else
        return false;
}

int MainApplication::getRemembrance()
{
    QFile file("remembrance.txt");
    QTextStream stream(&file);

    file.open(QIODevice::ReadOnly);
    int id;
    stream >> id;
    file.close();

    return id;
}

void MainApplication::incrementCountOfUsers()
{
    QFile file("count_of_users.txt");
    int prevCount = getCountOfUsers();
    file.open(QIODevice::WriteOnly | QIODevice::Truncate);
    QTextStream stream(&file);

    stream << (++prevCount);
}

int MainApplication::getCountOfUsers()
{
    QFile file("count_of_users.txt");
    file.open(QIODevice::ReadOnly);
    QTextStream stream(&file);

    int count;
    stream >> count;
    return count;
}

void MainApplication::setRemembrance(int _id)
{

    QFile file("remembrance.txt");
    QTextStream stream(&file);
    file.open(QIODevice::WriteOnly | QIODevice::Truncate);
    stream << _id;
    file.close();
}

//database methods

UserAccount* MainApplication::initCurrentAccount(int _id)
{
    dataBase->open();

    UserAccount* currentAccount = new UserAccount;

    setAccountFields(currentAccount, _id);
    setLibrary(currentAccount, _id);
    setActivity(currentAccount, _id);

    dataBase->close();
    return currentAccount;
}

PromocodesList *MainApplication::initPromocodesList()
{
    dataBase->open();

    QSqlQuery query(*dataBase);
    query.exec("SELECT * FROM Promocodes;");
    query.first();

    PromocodesList* pList = new PromocodesList();
    pList->insert(query.value(0).toString(), query.value(1).toString());

    while(query.next())
    {
        pList->insert(query.value(0).toString(), query.value(1).toString());
    }

    dataBase->close();

    return pList;
}

void MainApplication::setAccountFields(UserAccount* _account, int _id)
{
    QSqlQuery query(*dataBase);
    QString q = "";
    q += "SELECT * FROM ListOfUsers WHERE ID = "
         "'" + QString::number(_id) + "';";
    query.exec(q);

    query.first();
    _account->id = query.value(0).toInt();
    _account->realName = query.value(1).toString();
    _account->birthDate = query.value(2).toString();
    _account->email = query.value(3).toString();
    _account->password = query.value(4).toString();
    _account->userName = query.value(5).toString();
    _account->phoneNumber = query.value(6).toString();
    _account->country = query.value(7).toString();
    _account->balance = query.value(8).toDouble();
    _account->sq_type = static_cast<SecretQuestionTypes>(query.value(9).toInt());
    _account->sq_answer = query.value(10).toString();
    _account->status = query.value(11).toString();
}

void MainApplication::setLibrary(UserAccount *_account, int _id)
{
    QSqlQuery query(*dataBase);
    QString q = "";
    q += "SELECT * FROM UserLibraries WHERE ID = "
         "'" + QString::number(_id) + "';";
    query.exec(q);

    query.first();
    QString bought = query.value(1).toString();
    QString installed = query.value(2).toString();

    _account->library.setValues(bought, installed);
}

void  MainApplication::setActivity(UserAccount *_account, int _id)
{
    QSqlQuery query(*dataBase);
    QString q = "";
    q += "SELECT * FROM UserActivities WHERE ID = "
         "'" + QString::number(_id) + "';";
    query.exec(q);

    query.first();
    QString activity = query.value(1).toString();

    _account->activity.setValues(activity);
}

void MainApplication::updateUserAccount(int _id, const QString &_field, const QString &_value)
{
    dataBase->open();

    QSqlQuery query(*dataBase);
    QString q = "";
    q += "UPDATE ListOfUsers SET " + _field + " = '" + _value + "'";
    q += " WHERE ID = '" + QString::number(_id) + "';";

    query.exec(q);

    dataBase->close();
}

void MainApplication::addAccount()
{
    QString id = QString::number(getCountOfUsers());
    dataBase->open();
    QSqlQuery query(*dataBase);
    QString q = "";
    q += "INSERT INTO ListOfUsers"
         "(ID, RealName, DateOfBirth, Email, UserName,Password,"
         " PhoneNumber, Country, Balance, SecretQuestionType, SecretQuestionAnswer, Status)"
         " VALUES(";
    q += ("'" + id + "', ");
    q += ("'" + buffer->realName + "', ");
    q += ("'" + buffer->birthDate + "', ");
    q += ("'" + buffer->email + "', ");
    q += ("'" + buffer->email + "', ");
    q += ("'" + getHash(buffer->password) + "', ");
    q += ("'" + buffer->phoneNumber + "', ");
    q += ("'" + buffer->country + "', ");
    q += ("'0.0', ");
    q += ("'" + QString::number((int)buffer->sq_type) + "', ");
    q += ("'" + buffer->sq_answer + "', ");
    q += "'No information given');";

    query.exec(q);
    q.clear();
    query.clear();

    q += "INSERT INTO UserLibraries"
         "(ID, Bought, Installed) VALUES("
         "'" + id + "', '000000000', '000000000');";
    query.exec(q);
    q.clear();
    query.clear();

    q += "INSERT INTO UserActivities"
         "(ID, List) VALUES("
         "'" + id + "', '1-0-0');";
    query.exec(q);

    dataBase->close();
    incrementCountOfUsers();

    regWindow->restoreWindow();
    finregWindow->restoreWindow();
}

void MainApplication::getCountryAndSQ(int _id, SecretQuestionTypes &_type, QString& _answer, QString & _country)
{
    dataBase->open();
    QSqlQuery query(*dataBase);
    QString q = "";
    q += "SELECT SecretQuestionType, SecretQuestionAnswer, Country FROM ListOfUsers WHERE ID = ";
    q += "'" + QString::number(_id) + "';";
    query.exec(q);

    query.first();

    _type = (SecretQuestionTypes)query.value(0).toInt();
    _answer = query.value(1).toString();
    _country = query.value(2).toString();

    dataBase->close();
}

void MainApplication::addPromocode(const QString &_code, const QString _value)
{
    dataBase->open();

    QSqlQuery query(*dataBase);
    QString q = "";
    q += "INSERT INTO Promocodes(Code, Value) VALUES("
         "'" + _code + "', '" +_value + "');";
    query.exec(q);

    dataBase->close();
}

void MainApplication::deletePromocode(const QString &_code)
{
    dataBase->open();

    QSqlQuery query(*dataBase);
    QString q = "";
    q += "DELETE FROM Promocodes WHERE Code = "
         "'" +_code + "';";
    query.exec(q);

    dataBase->close();
}

void MainApplication::updateUserBalance(int _id, double _balance)
{
    dataBase->open();

    QSqlQuery query(*dataBase);
    QString q = "";
    q += "UPDATE ListOfUsers SET Balance = ";
    q += "'" + QString::number(_balance) + "'";
    q += " WHERE ID = ";
    q += "'" + QString::number(_id) + "';";
    query.exec(q);

    dataBase->close();
}

void MainApplication::updateUserLibrary(int _id, const QString &_bought, const QString &_installed)
{
    dataBase->open();

    QSqlQuery query(*dataBase);
    QString q = "";
    q += "UPDATE UserLibraries SET Bought = ";
    q += "'" + _bought + "', ";
    q += "Installed = ";
    q += "'" + _installed + "'";
    q += " WHERE ID = ";
    q += "'" + QString::number(_id) + "';";
    query.exec(q);

    dataBase->close();
}

void MainApplication::updateUserActivity(int _id, const QString &_list)
{
    dataBase->open();

    QSqlQuery query(*dataBase);
    QString q = "";
    q += "UPDATE UserActivities SET List = '" + _list + "'";
    q += " WHERE ID = '" + QString::number(_id) + "';";
    query.exec(q);

    dataBase->close();
}

SearchResult MainApplication::findAccount(int &result_id, QString _email, QString _password)
{
    dataBase->open();
    QSqlQuery query(*dataBase);
    QString q = "";
    q += "SELECT ID, Password FROM ListOfUsers WHERE Email = ";
    q += ("'" + _email + "';");
    query.exec(q);
    dataBase->close();

    if(!query.first())
        return SearchResult::EMAIL_NOT_FOUND;

    if(query.value(1).toString() != getHash(_password))
        return SearchResult::EMAIL_FOUND_WRONG_PASSWORD;

    result_id = query.value(0).toInt();
    return SearchResult::EMAIL_FOUND_RIGHT_PASSWORD;
}

int MainApplication::getIdByEmail(const QString &_email)
{
    dataBase->open();

    QSqlQuery query(*dataBase);
    QString q = "";
    q += "SELECT ID FROM ListOfUsers WHERE Email = ";
    q += "'" + _email + "';";
    query.exec(q);

    dataBase->close();

    if(!query.first())
        return -1;


    return query.value(0).toInt();
}

int MainApplication::getIdByPhoneNumber(const QString &_phoneNumber)
{
    dataBase->open();

    QSqlQuery query(*dataBase);
    QString q = "";
    q += "SELECT ID FROM ListOfUsers WHERE PhoneNumber = ";
    q += "'" + _phoneNumber + "';";
    query.exec(q);

    dataBase->close();

    if(!query.first())
        return -1;

    return query.value(0).toInt();
}

//Strings

QString MainApplication::getHash(const QString &_password)
{
    auto res = QCryptographicHash::hash(_password.toUtf8(), QCryptographicHash::Sha256);

    return {res.toHex()};
}

QString MainApplication::lineEdit_StyleSheet()
{
    QString styleSheet = "";
    styleSheet += "color: rgb(255, 255, 255);"
                  "background-color: rgb(74, 79, 90); "
                  "border: none;";


    return styleSheet;
}

QString MainApplication::lineEditError_StyleSheet()
{
    QString styleSheet = lineEdit_StyleSheet();
    styleSheet += "border-color: rgb(255, 0, 0);"
                  "border-style: solid;"
                  "border-width: 1px;";

    return styleSheet;
}

//Windows methods

void MainApplication::showMainWindow()
{
    mainWindow->show();
}

void MainApplication::hideMainWindow()
{
    mainWindow->hide();
}

void MainApplication::showLoginWindow()
{
    logWindow->show();
}

void MainApplication::hideLoginWindow()
{
    logWindow->hide();
}

void MainApplication::showRegistrationWindow()
{
    regWindow->show();
}

void MainApplication::hideRegistrationWindow()
{
    regWindow->hide();
}

void MainApplication::showFinalRegistrationWindow()
{
    finregWindow->show();
}

void MainApplication::hideFinalRegistrationWindow()
{
    finregWindow->hide();
}

void MainApplication::showSupportWindow()
{
    support->showMaximized();
}


//Slots

void MainApplication::showBankMessageSlot(const QString &_code, const QString &_sum)
{
    BankMessage* bm = new BankMessage(_code, _sum);
    bm->setWindowTitle("New message");
    bm->setWindowIcon(QPixmap("ApplicationIcons/MessageIcon.png"));
    bm->exec();
    delete bm;
}

void MainApplication::showStoreMessageSlot(const QString &_code, const QString &_action)
{
    StoreMessage* sm = new StoreMessage(_code, _action);
    sm->setWindowTitle("New message");
    sm->setWindowIcon(QPixmap("ApplicationIcons/MessageIcon.png"));
    sm->exec();
    delete sm;
}

void MainApplication::logOutSlot()
{
    mainWindow->close();
    setRemembrance((-1));
    delete mainWindow;
    mainWindow = nullptr;

    logWindow->show();
}


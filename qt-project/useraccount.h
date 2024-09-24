#ifndef USERACCOUNT_H
#define USERACCOUNT_H
#include <QString>
#include <QDebug>

//Страна / код
//USA +1
//Canada +1
//Russia +7
//UK +44
//France +33
//German +49
//Japan +81
//China +86

enum class SecretQuestionTypes
{
    NONE = 0,
    CITY_OF_BIRTH = 10,
    NAME_OF_FAVORITE_PET = 20,
    MOTHER_MAIDEN_NAME = 30,
    FAVORITE_FOOD = 40,
    MAKE_OF_FIRST_CAR = 50,
    FIRST_PHONE_MODEL = 60
};

enum class Games
{
    ELDEN_RING = 0,
    GOD_OF_WAR,
    STRAY,
    HORIZON,
    PLAGUE_TALE,
    LAST_OF_US,
    CUPHEAD,
    DYING_LIGHT,
    WARHAMMER
};

enum class ActivitiesList
{
    NONE = 0,
    REGISTRATION = 1,
    ELDEN_RING_BOUGHT = 10,
    GOD_OF_WAR_BOUGHT = 20,
    STRAY_BOUGHT = 30,
    HORIZON_BOUGHT = 40,
    PLAGUE_TALE_BOUGHT = 50,
    LAST_OF_US_BOUGHT = 60,
    CUPHEAD_BOUGHT = 70,
    DYING_LIGHT_BOUGHT = 80,
    WARHAMMER_BOUGHT = 90
};

class UserLibrary
{
public:
    bool bought[9];
    bool installed[9];

    void setValues(const QString& _bought, const QString& _installed);

};

class UserActivity
{
public:
    ActivitiesList first;
    ActivitiesList second;
    ActivitiesList third;

    void setValues(const QString& _list);

    void addNewActivity(ActivitiesList _activity);
};

class UserCart
{
public:
    bool list[9] = {false};
    int countOfItems();
};

class UserAccount
{
public:
    int id;
    QString email;
    QString country;
    QString password;
    QString userName;

    QString realName;
    QString phoneNumber;
    QString birthDate;
    SecretQuestionTypes sq_type;
    QString sq_answer;
    double balance;

    QString status;

    UserLibrary library;
    UserActivity activity;
    UserCart cart;

};

SecretQuestionTypes getQuestionType(const QString& _question);

QString getFullGameName(Games _game);

#endif // USERACCOUNT_H

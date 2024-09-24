#include "useraccount.h"
#include <QFontMetrics>
#include <random>

void UserLibrary::setValues(const QString &_bought, const QString &_installed)
{
    for(int i = 0; i < 9; ++i)
    {
        if(_bought[i] == '1')
            bought[i] = true;
        else
            bought[i] = false;
    }

    for(int i = 0; i < 9; ++i)
    {
        if(_installed[i] == '1')
            installed[i] = true;
        else
            installed[i] = false;
    }
}

void UserActivity::setValues(const QString &_list)
{
    QString value = "";
    int index = 1;

    for(auto elem : _list)
    {
        if(elem == '-')
        {
            auto temp = static_cast<ActivitiesList>(value.toInt());
            if(index == 1)
                first = temp;

            if(index == 2)
                second = temp;

            value.clear();
            ++index;
            continue;
        }

        value.push_back(elem);
    }

    third = static_cast<ActivitiesList>(value.toInt());
}

void UserActivity::addNewActivity(ActivitiesList _activity)
{
    third = second;
    second = first;
    first = _activity;
}

int UserCart::countOfItems()
{
    int count = 0;
    for(int i = 0; i < 9; ++i)
    {
        if(list[i])
            ++count;
    }

    return count;
}

SecretQuestionTypes getQuestionType(const QString &_question)
{
    if(_question == "None")
        return SecretQuestionTypes::NONE;

    if(_question == "The city in which you were born.")
        return SecretQuestionTypes::CITY_OF_BIRTH;

    else if(_question == "The name of your favorite pet.")
        return SecretQuestionTypes::NAME_OF_FAVORITE_PET;

    else if(_question == "The your favorite food.")
        return SecretQuestionTypes::FAVORITE_FOOD;

    else if(_question == "The maiden's name of your mother.")
        return SecretQuestionTypes::MOTHER_MAIDEN_NAME;

    else if(_question == "The make of your first car.")
        return SecretQuestionTypes::MAKE_OF_FIRST_CAR;
    else
        return SecretQuestionTypes::FIRST_PHONE_MODEL;
}

QString getFullGameName(Games _game)
{
    if(_game == Games::ELDEN_RING)
    {
        return "ELDEN RING";
    }

    if(_game == Games::GOD_OF_WAR)
    {
        return "God of War: Ragnarok";
    }

    if(_game == Games::STRAY)
    {
        return "Stray";
    }

    if(_game == Games::HORIZON)
    {
        return "Horizon Forbidden West";
    }

    if(_game == Games::PLAGUE_TALE)
    {
        return "Plague Tale: Requiem";
    }

    if(_game == Games::LAST_OF_US)
    {
        return "The Last of Us: Part I";
    }

    if(_game == Games::CUPHEAD)
    {
        return "Cuphead: The Delicious Last Course";
    }

    if(_game == Games::DYING_LIGHT)
    {
        return "Dying Light 2";
    }

    if(_game == Games::WARHAMMER)
    {
        return "Warhammer 40000: Darktide";
    }
}

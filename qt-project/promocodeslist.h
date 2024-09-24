#ifndef PROMOCODESLIST_H
#define PROMOCODESLIST_H

#include <map>
#include <utility>
#include <QString>


enum class PromocodeTypes
{
    GAME,
    MONEY
};

class PromocodesList
{
    std::map<QString, QString> list;

public:

    void insert(const QString& _code, const QString& _value)
    {
        list.insert(std::make_pair(_code, _value));
    }

    void remove(const QString& _code)
    {
        list.erase(_code);
    }

    bool find(const QString& _code, PromocodeTypes& _type, QString& _value)
    {
        auto result = list.find(_code);

        if(result == list.end())
            return false;

        QString record = result->second;

        if(record[0] == '0')
            _type = PromocodeTypes::GAME;
        else
            _type = PromocodeTypes::MONEY;


        QString value = "";
        for(int i = 2; i < record.size(); ++i)
        {
            value.push_back(record[i]);
        }

        _value = value;
        return true;
    }
};

#endif // PROMOCODESLIST_H

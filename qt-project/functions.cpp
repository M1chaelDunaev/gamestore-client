#include "functions.h"
#include <QString>
#include <QSize>
#include <QFontMetrics>
#include <QWidget>
#include <random>

QString roundTheDouble(double _value)
{
    QString temp = QString::number(_value);
    QString res = "";

    for(int i = 0; i < temp.size(); ++i)
    {
        if(temp[i] == '.')
        {
            res.push_back(temp[i]);
            res.push_back(temp[i + 1]);
            res.push_back(temp[i + 2]);
            break;
        }

        else
        {
            res.push_back(temp[i]);
        }
    }

    return res;
}

QString transformByLength(const QString &_input, const QSize& _widgetSize, const QFont& _font)
{
    QFontMetrics* metric = new QFontMetrics(_font);
    int minimumLineLength = _widgetSize.width() / (metric->size(Qt::TextSingleLine, "W").width() + 1); //Узнаем минимальное количество символов, точно входящих в виджет

    QString result = "";
    QString tempLine = "";
    QString checkpointLine = "";

    int index = 0;
    int tempLineWidth = 0;
    int lastSufficientIndex = -1;

    int checkpointIndex = 0;

    while(true)
    {
        //Если текущий индекс + минимальная длина строки >= длине всей строки
        //Копируем остаток в результат, выходим из цикла
        if(index + minimumLineLength >= _input.size())
        {
            result.push_back(_input.sliced(index));
            break;
        }

        tempLine.push_back(_input.sliced(index, minimumLineLength));
        index += minimumLineLength;
        tempLineWidth = metric->size(Qt::TextSingleLine, tempLine).width();

        //make checkpoint
        checkpointIndex = index;
        checkpointLine = tempLine;

        //right way
        lastSufficientIndex = -1;
        while(index < _input.size())
        {
            if(tempLineWidth + metric->size(Qt::TextSingleLine, QString(_input[index])).width() <
                _widgetSize.width())
            {
                tempLine.push_back(_input[index]);
                tempLineWidth += metric->size(Qt::TextSingleLine, QString(_input[index])).width();
            }
            else break;

            if(_input[index].isPunct() || _input[index].isSpace())
            {
                lastSufficientIndex = index;
            }

            ++index;
        }

        //left way
        if(lastSufficientIndex == (-1))
        {
            index = checkpointIndex - 1;
            tempLine = checkpointLine;

            while(!_input[index].isPunct() && !_input[index].isSpace())
            {
                --index;
                tempLine.removeLast();
            }
            lastSufficientIndex = index;
        }


        if(index > lastSufficientIndex)
        {
            --index;
            if(index != lastSufficientIndex)
            {
                while(index != lastSufficientIndex)
                {
                    --index;
                    tempLine.removeLast();
                }
            }
        }

        tempLine.push_back('\n');
        ++index;

        if(index + 1 < _input.size() && _input[index + 1].isSpace())
            ++index;

        result.push_back(tempLine);
        tempLine.clear();
    }

    return result;
}

bool checkCorrect_email(const QString &_email)
{
    char countOfAT = 0;
    char countOfDots = 0;
    char countOfLetters = 0;

    for(QChar elem : _email)
    {
        if(elem == '@')
            ++countOfAT;

        if(elem == '.')
            ++countOfDots;

        if(elem.isLetterOrNumber())
            ++countOfLetters;
    }

    if(countOfAT == 1 && countOfDots >= 1 && countOfLetters > 3)
        return true;
    else
        return false;
}

bool checkCorrect_password(const QString &_password)
{
    if(_password.size() < 8)
        return false;

    char countOfLetters = 0;
    char countOfDigits = 0;


    for (QChar elem : _password)
    {

        if(elem.isLetter())
            ++countOfLetters;

        if(elem.isNumber())
            ++countOfDigits;
    }

    if((countOfLetters > 0) && (countOfDigits > 0))
        return true;
    else
        return false;
}

bool checkCorrect_name(const QString &_name)
{
    for(QChar elem : _name)
    {
        if(!elem.isLetter())
            return false;
    }

    return true;
}

bool checkCorrect_date(const QString &_date)
{
    QString year = "";
    for (int i = 0; i < 4; ++i)
        year += _date[i];

    if(year.toInt() > 2010)
        return false;

    return true;
}

bool checkCorrect_phoneNumber(const QString &_number)
{
    char countOfDigits = 0;
    for (QChar elem : _number)
    {
        if(elem.isDigit())
        {
            ++countOfDigits;
            continue;
        }

        if(elem != ' ' && elem != '(' && elem != ')' && elem != '-')
            return false;
    }

    if(countOfDigits != 10)
        return false;

    return true;
}

QString getStandardNumber(const QString &_number)
{
    //template of phone number: XXX XXX-XX-XX
    //from[0] to [2] are digits
    //[3] is space
    //from [4] to [6] are digits
    //[7] is '-'
    //from [8] to [9] are digits
    //[10] is '-'
    //from [11] to [12] are degits

    if(_number.isEmpty())
        return "";

    QString res = "";
    res.resize(13);
    char pos = 0;

    for (QChar elem : _number)
    {
        if(pos > 12)
            break;

        if(pos == 3)
        {
            res[pos] = ' ';
            ++pos;
        }

        if(pos == 7 || pos == 10)
        {
            res[pos] = '-';
            ++pos;
        }

        if(elem.isDigit())
        {
            res[pos] = elem;
            ++pos;
            continue;
        }
    }

    return res;
}

QString generateCode()
{
    return QString::number(getRandomValue(1000, 9999));
}

int getRandomValue(int _low, int _top)
{
    std::random_device rd;
    std::mt19937 gen(rd());

    std::uniform_int_distribution distr(_low, _top);

    return distr(gen);
}

QString getPhoneCode(const QString &_country)
{
    if(_country == "USA" || _country == "Canada")
        return "+1";
    if(_country == "Russia")
        return "+7";
    if(_country == "UK")
        return "+44";
    if(_country == "France")
        return "+33";
    if(_country == "Germany")
        return "+49";
    if(_country == "Japan")
        return "+81";
    if(_country == "China")
        return "+86";
}

bool containsPoint(QWidget *_widget, const QPoint &_point)
{
    int xbegin = _widget->x();
    int xend = xbegin + _widget->width();
    int ybegin = _widget->y();
    int yend = ybegin + _widget->height();

    if(_point.x() >= xbegin && _point.x() <= xend &&
        _point.y() >= ybegin && _point.y() <= yend)
        return true;
    else
        return false;
}


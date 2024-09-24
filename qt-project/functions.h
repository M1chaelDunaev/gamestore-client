#ifndef FUNCTIONS_H
#define FUNCTIONS_H

class QString;
class QSize;
class QFont;
class QWidget;
class QPoint;

QString roundTheDouble(double _value);

QString transformByLength(const QString &_input, const QSize& _widgetSize, const QFont& _font);

bool checkCorrect_email(const QString& _email);

bool checkCorrect_password(const QString& _password);

bool checkCorrect_name(const QString& _name);

bool checkCorrect_date(const QString& _date);

bool checkCorrect_phoneNumber(const QString& _number);

QString getStandardNumber(const QString& _number);

QString generateCode();

int getRandomValue(int _low, int _top);

QString getPhoneCode(const QString& _country);

bool containsPoint(QWidget* _widget, const QPoint &_point);


#endif // FUNCTIONS_H

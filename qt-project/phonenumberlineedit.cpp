#include "phonenumberlineedit.h"
#include <QKeyEvent>
#include <QCursor>
#include "functions.h"


PhoneNumberLineEdit::PhoneNumberLineEdit(QWidget* parent) :
    QLineEdit(parent)
{
    restore();
    setFont(QFont("Arial", 11));
}

void PhoneNumberLineEdit::restore()
{
    displayedNumber = "(___)___-__-__";
    DNIndex = 1;
    cursorPos = 1;
}

QChar PhoneNumberLineEdit::getDigit(int _key)
{
    if(_key == Qt::Key_0)
        return '0';
    if(_key == Qt::Key_1)
        return '1';
    if(_key == Qt::Key_2)
        return '2';
    if(_key == Qt::Key_3)
        return '3';
    if(_key == Qt::Key_4)
        return '4';
    if(_key == Qt::Key_5)
        return '5';
    if(_key == Qt::Key_6)
        return '6';
    if(_key == Qt::Key_7)
        return '7';
    if(_key == Qt::Key_8)
        return '8';
    if(_key == Qt::Key_9)
        return '9';
}

void PhoneNumberLineEdit::moveCursorLeft()
{
    //(***)***-**-**
    if(cursorPos == 5 || cursorPos == 9 || cursorPos == 12)
    {
        cursorPos -=2;
        return;
    }


    --cursorPos;
}

void PhoneNumberLineEdit::moveCursorRight()
{
    if(cursorPos == 3 || cursorPos == 7 || cursorPos == 10)
    {
        cursorPos += 2;
        return;
    }

    ++cursorPos;
}

void PhoneNumberLineEdit::incrementDNIndex()
{

    if(DNIndex == 3 || DNIndex == 7 || DNIndex == 10)
    {
        DNIndex += 2;
        return;
    }

    ++DNIndex;
    //(***)***-**-**
}

void PhoneNumberLineEdit::decrementDNIndex()
{
    if(DNIndex == 5 || DNIndex == 9 || DNIndex == 12)
    {
        DNIndex -= 2;
        return;
    }

    --DNIndex;
}

bool PhoneNumberLineEdit::isValid()
{
    if(displayedNumber.back() != '_')
        return true;
    else
        return false;
}

QString PhoneNumberLineEdit::getStandardNumber()
{
    QString factualNumber = "";

    for(auto symb : displayedNumber)
    {
        if(symb.isDigit())
            factualNumber.push_back(symb);
    }

    //factualNumber.push_back(displayedNumber.back());

    return ::getStandardNumber(factualNumber);
}

void PhoneNumberLineEdit::keyPressEvent(QKeyEvent *event)
{
    auto key = event->key();
    if(key < Qt::Key_0 || key > Qt::Key_9)
    {
        if(key == Qt::Key_Backspace)
        {
            if(displayedNumber[1] == '_')
                return;

            if(displayedNumber[DNIndex] == '_')
            {
                decrementDNIndex();
                displayedNumber[DNIndex] = '_';
                moveCursorLeft();
            }
            else
            {
                displayedNumber[DNIndex] = '_';
                moveCursorLeft();
            }

            setText(displayedNumber);
            setCursorPosition(cursorPos);
        }

        return;
    }

    if(displayedNumber.back() != '_')
    {
        return;
    }

    QChar digit = getDigit(key);   
    displayedNumber[DNIndex] = digit;

    if(DNIndex < displayedNumber.size() - 1)
    {
        incrementDNIndex();
    }

    moveCursorRight();
    setText(displayedNumber);
    setCursorPosition(cursorPos);
}

void PhoneNumberLineEdit::focusInEvent(QFocusEvent *event)
{
    QLineEdit::focusInEvent(event);

    setText(displayedNumber);
    setCursorPosition(cursorPos);
}

void PhoneNumberLineEdit::focusOutEvent(QFocusEvent *event)
{
    QLineEdit::focusOutEvent(event);

    if(displayedNumber[1] == '_')
    {
        setText("");
    }
    else
    {
        setText(displayedNumber);
    }

}

void PhoneNumberLineEdit::mousePressEvent(QMouseEvent *event)
{
   setCursorPosition(cursorPos);
}

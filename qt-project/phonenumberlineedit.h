#ifndef PHONENUMBERLINEEDIT_H
#define PHONENUMBERLINEEDIT_H

#include <QLineEdit>
class QString;
class QWidget;

class PhoneNumberLineEdit : public QLineEdit
{
    Q_OBJECT

    int DNIndex;
    int cursorPos;
    QString displayedNumber;

    QChar getDigit(int _key);

    void moveCursorLeft();
    void moveCursorRight();
    void incrementDNIndex();
    void decrementDNIndex();

public:
    PhoneNumberLineEdit(QWidget* parent = nullptr);
    void restore();

    bool isValid();
    QString getStandardNumber();

    // QWidget interface
protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void focusInEvent(QFocusEvent *event) override;
    virtual void focusOutEvent(QFocusEvent *event) override;

    // QWidget interface
protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
};

#endif // PHONENUMBERLINEEDIT_H

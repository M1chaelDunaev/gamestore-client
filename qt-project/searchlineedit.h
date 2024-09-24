#ifndef SEARCHLINEEDIT_H
#define SEARCHLINEEDIT_H

#include <QLineEdit>

class SearchLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    SearchLineEdit(QWidget* parent = nullptr);

    // QWidget interface
protected:
    virtual void focusInEvent(QFocusEvent *event) override;
    virtual void focusOutEvent(QFocusEvent *event) override;
};

#endif // SEARCHLINEEDIT_H

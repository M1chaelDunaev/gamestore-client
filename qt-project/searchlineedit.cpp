#include "searchlineedit.h"

SearchLineEdit::SearchLineEdit(QWidget* parent) :
    QLineEdit(parent)
{
    setFont(QFont("Arial", 12));
    setText("Search...");
    setStyleSheet("background-color: rgb(85, 159, 204); background-image: none; color: rgb(255, 255, 255); border: 0px;");
}

void SearchLineEdit::focusInEvent(QFocusEvent *event)
{
    QLineEdit::focusInEvent(event);
    setText("");
}

void SearchLineEdit::focusOutEvent(QFocusEvent *event)
{
    QLineEdit::focusOutEvent(event);
    setText("Search...");
}

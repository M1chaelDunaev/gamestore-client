#ifndef RESTOREPHONENUMBER_H
#define RESTOREPHONENUMBER_H

#include <QDialog>
class Support;
enum class SecretQuestionTypes;

namespace Ui {
class RestorePhoneNumber;
}

class RestorePhoneNumber : public QDialog
{
    Q_OBJECT

    Ui::RestorePhoneNumber *ui;
    Support* support;
    QString code;
    int id;

    SecretQuestionTypes sqType;
    QString sqAnswer;
    QString country;

    QPointF prevMousePos;
    Qt::MouseButton lastPressedMouseButton;
    QScreen* screenInfo;

    void restoreEnterWidgets();

public:
    explicit RestorePhoneNumber(Support* _support);
    ~RestorePhoneNumber();

private slots:
    void on_GetCode_button_clicked();
    void on_ChangePhoneNumber_button_clicked();
    void on_Close_button_clicked();

    // QWidget interface
protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
};

#endif // RESTOREPHONENUMBER_H

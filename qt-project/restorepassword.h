#ifndef RESTOREPASSWORD_H
#define RESTOREPASSWORD_H

#include <QDialog>
class Support;
class PhoneNumberLineEdit;

namespace Ui {
class RestorePassword;
}

class RestorePassword : public QDialog
{
    Q_OBJECT

    Ui::RestorePassword *ui;
    PhoneNumberLineEdit* phoneNumberForm;
    Support* support;
    QString code;
    int id;

    QPointF prevMousePos;
    Qt::MouseButton lastPressedMouseButton;
    QScreen* screenInfo;

    void restoreEnterWidgets();

public:
    explicit RestorePassword(Support* _support);
    ~RestorePassword();

private slots:
    void on_GetCode_button_clicked();

    void on_ChangePassword_button_clicked();

    void on_Close_button_clicked();

    void setPhoneCode(const QString& _text);

    // QWidget interface
protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
};

#endif // RESTOREPASSWORD_H

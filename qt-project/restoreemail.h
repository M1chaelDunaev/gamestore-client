#ifndef RESTOREEMAIL_H
#define RESTOREEMAIL_H

#include <QDialog>

class Support;
class PhoneNumberLineEdit;

namespace Ui {
class RestoreEmail;
}

class RestoreEmail : public QDialog
{
    Q_OBJECT

    Ui::RestoreEmail *ui;
    PhoneNumberLineEdit* phoneNumberForm;
    Support* support;
    QString code;
    int id;

    QPointF prevMousePos;
    Qt::MouseButton lastPressedMouseButton;
    QScreen* screenInfo;

    void restoreEnterWidgets();

public:
    explicit RestoreEmail(Support* _support);
    ~RestoreEmail();

private slots:
    void on_GetCode_button_clicked();

    void on_ChangeEmail_button_clicked();

    void on_Close_button_clicked();

    void setPhoneCode(const QString& _text);

    // QWidget interface
protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
};

#endif // RESTOREEMAIL_H

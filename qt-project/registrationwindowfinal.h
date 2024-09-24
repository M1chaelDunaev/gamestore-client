#ifndef REGISTRATIONWINDOWFINAL_H
#define REGISTRATIONWINDOWFINAL_H
#include <QWidget>

class MainApplication;
class UserAccount;
class PhoneNumberLineEdit;

namespace Ui {
class RegistrationWindowFinal;
}

class RegistrationWindowFinal : public QWidget
{
    Q_OBJECT

    Ui::RegistrationWindowFinal *ui;
    MainApplication* mainApp;
    UserAccount* buffer;

    QPointF prevMousePos;
    Qt::MouseButton lastPressedMouseButton;
    QScreen* screenInfo;

    PhoneNumberLineEdit* phoneNumberForm;

public:
    explicit RegistrationWindowFinal(MainApplication* _app, UserAccount* _buffer);
    ~RegistrationWindowFinal();

    void restoreEnterWidgets();
    void restoreWindow();

private slots:
    void on_Close_button_clicked(){ close(); };
    void on_GoBack_button_clicked();

    void setPhoneCode();
    void on_CompleteRegistration_button_clicked();

protected:
    void showEvent(QShowEvent *event) override { setPhoneCode(); restoreEnterWidgets();};
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
};

#endif // REGISTRATIONWINDOWFINAL_H

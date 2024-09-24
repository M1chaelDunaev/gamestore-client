#ifndef REGISTRATIONWINDOW_H
#define REGISTRATIONWINDOW_H

#include <QDialog>

class UserAccount;
class MainApplication;


namespace Ui {
class RegistrationWindow;
}

class RegistrationWindow : public QWidget
{
    Q_OBJECT

    Ui::RegistrationWindow *ui;
    MainApplication *mainApp;
    UserAccount* buffer;
    bool agreement;

    QPointF prevMousePos;
    Qt::MouseButton lastPressedMouseButton;
    QScreen* screenInfo;

public:
    explicit RegistrationWindow(MainApplication* _app, UserAccount* _buffer);
    ~RegistrationWindow();

    void restoreEnterWidgets();//To restore all inputs widgets style
    void restoreWindow();//To restore style and clear all widgets

private slots:
    void on_Agree_button_clicked();

    void on_Close_button_clicked() { close(); };

    void on_Registration_button_clicked();

    void on_GoBack_button_clicked();

    // QWidget interface
protected:
    virtual void showEvent(QShowEvent *event) override { restoreEnterWidgets(); };

    // QWidget interface
protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
};
#endif // REGISTRATIONWINDOW_H

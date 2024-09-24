#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QWidget>

class MainApplication;

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QWidget
{
    Q_OBJECT

    Ui::LoginWindow *ui;
    MainApplication* mainApp;
    bool rememberMe;

    QPointF prevMousePos;
    Qt::MouseButton lastPressedMouseButton;
    QScreen* screenInfo;

    void restoreLineEdits();//Restore styles of lineEdits
public:
    explicit LoginWindow(MainApplication* app);
    ~LoginWindow();

private slots:

    void on_Close_button_clicked() { close();};

    void on_Remember_me_button_clicked();

    void on_Sign_in_button_clicked();

    void on_Registration_button_clicked();

    void on_Recover_button_clicked();

    // QWidget interface
protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
};
#endif // LOGINWINDOW_H

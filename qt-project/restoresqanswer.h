#ifndef RESTORESQANSWER_H
#define RESTORESQANSWER_H

#include <QDialog>
class Support;
class PhoneNumberLineEdit;

namespace Ui {
class RestoreSQAnswer;
}

class RestoreSQAnswer : public QDialog
{
    Q_OBJECT

    Ui::RestoreSQAnswer *ui;
    PhoneNumberLineEdit* phoneNumberForm;
    Support* support;
    QString code;
    int id;

    QPointF prevMousePos;
    Qt::MouseButton lastPressedMouseButton;
    QScreen* screenInfo;


    void restoreEnterWidgets();
public:
    explicit RestoreSQAnswer(Support* _support);
    ~RestoreSQAnswer();

private slots:
    void on_GetCode_button_clicked();
    void on_ChangeSQ_button_clicked();
    void on_Close_button_clicked();
    void setPhoneCode(const QString& _text);


    // QWidget interface
protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
};

#endif // RESTORESQANSWER_H

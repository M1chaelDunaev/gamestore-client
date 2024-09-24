#ifndef PAYMENT_H
#define PAYMENT_H

#include <QDialog>

class UserAccount;
class MainWindow;

namespace Ui {
class Payment;
}

enum class PurchaseTypes
{
    FOR_MYSELF,
    FOR_PROMOCODE
};


class Payment : public QDialog
{
    Q_OBJECT

    MainWindow* mainWindow;
    UserAccount* currentAccount;
    QString code;
    PurchaseTypes purchaseType;
    double paymentSum;

    QPointF prevMousePos;
    Qt::MouseButton lastPressedMouseButton;
    QScreen* screenInfo;

    void calcMax();
    bool isOnlyDigits(const QString& _str);
    bool isCorrectName(const QString& _str);
    bool isCorrecDate(const QString& _month, const QString& _year);

public:
    explicit Payment(MainWindow* _mainWindow, UserAccount* _currentAccount, PurchaseTypes _purchaseType);
    ~Payment();

private slots:
    void on_Close_button_clicked();

    void on_GetSmsCode_clicked();

    void on_MakePayment_clicked();

private:
    Ui::Payment *ui;

    // QWidget interface
protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
};

#endif // PAYMENT_H

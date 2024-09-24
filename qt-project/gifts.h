#ifndef GIFTS_H
#define GIFTS_H

#include <QDialog>
class MainWindow;
class UserAccount;
class PromocodesList;

namespace Ui {
class Gifts;
}

class Gifts : public QDialog
{
    Q_OBJECT

    MainWindow* mainWindow;
    UserAccount* currentAccount;
    PromocodesList* promocodesList;

    QString lineEditBase_styleSheet();
    QString lineEditError_styleSheet();

public:
    explicit Gifts(MainWindow* _mainWindow, UserAccount* _currentAccount,
                   PromocodesList* _promocodesList);
    ~Gifts();

private slots:


    void on_Activate_clicked();

    void on_Close_button_clicked();

private:
    Ui::Gifts *ui;
};

#endif // GIFTS_H

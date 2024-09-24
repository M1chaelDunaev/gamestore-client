#ifndef USERPROFILE_H
#define USERPROFILE_H

#include <QWidget>

class MainWindow;
class UserAccount;
class QLabel;
enum class Games;

namespace Ui {
class UserProfile;
}

class UserProfile : public QWidget
{
    Q_OBJECT

    Ui::UserProfile *ui;

    MainWindow* mainWindow;
    UserAccount* currentAccount;

    void setUserName();
    void setUserAvatar();
    void setUserActivity();
    void setUserStatus();

    void setRegActivity(QLabel* _icon, QLabel* _name, QLabel* _info);
    void setBuyingActivity(QLabel* _icon, QLabel* _name, QLabel* _info, const QString &_iconName, Games _game);

public:
    explicit UserProfile(MainWindow *_mainWindow, UserAccount* _currentAccount);
    ~UserProfile();

    void updateWidget();

private slots:
    void on_EditProfile_pushButton_clicked();
    void on_MyGames_pushButton_clicked();
    void on_Inventory_pushButton_clicked();
    void on_Screenshots_pushButton_clicked();
    void on_Video_pushButton_clicked();
    void on_Reviews_pushButton_clicked();
    void on_Manuals_pushButton_clicked();
    void on_Illustrations_pushButton_clicked();

    // QWidget interface
protected:
    virtual void showEvent(QShowEvent *event) override;
};

#endif // USERPROFILE_H
